import numpy as np
from sklearn.dummy import DummyRegressor
from sklearn.metrics import mean_squared_error
import pandas as pd

# Load data from CSV
data = pd.read_csv('numbers.csv')

# Extract input features (X) and target variable (y)
X = data[['AT', 'V', 'AP', 'RH']].values
y = data['PE'].values

# Create and fit the Dummy Regressor
dummy_regr = DummyRegressor(strategy="mean")
dummy_regr.fit(X, y)

# Generate predictions
predictions = dummy_regr.predict(X)

# Calculate MSE
mse = mean_squared_error(y, predictions)

# Output predictions, score, and MSE
print("Predictions:", predictions)
print("Score:", dummy_regr.score(X, y))
print("MSE:", mse)
