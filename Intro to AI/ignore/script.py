
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# We import the function train_test_split from sklearn and use this to split the data
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

# Step 1: Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Step 2: Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Step 3: Check the shape of the data
print("Shape of X:", X.shape)
print("Shape of Y:", Y.shape)

# Step 4: Split the data into training and testing sets
Xtrain, Xtest, ytrain, ytest = train_test_split(X, Y, test_size=0.1)

# Step 5: Check the shape of the training data
print("Shape of Xtrain:", Xtrain.shape)
print("Shape of ytrain:", ytrain.shape)

# Step 6: Create and fit the linear regression model
regr = LinearRegression()

# Create the figure and axes
fig, ax = plt.subplots()
ax.scatter(X[:,0], Y, label='Data')
ax.set_xlabel('x')
ax.set_ylabel('y')

regr.fit(Xtrain, ytrain)

# Print the coefficients and intercept
print("Coefficients:", regr.coef_)
print("Intercept:", regr.intercept_)

# Plot the fitted model
x = np.array([0, 10])
ax.plot(x, regr.coef_[0] * x + regr.intercept_, 'g', label='Fitted model')
plt.show()

# Reshape the test set for prediction
#Xtest = Xtest.reshape(-1, 1)

# Make predictions on the test set
ypred = regr.predict(Xtest)

# Calculate the mean squared error (MSE)
def MSE(y, pred):
    diffs = y - pred
    sse = (diffs ** 2).sum()
    mse = sse / len(diffs)
    print("MSE:", mse)
    return mse

# Calculate MSE using your custom function
MSE(ytest, ypred)

# Calculate MSE using sklearn's mean_squared_error function
from sklearn.metrics import mean_squared_error
print("MSE (sklearn):", mean_squared_error(ytest, ypred))
