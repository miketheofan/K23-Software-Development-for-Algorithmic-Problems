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

	trainLength = int(len(dataset)*.80)
	testLength = len(dataset) - trainLength

	training_set = []
	test_set = []

	# we append 80% of every value of every time-series to a 1D array
	# that will be used for training.
	for i in range(0,trainLength-1):
		training_set.append(dataset[i])

	training_set = np.array(training_set)
	training_set = training_set.flatten()	

	# we append the last 20% of every value of every time-series to a 1D array
	# that will be used for testing.
	for i in range(trainLength,):
		test_set.append(dataset[i])

	test_set = np.array(test_set)
	test_set = test_set.flatten()	

	# Feature Scaling
	training_set = np.reshape(training_set,(len(training_set),-1))
	sc = MinMaxScaler(feature_range = (0, 1))
	training_set_scaled = sc.fit_transform(training_set)

	#Creating a data structure with 60 time-steps and 1 output
	X_train = []
	y_train = []
	for i in range(60, len(training_set)):
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
	model.fit(X_train, y_train, epochs = 30, batch_size = 5000)

	#finally we save the model, in order for the main program to be able to
	# use it.
	model.save("model.h5")
	quit()