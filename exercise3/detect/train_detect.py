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

# The following function transforms a 1D array to a 2D nd_array by inserting  a
# date column with values 1,....,len(array).
def add_dates_to_array(tempList):

	df_dates = []
	dateCount = 1
	for j in range (0,len(tempList)):
		df_dates.append(dateCount)
		dateCount = dateCount + 1

	array = []
	array.append(df_dates)
	array.append(tempList)

	newArray = []
	for i in range (0,len(tempList)-1):
		newArray.append([array[0][i],array[1][i]])

	names = ['date','close']
	values = [_ for _ in range (0,len(newArray))]
	df = pd.DataFrame(newArray, index=values, columns=names)

	return df

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
	for i in range(trainLength,len(dataset)):
		test_set.append(dataset[i])

	test_set = np.array(test_set)
	test_set = test_set.flatten()	

	# we add the extra column of dates to each set.
	training_set = add_dates_to_array(training_set)
	test_set = add_dates_to_array(test_set)

	scaler = StandardScaler()
	scaler = scaler.fit(training_set[['close']])

	training_set['close'] = scaler.transform(training_set[['close']])
	test_set['close'] = scaler.transform(test_set[['close']])

	TIME_STEPS = 30

	X_train, y_train = create_dataset(
	  training_set[['close']],
	  training_set.close,		
	  TIME_STEPS
	)

	X_test, y_test = create_dataset(
	  test_set[['close']],
	  test_set.close,		
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
	    epochs=10,
	    batch_size=32,
	    validation_split=0.1,
	    shuffle=False
	)

	#finally we save the model, in order for the main program to be able to
	# use it.
	model.save("model.h5")