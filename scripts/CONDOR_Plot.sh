#To run: condor_submit scripts/CONDOR_Plot.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/run_Eff_Nano_Eff.x
notify_user = z374f439@ku.edu
notification = Complete
getenv = True
priority = 10
use_x509userproxy = true
request_memory = 24000
output = out_eff_test_$(CUT).log
error = err_eff_$(CUT).log
log = log_eff_$(CUT).log
Requirements = (Machine != "red-node000.unl.edu")
Arguments = "-x=MET -cut=$(CUT)"
#Arguments = "-x=MET -cut=$(CUT) --scale"
#Arguments = "-x=MET -cut=$(CUT) --scale -oFile=NoLowHT"
queue CUT from /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Cuts/NoCuts.txt
