import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.preprocessing import PolynomialFeatures

# Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Split the data into training, validation, and test sets
Xtrain, Xtest, Ytrain, Ytest = train_test_split(X, Y, test_size=0.2, random_state=0)
Xtrain, Xval, Ytrain, Yval = train_test_split(Xtrain, Ytrain, test_size=0.2, random_state=0)

mse_tr = []
mse_val = []
max_deg = 10
for i in range(max_deg):
    poly = PolynomialFeatures(degree=i + 1)
    Xtrain_new = poly.fit_transform(Xtrain)
    Xval_new = poly.transform(Xval)
    regr = LinearRegression()
    regr.fit(Xtrain_new, Ytrain)
    pred_tr = regr.predict(Xtrain_new)
    pred_v = regr.predict(Xval_new)
    mse_tr.append(mean_squared_error(pred_tr, Ytrain))
    mse_val.append(mean_squared_error(pred_v, Yval))

plt.plot(range(1, max_deg + 1), mse_tr, label='Training')
plt.plot(range(1, max_deg + 1), mse_val, label='Validation')
plt.legend()
plt.xlabel('Degree')
plt.ylabel('MSE')

Xtest_new = poly.transform(Xtest)
pred_test = regr.predict(Xtest_new)
mse_test = mean_squared_error(pred_test, Ytest)

print(f"Test Mean Squared Error: {mse_test:.4f}")
plt.show()
