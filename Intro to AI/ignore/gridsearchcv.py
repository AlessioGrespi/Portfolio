import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import mean_squared_error

# Load the dataset
data = pd.read_csv('numbers.csv')

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Create the Linear Regression model
model = LinearRegression()

# Define the parameter grid
param_grid = {
    "fit_intercept" : [True, False],
    "copy_X" : [True, False],
    "n_jobs" : [-1, 0, 1],
    "positive" : [True, False]
}

# Create the GridSearchCV object
grid_search = GridSearchCV(model, param_grid, cv=5, scoring='neg_mean_squared_error')

# Fit the data to perform the grid search
grid_search.fit(X, Y)

# Print the best parameters and score
print("Best Parameters: ", grid_search.best_params_)
print("Best Score: ", -grid_search.best_score_)

# Get the best model
best_model = grid_search.best_estimator_

# Make predictions using the best model
y_pred = best_model.predict(X)

# Calculate the mean squared error
mse = mean_squared_error(Y, y_pred)
print("Mean Squared Error: ", mse)
import pandas as pd
from sklearn.linear_model import Ridge
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import mean_squared_error

# Load the dataset
data = pd.read_csv('numbers.csv')

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Create the Ridge model
model = Ridge()

# Define the parameter grid
param_grid = {
    'fit_intercept': [True, False],
    'normalize': [True, False]
}

# Create the GridSearchCV object
grid_search = GridSearchCV(model, param_grid, cv=5, scoring='neg_mean_squared_error')

# Fit the data to perform the grid search
grid_search.fit(X, Y)

# Print the best parameters and score
print("Best Parameters: ", grid_search.best_params_)
print("Best Score: ", -grid_search.best_score_)

# Get the best model
best_model = grid_search.best_estimator_

# Make predictions using the best model
y_pred = best_model.predict(X)

# Calculate the mean squared error
mse = mean_squared_error(Y, y_pred)
print("Mean Squared Error: ", mse)

