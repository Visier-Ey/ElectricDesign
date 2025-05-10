import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

# 原始数据
data = [
    (1000,1,377.000000), (1000,2,522.000000), (1000,3,684.000000), (1000,4,822.000000), (1000,5,988.000000),
    (2000,1,445.000000), (2000,2,685.000000), (2000,3,922.000000), (2000,4,1163.000000),
    (3000,1,509.000000), (3000,2,778.000000), (3000,3,1060.000000), (3000,5,1640.000000),
    (4000,1,519.000000), (4000,2,814.000000), (4000,3,1122.000000), (4000,4,1414.000000),
    (5000,1,514.000000), (5000,2,810.000000), (5000,3,1094.000000), (5000,4,1392.000000), (5000,5,1689.000000),
    (6000,1,502.000000), (6000,2,789.000000), (6000,5,1635.000000),
    (7000,1,495.000000), (7000,2,789.000000), (7000,3,1057.000000), (7000,4,1342.000000), (7000,5,1609.000000),
    (8000,1,490.000000), (8000,2,755.000000), (8000,3,1019.000000), (8000,4,1283.000000), (8000,5,1549.000000),
    (9000,1,472.000000), (9000,2,702.000000), (9000,3,951.000000), (9000,4,1199.000000), (9000,5,1442.000000),
    (10000,1,454.000000), (10000,2,677.000000), (10000,4,1111.000000), (10000,5,1365.000000)
]

# 转换为特征(X)和目标(y)
X = np.array([[x[0], x[2]] for x in data])  # 频率和幅度
y = np.array([x[1] for x in data])          # 调频度

# 绘制3D散点图
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(X[:, 0], X[:, 1], y, c='r', marker='o')
ax.set_xlabel('Frequency')
ax.set_ylabel('Amplitude')
ax.set_zlabel('Modulation Degree')
plt.title('3D Scatter Plot of Frequency, Amplitude and Modulation Degree')



poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X)

model = LinearRegression()
model.fit(X_poly, y)

r_squared = model.score(X_poly, y)
print(f"R-squared: {r_squared:.4f}")

coefficients = model.coef_
intercept = model.intercept_

print(f"调频度 = {intercept:.4f} + "
      f"{coefficients[0]:.4f}*频率 + "
      f"{coefficients[1]:.4f}*幅度 + "
      f"{coefficients[2]:.4f}*频率^2 + "
      f"{coefficients[3]:.4f}*频率*幅度 + "
      f"{coefficients[4]:.4f}*幅度^2")

# 画出拟合曲面
x_range = np.linspace(X[:, 0].min(), X[:, 0].max(), 100)
y_range = np.linspace(X[:, 1].min(), X[:, 1].max(), 100)
X1, X2 = np.meshgrid(x_range, y_range)
X_grid = np.c_[X1.ravel(), X2.ravel()]
X_grid_poly = poly.transform(X_grid)
y_grid = model.predict(X_grid_poly).reshape(X1.shape)

ax.plot_surface(X1, X2, y_grid, alpha=0.5, rstride=100, cstride=100, color='b')
plt.show()
