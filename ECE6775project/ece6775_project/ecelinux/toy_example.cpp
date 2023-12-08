#include "ap_int.h"
#include "hls_stream.h"
#include <cstdint>
#include <iostream>

typedef ap_uint<32> bit32_t;

// The union type is the trick to the conversion
union streamVal {
  float fl;
  uint32_t u32;
};

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out) {
  // Let's add 1.1 to the float value
  // First pack the ap_uint into 32b ints
  uint32_t cint = strm_in.read();
  // Init our union
  streamVal input = {.u32 = cint};
  // Add as float type
  input.fl = input.fl + 1.1;

  // Write out the 32b value with implicit conversion to ap_uint
  strm_out.write(input.u32);
}

int main() {

  // Floats should be 32b on the platform
  assert(sizeof(float) == sizeof(uint32_t));

  hls::stream<bit32_t> strm_in, strm_out;
  float myFloats[5] = {1.3, 5.0002, 254.2351, 6479.21, 4567.7};

  for (int i = 0; i < 5; ++i) {

    // Converting input float type to the 32b stream
    streamVal input = {.fl = myFloats[i]};
    strm_in.write(input.u32);

    // Run "add + 1.1 as float"
    dut(strm_in, strm_out);

    // Convert 32b stream to output float type
    uint32_t output = strm_out.read();
    streamVal outputVal = {.u32 = output};

    // Check that answer is close enough
    if (fabs(outputVal.fl - (myFloats[i] + 1.1)) > 0.0001) {
      std::cout << "Answer " << i << " incorrect by a difference of "
                << std::to_string(fabs(outputVal.fl - (myFloats[i] + 1.1)))
                << std::endl;
      return 1;
    }
  }

  std::cout << "SUCCESS\n";
  return 0;
}
