import math

# Libraries for analysis
import pickle

# Libraries for visualisation
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from sklearn.decomposition import PCA
from sklearn.metrics import accuracy_score
from sklearn.metrics import plot_confusion_matrix
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import scale
from sklearn.svm import SVC

# Read csv
df = pd.read_csv('dataset.csv')

# Remove missing dataset
for index, row in df.iterrows():
    for x in row:
        if type(x) == str:
            continue
        if math.isnan(x):
            df = df.drop(index)
            break

# separate label and other columns into two df
X = df.drop('type', axis=1).copy()
y = df['type'].copy()

# centering and scaling
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)
X_train_scaled = scale(X_train)
X_test_scaled = scale(X_test)

# build a preliminary SVM
params_grid = [
    {
        'kernel': ['rbf'], 'gamma': [1e-3, 1e-4],
        'C': [1, 10, 100, 1000]
    },
    {
        'kernel': ['linear'],
        'C': [1, 10, 100, 1000]
    }
]
clf_svm = GridSearchCV(SVC(random_state=42), params_grid)
clf_svm.fit(X_train_scaled, y_train)
prediction = clf_svm.predict(X_test_scaled)
print(accuracy_score(y_test, prediction))


# plot confusion matrix
plot_confusion_matrix(clf_svm,
                      X_test_scaled,
                      y_test)
print(plot_confusion_matrix)
plt.show()


pca = PCA()
X_train_pca = pca.fit_transform(X_train_scaled)
per_var = np.round(pca.explained_variance_ratio_*100, decimals=1)
labels = [str(x) for x in range(1, len(per_var) + 1)]
plt.bar(x=range(1, len(per_var) + 1), height=per_var)
plt.tick_params(
    axis='x',
    which='both',
    bottom=False,
    top=False,
    labelbottom=False
)
plt.show()


counter = 0
right_counter = 0
down_counter = 0
left_counter = 0
up_counter = 0

predicted = clf_svm.predict(X_test_scaled)
temp = zip(predicted, y_test)

correct_answer = 0
wrong_answer = 0
for x, y in temp:
    if x == 'right':
        if y == 'right':
            correct_answer += 1
        else:
            wrong_answer += 1
        right_counter += 1
    elif x == 'up':
        if y == 'up':
            correct_answer += 1
        else:
            wrong_answer += 1
        up_counter += 1
    elif x == 'left':
        if y == 'left':
            correct_answer += 1
        else:
            wrong_answer += 1
        left_counter += 1
    elif x == 'down':
        if y == 'down':
            correct_answer += 1
        else:
            wrong_answer += 1
        down_counter += 1
    counter += 1
print(right_counter)
print(up_counter)
print(down_counter)
print(left_counter)
print(correct_answer)
print(wrong_answer)
print(correct_answer/len(X_test))


# save the model to disk
# filename = 'finalized_model.sav'
# pickle.dump(clf_svm, open(filename, 'wb'))
