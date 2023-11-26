// fft_tables.cpp
#include "fft.h"
#include <cmath>

double cos_lookup_table[SIZE2];
double sin_lookup_table[SIZE2];

void initialize_lookup_tables() {
    for (int i = 0; i < SIZE2; i++) {
        double angle = -6.283185307178 * i / SIZE;
        cos_lookup_table[i] = cos(angle);
        sin_lookup_table[i] = sin(angle);
    }
}
