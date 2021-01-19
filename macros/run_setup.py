#!/usr/bin/env python
import os
import sys

list_cuts = [
    "SingleElectrontriggerE1-NeleBronzeE1",
#    "SingleElectrontriggerE1-NeleSilverE1",
#    "SingleElectrontriggerE1-NeleGoldE1",
#    "SingleElectrontriggerE1-NeleE1",
#    "SingleMuontriggerE1-NmuBronzeE1",
#    "SingleMuontriggerE1-NmuSilverE1",
#    "SingleMuontriggerE1-NmuGoldE1",
#    "SingleMuontriggerE1-NmuE1",
#    "DoubleElectrontriggerE1-NeleBronzeE2",
#    "DoubleElectrontriggerE1-NeleSilverE2",
#    "DoubleElectrontriggerE1-NeleGoldE2",
#    "DoubleElectrontriggerE1-NeleE2",
#    "DoubleMuontriggerE1-NmuBronzeE2",
#    "DoubleMuontriggerE1-NmuSilverE2",
#    "DoubleMuontriggerE1-NmuGoldE2",
#    "DoubleMuontriggerE1-NmuE2",
#    "NeleBronzeE1",
#    "NeleSilverE1",
#    "NeleGoldE1",
#    "NeleE1",
#    "NmuBronzeE1",
#    "NmuSilverE1",
#    "NmuGoldE1",
#    "NmuE1",
#    "NeleBronzeE2",
#    "NeleSilverE2",
#    "NeleGoldE2",
#    "NeleE2",
#    "NmuBronzeE2",
#    "NmuSilverE2",
#    "NmuGoldE2",
#    "NmuE2",
]

print("Writing shell scripts")

#path where lists are stored
#can be gotten by running get_lists.py
list_path = "samples/NANO/Lists/"

list_tags_SingleMuon_2017 = [
    list_path+"Fall17_102X_Data_SingleMuon.list",
]

list_tags_SingleElectron_2017 = [
    list_path+"Fall17_102X_Data_SingleElectron.list",
]

list_tags_DoubleMuon_2017 = [
    list_path+"Fall17_102X_Data_DoubleMuon.list",
]

list_tags_DoubleElectron_2017 = [
    list_path+"Fall17_102X_Data_DoubleEG.list",
]

list_tags_Bkg_2017 = [
    list_path+"Fall17_102X_SubBkg.list",
]


#master list of samples to run over
list_list = [
    'SingleMuon_2017',list_tags_SingleMuon_2017,
    'SingleElectron_2017',list_tags_SingleElectron_2017,
    'DoubleMuon_2017',list_tags_DoubleMuon_2017,
    'DoubleElectron_2017',list_tags_DoubleElectron_2017,
    'Bkg_2017',list_tags_Bkg_2017,
]


def run_hadd(head_dir):
    print("Running HADD")
    for cut in list_cuts:
        cut_dir = head_dir+cut+"/"
        for subdir in os.listdir(cut_dir):
            for subsubdir in os.listdir(cut_dir+"/"+subdir):
                for subsubsubdir in os.listdir(cut_dir+"/"+subdir+"/"+subsubdir):
                    os.system("hadd -k "+cut_dir+subdir+"/"+subsubdir+"/"+subsubsubdir+".root "+cut_dir+"/"+subdir+"/"+subsubdir+"/"+subsubsubdir+"/*.root")
                os.system("hadd -k "+cut_dir+subdir+"/"+subsubdir+".root "+cut_dir+"/"+subdir+"/"+subsubdir+"/*.root")
            os.system("hadd -k "+cut_dir+subdir+".root "+cut_dir+"/"+subdir+"/*.root")
        os.system("hadd -k "+head_dir+"Eff_output_"+cut+".root "+cut_dir+"*.root")
      

def get_jobs():
    os.system("source ../scripts/Plot_watch.sh > watch.txt")
    os.system("sleep 3")
    watch_file = open("watch.txt","r")
    for line in watch_file:
        watch_jobs = line.split(',')
        for phrase in watch_jobs:
            if 'query' in phrase:
                words = phrase.split()
                return int(words[3])
    os.system("rm watch.txt")


if __name__ == "__main__":
    if not len(sys.argv) > 1 or '-h' in sys.argv or '--help' in sys.argv:
        print "Usage: %s -split n [--eff] [--hist]" % sys.argv[0]
        print
        sys.exit(1)

    argv_pos = 1
    DO_HIST = 0
    DO_EFF = 0
    DO_HADD = 0
    SPLIT = 1
    safety_jobs = 0
    output_dir = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/"
  
    if '-split' in sys.argv:
        p = sys.argv.index('-split')
        SPLIT = int(sys.argv[p+1])
        argv_pos += 2
    if '--eff' in sys.argv:
        DO_EFF = 1
        argv_pos += 1
    if '--hist' in sys.argv:
        DO_HIST = 1
        argv_pos += 1
    if '--hadd' in sys.argv:
        DO_HADD = 1
        argv_pos += 1
    if '-safety' in sys.argv:
        p = sys.argv.index('-safety')
        safety_jobs = int(sys.argv[p+1])
        argv_pos += 2
    if '-o' in sys.argv:
        p = sys.argv.index('-o')
        output_dir = int(sys.argv[p+1])
        argv_pos += 2


TOT_NJOBS = 0
NJOBS = 0
if SPLIT > safety_jobs:
    print("Safety Limit is larger than split!")
    print("No jobs will be submitted!")
    sys.exit(1)

#run python
current_tag = ''
for cut in list_cuts:
    for tag in list_list:
        if isinstance(tag,list):
            for list_tag in tag:
                NJOBS = get_jobs()+SPLIT
                while NJOBS > safety_jobs:
                    print("Hit safety limit")
                    print("Waiting for jobs to finish...")
                    NJOBS = get_jobs()+SPLIT
                TOT_NJOBS+=(SPLIT*sum(1 for line in open(list_tag)))
                if(DO_EFF):
                    os.system("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" -output "+output_dir+" -split "+str(SPLIT)+" --eff ")
                if(DO_HIST):
                    os.system("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" -output "+output_dir+" -split "+str(SPLIT)+" --hist ")
        else:
            current_tag = tag

print("Finished Submitting Jobs")
print("Submitted a Total of: "+str(TOT_NJOBS)+" Jobs")

if get_jobs() == 0 and DO_HADD:
    run_hadd(output_dir)

