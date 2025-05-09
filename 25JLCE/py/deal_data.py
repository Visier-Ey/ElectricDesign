import json

def convert_text_to_json(input_file):
    """
    将特定格式的文本文件转换为嵌套的JSON对象并返回，对相同y值的x取平均
    
    参数:
        input_file (str): 输入文本文件路径
    
    返回:
        dict: 转换后的JSON对象（Python字典），其中相同y值的x已取平均
        None: 如果转换失败则返回None
    
    文件格式要求:
        每行应为 (key, subkey, value) 格式，例如: (1, 101, 3.14)
    """
    try:
        # 读取数据文件
        with open(input_file, 'r') as file:
            lines = file.readlines()

        # 解析数据
        data = []
        for line in lines:
            # 移除空白字符和两端的括号
            cleaned = line.strip().strip('()')
            if not cleaned:
                continue
            
            # 分割各部分
            parts = [p.strip() for p in cleaned.split(',')]
            
            # 确保有3部分且最后一部分能正确处理
            if len(parts) >= 3:
                try:
                    # 处理第三部分可能包含的右括号
                    value_part = parts[2].replace(')', '')
                    key = int(parts[0])
                    subkey = int(parts[1])
                    value = float(value_part)
                    data.append((key, subkey, value))
                except ValueError as e:
                    print(f"解析错误: {parts}, 错误: {e}")
                    continue

        # 转换为目标格式并对相同y值取x的平均
        result = {}
        for item in data:
            key = str(item[0])
            subkey = item[1]
            value = item[2]
            
            if key not in result:
                result[key] = {}
            
            if subkey in result[key]:
                # 如果已有相同的y值，则累计值和计数
                result[key][subkey]['sum'] += value
                result[key][subkey]['count'] += 1
            else:
                # 第一次遇到这个y值
                result[key][subkey] = {'sum': value, 'count': 1}

        # 计算平均值并转换为最终格式
        final_result = {}
        for key in result:
            final_result[key] = []
            # 按y值排序
            for subkey in sorted(result[key].keys()):
                avg_value = result[key][subkey]['sum'] / result[key][subkey]['count']
                final_result[key].append([subkey, avg_value])

        print(f"数据已成功从 {input_file} 转换为JSON对象，并处理了重复y值的平均")
        return final_result
    
    except FileNotFoundError:
        print(f"错误: 文件 {input_file} 未找到")
        return None
    except Exception as e:
        print(f"发生未知错误: {str(e)}")
        return None


# 使用示例
# json_data = convert_text_to_json('data.txt')
# if json_data:
#     with open('data.json', 'w') as outfile:
#         json.dump(json_data, outfile, indent=2)