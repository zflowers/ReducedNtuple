#To run: condor_submit scripts/CONDOR_HADD.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/scripts/DO_hadd_MET.sh 
getenv = True
priority = 10
use_x509userproxy = true
output = hadd_out.log
error = hadd_err.log
log = hadd_log.log
Requirements = (Machine != "red-node000.unl.edu")
queue
