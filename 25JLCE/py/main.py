import json
import numpy as np
from numpy.polynomial import Polynomial
from deal_data import convert_text_to_json


def load_coefficients(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"错误：文件 {filename} 未找到！")
        return {}
    except json.JSONDecodeError:
        print("错误：文件不是有效的JSON格式！")
        return {}
    except Exception as e:
        print(f"发生未知错误：{e}")
        return {}


def fit_data(data_dict, degree):
    """
    对每组数据进行多项式拟合，返回拟合系数
    
    参数:
        data_dict: 输入数据字典
        degree: 多项式拟合的阶数
        
    返回:
        包含拟合系数的字典
    """
    coefficients_dict = {}
    
    for key, values in data_dict.items():
        # 分离x和y值 (x是每组数据中的第二个数字，y是第三个数字)
        x = []
        y = []
        for item in values:
            x_val = item[1]
            y_val = item[0]
            # 只使用非零数据点进行拟合
            if y_val != 0:
                x.append(x_val)
                y.append(y_val)
        
        # 如果有足够的数据点进行拟合
        if len(x) > degree and len(y) > degree:
            # 使用numpy的Polynomial进行拟合
            coefs = Polynomial.fit(x, y, degree).convert().coef
            # 将系数转换为列表并保留6位小数
            coefficients_dict[key] = [round(c, 6) for c in coefs]
        else:
            coefficients_dict[key] = None  # 数据不足无法拟合
    
    return coefficients_dict

# 示例数据 (替换为你实际的数据)
data = convert_text_to_json('data.txt')

# 从用户输入获取拟合阶数
degree = int(input("请输入多项式拟合的阶数: "))

# 进行拟合
coefficients = fit_data(data, degree)

# 保存结果到JSON文件
output_filename = f"polynomial_fit_coefficients_degree_{degree}.json"
with open(output_filename, 'w') as f:
    json.dump(coefficients, f, indent=4)

print(f"拟合完成! 结果已保存到 {output_filename}")
print("拟合系数示例:")
for key, coef in list(coefficients.items())[:5]:  # 只显示前5个结果作为示例
    print(f"{key}: {coef}")