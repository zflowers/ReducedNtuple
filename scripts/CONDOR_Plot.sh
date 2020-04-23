#To run: condor_submit scripts/CONDOR_Plot.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/ForCONDOR.sh 
getenv = True
priority = 10
use_x509userproxy = true
output = out_test.log
error = err_test.log
log = log_test.log
Requirements = (Machine != "red-node000.unl.edu")
queue
