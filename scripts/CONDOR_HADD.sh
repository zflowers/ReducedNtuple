#To run: condor_submit scripts/CONDOR_HADD.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/scripts/DO_hadd_MET.sh 
getenv = True
priority = 10
use_x509userproxy = true
output = rsync_out.log
error = rsync_err.log
log = rsync_log.log
Requirements = (Machine != "red-node000.unl.edu")
queue
