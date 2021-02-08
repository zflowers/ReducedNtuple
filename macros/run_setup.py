#!/usr/bin/env python
import os
import sys

argv_pos = 1
DO_HIST = 0
DO_EFF = 0
DO_HADD = 0
HADD_ONLY = 0
SPLIT = 1
safety_jobs = 100
HOLD = 50 #Number of times to check jobs before temp holding
NHOLD = 0
output_dir = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/"

print("Writing shell scripts")

list_cuts_hist = [
    "PreSelection",
]

list_cuts_eff = [
    "PreSelection",
    #"SingleElectrontriggerE1-NeleBronzeE1",
    #"SingleElectrontriggerE1-NeleSilverE1",
    #"SingleElectrontriggerE1-NeleGoldE1",
    "SingleElectrontriggerE1-NeleE1",
    #"SingleMuontriggerE1-NmuBronzeE1",
    #"SingleMuontriggerE1-NmuSilverE1",
    #"SingleMuontriggerE1-NmuGoldE1",
    "SingleMuontriggerE1-NmuE1",
    #"DoubleElectrontriggerE1-NeleBronzeE2",
    #"DoubleElectrontriggerE1-NeleSilverE2",
    #"DoubleElectrontriggerE1-NeleGoldE2",
    "DoubleElectrontriggerE1-NeleE2",
    #"DoubleMuontriggerE1-NmuBronzeE2",
    #"DoubleMuontriggerE1-NmuSilverE2",
    #"DoubleMuontriggerE1-NmuGoldE2",
    "DoubleMuontriggerE1-NmuE2",
    #"NeleBronzeE1",
    #"NeleSilverE1",
    #"NeleGoldE1",
    "NeleE1",
    #"NmuBronzeE1",
    #"NmuSilverE1",
    #"NmuGoldE1",
    "NmuE1",
    #"NeleBronzeE2",
    #"NeleSilverE2",
    #"NeleGoldE2",
    "NeleE2",
    #"NmuBronzeE2",
    #"NmuSilverE2",
    #"NmuGoldE2",
    "NmuE2",
    "HTlow",
    #"HTlow-SingleElectrontriggerE1-NeleBronzeE1",
    #"HTlow-SingleElectrontriggerE1-NeleSilverE1",
    #"HTlow-SingleElectrontriggerE1-NeleGoldE1",
    "HTlow-SingleElectrontriggerE1-NeleE1",
    #"HTlow-SingleMuontriggerE1-NmuBronzeE1",
    #"HTlow-SingleMuontriggerE1-NmuSilverE1",
    #"HTlow-SingleMuontriggerE1-NmuGoldE1",
    "HTlow-SingleMuontriggerE1-NmuE1",
    #"HTlow-DoubleElectrontriggerE1-NeleBronzeE2",
    #"HTlow-DoubleElectrontriggerE1-NeleSilverE2",
    #"HTlow-DoubleElectrontriggerE1-NeleGoldE2",
    "HTlow-DoubleElectrontriggerE1-NeleE2",
    #"HTlow-DoubleMuontriggerE1-NmuBronzeE2",
    #"HTlow-DoubleMuontriggerE1-NmuSilverE2",
    #"HTlow-DoubleMuontriggerE1-NmuGoldE2",
    "HTlow-DoubleMuontriggerE1-NmuE2",
    #"HTlow-NeleBronzeE1",
    #"HTlow-NeleSilverE1",
    #"HTlow-NeleGoldE1",
    "HTlow-NeleE1",
    #"HTlow-NmuBronzeE1",
    #"HTlow-NmuSilverE1",
    #"HTlow-NmuGoldE1",
    "HTlow-NmuE1",
    #"HTlow-NeleBronzeE2",
    #"HTlow-NeleSilverE2",
    #"HTlow-NeleGoldE2",
    "HTlow-NeleE2",
    #"HTlow-NmuBronzeE2",
    #"HTlow-NmuSilverE2",
    #"HTlow-NmuGoldE2",
    "HTlow-NmuE2",
    "HTmed",
    #"HTmed-SingleElectrontriggerE1-NeleBronzeE1",
    #"HTmed-SingleElectrontriggerE1-NeleSilverE1",
    #"HTmed-SingleElectrontriggerE1-NeleGoldE1",
    "HTmed-SingleElectrontriggerE1-NeleE1",
    #"HTmed-SingleMuontriggerE1-NmuBronzeE1",
    #"HTmed-SingleMuontriggerE1-NmuSilverE1",
    #"HTmed-SingleMuontriggerE1-NmuGoldE1",
    "HTmed-SingleMuontriggerE1-NmuE1",
    #"HTmed-DoubleElectrontriggerE1-NeleBronzeE2",
    #"HTmed-DoubleElectrontriggerE1-NeleSilverE2",
    #"HTmed-DoubleElectrontriggerE1-NeleGoldE2",
    "HTmed-DoubleElectrontriggerE1-NeleE2",
    #"HTmed-DoubleMuontriggerE1-NmuBronzeE2",
    #"HTmed-DoubleMuontriggerE1-NmuSilverE2",
    #"HTmed-DoubleMuontriggerE1-NmuGoldE2",
    "HTmed-DoubleMuontriggerE1-NmuE2",
    #"HTmed-NeleBronzeE1",
    #"HTmed-NeleSilverE1",
    #"HTmed-NeleGoldE1",
    "HTmed-NeleE1",
    #"HTmed-NmuBronzeE1",
    #"HTmed-NmuSilverE1",
    #"HTmed-NmuGoldE1",
    "HTmed-NmuE1",
    #"HTmed-NeleBronzeE2",
    #"HTmed-NeleSilverE2",
    #"HTmed-NeleGoldE2",
    "HTmed-NeleE2",
    #"HTmed-NmuBronzeE2",
    #"HTmed-NmuSilverE2",
    #"HTmed-NmuGoldE2",
    "HTmed-NmuE2",
    "HThigh",
    #"HThigh-SingleElectrontriggerE1-NeleBronzeE1",
    #"HThigh-SingleElectrontriggerE1-NeleSilverE1",
    #"HThigh-SingleElectrontriggerE1-NeleGoldE1",
    "HThigh-SingleElectrontriggerE1-NeleE1",
    #"HThigh-SingleMuontriggerE1-NmuBronzeE1",
    #"HThigh-SingleMuontriggerE1-NmuSilverE1",
    #"HThigh-SingleMuontriggerE1-NmuGoldE1",
    "HThigh-SingleMuontriggerE1-NmuE1",
    #"HThigh-DoubleElectrontriggerE1-NeleBronzeE2",
    #"HThigh-DoubleElectrontriggerE1-NeleSilverE2",
    #"HThigh-DoubleElectrontriggerE1-NeleGoldE2",
    "HThigh-DoubleElectrontriggerE1-NeleE2",
    #"HThigh-DoubleMuontriggerE1-NmuBronzeE2",
    #"HThigh-DoubleMuontriggerE1-NmuSilverE2",
    #"HThigh-DoubleMuontriggerE1-NmuGoldE2",
    "HThigh-DoubleMuontriggerE1-NmuE2",
    #"HThigh-NeleBronzeE1",
    #"HThigh-NeleSilverE1",
    #"HThigh-NeleGoldE1",
    "HThigh-NeleE1",
    #"HThigh-NmuBronzeE1",
    #"HThigh-NmuSilverE1",
    #"HThigh-NmuGoldE1",
    "HThigh-NmuE1",
    #"HThigh-NeleBronzeE2",
    #"HThigh-NeleSilverE2",
    #"HThigh-NeleGoldE2",
    "HThigh-NeleE2",
    #"HThigh-NmuBronzeE2",
    #"HThigh-NmuSilverE2",
    #"HThigh-NmuGoldE2",
    "HThigh-NmuE2",
    "eleHTlow",
    #"eleHTlow-SingleElectrontriggerE1-NeleBronzeE1",
    #"eleHTlow-SingleElectrontriggerE1-NeleSilverE1",
    #"eleHTlow-SingleElectrontriggerE1-NeleGoldE1",
    "eleHTlow-SingleElectrontriggerE1-NeleE1",
    #"eleHTlow-SingleMuontriggerE1-NmuBronzeE1",
    #"eleHTlow-SingleMuontriggerE1-NmuSilverE1",
    #"eleHTlow-SingleMuontriggerE1-NmuGoldE1",
    "eleHTlow-SingleMuontriggerE1-NmuE1",
    #"eleHTlow-DoubleElectrontriggerE1-NeleBronzeE2",
    #"eleHTlow-DoubleElectrontriggerE1-NeleSilverE2",
    #"eleHTlow-DoubleElectrontriggerE1-NeleGoldE2",
    "eleHTlow-DoubleElectrontriggerE1-NeleE2",
    #"eleHTlow-DoubleMuontriggerE1-NmuBronzeE2",
    #"eleHTlow-DoubleMuontriggerE1-NmuSilverE2",
    #"eleHTlow-DoubleMuontriggerE1-NmuGoldE2",
    "eleHTlow-DoubleMuontriggerE1-NmuE2",
    #"eleHTlow-NeleBronzeE1",
    #"eleHTlow-NeleSilverE1",
    #"eleHTlow-NeleGoldE1",
    "eleHTlow-NeleE1",
    #"eleHTlow-NmuBronzeE1",
    #"eleHTlow-NmuSilverE1",
    #"eleHTlow-NmuGoldE1",
    "eleHTlow-NmuE1",
    #"eleHTlow-NeleBronzeE2",
    #"eleHTlow-NeleSilverE2",
    #"eleHTlow-NeleGoldE2",
    "eleHTlow-NeleE2",
    #"eleHTlow-NmuBronzeE2",
    #"eleHTlow-NmuSilverE2",
    #"eleHTlow-NmuGoldE2",
    "eleHTlow-NmuE2",
    "eleHThigh",
    #"eleHThigh-SingleElectrontriggerE1-NeleBronzeE1",
    #"eleHThigh-SingleElectrontriggerE1-NeleSilverE1",
    #"eleHThigh-SingleElectrontriggerE1-NeleGoldE1",
    "eleHThigh-SingleElectrontriggerE1-NeleE1",
    #"eleHThigh-SingleMuontriggerE1-NmuBronzeE1",
    #"eleHThigh-SingleMuontriggerE1-NmuSilverE1",
    #"eleHThigh-SingleMuontriggerE1-NmuGoldE1",
    "eleHThigh-SingleMuontriggerE1-NmuE1",
    #"eleHThigh-DoubleElectrontriggerE1-NeleBronzeE2",
    #"eleHThigh-DoubleElectrontriggerE1-NeleSilverE2",
    #"eleHThigh-DoubleElectrontriggerE1-NeleGoldE2",
    "eleHThigh-DoubleElectrontriggerE1-NeleE2",
    #"eleHThigh-DoubleMuontriggerE1-NmuBronzeE2",
    #"eleHThigh-DoubleMuontriggerE1-NmuSilverE2",
    #"eleHThigh-DoubleMuontriggerE1-NmuGoldE2",
    "eleHThigh-DoubleMuontriggerE1-NmuE2",
    #"eleHThigh-NeleBronzeE1",
    #"eleHThigh-NeleSilverE1",
    #"eleHThigh-NeleGoldE1",
    "eleHThigh-NeleE1",
    #"eleHThigh-NmuBronzeE1",
    #"eleHThigh-NmuSilverE1",
    #"eleHThigh-NmuGoldE1",
    "eleHThigh-NmuE1",
    #"eleHThigh-NeleBronzeE2",
    #"eleHThigh-NeleSilverE2",
    #"eleHThigh-NeleGoldE2",
    "eleHThigh-NeleE2",
    #"eleHThigh-NmuBronzeE2",
    #"eleHThigh-NmuSilverE2",
    #"eleHThigh-NmuGoldE2",
    "eleHThigh-NmuE2",
]

