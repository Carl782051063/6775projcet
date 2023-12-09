import numpy as np
from scipy.io import wavfile

def read_array_from_file(filename):
    """从文本文件中读取数组"""
    with open(filename, 'r') as file:
        array = [float(line.strip()) for line in file]
    return np.array(array)

def create_wav(real_file, imag_file, sample_rate, output_file):
    """从实数和虚数文件中读取数据并保存为WAV文件"""
    # 从文件中读取实数和虚数部分
    real_part = read_array_from_file(real_file)
    imag_part = read_array_from_file(imag_file)

    # 将实数和虚数部分组合为复数数组
    complex_data = real_part + 1j * imag_part

    # 取复数数组的实部并转换为int16类型
    signal = np.real(complex_data).astype(np.int16)

    # 写入到WAV文件
    wavfile.write(output_file, sample_rate, signal)

# 使用示例
real_file = 'column1.txt'  # 实数部分文件名
imag_file = 'column2.txt'  # 虚数部分文件名
sample_rate = 12000         # 采样率，例如44100Hz
output_file = '2.wav'   # 输出文件名

create_wav(real_file, imag_file, sample_rate, output_file)
