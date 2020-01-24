#To run: condor_submit scripts/CONDOR_RSYNC.sh

universe = vanilla
#executable = /usr/bin/rsync
executable = /usr/bin/cp
getenv = True
priority = 10
use_x509userproxy = true
#Arguments = -hvrPt --remove-source-files /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/root/ /mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/ 
Arguments = -r /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/root/ /mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/ 
output = rsync_out.log
error = rsync_err.log
log = rsync_log.log
Requirements = (Machine != "red-node000.unl.edu")
queue
