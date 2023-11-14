

#define FFT_BITS 10            // Number of bits of FFT, i.e., log(1024)
#define SIZE 1024                // SIZE OF FFT
#define SIZE2 SIZE >> 1 // SIZE/2
#define DTYPE int


void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);