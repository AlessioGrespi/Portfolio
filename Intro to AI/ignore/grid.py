import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.linear_model import LinearRegression

data = pd.read_csv("numbers.csv")
data.head()

X = data.iloc[:, :4].values
Y = data.iloc[:, 4].values.reshape(-1,1)
print(X)
print(Y)

print(np.shape(X))
print(np.shape(Y))

Xtrain, Xtest, Ytrain, Ytest = train_test_split(X, Y, test_size=0.2, random_state=0)
Xtrain, Xval, Ytrain, Yval = train_test_split(Xtrain, Ytrain, test_size=0.2, random_state=0)

# Create and fit the linear regression model
regr = LinearRegression()
regr.fit(Xtrain, Ytrain)

# Make predictions on the validation set
pred = regr.predict(Xval)

# Make a dictionary of hyperparameter values to search
search_space = {
    "fit_intercept": [True, False],
    "copy_X": [True, False],
    "n_jobs": [-1, 0, 1],
    "positive": [True, False]
}

# Make a GridSearchCV object
GS = GridSearchCV(estimator=LinearRegression(),
                  param_grid=search_space,
                  scoring=["r2", "neg_mean_squared_error"],
                  refit="r2",
                  cv=5,
                  verbose=4)

GS.fit(Xtest, Ytest)
