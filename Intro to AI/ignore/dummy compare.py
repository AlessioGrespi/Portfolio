import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.dummy import DummyRegressor
from sklearn.metrics import mean_squared_error, r2_score

# Step 1: Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Step 2: Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Step 3: Split the data into training and testing sets
Xtrain, Xtest, ytrain, ytest = train_test_split(X, Y, test_size=0.2, random_state=42)

# Step 4: Create and fit your regression model

from sklearn.ensemble import GradientBoostingRegressor

regr = LinearRegression()
gbrRegr = GradientBoostingRegressor()
regr.fit(Xtrain, ytrain)
gbrRegr.fit(Xtrain, ytrain)

# Step 5: Make predictions on the test data using your regression model
pred_test = regr.predict(Xtest)
pred_gbr_test=gbrRegr.predict(Xtest)

# Step 6: Calculate the mean squared error (MSE) on the test data
r2_gbr_test = r2_score(ytest, pred_gbr_test)
print("Test r2 (GBR): ", r2_gbr_test)
mse_gbr_test = mean_squared_error(ytest, pred_gbr_test)
print("Test MSE (GBR):", mse_gbr_test)

r2_test = r2_score(ytest, pred_test)
print("Test r2 (Regression): ", r2_test)
mse_test = mean_squared_error(ytest, pred_test)
print("Test MSE (Regression):", mse_test)

# Step 7: Create and fit the dummy regressor model
dummy_regr = DummyRegressor(strategy='mean')
dummy_regr.fit(Xtrain, ytrain)

# Step 8: Make predictions on the test data using the dummy regressor
dummy_pred_test = dummy_regr.predict(Xtest)

# Step 9: Calculate the mean squared error (MSE) on the test data using the dummy regressor
dummy_r2_test = r2_score(ytest, dummy_pred_test)
dummy_mse_test = mean_squared_error(ytest, dummy_pred_test)
print("Test MSE (Dummy):", dummy_mse_test)
print("Test r2 (Dummy):", dummy_r2_test)

# Step 10: Compare the performance of your regression model and the dummy regressor
improvement_mse = (dummy_mse_test - mse_test) / dummy_mse_test
improvement_r2 = (dummy_r2_test - r2_test) / dummy_r2_test

print("MSE LinReg Improvement over Dummy: {:.2%}".format(improvement_mse))
print("r2 LinReg Improvement over Dummy: {:.2%}".format(improvement_r2))

improvement_gbr_mse = (dummy_mse_test - mse_gbr_test) / dummy_mse_test
improvement_gbr_r2 = (dummy_r2_test - r2_gbr_test) / dummy_r2_test

print("MSE GBR Improvement over Dummy: {:.2%}".format(improvement_gbr_mse))
print("r2 GBR Improvement over Dummy: {:.2%}".format(improvement_gbr_r2))

improvement_gbr_linreg_mse = (mse_test - mse_gbr_test) / mse_test
improvement_gbr_linreg_r2 = (r2_test - r2_gbr_test) / r2_test

print("MSE GBR Improvement over LinReg: {:.2%}".format(improvement_gbr_linreg_mse))
print("r2 GBR Improvement over LinReg: {:.2%}".format(improvement_gbr_linreg_r2))
