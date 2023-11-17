#include "reverse.h"
#include "fft.h"


void fft_stage(int stage, DTYPE X_R[SIZE], DTYPE X_I[SIZE],
            DTYPE Out_R[SIZE], DTYPE Out_I[SIZE]){
    int DFTpts = 1 << stage; // DFT = 2^stage = points in sub DFT
    int numBF = DFTpts / 2; // Butterfly WIDTHS in sub−DFT
    int step = SIZE >> stage;
    DTYPE k = 0;
    DTYPE e = −6.283185307178 / DFTpts;
    DTYPE a = 0.0;
    // Perform butterflies for j−th stage
butterfly loop:
    for (int j = 0; j < numBF; j++){
        DTYPE c = cos(a);
        DTYPE s = sin(a);
        a = a + e;
        // Compute butterflies that use same W**k
    dft loop:
        for (int i = j; i < SIZE; i += DFTpts){
            int i_lower = i + numBF; // index of lower point in butterfly
            DTYPE temp_R = X_R[i_lower] * c − X_I[i_lower] * s;
            DTYPE temp_I = X_I[i_lower] * c + X_R[i_lower] * s;
            Out_R[i_lower] = X_R[i] − temp_R;
            Out_I[i_lower] = X_I[i] − temp_I;
            Out_R[i] = X_R[i] + temp_R;
            Out_I[i] = X_I[i] + temp_I;
        }
        k += step;
    }
}

void fft_streaming(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
  #pragma HLS dataflow
  DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
  DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
  DTYPE Stage3_R[SIZE], Stage3_I[SIZE];

  bit_reverse(X_R, X_I, Stage1_R, Stage1_I);
  fft_stage(1,Stage1_R, Stage1_I, Stage2_R, Stage2_I);
  fft_stage(2,Stage2_R, Stage2_I, Stage3_R, Stage3_I);
  fft_stage(3,Stage3_R, Stage3_I, OUT_R, OUT_I);
}