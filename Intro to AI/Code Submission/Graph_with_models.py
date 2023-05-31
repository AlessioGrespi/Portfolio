import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.dummy import DummyRegressor
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.metrics import mean_squared_error, r2_score

# Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Split the data into training and testing sets
Xtrain, Xtest, ytrain, ytest = train_test_split(X, Y, test_size=0.2, random_state=80)

# Create regression models

# Linear Regression
lr = LinearRegression()

# Setting Linear parameters
lr.set_params(**{ #comment out for default parameters
    'copy_X': True, 
    'fit_intercept': True, 
    'n_jobs': -1, 
    'positive': False,
})

# Gradient Boosting Regressor
gbr = GradientBoostingRegressor()
params = gbr.get_params()
print("gbr params:",params)

# Setting GBR parameters
gbr.set_params(**{ #comment out for default parameters
    'learning_rate': 0.05, 
    'loss': 'squared_error', 
    'max_depth': 4, 
    'min_samples_leaf': 1, 
    'min_samples_split': 4, 
    'n_estimators': 900
  })

# Fit regression models
regr = LinearRegression()
gbrRegr = GradientBoostingRegressor()
regr.fit(Xtrain, ytrain)
gbrtrain = gbrRegr.fit(Xtrain, ytrain)

# Make predictions on the test data using regression models
pred_test = regr.predict(Xtest)
pred_gbr_test = gbrRegr.predict(Xtest)

# Calculate the mean squared error (MSE) and R^2 on the test data
r2_gbr_test = r2_score(ytest, pred_gbr_test)
#r2_gbr_training = r2_score(ytrain, pred_gbr_test)
print("Test r2 (GBR): ", r2_gbr_test)
mse_gbr_test = mean_squared_error(ytest, pred_gbr_test)
print("Test MSE (GBR):", mse_gbr_test)

r2_test = r2_score(ytest, pred_test)
print("Test r2 (LinRegression): ", r2_test)
mse_test = mean_squared_error(ytest, pred_test)
print("Test MSE (LinRegression):", mse_test)

# Create and fit the dummy regressor model
dummy_regr = DummyRegressor(strategy='mean')
dummy_regr.fit(Xtrain, ytrain)

# Make predictions on the test data using the dummy regressor
dummy_pred_test = dummy_regr.predict(Xtest)

# Calculate the mean squared error (MSE) and R^2 on the test data using the dummy regressor
dummy_r2_test = r2_score(ytest, dummy_pred_test)
dummy_mse_test = mean_squared_error(ytest, dummy_pred_test)
print("Test MSE (Dummy):", dummy_mse_test)
print("Test r2 (Dummy):", dummy_r2_test)

# Compare the performance of your regression models and the dummy regressor
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


# Create the scatter plot
plt.scatter(ytest, pred_test, label='Tuned Linear Regression', alpha=0.5, s=10)
plt.scatter(ytest, pred_gbr_test, label='Tuned Gradient Boosted Regressor', alpha=0.5, s=10)
plt.scatter(ytest, dummy_pred_test, label='Dummy Regressor', alpha=0.5, s=10)
plt.plot([ytest.min(), ytest.max()], [ytest.min(), ytest.max()], 'k--', label='y=x')

plt.xlabel('True Values')
plt.ylabel('Predictions')
plt.title('Regression Model Comparison')
plt.legend()

# Show the graph
plt.show()