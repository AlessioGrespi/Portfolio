import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

print(X)
print(Y)

# Split the data into training, validation, and test sets
Xtrain, Xtest, Ytrain, Ytest = train_test_split(X, Y, test_size=0.2, random_state=0)
Xtrain, Xval, Ytrain, Yval = train_test_split(Xtrain, Ytrain, test_size=0.2, random_state=0)

# Create and fit the linear regression model
LinearRegression.set_params({'copy_X': True, 'fit_intercept': True, 'n_jobs': -1, 'positive': False})
regr = LinearRegression()
regr.fit(Xtrain, Ytrain)

# Make predictions on the validation set
pred = regr.predict(Xval)

# Calculate the mean squared error and R^2 score
mse = mean_squared_error(Yval, pred)
r2 = r2_score(Yval, pred)

print(f"Mean Squared Error: {mse:.4f}")
print(f"R^2 Score: {r2:.4f}")

# Plot the predicted values against the actual values
plt.scatter(pred, Yval, color='black')
plt.plot(Yval, Yval, color='blue', linewidth=2, label='y=x')
plt.xlabel('Predicted Values')
plt.ylabel('Actual Values')
plt.title('Linear Regression')
plt.legend()
plt.show()
