#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/jt842/fpga_f/fft1130work/ecelinux/fft_test.prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}