#path where lists are stored
#can be gotten by running get_lists.py
list_path = "samples/NANO/Lists/"

list_tags_SingleMuon_2016 = [
    list_path+"Summer16_102X_Data_SingleMuon.list",
]

list_tags_SingleElectron_2016 = [
    list_path+"Summer16_102X_Data_SingleElectron.list",
]

list_tags_DoubleMuon_2016 = [
    list_path+"Summer16_102X_Data_DoubleMuon.list",
]

list_tags_DoubleElectron_2016 = [
    list_path+"Summer16_102X_Data_DoubleEG.list",
]

list_tags_TTJets_2016 = [
    list_path+"Summer16_102X_TTJets.list",
]

list_tags_Bkg_2016 = [
    list_path+"Summer16_102X_NoQCD.list",
]

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

list_tags_TTJets_2017 = [
    list_path+"Fall17_102X_TTJets.list",
]

list_tags_Test_2017 = [
    list_path+"Fall17_102X_Test.list",
]

list_tags_Bkg_2017 = [
    list_path+"Fall17_102X_NoQCD.list",
]

list_tags_SingleMuon_2018 = [
    list_path+"Autumn18_102X_Data_SingleMuon.list",
]

list_tags_SingleElectron_2018 = [
    list_path+"Autumn18_102X_Data_EGamma.list",
]

