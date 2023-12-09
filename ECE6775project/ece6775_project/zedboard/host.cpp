#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>
#include "fft.h"
#include "typedefs.h"
#include "timer.h"

//--------------------------------------
// main function
//--------------------------------------

/* Host Code */
union u_1 { float fval; int32_t ival; };
int nbytes;
//u.fval = 1.01;
//int iv = u.ival; // then send "iv" to the FIFO

/* On the FPGA DUT side, you also need to create a union and do the opposite thing */

int main(int argc, char **argv) {
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0)) {
    fprintf(stderr, "Failed to open Xillybus device channels\n");
    return -1;
  }

  // Number of test instances
  const int N = 16384;

  // Arrays to store test data and expected results
  int32_t inputs_real[N];   
  int32_t inputs_imag[N];   
  float result_real[N];
  float result_imag[N];
  //--------------------------------------------------------------------
  // Read real part of data from the input file into two arrays
  //--------------------------------------------------------------------
 // Read input file for the testing set
  std::string line_real;
  std::ifstream myfile_real("PCMdata_real.txt");

  if (!myfile_real.is_open()) {
    std::cout << "Unable to open real file for the testing set!" << std::endl;
    return 1;
  }     
  for (int i = 0; i < N; ++i) {
    assert(std::getline(myfile_real, line_real));
    // convert to float
    float input_real = std::stof(line_real);
    
    u_1 u1 = {.fval = input_real};
    //using union to convert from float to int
    //in_1.fval = input_real;
    int32_t int_input_real = u1.ival;
    // // Store the digits into arrays
     inputs_real[i] = int_input_real; //32 bits
  }
  //--------------------------------------------------------------------
  // Read imag part of data from the input file into two arrays
  //--------------------------------------------------------------------
 // Read input file for the testing set
  std::string line_imag;
  std::ifstream myfile_imag("PCMdata_imag.txt");

  if (!myfile_imag.is_open()) {
    std::cout << "Unable to open imag file for the testing set!" << std::endl;
    return 1;
  }


  for (int i = 0; i < N; ++i) {
    assert(std::getline(myfile_imag, line_imag));
    // convert to float
    float input_imag = std::stof(line_imag);
    u_1 u2 = {.fval = input_imag};
    //using union to convert from float to int
    //in_2.fval = input_imag;
    int32_t int_input_imag = u2.ival;
    // Store the digits into arrays
    inputs_imag[i] = int_input_imag; //32 bits 
  }
  // Timer
  Timer timer("FFT FPGA");
  timer.start();
  //--------------------------------------------------------------------
  // Add your code here to communicate with the hardware module
  //--------------------------------------------------------------------
  for (int i = 0; i < N; ++i) {
    
  
    // Convert fixed-point to int64
    int32_t input_real_in = inputs_real[i];
    int32_t input_imag_in = inputs_imag[i];
    // Send bytes through the write channel
    // and assert that the right number of bytes were sent
    nbytes = write (fdw, (void*)&input_real_in, sizeof(input_real_in));
    assert (nbytes == sizeof(input_real_in));
    nbytes = write (fdw, (void*)&input_imag_in, sizeof(input_imag_in));
    assert (nbytes == sizeof(input_imag_in));

  }
  for (int i = 0; i < N; ++i) {
    // Receive bytes through the read channel
    // and assert that the right number of bytes were recieved
    int32_t real_out;
    int32_t imag_out;

    nbytes = read (fdr, (void*)&real_out, sizeof(real_out));
    assert (nbytes == sizeof(real_out));

    nbytes = read (fdr, (void*)&imag_out, sizeof(imag_out));
    assert (nbytes == sizeof(imag_out));
  
  
    // Convert int to float
    u_1 u3 = {.ival = real_out};
    u_1 u4 = {.ival = imag_out};
    float out_real_out = u3.fval;
    float out_imag_out = u4.fval;

    result_real[i] = out_real_out;
    result_imag[i] = out_imag_out;    
  }
  timer.stop();
   // Open a file for writing
    std::ofstream outputFile("./fft_result/output.dat");

    if (outputFile.is_open()) {
        // Write the real and imaginary parts to the file
        for (size_t i = 0; i < N; ++i) {
            outputFile <<  std::to_string(result_real[i]) << " " << std::to_string(result_imag[i]) << std::endl;
        }

        // Close the file
        outputFile.close();
        std::cout << "Data has been written to output.dat" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
            // Close the file
        outputFile.close();


  // Close input file for the testing set
  myfile_real.close();
  myfile_imag.close();

  return 0;
}
