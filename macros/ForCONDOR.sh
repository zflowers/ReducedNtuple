cd /home/t3-ku/z374f439/NANOAOD/CMSSW_10_2_9/src/
eval `scramv1 runtime -sh`
cd /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/

root -l 'run_Eff_Nano_Hist.cc("DoubleMu.root")' 