list_tags_DoubleMuon_2018 = [
    list_path+"Autumn18_102X_Data_DoubleMuon.list",
]

list_tags_DoubleElectron_2018 = [
    list_path+"Autumn18_102X_Data_EGamma.list",
]

list_tags_TTJets_2018 = [
    list_path+"Autumn18_102X_TTJets.list",
]

list_tags_Bkg_2018 = [
    list_path+"Autumn18_102X_NoQCD.list",
]


#master list of samples to run over
list_list_eff = [
    'SingleMuon_2016',list_tags_SingleMuon_2016,
    'SingleElectron_2016',list_tags_SingleElectron_2016,
    'DoubleMuon_2016',list_tags_DoubleMuon_2016,
    'DoubleElectron_2016',list_tags_DoubleElectron_2016,
    'Bkg_2016',list_tags_Bkg_2016,
    'SingleMuon_2017',list_tags_SingleMuon_2017,
    'SingleElectron_2017',list_tags_SingleElectron_2017,
    'DoubleMuon_2017',list_tags_DoubleMuon_2017,
    'DoubleElectron_2017',list_tags_DoubleElectron_2017,
    'Bkg_2017',list_tags_Bkg_2017,
    'SingleMuon_2018',list_tags_SingleMuon_2018,
    'SingleElectron_2018',list_tags_SingleElectron_2018,
    'DoubleMuon_2018',list_tags_DoubleMuon_2018,
    'DoubleElectron_2018',list_tags_DoubleElectron_2018,
    'Bkg_2018',list_tags_Bkg_2018,
#    'Test_2017',list_tags_Test_2017,
]

