from keras.layers import Input, Dense, Conv1D, MaxPooling1D, UpSampling1D, BatchNormalization, LSTM, RepeatVector
from keras.models import Model
from keras.models import model_from_json
from keras import regularizers
from plot_keras_history import plot_history
from keras.models import load_model
import matplotlib.pyplot as plt
import datetime
import time
import sys
import requests as req
import json
import pandas as pd
import pickle
import string
import os
import random
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from tqdm import tqdm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

# def plot_examples(stock_input, stock_decoded):
    
#     n = 10  
#     plt.figure(figsize=(20, 4))
#     for i, idx in enumerate(list(np.arange(0, test_size, 200))):
#         # display original
#         ax = plt.subplot(2, n, i + 1)
#         if i == 0:
#             ax.set_ylabel("Input", fontweight=600)
#         else:
#             ax.get_yaxis().set_visible(False)
#         plt.plot(stock_input[idx])
#         ax.get_xaxis().set_visible(False) 

#         # display reconstruction
#         ax = plt.subplot(2, n, i + 1 + n)
#         if i == 0:
#             ax.set_ylabel("Output", fontweight=600)
#         else:
#             ax.get_yaxis().set_visible(False)
#         plt.plot(stock_decoded[idx])
#         ax.get_xaxis().set_visible(False)
        
        
# def plot_history(history):
#     plt.figure(figsize=(15, 5))
#     ax = plt.subplot(1, 2, 1)
#     plt.plot(history.history["loss"])
#     plt.title("Train loss")
#     ax = plt.subplot(1, 2, 2)
#     plt.plot(history.history["val_loss"])
#     plt.title("Test loss")

# the following function is used to write data to a file given.
def write_to_file(array,file,scaler):

    letters = string.ascii_lowercase

    inverted_array = array.reshape(len(array),len(array[0]))    
    inverted_array = scaler.inverse_transform(inverted_array)

    with open(file, 'a') as f:
        # first value of each timeseries is its 'id' which will be
        # a random string.
        f.write(random.choice(letters)+'\t')
        for i in range(len(inverted_array)):
            for j in range(len(inverted_array[i])):
                f.write(str(inverted_array[i][j])+'\t')

        f.write('\n')        


if __name__ == "__main__":
    
    for i in range(len(sys.argv)):
        if sys.argv[i] == "-d":
            d = sys.argv[i+1]
        elif sys.argv[i] == "-q":
            querySet = sys.argv[i+1] 
        elif sys.argv[i] == "-od":
            od = sys.argv[i+1]     
        elif sys.argv[i] == "-oq":
            oq = sys.argv[i+1]     

    open(od, 'w').close()
    open(oq, 'w').close()
        

    dataset = []

    with open(d,'r') as file:   
        for line in file:
            timestamp = []
            count =0
            for word in line.split():
                if(count == 0):
                    count =1
                    continue
                timestamp.append(float(word))
            dataset.append(timestamp)

    for i in range(len(dataset)):
        
        names = ['price']
        values = [_ for _ in range (0,len(dataset[i]))]
        df = pd.DataFrame(dataset[i], index=values, columns=names)        

        train_size = int(len(df)*0.80)
        test_size = len(df) - train_size

        window_length = 10
        encoding_dim = 3
        epochs = 100

        scaler = MinMaxScaler()
        x_train_nonscaled = np.array([df['price'].values[i-window_length:i].reshape(-1, 1) for i in tqdm(range(window_length+1,len(df['price'])))])
        x_train = np.array([scaler.fit_transform(df['price'].values[i-window_length:i].reshape(-1, 1)) for i in tqdm(range(window_length+1,len(df['price'])))])

        x_test = x_train[-test_size:]
        x_train = x_train[:-test_size]

        x_train = x_train.astype('float32')
        x_test = x_test.astype('float32')

        input_window = Input(shape=(window_length,1))
        x = Conv1D(16, 3, activation="relu", padding="same")(input_window) # 10 dims
        #x = BatchNormalization()(x)
        x = MaxPooling1D(2, padding="same")(x) # 5 dims
        x = Conv1D(1, 3, activation="relu", padding="same")(x) # 5 dims
        #x = BatchNormalization()(x)

        encoded = MaxPooling1D(2, padding="same")(x) # 3 dims
        encoder = Model(input_window, encoded)

        encoded_stocks = encoder.predict(x_test)

        write_to_file(encoded_stocks,od,scaler)
        write_to_file(encoded_stocks,oq,scaler)

        # # 3 dimensions in the encoded layer
        # x = Conv1D(1, 3, activation="relu", padding="same")(encoded) # 3 dims
        # #x = BatchNormalization()(x)
        # x = UpSampling1D(2)(x) # 6 dims
        # x = Conv1D(16, 2, activation='relu')(x) # 5 dims
        # #x = BatchNormalization()(x)
        # x = UpSampling1D(2)(x) # 10 dims

        # decoded = Conv1D(1, 3, activation='sigmoid', padding='same')(x) # 10 dims
        # autoencoder = Model(input_window, decoded)
        # autoencoder.summary()

        # autoencoder.compile(optimizer='adam', loss='binary_crossentropy')
        # history = autoencoder.fit(x_train, x_train,
        #                 epochs=epochs,
        #                 batch_size=1024,
        #                 shuffle=True,
        #                 validation_data=(x_test, x_test))

        # decoded_stocks = autoencoder.predict(x_test)

        # # plot_history(history)
        # # plt.show()
        # # plot_examples(x_test, decoded_stocks)
        # # plt.show()