# ECE 6775 Final Project
## FPGA-Based FFT Accelerator for Voice Optimizer

### Team Members
- Jiacheng Tu - Bolong Tan
- Ruyi Zhou   - Klora Wang

### Project Structure
This project is divided into three main parts:

#### **ECElinux**: Code files for running software testbench on ECElinux.
- fft_test.cpp (software testbench)
- fft.cpp (fft subfunctions)
- fft.h
- Makefile
- PCMdata_imag.txt (input data imaginary  part)
- PCMdata_real.txt (input data real part)
- run_bitstream.sh
- run.tcl
- timer.h
- typedefs.h

#### **Zedboard**: Code files for running on ARM and FPGA based on a Zybd7000 platform.
- fft_test.cpp (software testbench)
- fft.cpp (fft subfunctions)
- host.cpp (communication file for sending and receiving data between fpga and arm)
- fft.h
- Makefile
- PCMdata_imag.txt (input data imaginary  part)
- PCMdata_real.txt (input data real part)
- timer.h
- typedefs.h
  
#### **PythonScript**: Code files for converting real audio files (.wav) to our input data format and converting the `output.dat` back to real audio files (.wav).
- (1) Convert real audio file (.wav) to input data array format (`resample_to_decrease_size.py` and `wav_to_array.py`)
- (2) Convert `output.dat` back to real audio file (.wav) (`split_to_twofile.py` and `array_to_wav.py`)

### Usage Instructions
If you want to replace the input audio data or convert the `output.dat` back to a real audio file (.wav), please use the code files in the `pythonscript` directory.

#### Running the Project on software
- For the software testbench on ECElinux, run `make fft-sw` in the `/ecelinux` directory to generate the `output.dat`.
- For the software testbench on ARM, run `make sw` in the `/zedboard` directory to generate the `output.dat` when you load the file on FPGA.

#### Running on FPGA
- First, run `vivado_hls -f run.tcl` and 'source run_bitstream.sh' in the `/ecelinux` directory to generate the bitstream.
- After loading the file and mounting the bitstream on FPGA, run `make fpga` in the `/zedboard` directory to generate the `output.dat`.

### Input and Output Files
- There are two prepared input files converted from real audio (.wav): `PCMdata_real.txt` and `PCMdata_imag.txt`, containing the real part data and imaginary part data separately.
- After running the project, it will output a file named `output.dat`, where the first column represents the processed real part data, and the second column represents the processed imaginary part data.


