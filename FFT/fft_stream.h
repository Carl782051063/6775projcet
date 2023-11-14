
#include "reverse.h"
#include "fft.h"

void fft_stage(int stage, DTYPE X_R[SIZE], DTYPE X_I[SIZE],
            DTYPE Out_R[SIZE], DTYPE Out_I[SIZE]);
            
void fft_streaming(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);