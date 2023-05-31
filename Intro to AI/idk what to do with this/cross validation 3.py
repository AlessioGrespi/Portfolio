import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, KFold
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Load the dataset
dataset_path = "numbers.csv"
data = pd.read_csv(dataset_path)

# Split the dataset into input features (X) and target variable (Y)
X = data[['AT', 'V', 'AP', 'RH']].values
Y = data['PE'].values

# Split the data into training, validation, and test sets
Xtrain, Xtest, Ytrain, Ytest = train_test_split(X, Y, test_size=0.2, random_state=0)
Xtrain, Xval, Ytrain, Yval = train_test_split(Xtrain, Ytrain, test_size=0.2, random_state=0)

# Create and fit the linear regression model
regr = LinearRegression()
regr.fit(Xtrain, Ytrain)

# Make predictions on the validation set
pred = regr.predict(Xval)

# Calculate the mean squared error and R^2 score
mse = mean_squared_error(Yval, pred)
r2 = r2_score(Yval, pred)

print(f"Mean Squared Error: {mse:.4f}")
print(f"R^2 Score: {r2:.4f}")

# Perform cross-validation
kf = KFold(n_splits=30, shuffle=True, random_state=0)

# Initialize lists to store training and validation accuracies
train_accuracy = []
val_accuracy = []

# Perform cross-validation with different train-test splits
for train_index, val_index in kf.split(X):
    Xtrain, Xval = X[train_index], X[val_index]
    Ytrain, Yval = Y[train_index], Y[val_index]
    
    # Fit the linear regression model
    regr.fit(Xtrain, Ytrain)
    
    # Make predictions on training and validation sets
    train_pred = regr.predict(Xtrain)
    val_pred = regr.predict(Xval)
    
    # Calculate and store training and validation accuracies
    train_accuracy.append(r2_score(Ytrain, train_pred))
    val_accuracy.append(r2_score(Yval, val_pred))

# Create a line graph to visualize training and validation accuracies
plt.plot(range(1, 31), train_accuracy, label='Training Accuracy')
plt.plot(range(1, 31), val_accuracy, label='Validation Accuracy')
plt.xlabel('Fold')
plt.ylabel('Accuracy')
plt.title('Cross-Validation Accuracy')
plt.legend()
plt.show()

# Plot the predicted values against the actual values
plt.scatter(pred, Yval, color='black')
plt.plot(Yval, Yval, color='blue', linewidth=2, label='y=x')
plt.xlabel('Predicted Values')
plt.ylabel('Actual Values')
plt.title('Linear Regression')
plt.legend()
plt.show()
