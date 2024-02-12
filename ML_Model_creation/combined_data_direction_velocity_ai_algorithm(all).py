
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from google.colab import drive
drive.mount('/content/drive')

data = pd.read_csv('/content/drive/MyDrive/AI_models_wind_direction/combined_data_direction_velocity.csv')

X=data.iloc[:, :-2].values
print(X)



y=data.iloc[:,[4,5]].values
print(y)

from sklearn.model_selection import train_test_split
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.2,random_state=1)

from sklearn.linear_model import LinearRegression
linear_regressor=LinearRegression()
linear_regressor.fit(X_train,y_train)

from sklearn.linear_model import LinearRegression
lin_reg=LinearRegression()
lin_reg.fit(X_train,y_train)
from sklearn.preprocessing import PolynomialFeatures
poly_reg=PolynomialFeatures(degree=6)
X_poly=poly_reg.fit_transform(X)
lin_reg_2=LinearRegression()
lin_reg_2.fit(X_poly,y)

from sklearn.tree import DecisionTreeRegressor
Decision_tree_regressor=DecisionTreeRegressor(random_state=0)
Decision_tree_regressor.fit(X,y)

from sklearn.ensemble import RandomForestRegressor
random_forest_regressor=RandomForestRegressor(n_estimators=100,random_state=0)
random_forest_regressor.fit(X,y)

linear_y_pred=linear_regressor.predict(X_test)
np.set_printoptions(precision=6)
precision=np.concatenate((X_test,linear_y_pred,y_test),1)
result1=','.join(map(str,precision))
print(result1)

polynomial_y_pred=lin_reg_2.predict(poly_reg.fit_transform(X_test))
np.set_printoptions(precision=2)
#precision=np.concatenate((X_test,y_pred.reshape(len(y_pred),1),y_test.reshape(len(y_test),1)),1)#
precision=np.concatenate((X_test,y_test,polynomial_y_pred),1)
result2=','.join(map(str,precision))
print(result2)

Decision_tree_y_pred=Decision_tree_regressor.predict(X_test)
np.set_printoptions(precision=6)
precision=np.concatenate((X_test,Decision_tree_y_pred,y_test),1)
result3=','.join(map(str,precision))
print(result3)

random_forest_y_pred=random_forest_regressor.predict(X_test)
np.set_printoptions(precision=6)
precision=np.concatenate((X_test,random_forest_y_pred,y_test),1)
result4=','.join(map(str,precision))
print(result4)

from sklearn.metrics import r2_score
r2_score(y_test,linear_y_pred)

from sklearn.metrics import r2_score
r2_score(y_test,polynomial_y_pred)

from sklearn.metrics import r2_score
r2_score(y_test,Decision_tree_y_pred)

from sklearn.metrics import r2_score
r2_score(y_test,random_forest_y_pred)

#df=pd.DataFrame(precision)
#df.to_csv('/content/drive/My Drive/combined_data_Polynomial_Regression.csv', index=False)

#df_verify = pd.read_csv('/content/drive/My Drive/combined_data_Polynomial_Regression.csv')
#print(df_verify)

Decision_tree_regressor.predict([[565,590,27.5,57.5]])
