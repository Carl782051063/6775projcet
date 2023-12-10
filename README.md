# ECE 6775 projcet
ECE6775 final project
FPGA-Based FFT Accelerator for Voice Optimizer
Work Jiacheng Tu, Ruyi Zhou, Klora Wang and Bolong Tan 

The project structure contains three parts:

1.ECElinux (code files for running software testbench on ecelinux)

2.Zedboard (code files for running on ARM and FPGA based on a zybd7000)

3.pythonscript (code files for convert real aduio file(.wav) to our input data format and convert the output.dat back to real audio file (.wav))

(1) Convert real audio file(.wav) to input data array format (resample_to_decrease_size.py and wav_to_array.py)

(2) Covert output.dat back to real audio file(.wav) (split_to_twofile.py and array_to_wav.py)


If you want to replace the input auido data or want to convert the output.dat back to real aduio file(.wav), please use the code files in pythonscript.

To run the project,
For the software testbench on ecelinux, run "make fft-sw" in the directory /ecelinux to generate the ouput.dat.
For the software testbench on ARM, run "make sw" in the directory /zedboard to generate the output.dat when you load the file on FPGA.

To run on FPGA, first run "make xillydemo.bit" in the directory /ecelinux to generate the bitstream.
After loading the file and mounting the bitstream on FPGA,run "make fpga" in the directory /zedboard to generate the output.dat.


There are two prepared input file converted from real audio(.wav), "PCMdata_real.txt" and "PCMdata_imag.txt" contains the real part data and imaginary part data separately.
After running the project, it will output a file named "output.dat" where the first colume represent the processed real part data and second colume represents the processed imag part data.


# ECE 6775 Final Project
## FPGA-Based FFT Accelerator for Voice Optimizer

### Team Members
- Jiacheng Tu- Ruyi Zhou- Klora Wang- Bolong Tan

### Project Structure
This project is divided into three main parts:

1. **ECElinux**: Code files for running software testbench on ECElinux.
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
- (2) Convert `output.dat` back to real audio file (.wav) (`split_to_twofile.py` and `array_to_wav.py`)
3. **Zedboard**: Code files for running on ARM and FPGA based on a Zybd7000 platform.
- fft_test.cpp (software testbench)
- fft.cpp (fft subfunctions)
- host.cpp (communication file for sending and receiving data between fpga and arm)
- fft.h
- Makefile
- PCMdata_imag.txt (input data imaginary  part)
- PCMdata_real.txt (input data real part)
- timer.h
- typedefs.h
4. **PythonScript**: Code files for converting real audio files (.wav) to our input data format and converting the `output.dat` back to real audio files (.wav).
- (1) Convert real audio file (.wav) to input data array format (`resample_to_decrease_size.py` and `wav_to_array.py`)
- (2) Convert `output.dat` back to real audio file (.wav) (`split_to_twofile.py` and `array_to_wav.py`)

### Usage Instructions
If you want to replace the input audio data or convert the `output.dat` back to a real audio file (.wav), please use the code files in the `pythonscript` directory.

#### Running the Project on software
- For the software testbench on ECElinux, run `make fft-sw` in the `/ecelinux` directory to generate the `output.dat`.
- For the software testbench on ARM, run `make sw` in the `/zedboard` directory to generate the `output.dat` when you load the file on FPGA.

#### Running on FPGA
- First, run `make xillydemo.bit` in the `/ecelinux` directory to generate the bitstream.
- After loading the file and mounting the bitstream on FPGA, run `make fpga` in the `/zedboard` directory to generate the `output.dat`.

### Input and Output Files
- There are two prepared input files converted from real audio (.wav): `PCMdata_real.txt` and `PCMdata_imag.txt`, containing the real part data and imaginary part data separately.
- After running the project, it will output a file named `output.dat`, where the first column represents the processed real part data, and the second column represents the processed imaginary part data.


