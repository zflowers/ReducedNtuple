#To run: condor_submit scripts/CONDOR_Hist.sh

universe = vanilla
executable = /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Eff_Nano_Hist.x
#notify_user = z374f439@ku.edu
#notification = Complete
getenv = True
priority = 10
use_x509userproxy = true
request_memory = 1000
output = LOG_HIST/out_$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).log
error = LOG_HIST/err_$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).log
log = LOG_HIST/log_$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).log
Requirements = (Machine != "red-node000.unl.edu")
Arguments = "-cut=$(CUT) -tag=$(TAG) -dir=$(DIR) -filename=$(FILENAME) -num=$(NUM)"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
transfer_output_files = $(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root
transfer_output_remaps = "$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root = /mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/HIST/$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root"
queue
#queue CUT,TAG,DIR,FILENAME,NUM from /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/test.txt
#queue CUT,TAG,DIR,FILENAME,NUM from /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/setup.py |
