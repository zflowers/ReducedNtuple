#To run: watch -n 60 scripts/watch.sh

#condor_submit /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/scripts/CONDOR_RSYNC.sh

#tail -q -f -n 5 /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/rsync_out.log

#du -sh /mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ 

du -sh /home/t3-ku/z374f439/

#find /mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ -type f | wc -l

condor_q -totals z374f439 
