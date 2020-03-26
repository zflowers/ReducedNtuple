#To run: condor_submit scripts/CONDOR_Plot.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/ForCONDOR.sh 
getenv = True
priority = 10
use_x509userproxy = true
output = out_DoubleMuTrigBronzeNoSOS.log
error = err_DoubleMuTrigBronzeNoSOS.log
log = log_DoubleMuTrigBronzeNoSOS.log
Requirements = (Machine != "red-node000.unl.edu")
queue
