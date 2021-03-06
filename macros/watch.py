import os

print("Checking if jobs finished")
complete = False
while complete is not True:
    os.system("condor_q $USER > watch.txt")
    os.system("condor_release $USER")
    os.system("sleep 60")
    with open('watch.txt') as watch:
        if 'Total for query: 0 jobs; 0 completed, 0 removed, 0 idle, 0 running, 0 held, 0 suspended' in watch.read():
            complete = True
os.system("echo \"Subject: Condor Jobs Finished\" > notify.txt")
os.system("echo \"Condor Jobs Have Finished Running\" >> notify.txt")
os.system("sendmail z374f439@ku.edu < notify.txt")
print("Finished Running Jobs")