list_list_hist = [
    'Bkg_2017',list_tags_Bkg_2017,
]

def run_hadd(head_dir,list_dir):
    print("Running HADD")
    for cut in list_dir:
        cut_dir = head_dir+cut+"/"
        for subdir in os.listdir(cut_dir):
            for subsubdir in os.listdir(cut_dir+"/"+subdir):
                for subsubsubdir in os.listdir(cut_dir+"/"+subdir+"/"+subsubdir):
                    os.system("hadd -k "+cut_dir+subdir+"/"+subsubdir+"/"+subsubsubdir+".root "+cut_dir+"/"+subdir+"/"+subsubdir+"/"+subsubsubdir+"/*.root")
                    os.system("rm -rf "+cut_dir+subdir+"/"+subsubdir+"/"+subsubsubdir+"/")
                os.system("hadd -k "+cut_dir+subdir+"/"+subsubdir+".root "+cut_dir+"/"+subdir+"/"+subsubdir+"/*.root")
                os.system("rm -rf "+cut_dir+subdir+"/"+subsubdir+"/")
            os.system("hadd -k "+cut_dir+subdir+".root "+cut_dir+"/"+subdir+"/*.root")
            os.system("rm -rf "+cut_dir+subdir+"/")
        if DO_EFF:
            os.system("hadd -k "+head_dir+"Eff_output_"+cut+".root "+cut_dir+"*.root")
        if DO_HIST:
            os.system("hadd -k "+head_dir+"Hist_output_"+cut+".root "+cut_dir+"*.root")
        #os.system("rm -rf "+cut_dir)

      

