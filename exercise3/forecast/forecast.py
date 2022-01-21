import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import sys
import math
import matplotlib.pyplot as plt
import random
import keras
import pandas as pd
import numpy as np
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

if __name__ == "__main__":

	for i in range(len(sys.argv)):
		if sys.argv[i] == "-d":
			d = sys.argv[i+1]
		elif sys.argv[i] == "-n":
			n = int(sys.argv[i+1])	

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

	for i in range(0,n):

		randomTimeSeries = random.randint(0,len(df))

		training_set = df.iloc[randomTimeSeries, :3000].values
		test_set = df.iloc[randomTimeSeries, 3000:].values

		# Feature Scaling
		training_set = np.reshape(training_set,(len(training_set),-1))
		sc = MinMaxScaler(feature_range = (0, 1))
		training_set_scaled = sc.fit_transform(training_set)

		#Creating a data structure with 60 time-steps and 1 output
		X_train = []
		y_train = []
		for i in range(60, 3000):
		    X_train.append(training_set_scaled[i-60:i, 0])
		    y_train.append(training_set_scaled[i, 0])
		X_train, y_train = np.array(X_train), np.array(y_train)
		X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))

		model = Sequential()
		#Adding the first LSTM layer and some Dropout regularisation
		model.add(LSTM(units = 50, return_sequences = True, input_shape = (X_train.shape[1], 1)))
		model.add(Dropout(0.2))
		# Adding a second LSTM layer and some Dropout regularisation
		model.add(LSTM(units = 50, return_sequences = True))
		model.add(Dropout(0.2))
		# Adding a third LSTM layer and some Dropout regularisation
		model.add(LSTM(units = 50, return_sequences = True))
		model.add(Dropout(0.2))
		# Adding a fourth LSTM layer and some Dropout regularisation
		model.add(LSTM(units = 50))
		model.add(Dropout(0.2))
		# Adding the output layer
		model.add(Dense(units = 1))

		# Compiling the RNN
		model.compile(optimizer = 'adam', loss = 'mean_squared_error')

		# Fitting the RNN to the Training set
		model.fit(X_train, y_train, epochs = 30, batch_size = 512)

		model_big = load_model("model.h5")

		dataset_train = df.iloc[randomTimeSeries, 1:3000]
		dataset_test = df.iloc[randomTimeSeries, 3000:]
		dataset_total = pd.concat((dataset_train, dataset_test), axis = 0)
		inputs = dataset_total[len(dataset_total) - len(dataset_test) - 60:].values
		inputs = np.reshape(inputs,(len(inputs),-1))

		inputs = sc.transform(inputs)
		X_test = []
		for i in range(60, 710):
		    X_test.append(inputs[i-60:i, 0])
		X_test = np.array(X_test)
		X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))
		print(X_test.shape)

		predicted_stock_price = model.predict(X_test)
		predicted_stock_price = sc.inverse_transform(predicted_stock_price)

		# Visualising the results
		plt.plot(dataset_test.values, color = "red", label = "Real Price")
		plt.plot(predicted_stock_price, color = "blue", label = "Predicted Price")
		plt.xticks(np.arange(650,60,1))
		plt.title("Price Prediction")
		plt.xlabel("Time")
		plt.ylabel("Price")
		plt.legend()
		plt.show()

		predicted_stock_price = model_big.predict(X_test)
		predicted_stock_price = sc.inverse_transform(predicted_stock_price)

		# Visualising the results
		plt.plot(dataset_test.values, color = "red", label = "Real Price")
		plt.plot(predicted_stock_price, color = "blue", label = "Predicted Price")
		plt.xticks(np.arange(650,60,1))
		plt.title("Price Prediction")
		plt.xlabel("Time")
		plt.ylabel("Price")
		plt.legend()
		plt.show()