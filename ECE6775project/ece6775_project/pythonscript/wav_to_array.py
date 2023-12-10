import numpy as np
from scipy.io import wavfile

wavefile = "output_resampled.wav"
textfile_real = "PCMdata_real.txt"
textfile_imag = "PCMdata_imag.txt"

# Read the .wav file
sample_rate, data = wavfile.read(wavefile)

# Print the sampling rate
print(f"Sampling rate: {sample_rate} Hz")

# Ensure the audio data is one-dimensional (mono)
if data.ndim > 1:
    data = data[:, 0]

# Create a complex array where the real part is the audio data and the imaginary part is set to 0
complex_data = data.astype(np.float32) + 0j

# Calculate the necessary padding length
desired_length = 2**np.ceil(np.log2(len(complex_data))).astype(int)
padding_length = desired_length - len(complex_data)

# Pad the array with zeros
complex_data_padded = np.pad(complex_data, (0, padding_length), 'constant')

# Separate the real and imaginary parts
real_part = complex_data_padded.real
imaginary_part = complex_data_padded.imag

# Write the real and imaginary parts to text files
np.savetxt(textfile_real, real_part, fmt='%f')
np.savetxt(textfile_imag, imaginary_part, fmt='%f')
