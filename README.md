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


