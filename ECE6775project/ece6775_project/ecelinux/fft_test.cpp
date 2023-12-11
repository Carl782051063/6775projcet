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
    bit14_t shift_idex=0;
    DTYPE temp=0;
    DTYPE max=0;
    bit_fixed_16_15 base_freq=0;
    std::vector<DTYPE> real_input;
    std::vector<DTYPE> input_imag;
    std::string line;
    // Open the real part text file for reading
    std::ifstream realFile("PCMdata_real.txt");
    // Open the imaginary part text file for reading
    std::ifstream imagFile("PCMdata_imag.txt");

    hls::stream<bit32_t>stream_in,stream_out;


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
            input_imag.push_back(value);
        }
    }
    imagFile.close();

    // Ensure both inputs are the same size
    if (real_input.size() != input_imag.size()) {
        std::cerr << "Error: The real and imaginary files have different lengths." << std::endl;
        return 0; // Exit with an error code
    }
  // Timer
    Timer timer("FFT SW");
    timer.start();
    // // Call fft function
     fft(real_input.data(), input_imag.data());
    std::cout << "FFT function has been called successfully!" << std::endl;
    for (size_t i = 0; i < real_input.size(); i++) {
        std::cout << "Index " << i << " ,freq:"<< freq[i] <<": ("
                  << real_input[i] << ", " << input_imag[i] << ")" << std::endl;
    }
    
    //Start Signal Processing
    std::cout << "Start signal processing!" << std::endl;
    // Bandpass filter filter keep freq component(lowbound - highbound)
    for(int j=0;j<SIZE/2;j++){
        if(freq[j]<lowbound||freq[j]>highbound){
            real_input[j]=0;
            real_input[SIZE-j-1]=0;
            input_imag[j]=0;
            input_imag[SIZE-j-1]=0;
        }
        else {
          // Calcualate Amplitude spectrum
          temp=(real_input[j]*real_input[j]+input_imag[j]*input_imag[j]);
              // Threshold filtering (amplitude lower than threshold)
            if(temp<threshold){
            real_input[j]=0;
            real_input[SIZE-j-1]=0;
            input_imag[j]=0;
            input_imag[SIZE-j-1]=0;   
            }
            //Find the base frequency component
            if(temp>max){
                max=temp;
                base_freq=freq[j];
                shift_idex=j;
            }
        }
    }
        std::cout << "shift_idex= " << shift_idex <<std::endl;
       // Spectral attenuation
for(int z=730; z<3330;z++){
       //#pragma HLS pipeline
       if(z<1030){
       real_input[z]= real_input[z]*factor1;
       input_imag[z]= input_imag[z]*factor1;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor1;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor1;    
        }
       else if(z<1430){
       real_input[z]= real_input[z]*factor2;
       input_imag[z]= input_imag[z]*factor2;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor2;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor2;    
        }
       else if(z<1830){
       real_input[z]= real_input[z]*factor3;
       input_imag[z]= input_imag[z]*factor3;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor3;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor3;    
        }
       else if(z<2330){
       real_input[z]= real_input[z]*factor4;
       input_imag[z]= input_imag[z]*factor4;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor4;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor4;    
        } 
       else if(z<2730){
       real_input[z]= real_input[z]*factor5;
       input_imag[z]= input_imag[z]*factor5;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor5;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor5;    
        }
        else{
       real_input[z]= real_input[z]*factor6;
       input_imag[z]= input_imag[z]*factor6;
       real_input[SIZE-z-1]=real_input[SIZE-z-1]*factor6;
       input_imag[SIZE-z-1]=input_imag[SIZE-z-1]*factor6;    
        }            
     }
        
     // Inverse fft
       for(int i=0; i < SIZE; i++){
         input_imag[i] = (-1)*input_imag[i];
       }
       fft(real_input.data(), input_imag.data());
   
       for(int i=0; i < SIZE; i++){
         input_imag[i] = (-1)*input_imag[i];
       }   
       for(int i=0; i < SIZE; i++){
         real_input[i] = real_input[i]/SIZE;
         input_imag[i] = input_imag[i]/SIZE;
       }
    
    // Open a file for writing
    std::ofstream outputFile("./fft_result/output.dat");

    if (outputFile.is_open()) {
        // Write the real and imaginary parts to the file
        for (size_t i = 0; i < real_input.size(); ++i) {
            outputFile << real_input[i] << " " << input_imag[i] << std::endl;
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
                  << real_input[i] << ", " << input_imag[i] << ")" << std::endl;
    }
    std::cout << "The Base Freqency of the input signal= " << base_freq <<" Hz"<<std::endl;
   timer.stop();
    return 0;
}
