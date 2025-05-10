import json

def generate_c_expression(coeffs):
    if coeffs is None or not coeffs:
        return "0.0f"
    
    # Ensure coeffs is a list (handle cases where it might be a single float)
    if not isinstance(coeffs, (list, tuple)):
        return f"{float(coeffs)}f"
    
    # 创建一个字典来存储系数，键是幂次，值是系数
    terms_dict = {}
    for power, coefficient in enumerate(coeffs):
        if coefficient == 0:
            continue
        terms_dict[power] = f"{coefficient}f"
    
    # 生成按幂次排序的项
    terms = []
    for power in sorted(terms_dict.keys()):
        terms.append(f"{terms_dict[power]} * pow(var, {power})")
    
    if not terms:
        return "0.0f"
    
    return " + ".join(terms)

def generate_am_modulate_function(data):
    c_code = []
    c_code.append("float calculateAMModulate(float var, uint16_t CarrierFreq) {")
    c_code.append("  float y = 0;")
    
    # Filter out null frequencies and convert to integers
    valid_freqs = [int(k) for k in data.keys() if data[k] is not None]
    sorted_freqs = sorted(valid_freqs, reverse=True)
    
    if not sorted_freqs:
        c_code.append("  return 0.0f;")
        c_code.append("}")
        return "\n".join(c_code)
    
    # 生成条件判断语句
    for i, freq in enumerate(sorted_freqs):
        if i == 0:
            # 第一个条件（最高频率）
            c_code.append(f"  if (CarrierFreq >= {freq}) {{")
        else:
            c_code.append(f"  }} else if (CarrierFreq >= {freq}) {{")
        
        expr = generate_c_expression(data[str(freq)])
        c_code.append(f"    y = {expr};")
    
    # 添加默认条件（最低频率）
    c_code.append("  } else {")
    expr = generate_c_expression(data[str(sorted_freqs[-1])])
    c_code.append(f"    y = {expr};")
    c_code.append("  }")
    
    c_code.append("  return y;")
    c_code.append("}")
    
    return "\n".join(c_code)

try:
    # 从polynomial_fit_coefficients_degree_3.json文件读取数据
    power = 6
    with open(f'polynomial_fit_coefficients_degree_{power}.json', 'r') as file:
        data = json.load(file)
    
    # 生成C语言函数代码
    c_function = generate_am_modulate_function(data)
    print(c_function)

except FileNotFoundError:
    print(f"错误: 未找到polynomial_fit_coefficients_degree_{power}.json文件")
except json.JSONDecodeError:
    print(f"错误: polynomial_fit_coefficients_degree_{power}.json文件格式不正确")
except Exception as e:
    print(f"发生未知错误: {str(e)}")