def get_jobs():
    os.system("source ../scripts/Plot_watch.sh > watch.txt")
    os.system("sleep 5")
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
        output_dir = sys.argv[p+1]
        argv_pos += 2
    if '--only-hadd' in sys.argv:
        HADD_ONLY = 1
        argv_pos += 1
    

if(DO_EFF):
    list_cuts = list_cuts_eff
    list_list = list_list_eff
if(DO_HIST):
    list_cuts = list_cuts_hist
    list_list = list_list_hist

if(HADD_ONLY):
    if(DO_EFF):
        run_hadd(output_dir+"EFF/",list_cuts_eff)
        sys.exit(1)
    if(DO_HIST):
        run_hadd(output_dir+"HIST/",list_cuts_hist)
        sys.exit(1)

TOT_NJOBS = 0
NJOBS = 0
if SPLIT > safety_jobs:
    print("Safety Limit is larger than split!")
    print("No jobs will be submitted!")
    sys.exit(1)


current_tag = ''
for cut in list_cuts:
    for tag in list_list:
        if isinstance(tag,list):
            for list_tag in tag:
                NJOBS = get_jobs()+(SPLIT*sum(1 for line in open(list_tag)))
                while NJOBS > safety_jobs:
                    print("Hit safety limit")
                    print("Waiting for jobs to finish...")
                    NJOBS = get_jobs()+(SPLIT*sum(1 for line in open(list_tag)))
                    print("Trying to submit: "+str((SPLIT*sum(1 for line in open(list_tag))))+" jobs...")
                    os.system("sleep 60")
                    NHOLD+=1
                    if NHOLD == HOLD:
                        os.system("condor_hold $USER")
                        NHOLD = 0
                    if (SPLIT*sum(1 for line in open(list_tag))) > safety_jobs:
                        break
                TOT_NJOBS+=(SPLIT*sum(1 for line in open(list_tag)))
                if(DO_EFF):
                    os.system("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" -output "+output_dir+" -split "+str(SPLIT)+" --eff ")
                if(DO_HIST):
                    os.system("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" -output "+output_dir+" -split "+str(SPLIT)+" --hist ")
                NJOBS = int(get_jobs())+int(((SPLIT*sum(1 for line in open(list_tag)))))
                while NJOBS > safety_jobs:
                    print("Hit safety limit")
                    print("Waiting for jobs to finish...")
                    NJOBS = get_jobs()
                    os.system("sleep 60")
                    NHOLD+=1
                    if NHOLD == HOLD:
                        os.system("condor_hold $USER")
                        NHOLD = 0
                    
        else:
            current_tag = tag

print("Finished Submitting Jobs")
print("Submitted a Total of: "+str(TOT_NJOBS)+" Jobs")

if DO_HADD:
    print("Waiting for jobs to finish to run hadd")
    NJOBS = get_jobs()
    while NJOBS is not 0:
        NJOBS = get_jobs()
        os.system("sleep 60")
        NHOLD+=1
        if NHOLD == HOLD:
            os.system("condor_hold $USER")
            NHOLD = 0
    if(DO_EFF):
        run_hadd(output_dir+"EFF/",list_cuts_eff)
    if(DO_HIST):
        run_hadd(output_dir+"HIST/",list_cuts_hist)

print("Submitted a Total of: "+str(TOT_NJOBS)+" Jobs")
