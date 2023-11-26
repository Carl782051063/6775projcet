#include "typedefs.h"

#define FFT_BITS 15            // Number of bits of FFT, i.e., log(1024)
#define SIZE 32768                // SIZE OF FFT
#define SIZE2 SIZE >> 1 // SIZE/2
#define DTYPE bit_fixed
#define M 15
#define sample_freq 24000.0 
#define pitchshift_factor 2
#define threshold 1.0
#define lowbound 20
#define highbound 4520

unsigned int reverse_bits(unsigned int input);
void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
