#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the digit recongnition design.
#
# @desc: This script launches a batch of simulation & synthesis runs
# to quickly explore different K parameters.
#
# 1. The user specifies the list of K values.
# 2. Useful simulation & synthesis stats are consolidated into ./result/result.csv

#------------------------------------------------------
# Remove old result file
#------------------------------------------------------
set filename "output.csv"
file delete -force "./fft_result/${filename}"

#------------------------------------------------------
# You can specify a set of parameter K to explore.
#------------------------------------------------------
#set value_k { 3 }
#------------------------------------------------------
# run batch experiments
#------------------------------------------------------
#foreach { K } $value_k {

# Define the bitwidth macros from CFLAGs
#set CFLAGS "-DK_CONST=${K}"

# Project name
set hls_prj fft.prj

# Open/reset the project
open_project ${hls_prj} -reset
# Top function of the design is "digitrec"
set_top fft

# Add design and testbench files
add_files fft.cpp 
add_files -tb fft_test.cpp 
add_files -tb PCMdata_imag.txt
add_files -tb PCMdata_real.txt


open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10



# Do not inline update_knn and knn_vote functions 
#set_directive_inline -off update_knn
#et_directive_inline -off knn_vote
### You can add your own directives here ###
#pragma HLS unroll
#set_directive_unroll digitrec/LOOP_dig_1    
#pragma HLS array_partition variable=knn_set block factor=10
#set_directive_array_partition digitrec knn_set


# Simulate the C++ design
csim_design
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
#set argv [list $filename $hls_prj]
#set argc 2
#source "./script/collect_result.tcl"
#}
exit
