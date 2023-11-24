//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H


#ifndef TOT_WIDTH
#define TOT_WIDTH 16
#endif

#ifndef INT_WIDTH
#define INT_WIDTH 15
#endif

#include "ap_int.h"
#include "ap_fixed.h"
typedef ap_uint<4> bit4;
typedef ap_uint<6> bit6;
typedef ap_uint<14> bit14;
typedef ap_uint<32> bit32;
typedef ap_uint<64> bit64;
typedef ap_uint<49> digit;
typedef ap_fixed<TOT_WIDTH, INT_WIDTH> bit_fixed;
#endif
