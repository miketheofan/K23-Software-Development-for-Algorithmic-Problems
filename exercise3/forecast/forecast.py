import math
import matplotlib.pyplot as plt

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import keras
import pandas as pd
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout
from keras.layers import *
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.model_selection import train_test_split
from keras.callbacks import EarlyStopping

# df=pd.read_csv("../nasdaq2007_17.csv")
# print("Number of rows and columns:", df.shape)
# df.head(5)

dataset = []

with open('../nasdaq2007_17.csv','r') as file:	
	for line in file:
		timestamp = []
		for word in line.split():
			timestamp.append(word)
		dataset.append(timestamp)

# print("Number of rows and columns:",len(dataset),len(dataset[0]))

# import numpy as np
# print(np.matrix(dataset))

df = pd.DataFrame(dataset)
print("Number of rows and columns:", df.shape)

training_set = df.iloc[0, 1:3001].values
test_set = df.iloc[0, 3001:].values

# print("TRAINING SET:",training_set)
# print("TEST SET:",test_set)

# print(training_set)

# Feature Scaling
training_set = np.reshape(training_set,(len(training_set),-1))
# training_set.reshape(-1,1)
sc = MinMaxScaler(feature_range = (0, 1))
training_set_scaled = sc.fit_transform(training_set)

# print(training_set_scaled)

# print("Number of rows and columns:",len(training_set),len(training_set[0]))

#Creating a data structure with 60 time-steps and 1 output
X_train = []
y_train = []
for i in range(60, 3000):
    X_train.append(training_set_scaled[i-60:i, 0])
    y_train.append(training_set_scaled[i, 0])
X_train, y_train = np.array(X_train), np.array(y_train)
X_train = np.reshape(X_train, (X_train.shape[0], X_train.shape[1], 1))

# print(y_train)

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
model.fit(X_train, y_train, epochs = 10, batch_size = 32)

# Getting the predicted stock price of 2017
dataset_train = df.iloc[0, 1:3001]
dataset_test = df.iloc[0, 3001:]
dataset_total = pd.concat((dataset_train, dataset_test), axis = 0)
inputs = dataset_total[len(dataset_total) - len(dataset_test) - 60:].values
inputs = np.reshape(inputs,(len(inputs),-1))

# print(inputs)

# inputs = inputs.reshape(-1,1)

# print(inputs)

inputs = sc.transform(inputs)
X_test = []
for i in range(60, 710):
    X_test.append(inputs[i-60:i, 0])
X_test = np.array(X_test)
X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))
print(X_test.shape)

predicted_stock_price = model.predict(X_test)
predicted_stock_price = sc.inverse_transform(predicted_stock_price)

print("\ndf.loc",df)
print("\ndataset_test.values",dataset_test.values)

# Visualising the results
plt.plot(df.loc[0, 3001:],dataset_test.values, color = "red", label = "‘Real TESLA Stock Price’")
plt.plot(df.loc[0, 3001:],predicted_stock_price, color = "blue", label = "‘Predicted TESLA Stock Price’")
plt.xticks(np.arange(650,60,1))
plt.title("TESLA Stock Price Prediction")
plt.xlabel("Time")
plt.ylabel("TESLA Stock Price")
plt.legend()
plt.show()