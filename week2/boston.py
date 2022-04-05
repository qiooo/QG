#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 忽略警告
import warnings
warnings.filterwarnings('ignore')

# 导入波士顿房价数据集
from sklearn.datasets import load_boston 
boston=load_boston()

# 将绘制出的图像直接嵌入在notebook单元格中
get_ipython().run_line_magic('matplotlib', 'inline')

# 绘图设置
plt.style.use({'figure.figsize':(15,10)})
plt.rcParams['font.sans-serif']=['SimHei'] # 黑体
plt.rcParams['axes.unicode_minus']=False  # 负号


# In[2]:


# 查看数据集的特征
boston.feature_names


# In[3]:


# 查看数据集的简述
print(boston.DESCR)


# In[4]:


# 查看数据集
boston_df=pd.DataFrame(boston.data,columns=boston.feature_names)
# 增加价格这一列便于预测数据
boston_df['PRICE']=boston.target
boston_df


# In[5]:


# 查看空值
boston_df.isnull().sum()
# 由结果来看不存在空值


# In[6]:


# 查看数据的描述信息
boston_df.describe()


# In[7]:


# 数据可视化
# 折线图：横坐标：index，纵坐标：value
boston_df.plot(subplots=True,figsize=(25,45),fontsize=20,linewidth=2)
# 由图可知，无缺失值


# In[8]:


# 直方图
boston_df.hist(bins=25,color='g',edgecolor='k',linestyle='-',alpha=0.5)


# In[9]:


# 查看数据与房价的相关性
boston_corr=boston_df.corr()['PRICE']
boston_corr


# In[10]:


# 查看价格与其他特征的相关性，正相关
boston_corr['PRICE']>0.5
# 由结果得，RM(平均客房数)


# In[11]:


# 负相关
boston_corr.PRICE<-0.5
# 由结果得，PTRATIO(学生与教师的比例)，LSTAT(低收入人群占比)


# In[12]:


# 相关性柱状图
boston_corr[abs(boston_corr) > 0.5].sort_values().plot.bar(figsize=(8,8),fontsize=18,alpha=0.5)
plt.title('与房价具有相关性特征柱状图',fontsize=20)


# In[13]:


# 散点图
x1=boston_df['RM']
x2=boston_df['LSTAT']
x3=boston_df['PTRATIO']
y=boston_df['PRICE']

plt.figure(figsize=(15,25))


plt.subplot(311)
plt.scatter(x1,y)
plt.title('平均客房数与房价的散点图',fontsize=20)
plt.grid(linestyle='--',alpha=0.5)
plt.yticks(range(0,55,5))

plt.subplot(312)
plt.scatter(x2,y,color='g')
plt.title('学生与教师的比例与房价的散点图',fontsize=20)
plt.grid(linestyle='--',alpha=0.5)
plt.yticks(range(0,55,5))

plt.subplot(313)
plt.scatter(x3,y,color='y',alpha=0.5)
plt.title('低收入人群占比的散点图',fontsize=20)
plt.grid(linestyle='--',alpha=0.5)
plt.yticks(range(0,55,5))

#plt.xlabel('平均客房数',fontsize=20)
#plt.ylabel('房价',fontsize=20)

#由图知，三者均与房价具有较强的相关性


# In[14]:


data=boston_df[['RM','LSTAT','PTRATIO','PRICE']]
pd.plotting.scatter_matrix(data,figsize=(15,15),color='g')


# In[15]:


# 箱线图
data1=boston_df['RM']
data2=boston_df['LSTAT']
data3=boston_df['PTRATIO']

plt.figure(figsize=(10,10))
plt.boxplot([data1,data2,data3],labels=['平均客房数','学生与教师的比例','低收入人群占比'],whis=2,
            flierprops={'marker':'o','markerfacecolor':'g','color':'k'},patch_artist=True,boxprops={'facecolor':'g','color':'k'})
ax=plt.gca()
ax.patch.set_facecolor('g')
ax.patch.set_alpha(0.1)
plt.title('影响房价特征房价箱线图',fontsize=20)
#由图可得异常值


# In[16]:


# 数据预处理

