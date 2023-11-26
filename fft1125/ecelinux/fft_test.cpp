#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "fft.h" // Make sure this path is correct for your fft.h file
#include "typedefs.h"
#include "timer.h"

int main() {
    bit_fixed_16_15 freq[SIZE];
    bit14 shift_idex=0;
    digit temp=0;
    digit max=0;
    bit_fixed_16_15 base_freq=0;
    std::vector<DTYPE> real_input;
    std::vector<DTYPE> imag_input;
    std::string line;
    // Open the real part text file for reading
    std::ifstream realFile("PCMdata_real.txt");
    // Open the imaginary part text file for reading
    std::ifstream imagFile("PCMdata_imag.txt");

    //Freq Array
    for(int i=0;i<SIZE/2;i++){
        freq[i]=(sample_freq*i)/SIZE;
        freq[SIZE-i-1]=(-1)*freq[i];
    }
    

    if (!realFile.is_open() || !imagFile.is_open()) {
        std::cerr << "Unable to open the files for reading." << std::endl;
        return 0; // Exit with an error code
    }

    // Read the real part from the file
    while (std::getline(realFile, line)) {
        std::istringstream iss(line);
        DTYPE value;
        if (iss >> value) {
            real_input.push_back(value);
        }
    }
    realFile.close();

    // Read the imaginary part from the file
    while (std::getline(imagFile, line)) {
        std::istringstream iss(line);
        DTYPE value;
        if (iss >> value) {
            imag_input.push_back(value);
        }
    }
    imagFile.close();

    // Ensure both inputs are the same size
    if (real_input.size() != imag_input.size()) {
        std::cerr << "Error: The real and imaginary files have different lengths." << std::endl;
        return 0; // Exit with an error code
    }

    // Call fft function
    fft(real_input.data(), imag_input.data());
    std::cout << "FFT function has been called successfully!" << std::endl;
    for (size_t i = 0; i < real_input.size(); i++) {
        std::cout << "Index " << i << " ,freq:"<< freq[i] <<": ("
                  << real_input[i] << ", " << imag_input[i] << ")" << std::endl;
    }
    

//    //Start Signal Processing
//    std::cout << "Start signal processing!" << std::endl;
//    // Bandpass filter filter keep freq component(lowbound - highbound)
//    for(int j=0;j<SIZE/2;j++){
//        if(freq[j]<lowbound||freq[j]>highbound){
//            real_input[j]=0;
//            real_input[SIZE-j-1]=0;
//            imag_input[j]=0;
//            imag_input[SIZE-j-1]=0;
//        }
//        else {
//          // Calcualate Amplitude spectrum
//          temp=(real_input[j]*real_input[j]+imag_input[j]*imag_input[j]);
//              // Threshold filtering (amplitude lower than threshold)
//            if(temp<threshold){
//            real_input[j]=0;
//            real_input[SIZE-j-1]=0;
//            imag_input[j]=0;
//            imag_input[SIZE-j-1]=0;   
//            }
//            //Find the base frequency component
//            if(temp>max){
//                max=temp;
//                base_freq=freq[j];
//                shift_idex=j;
//            }
//        }
//    }
//        std::cout << "shift_idex= " << shift_idex <<std::endl;
//       // Pitchshift modification        Move 120 point around base freq to low freq domian, {80Hz(index 110)-161Hz(index 230)} 
//       for(int z=110; z<230;z++){
//            real_input[z]= real_input[shift_idex-60]*pitchshift_factor;
//            imag_input[z]= imag_input[shift_idex-60]*pitchshift_factor;
//            real_input[SIZE-z-1]=real_input[shift_idex-60]*pitchshift_factor;
//            imag_input[SIZE-z-1]=imag_input[shift_idex-60]*pitchshift_factor;
//            shift_idex++;
//        }
        
     // Inverse fft
       for(int i=0; i < SIZE; i++){
         imag_input[i] = (-1)*imag_input[i];
       }
       fft(real_input.data(), imag_input.data());
   
       for(int i=0; i < SIZE; i++){
         imag_input[i] = (-1)*imag_input[i];
       }   
       for(int i=0; i < SIZE; i++){
         real_input[i] = real_input[i]/SIZE;
         imag_input[i] = imag_input[i]/SIZE;
       }
    
    // Open a file for writing
    std::ofstream outputFile("./fft_result/output.dat");

    if (outputFile.is_open()) {
        // Write the real and imaginary parts to the file
        for (size_t i = 0; i < real_input.size(); ++i) {
            outputFile << real_input[i] << " " << imag_input[i] << std::endl;
        }

        // Close the file
        outputFile.close();
        std::cout << "Data has been written to output.dat" << std::endl;
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
    // Print the results to the console
    std::cout << "Inverse FFT function has been called successfully!" << std::endl;
    for (size_t i = 0; i < real_input.size(); i++) {
        std::cout << "Index " << i <<": ("
                  << real_input[i] << ", " << imag_input[i] << ")" << std::endl;
    }
    std::cout << "The Base Freqency of the input signal= " << base_freq <<" Hz"<<std::endl;
 
    return 0;
}