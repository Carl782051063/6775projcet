# 定义两个文件名
output_file_col1 = 'column1.txt'
output_file_col2 = 'column2.txt'

# 打开输入文件和输出文件
with open('data.txt', 'r') as input_file, \
     open(output_file_col1, 'w') as output_file1, \
     open(output_file_col2, 'w') as output_file2:

    # 逐行读取输入文件
    for line in input_file:
        # 以空格分割每一行
        columns = line.split()
        if len(columns) >= 2:
            # 提取第一列和第二列数据
            col1 = columns[0]
            col2 = columns[1]

            # 将数据写入相应的输出文件
            output_file1.write(col1 + '\n')
            output_file2.write(col2 + '\n')
