#include <iostream>
#include <fstream>
#include <string>
#include "fft.h"

int main() {

    DTYPE real_input[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DTYPE imag_input[SIZE] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    // Call fft function
    fft(real_input, imag_input);

    // Open a file for writing
    std::ofstream outputFile("./fft_result/output.dat");

    if (outputFile.is_open()) {
        // Write the real and imaginary parts to the file
        for (int i = 0; i < SIZE; ++i) {
            outputFile << real_input[i] << " " << imag_input[i] << std::endl;
        }

        // Close the file
        outputFile.close();
        std::cout << "Data has been written to output.txt" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }

    // Print the results to the console
    for (int i = 0; i < SIZE; i++) {
        std::cout << "Index " << i << ": ("
                  << real_input[i] << ", " << imag_input[i] << ")" << std::endl;
    }

    std::cout << "Have called the function !" << std::endl;

    return 0;
}
