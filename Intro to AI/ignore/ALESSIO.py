import sklearn
import pandas as pd
from sklearn.model_selection import train_test_split

dataset = pd.read_csv('numbers.csv')

#print(dataset)


# split the data set for training/testing
def LinearRegressionModel(dataset):
    X = dataset[['AT', 'V', 'AP', 'RH']]
    y = dataset['PE']
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=0)  # test size = 20% alalocation random state is the rest otherwise known as the pareto priniciple but i dont fucking know

    #Xtrain, Xtest, Ytrain, Ytest = train_test_split(X, Y, test_size=0.2, random_state=0)
    #Xtrain, Xval, Ytrain, Yval = train_test_split(Xtrain, Ytrain, test_size=0.2, random_state=0)



    # we must know instantiate linear regression and train our fucking demonbaby
    from sklearn.linear_model import LinearRegression
    model = LinearRegression()
    model.fit(X_train, y_train)
    # interpret our demonbaby
    from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

    y_prediction = model.predict(X_test)
    mse = mean_squared_error(y_test, y_prediction)
    mae = mean_absolute_error(y_test, y_prediction)
    r2 = r2_score(y_test, y_prediction)
    print("LINEAR REGRESSION: ")

    print("mse = ", mse)
    print("mae = ", mae)
    print("Pirate Noise Squared = ", r2)

    coefficients = model.coef_
    intercept = model.intercept_

    print("Coefficents: ",coefficients)
    print("Intercept:",intercept)
    print("---------------------------------")
def GradiantBoostingRegressionModel(dataset):
#split the dataset, axis= 1 in pandas refers to the column, where drop lets us isolate values.
  Xs = dataset.drop('PE',axis=1)
  ys= dataset['PE']

#we do the same shit as linear regression according to docs for training
  X_train, X_test, y_train, y_test = train_test_split(Xs,ys, test_size=0.2, random_state=80)
  from sklearn.ensemble import GradientBoostingRegressor
  ergoRegression = GradientBoostingRegressor(n_estimators=100, learning_rate=0.2, max_depth=3, random_state=80)
  ergoRegression.fit(X_train, y_train)

  y_prediction = ergoRegression.predict(X_test)
  from sklearn.metrics import mean_squared_error, r2_score

  mse = mean_squared_error(y_test, y_prediction)
  pirateSoundSquared = r2_score(y_test, y_prediction)
  print("GRADIANT REGRESSION: ")
  print("Mean Squared Error:", mse)
  print("R2 Score:", pirateSoundSquared)


  print("MSE:, " ,mse)
  print("R2, ", pirateSoundSquared)

LinearRegressionModel(dataset)
GradiantBoostingRegressionModel(dataset)

