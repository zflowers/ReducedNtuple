To run:

root -l -b run_Eff_Nano_Hist.cc

To make plots with CONDOR (Almost Only Option)
Make sure you define what cuts you need (see .sh file)

condor_submit ../scripts/CONDOR_Plot.sh

After jobs finish do

./Plotter.x Cuts/cuts_Example.txt 

For local tests:

./run_Eff_Nano_Eff.x -x=MET -cut=PreSelection -oFile=Test

With New Splitting Example:

python run_setup.py -split 10 --eff --hadd -safety 100 -o $PWD/
