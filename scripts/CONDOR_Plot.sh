#To run: condor_submit scripts/CONDOR_Plot.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/For_CONDOR.sh 
getenv = True
priority = 10
use_x509userproxy = true
output = Plot_out.log
error = Plot_err.log
log = Plot_log.log
Requirements = (Machine != "red-node000.unl.edu")
queue
