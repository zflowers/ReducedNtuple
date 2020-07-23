#To run: condor_submit scripts/CONDOR_Plot.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/run_Eff_Nano.x
notify_user = z374f439@ku.edu
notification = Complete
getenv = True
priority = 10
use_x509userproxy = true
request_memory = 8000
output = out_test.log
error = err_test.log
log = log_test.log
Requirements = (Machine != "red-node000.unl.edu")
queue
