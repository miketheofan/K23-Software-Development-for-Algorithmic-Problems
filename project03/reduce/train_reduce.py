from keras.layers import Input, Dense, Conv1D, MaxPooling1D, UpSampling1D, BatchNormalization, LSTM, RepeatVector
from keras.models import Model
from keras.models import model_from_json
from keras import regularizers
import datetime
import time
import requests as req
import json
import pandas as pd
import pickle
import os
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

window_length = 10
encoding_dim = 3
epochs = 100
test_samples = 2000

def plot_examples(stock_input, stock_decoded):
    n = 10  
    plt.figure(figsize=(20, 4))
    for i, idx in enumerate(list(np.arange(0, test_samples, 200))):
        # display original
        ax = plt.subplot(2, n, i + 1)
        if i == 0:
            ax.set_ylabel("Input", fontweight=600)
        else:
            ax.get_yaxis().set_visible(False)
        plt.plot(stock_input[idx])
        ax.get_xaxis().set_visible(False)
        

        # display reconstruction
        ax = plt.subplot(2, n, i + 1 + n)
        if i == 0:
            ax.set_ylabel("Output", fontweight=600)
        else:
            ax.get_yaxis().set_visible(False)
        plt.plot(stock_decoded[idx])
        ax.get_xaxis().set_visible(False)
        
        
def plot_history(history):
    plt.figure(figsize=(15, 5))
    ax = plt.subplot(1, 2, 1)
    plt.plot(history.history["loss"])
    plt.title("Train loss")
    ax = plt.subplot(1, 2, 2)
    plt.plot(history.history["val_loss"])
    plt.title("Test loss")

if __name__ == "__main__":

    for i in range(len(sys.argv)):
        if sys.argv[i] == "-d":
            d = sys.argv[i+1]

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

    dt = []

    for i in range(0,len(dataset)):
        dt.append(dataset[])

    dt = np.array(training_set)
    dt = training_set.flatten()

    names = ['close']
    values = [_ for _ in range (0,len(dataset[i]))]
    df = pd.DataFrame(dt, index=values, columns=names)        

    print(df.size)

    train_size = int(len(df)*0.80)
    test_size = len(df) - train_size

    window_length = 10
    encoding_dim = 3
    epochs = 100

    scaler = MinMaxScaler()
    x_train_nonscaled = np.array([df['close'].values[i-window_length:i].reshape(-1, 1) for i in tqdm(range(window_length+1,len(df['close'])))])
    x_train = np.array([scaler.fit_transform(df['close'].values[i-window_length:i].reshape(-1, 1)) for i in tqdm(range(window_length+1,len(df['close'])))])

    # we append the last 20% of every value of every time-series to a 1D array
    # that will be used for testing.
    x_test = x_train[-test_size:]
    # we append 80% of every value of every time-series to a 1D array
    # that will be used for training.
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
    
    #finally we save the model, in order for the main program to be able to
    # use it.
    encoder.save("model.h5")