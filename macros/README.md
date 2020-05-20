To run:

root -l 'run_Eff_Nano_Hist.cc("output_filename.root")'

To make plots with CONDOR

condor_submit ../scripts/CONDOR_Plot.sh

Note that running in batch mode (condor or -b) does not allow saving of plots
