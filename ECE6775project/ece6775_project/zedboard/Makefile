#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the bnn program
#
# @desc: 1. "make" or "make sw" runs software execution by default
#        2. "make fpga" invokes the HW accelerator
#        3. "make clean" cleans up the directory


INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH} -DHLS_NO_XIL_FPO_LIB -std=c++11

.PHONY: all sw fpga

all: sw

fft-arm: fft.cpp fft_test.cpp
	@echo "Compiling & executing bnn software program on ARM ..."
	g++ ${CFLAGS} $^ -o $@

fft_result/output.dat: fft-arm
	mkdir -p fft_result
	./$< | tee $@

sw: fft_result/output.dat
	@echo "Result saved to $@"

fft-fpga: host.cpp
	@echo "Compiling host program"
	g++ -I/usr/include/vivado_hls -DHLS_NO_XIL_FPO_LIB -std=c++11 host.cpp -o fft-fpga
	@echo "Make sure bitstream is loaded!"

fpga: fft-fpga
	mkdir -p fft_result
	@echo "Running fft accelerator ..."
	./$<

# Clean up the directory before submissio
clean:
	@echo "Clean up output files"
	rm -rf fft-arm vivado_hls.log *.prj fft_result
	rm -rf fft-fpga
