# Assignment 3 - Software Development for Algorithmic Problems

# Time Series Forecasting and Analysis

This project involves several stages of time series analysis, including forecasting, anomaly detection, compression, and clustering. Below are details for each part of the project.

## Part 1 - Forecasting

### Implementation

**File:** `forecast/forecast.py`

We implemented a Recursive Neural Network (RNN) with stacked Long Short-Term Memory (LSTM) layers for forecasting time series data. The model receives a window of historical values and forecasts the next value.

- **Training Data:** The model was trained using the dataset `nasdaq2007_17.csv`.
- **Models:**
  - One final model trained on all time series from the dataset.
  - 20 additional models trained on individual time series.

### Usage

**Execution command**

```
  make out1
```

**Train command**

```
  make out1train
```

## Part 2 - Anomaly Detection

### Implementation

**File:** `detect/detect.py`

An auto-encoder using a Recursive Neural Network with stacked LSTM layers was implemented for anomaly detection. The network includes encoding and decoding layers. Anomalies are detected using the Mean Absolute Error (MAE) with a predefined threshold.

- **Training Data:** The model was trained using `nasdaq2007_17.csv`.
- **Output:** Anomalies are visualized using graphical plots.

## Usage

**Execution command**

```
  make out2
```

**Train command**

```
  make out2train
```

## Part 3 - Time Series Compression

### Implementation

**File:** `reduce/reduce.py`

A Convolutional Autoencoder Neural Network was developed to compress time series data. The network includes encoding and decoding layers with a bottleneck. Each time series is split into non-overlapping sets of 10 values, which are compressed into sets of 3 values.

- **Input Files:** Two files containing time series data.
- **Output Files:** Two files containing the compressed time series data.

## Usage

**Execution command**

```
  make out3
```

**Train command**

```
  make out3train
```
