import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import sys
import math
import matplotlib.pyplot as plt
import random
import keras
import tensorflow as tf
import pandas as pd
import numpy as np
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout
from keras.layers import *
from keras.models import load_model
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.model_selection import train_test_split
from keras.callbacks import EarlyStopping

def create_dataset(X, y, time_steps=1):
    
    X_train, y_train = [], []
    
    for i in range(len(X) - time_steps):
        v = X.iloc[i:(i + time_steps)].values
        X_train.append(v)
        y_train.append(y.iloc[i + time_steps])

    return np.array(X_train), np.array(y_train)

if __name__ == "__main__":

	for i in range(len(sys.argv)):
		if sys.argv[i] == "-d":
			d = sys.argv[i+1]
		elif sys.argv[i] == "-n":
			n = int(sys.argv[i+1])	
		elif sys.argv[i] == "-mae":
			mae = float(sys.argv[i+1])	

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

	df = pd.DataFrame(dataset)

	training_set = df.iloc[2, :3000].values
	test_set = df.iloc[2, 3000:].values

	print(training_set.shape,test_set.shape)

	training_set = np.reshape(training_set,(len(training_set),-1))
	test_set = np.reshape(test_set,(len(test_set),-1))

	scaler = StandardScaler()
	scaler = scaler.fit(training_set)

	training_set = scaler.transform(training_set)
	test_set = scaler.transform(test_set)

	TIME_STEPS = 60

	X_train, y_train = create_dataset(
	  pd.DataFrame(training_set),
	  pd.DataFrame(training_set),
	  TIME_STEPS
	)

	X_test, y_test = create_dataset(
	  pd.DataFrame(test_set),
	  pd.DataFrame(test_set),
	  TIME_STEPS
	)

	print(X_train.shape)

	model = keras.Sequential()
	model.add(keras.layers.LSTM(
	    units=64,
	    input_shape=(X_train.shape[1], X_train.shape[2])
	))
	model.add(keras.layers.Dropout(rate=0.2))
	model.add(keras.layers.RepeatVector(n=X_train.shape[1]))
	model.add(keras.layers.LSTM(units=64, return_sequences=True))
	model.add(keras.layers.Dropout(rate=0.2))
	model.add(
	  keras.layers.TimeDistributed(
	    keras.layers.Dense(units=X_train.shape[2])
	  )
	)
	model.compile(loss='mae', optimizer='adam')

	history = model.fit(
	    X_train, y_train,
	    epochs=5,
	    batch_size=500,
	    validation_split=0.1,
	    shuffle=False
	)

	X_train_pred = model.predict(X_train)
	train_mae_loss = np.mean(np.abs(X_train_pred,X_train),axis = 1)
	
	# sns.displot(train_mae_loss,bins=50,kde=True)
	# plt.tight_layout()
	# plt.show()

	TRESHOLD = 1.70

	X_test_pred = model.predict(X_test)

	test_mae_loss = np.mean(np.abs(X_test_pred - X_test), axis=1)
	
	test_score_df = pd.DataFrame(test_set)
	test_score_df['loss'] = test_mae_loss
	test_score_df['threshold'] = THRESHOLD
	test_score_df['anomaly'] = test_score_df.loss > test_score_df.threshold
	test_score_df['close'] = test[TIME_STEPS:].close

	anomalies = test_score_df[test_score_df.anomaly == True]

	plt.plot(test_set,scaler.inverse_transform[TIME_STEPS:].close,label='close price');
	sns.scatterplot(anomalies.index,scaler.inverse_transform(anomalies.close),color=sns.color_palette()[3],s=52,label='anomaly')

	plt.xticks(rotation=25)
	plt.legend()
	plt.show()

	# X_train_pred = X_train_pred.reshape(-1,)

	# print(X_train_pred)

	# plt.plot(history.history['loss'], color = "red", label = "‘Real TESLA Stock Price’")
	# plt.plot(history.history['val_loss'], color = "blue", label = "‘Real TESLA Stock Price’")
	# plt.legend()
	# plt.show()
	# train_mae_loss = np.mean(np.abs(X_train_pred - X_train), axis=1)

	# test_score_df = pd.DataFrame(index=test[TIME_STEPS:].index)
	# test_score_df['loss'] = test_mae_loss
	# test_score_df['threshold'] = THRESHOLD
	# test_score_df['anomaly'] = test_score_df.loss > test_score_df.threshold
	# test_score_df['close'] = test[TIME_STEPS:].close