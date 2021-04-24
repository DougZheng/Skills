## python

### 输入

```python
# 输入一个整数
t = int(input())

# 输入两个整数
n, m = map(int, input().split())

# 输入序列
a = list(map(int, input().split()))

# 多组数据
while True:
    try:
        pass # test
    except:
        break
```

### 输出

```python
# 输出序列a
print(a, seq = ', ', end = ' ')

# 格式化输出
print('{0:d}, {1:.2f}'.format(233, 233))
```

### 循环

```python
# [0, n)
for i in range(n): pass

# [1, n + 1)，步长为2
for i in range(1, n + 1, 2): pass

# [n, 0)，步长为-1
for i in range(n, 0, -1): pass

# 下标，值
for i, v in enumerate(a): pass
```

### 字符串

```python
s = '123'

# 字符串翻转
s = s[::-1] # reverse
s = ''.join(reversed(s)) # reverse

# 分割与连接
a = s.strip().split()
s = ' '.join(str(v) for v in a)
```

### 数组

```python
# 一维数组
a = [0 for i in range(n)]
a = [[0, 0] for i in range(n)]

# 二维数组
a = [[0 for j in range(m)] for i in range(n)]
```

### 排序

```python
# lambda传入键，默认升序，reverse=True则降序
a.sort(key = lambda x : x[1], reverse = True)

# sorted不改变原序列
a = set(eval('[1, 2, 3, 4]')) # set: unique element
a = sorted(a, key = lambda x : (x[0], x[1]), reverse = True)

# 用cmp自定义排序
import functools
def cmp(x, y): return y[0] - x[0] if x[0] != y[0] else y[1] - x[1]
a.sort(key = functools.cmp_to_key(cmp))
```

### 注意事项

```python
n = 0
def func():
    # global n
    n = 1 # 局部定义并初始化
    print(n)
```



## pandas

```python
import numpy as np, pandas as pd 

df1 = pd.DataFrame([[11, 12], [21, 22]], columns = ['c1', 'c2'], index = ['r1', 'r2'])
sr1 = pd.Series([1, 2, 3, 4], index = ['r1', 'r2', 'r3', 'r4'], name = 'exercise')
# df1 = pd.read_csv('/path', index_col = '')
# df1.to_csv('/path')

c1 = df1['c1'][ : 2] # [col][row]
c1 = df1.iloc[ : 2, 0] # [row, col], using integer index, [l : r)
c1 = df1.loc['r1' : 'r2', 'c1'] # [row, col], using string index, [l : r]
records = df1.loc[(df1['c1'] == 11) & (df1.c1 == 11)] # bool index
records = df1.loc[(df1['c1'].isin([11, 111])) & (df1.c1.notnull()) & (df1.c1.isnull())] # builtin func

# mean, medium, count(), sum, unique, value_counts, max, idxmax
sr1.map(lambda x : x)
df1.c1.map(lambda x : x) # actually in col
df1.apply(lambda x : x, axis = 'columns') # fetch each row, maybe it like using map along column

df1.groupby('c1').size()
df1.groupby('c1').c2.count()
df1.groupby(['c1', 'c2']).c2.agg(['min', 'max']) # reset_index
df1.sort_values(by = 'c1', ascending = False)
sr1.sort_values(ascending = False)
sr1.sort_index()

df1.c1.dtype
sr1 = df1.c1.astype('float64')
df1.c1.fillna('Unknown')
df1.c1.replace('old', 'new')

df1.rename(columns = {'c1' : 'cc1'})
df1.rename_axis('index')
df1.rename_axis('columns', axis = 'columns')
df2 = df1
pd.concat([df1, df2])
df1.set_index('c2')
df2.set_index('c2')
df1.join(df2)
```



## pyplot

```python
import numpy as npy, pandas as pd, matplotlib.pyplot as plt, seaborn as sns

flight_data = pd.read_csv('flight_delays.csv', index_col = 'Month')
# plt.figure(figsize = (10, 10))
# plt.title('exercises for seaborn')
# plt.xlabel('x axis')
# plt.ylabel('y axis')
# sns.lineplot(data = flight_data)
# sns.barplot(x = flight_data.index, y = flight_data['NK'])
# sns.heatmap(data = flight_data, annot = True)
# sns.scatterplot(x = flight_data.index, y = flight_data['NK'])
# sns.regplot(x = flight_data.index, y = flight_data['NK'])
# sns.scatterplot(x = data[''], y = data[''], hue = data[''])
# sns.lmplot(x = '', y = '', hue = '', data = )
# sns.swarmplot(x = data[''], y = data[''])
# sns.distplot(a = flight_data['NK'], kde = False)
# sns.kdeplot(data = flight_data['NK'], shade = True)
sns.jointplot(x = flight_data['NK'], y = flight_data['OO'], kind = 'kde')
```



## Machine Learning

```python
import numpy as np, pandas as pd
from scipy import stats
import sklearn.preprocessing as sp
import chardet

df1 = pd.DataFrame([[11, 12], [21, 22]], columns = ['c1', 'c2'], index = ['r1', 'r2'])
df1.isnull().sum() # num. of null values each col.
df1.isnull().sum().sum() # num. of all null values
np.product(df1.shape) # total num.
df1.size # num. of rows
df1.shape[1] # num. of cols

df1.dropna(axis = 1) # 1: drop col. containing NAN; 0: row, default
df1.fillna(method = 'bfill').fillna(method = 'ffill').fillna(0) # back fill, front fill, 0

scaler = sp.MinMaxScaler(feature_range = (0, 1))
scaler.fit(df1)
scaler.transform(df1)
scaler.fit_transform(df1) # return ndarray
# stats.boxcox()

# pd.to_datetime(df[''], format = '%m/%d/%Y', infer_datetime_format = True)

# with open('', 'rb') as fin:
#     chardet.detect(fin.read())
# pd.read_csv('', encoding = '')
```



```python
import pandas as pd
from sklearn.metrics import mean_absolute_error
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
from sklearn.model_selection import train_test_split, cross_val_score, KFold 
from xgboost import XGBRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import cross_val_score

# train_X, val_X, train_y, val_y = train_test_split(X, y, random_state = 1)

# imputer = SimpleImputer()
# imputer_X_train = pd.DataFrame(imputer.fit_transform(X_train))
# imputer_X_valid = pd.DataFrame(imputer.transform(X_valid))
# imputer_X_train.columns = X_train.columns
# imputer_X_valid.columns = X_valid.columns

# drop_X_train = X_train.select_dtypes(exclude = ['object'])
# drop_X_valid = X_valid.select_dtypes(exclude = ['object'])

# label_X_train = X_train.copy()
# label_X_valid = X_valid.copy()
# label_encoder = LabelEncoder()
# for col in object_col:
#     label_X_train[col] = label_encoder.fit_transform(X_train[col])
#     label_X_valid[col] = label_encoder.transform(X_valid[col])

# X_train[col].nunique()
# OH_encoder = OneHotEncoder(handle_unknown = 'ignore', sparse = False)
# OH_cols_train = pd.DataFrame(OH_encoder.fit_transform(X_train[low_cardinality_cols]))
# OH_cols_valid = pd.DataFrame(OH_encoder.transform(X_valid[low_cardinality_cols]))
# OH_cols_train.index = X_train.index
# OH_cols_valid.index = X_valid.index
# OH_X_train = pd.concat([X_train.drop(object_cols, axis = 1), OH_cols_train], axis = 1)
# OH_X_valid = pd.concat([X_valid.drop(object_cols, axis = 1), OH_cols_valid], axis = 1)
```

