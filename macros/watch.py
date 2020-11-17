import os

print("Checking if jobs finished")
complete = False
while complete is not True:
    os.system("/stash/user/zflowers/CMSSW_10_2_20_UL/src/ReducedNtuple/scripts/Plot_watch.sh > /stash/user/zflowers/CMSSW_10_2_20_UL/src/ReducedNtuple/macros/watch.txt")
    os.system("sleep 60")
    with open('watch.txt') as watch:
        if 'Total for query: 0 jobs; 0 completed, 0 removed, 0 idle, 0 running, 0 held, 0 suspended' in watch.read():
            complete = True
os.system("rm watch.txt")
os.system("sendmail z374f439@ku.edu < notify.txt")
print("Finished Running Jobs")
