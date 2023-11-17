//=========================================================================
// testbench.cpp
//=========================================================================
// @brief: testbench for k-nearest-neighbor digit recongnition application

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "fft.h"

// using namespace std;

int main() {
  // Output file that saves the test bench results
  std::ofstream outfile;
  outfile.open("out.dat");

  // Read input file for the testing set
 
  std::ifstream myfile("data/testing_set.dat");
  std::vector<DTYPE> real_array;
  DTYPE value;

  if (myfile.is_open()) {

      while (myfile >> value) {
          real_array.push_back(value);
      }

      myfile.close();

      
  } else{
    std::cout << "Unable to open file for the testing set 0 !" << std::endl;
  }

  std::ifstream myfile_2("data/testing_set_0.dat");
  std::vector<DTYPE> image_array;
  DTYPE value_i;

  if (myfile_2.is_open()) {

      while (myfile_2 >> value_i) {
          image_array.push_back(value_i);
      }

      myfile_2.close();

  } else{
    std::cout << "Unable to open file for the testing set 1!" << std::endl;
  }
  // Call design under test (DUT)
      fft(real_array.data(), image_array.data());
  // Close output file
  outfile.close();

  return 0;
}