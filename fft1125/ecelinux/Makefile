# Extract Vivado HLS include path
XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
VHLS_INC=$(XILINX_VIVADO)/include
# Specify compilation flags
CFLAGS=-g -I${VHLS_INC}

# Define the source files
SOURCES = fft.cpp fft_test.cpp

# Define the object files
OBJECTS = $(SOURCES:.cpp=.o)

# Specify the name of the output executable
EXECUTABLE = fft_test

# Main target: build the fft_test executable
$(EXECUTABLE): $(OBJECTS)
	g++ ${CFLAGS} $^ -o $@ -lrt

# Rule to build object files from source files
%.o: %.cpp
	g++ ${CFLAGS} -c $< -o $@

# PHONY targets
.PHONY: all clean fft-sw bitstream

# Target to build all and run fft_test (default)
all: $(EXECUTABLE)
	./$(EXECUTABLE)

	
# Run the fft_test program
fft-sw: $(EXECUTABLE)
	@echo "Running fft sim..."
	mkdir -p fft_result
	./$(EXECUTABLE) | tee $@

xillydemo.bit:
	@echo "=================================================================" 
	@echo "Synthesizing bnn and creating bitstream with $(TCL_SCRIPT)..."
	@echo "=================================================================" 
	$(XIL_HLS) -f $(TCL_SCRIPT)
	source $(XILINX_VIVADO)/settings64.sh; ./run_bitstream.sh

bitstream: xillydemo.bit
	@echo "Bitstream saved to $<"

# Clean up the directory
clean:
	@echo "Clean up output files"
	rm -f $(EXECUTABLE) $(OBJECTS) 
	rm -rf ./fft_result
	rm -rf fft-sw
	rm -rf fft.prj
	