# 去除无相关性特征
boston_df = boston_df[['LSTAT', 'PTRATIO', 'RM', 'PRICE']]
# 目标值
y=np.array(boston_df['PRICE'])
# 特征值
boston_df = boston_df.drop(['PRICE'], axis=1)
X=np.array(boston_df)


# In[17]:


from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.linear_model import LinearRegression 
from sklearn.metrics import mean_squared_error,r2_score


# In[18]:


# 划分训练集和测试集
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.2,random_state=0)
print(X_train.shape,X_test.shape,y_train.shape,y_test.shape)


# In[19]:


X_train=MinMaxScaler().fit_transform(X_train)
y_train=MinMaxScaler().fit_transform(y_train.reshape(-1,1)) # 二维
X_test=MinMaxScaler().fit_transform(X_test)
y_test=MinMaxScaler().fit_transform(y_test.reshape(-1,1))


# In[20]:


# 恢复索引,删除过的numpy不能用index
#for i in [X_train,X_test]:
#    i.index=range(i.shape[0])


# In[21]:


# 模型训练
fited=LinearRegression().fit(X_train,y_train)
#测试集的预测值
y_test_pred=fited.predict(X_test)


# In[22]:


# 查看系数
fited.coef_


# In[23]:


# 代码实现
# 方阵才能进行计算
data_hat=np.linalg.inv(X_train.T.dot(X_train)).dot(X_train.T).dot(y_train)
data_hat
# 不一样？


# In[24]:


# 查看截距
fited.intercept_


# In[25]:


# 模型评估

# 均方误差
mean_squared_error(y_test,y_test_pred)


# In[26]:


# 均方误差代码实现
def cost(xs,ys):
    ys_pred=fited.predict(xs)
    cost=sum([val_**2 for val_ in (ys_pred-ys)])
    return cost/len(xs)
cost(X_test,y_test)


# In[27]:


#拟合效果评分
fited.score(X_test,y_test)


# In[28]:


# R^2决定系数
r2_score(y_test,y_test_pred)
# 二者一样


# In[29]:


# 决定系数代码实现
import math
r=math.sqrt(1-sum([val_**2 for val_ in (y_test_pred-y_test)])/sum([val__**2 for val__ in (y_test-y.mean())]))
r
# 又不一样？


# In[30]:


# 拟合结果可视化
plt.figure(figsize=(10,8))
plt.title('测试集的真实值与预测值的拟合效果',fontsize=20)
plt.plot(range(len(y_test)),sorted(y_test),label='Data')
plt.plot(range(len(y_test_pred)),sorted(y_test_pred),color='r',label='Predict')
plt.legend(loc='best')


# In[45]:


# 梯度下降法
epsilon = 0.0001 # 阈值
# 初始化参数
theta0=0
theta1=0
theta2=0
b=0
error0=0
count=0 # 迭代次数
learning_rate=0.000001 # 学习率
x=X_test
y=y_test
while True:
    count+=1
    for i in range(len(x)):
        y_pred=theta0*x[i][0]+theta1*x[i][1]+theta2*x[i][2]
        theta0-=learning_rate*(y_pred-y[i])*x[i][0]
        theta1-=learning_rate*(y_pred-y[i])*x[i][1]
        theta2-=learning_rate*(y_pred-y[i])*x[i][2]
        b-=learning_rate*(y_pred-y)
    error1=0
    for j in range(len(x)):
        error1+=(y[j]-y_pred)**2/2
    if abs(error1-error0)< epsilon:
        break
    else:
        error0=error1
    print('theta0 : %f, theta1 : %f, theta2 : %f, error1 : %f, error0: %f' % (theta0, theta1, theta2,error1, error0))
print('Done: theta0 : %f, theta1 : %f, theta2 : %f' % (theta0, theta1, theta2))
print('迭代次数: %d' % count)


# In[46]:


# 查看梯度下降结果
print('Done: theta0 : %f, theta1 : %f, theta2 : %f' % (theta0, theta1, theta2))
print('迭代次数: %d' % count)


# In[32]:


# 三种结果比较
data_hat


# In[42]:


fited.coef_


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




