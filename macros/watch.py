import os

print("Checking if jobs finished")
complete = False
while complete is not True:
    os.system("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/scripts/Plot_watch.sh > /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/watch.txt")
    os.system("sleep 5")
    with open('watch.txt') as watch:
        if 'Total for query: 0 jobs; 0 completed, 0 removed, 0 idle, 0 running, 0 held, 0 suspended' in watch.read():
            complete = True
os.system("rm watch.txt")
print("Finished Running Jobs")
