#!/bin/bash
#To run: watch -n 60 scripts/Plot_watch.sh

#pic /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/Plot_log.log

#pic /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/err_*.log

#pic /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/out_*.log

#condor_q -totals z374f439 
condor_q z374f439 

#JOB_ID=$1
#JOB_ID="3512908.1"

#condor_tail -maxbytes 2000 $JOB_ID >> tail.txt
#condor_tail -maxbytes 2000 $JOB_ID

#condor_tail -stderr $JOB_ID

