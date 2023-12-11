#include "typedefs.h"
#include <hls_stream.h>

#define FFT_BITS 14            // Number of bits of FFT, i.e., log(1024)
#define SIZE 16384                // SIZE OF FFT
#define SIZE2 SIZE >> 1 // SIZE/2
#define DTYPE float
#define M 14
#define sample_freq 12000.0 
#define threshold 1.0
#define lowbound 20
#define highbound 2420
#define factor1 0.25
#define factor2 0.1
#define factor3 0.05
#define factor4 0.03
#define factor5 0.015
#define factor6 0.001

unsigned int reverse_bits(unsigned int input);
void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
// Top function for synthesis
void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out);
