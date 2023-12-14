import numpy as np
from scipy.io import wavfile

def read_array_from_file(filename):
    """Read an array from a text file"""
    with open(filename, 'r') as file:
        array = [float(line.strip()) for line in file]
    return np.array(array)

def create_wav(real_file, imag_file, sample_rate, output_file):
    """Read data from real and imaginary files and save as a WAV file"""
    # Read the real and imaginary parts from files
    real_part = read_array_from_file(real_file)
    imag_part = read_array_from_file(imag_file)

    # Combine the real and imaginary parts into a complex array
    complex_data = real_part + 1j * imag_part

    # Take the real part of the complex array and convert it to int16 type
    signal = np.real(complex_data).astype(np.int16)

    # Write to a WAV file
    wavfile.write(output_file, sample_rate, signal)

# Example usage
real_file = 'column1.txt'  # Filename for the real part
imag_file = 'column2.txt'  # Filename for the imaginary part
sample_rate = 12000        # Sample rate, e.g., 44100 Hz
output_file = 'output.wav'      # Output filename

create_wav(real_file, imag_file, sample_rate, output_file)