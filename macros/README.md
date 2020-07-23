To run:

root -l -b run_Eff_Nano_Hist.cc

To make plots with CONDOR (Almost Only Option)

condor_submit ../scripts/CONDOR_Plot.sh Cuts/cuts_Example.txt

After jobs finish do

./Plotter Cuts/cuts_Example.txt 
