# Import libraries
import pandas as pd
from sklearn.model_selection import train_test_split

# Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values


# Split the dataset into training and test 
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=80)
from sklearn.ensemble import GradientBoostingRegressor
ergoRegression = GradientBoostingRegressor()
ergoRegression.fit(X_train, y_train) 

y_prediction = ergoRegression.predict(X_test)

# Make a dictionary of hyperparameter values to search
search_space = {
    "loss": ["squared_error"],
    "learning_rate": [0.05],
    "n_estimators": [900],
    "max_depth": [4,5,6],
    "min_samples_split": [4,5,6],
    "min_samples_leaf": [1]
}

#Tested parameters
"""search_space = { 
    "loss": ["squared_error"],
    "learning_rate": [0.05,0.075,0.1],
    "n_estimators": [800,900,1000,1100],
    "max_depth": [2,3,4],
    "min_samples_split": [2,3,4],
    "min_samples_leaf": [1,2]
}"""

# Full list of parameters available to GBR Model
"""{'alpha': 0.9, 
 'ccp_alpha': 0.0, 
 'criterion': 'friedman_mse', 
 'init': None, 
 'learning_rate': 0.1, 
 'loss': 'squared_error', 
 'max_depth': 3, 
 'max_features': None, 
 'max_leaf_nodes': None, 
 'min_impurity_decrease': 0.0, 
 'min_samples_leaf': 1, 
 'min_samples_split': 2, 
 'min_weight_fraction_leaf': 0.0, 
 'n_estimators': 100, 
 'n_iter_no_change': None, 
 'random_state': None, 
 'subsample': 1.0, 
 'tol': 0.0001, 
 'validation_fraction': 0.1, 
 'verbose': 0, 
 'warm_start': False}"""

# Setup and Run GridSearchCV
from sklearn.model_selection import GridSearchCV

# Make a GridSearchCV object
GS = GridSearchCV(estimator =  GradientBoostingRegressor(),
                  param_grid = search_space,
                  scoring = ["r2", "neg_mean_squared_error"], #sklearn.metrics.SCORERS.keys()
                  refit = "r2",
                  cv = 5,
                  verbose = 4)

# Run GridsearchCV
GS.fit(X_test, y_test)

print("best model: ", GS.best_estimator_) # to get the complete details of the best model
print("best parameter values: ", GS.best_params_) # to get only the best hyperparameter values that we searched for
print("best r^2 value: ", GS.best_score_) # score according to the metric we passed in refit

df = pd.DataFrame(GS.cv_results_)
df = df.sort_values("rank_test_r2")
df.to_csv("cv_gbr_results.csv", index = False)