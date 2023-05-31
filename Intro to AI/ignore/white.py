
""" 
import matplotlib.pyplot as plt


# Step 1: Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Step 2: Explore the dataset
print(data.head())
print(data.shape)
print(data.dtypes)
print(data.describe()) """


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# We import the function train_test_split from sklearn and use this to split the data
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from matplotlib import axes


#%matplotlib inline

"""
# We set up a random number generator (rng), seeded with a number (in this case 10). 
# Using a seed means we can generate the same sequence of pseudorandom numbers, and so we can check results easily.
rng = np.random.default_rng(10) 

# a and b are coefficients for the line
a = 2
b = -1

# Use np.linspace to generate datapoints from 0 to 10 (inclusive) spaced at 0.1
X = np.linspace(0, 10, 101) 

# Create data Y using the equation for a line
Y = a*X + b

# Adds Gaussian noise with mean 0 and standard deviation 3 to the data
Y = Y + 3*rng.standard_normal(len(Y)) 

fig, ax = plt.subplots() # This generates us a named figure and axes
ax.scatter(X, Y, label = 'Data') # We generate a scatterplot of the data on the axes.
plt.xlabel('x')
plt.ylabel('y')
"""


# Step 1: Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Step 2: Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values





# Write your answer here
Xtrain, Xtest, ytrain, ytest = train_test_split(X, Y, test_size=0.1)


regr = LinearRegression()

# This reshapes the data to have 1 column and however many rows make sense for the data
Xtrain = Xtrain.reshape(-1, 1)

# Write your answer here
regr.fit(Xtrain, ytrain)

print(regr.coef_)

print(regr.intercept_)

# Write your answer here 
x = np.array([0, 10])
axes.plot(x, regr.coef_[0]*x + regr.intercept_, 'g', label='Fitted model')
plt.show()

Xtest = Xtest.reshape(-1, 1)
ypred = regr.predict(Xtest)

print(Xtest)
print(ypred)

#MSE Calc

def MSE(y, pred):
    diffs = y - pred
    sse = (diffs**2).sum()
    mse = sse/len(diffs)
    print(mse)
    return mse


print(MSE(ytest, ypred) == mean_squared_error(ytest, ypred))