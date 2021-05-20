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
RUN_JOBS = 0 #Number of currently running jobs
output_dir = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/"

print("Writing shell scripts")

list_cuts_hist = [
    "PreSelection",
    "HEM_Veto",
    "EventFilter-E1",
    "EventFilter-E0",
    "HEM_Veto--EventFilter-E1",
    "HEM_Veto--EventFilter-E0",
]

list_cuts_eff = [
    "Clean--HT-Le600--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HEM_Veto--HT-Le600--SingleElectrontrigger-E1--Nele-E1",
    "HEM_Veto--HT-Le600--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HT-Le600--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HEM_Veto--HT-Le600--SingleMuontrigger-E1--Nmu-E1",
    "HEM_Veto--HT-Le600--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HEM_Veto--HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",
    "HEM_Veto--HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HEM_Veto--HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",
    "HEM_Veto--HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HT-Ge750--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HEM_Veto--HT-Ge750--SingleElectrontrigger-E1--Nele-E1",
    "HEM_Veto--HT-Ge750--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HT-Ge750--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HEM_Veto--HT-Ge750--SingleMuontrigger-E1--Nmu-E1",
    "HEM_Veto--HT-Ge750--SingleMuontrigger-E1--Nmu-E1",
    "Clean--SingleMuontrigger-E1--Nmu-E1",
    "Clean--HEM_Veto--SingleMuontrigger-E1--Nmu-E1",
    "HEM_Veto--SingleMuontrigger-E1--Nmu-E1",
    "Clean--SingleElectrontrigger-E1--Nele-E1",
    "Clean--HEM_Veto--SingleElectrontrigger-E1--Nele-E1",
    "HEM_Veto--SingleElectrontrigger-E1--Nele-E1",


    #"PreSelection",
    #"Nlep-E0",
    #"Njet_S-E0",
    #"Njet_S-E1",
    #"Njet_S-Ge2",
    #"Njet_S-E0--Nlep-E0",
    #"Njet_S-E1--Nlep-E0",
    #"Njet_S-Ge2--Nlep-E0",
    #"Njet_S-E0--SingleElectrontrigger-E1--NeleBronze-E1",
    #"Njet_S-E0--SingleElectrontrigger-E1--NeleSilver-E1",
    #"Njet_S-E0--SingleElectrontrigger-E1--NeleGold-E1",
    #"Njet_S-E1--SingleElectrontrigger-E1--NeleBronze-E1",
    #"Njet_S-E1--SingleElectrontrigger-E1--NeleSilver-E1",
    #"Njet_S-E1--SingleElectrontrigger-E1--NeleGold-E1",
    #"Njet_S-Ge2--SingleElectrontrigger-E1--NeleBronze-E1",
    #"Njet_S-Ge2--SingleElectrontrigger-E1--NeleSilver-E1",
    #"Njet_S-Ge2--SingleElectrontrigger-E1--NeleGold-E1",
    #"Njet_S-E0--SingleElectrontrigger-E1--Nele-E1",
    #"Njet_S-E1--SingleElectrontrigger-E1--Nele-E1",
    #"Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1",
    #"Njet_S-E0--SingleMuontrigger-E1--Nmu-E1",
    #"Njet_S-E1--SingleMuontrigger-E1--Nmu-E1",
    #"Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1",
    #"Njet_S-E0--SingleMuontrigger-E1--NmuBronze-E1",
    #"Njet_S-E0--SingleMuontrigger-E1--NmuSilver-E1",
    #"Njet_S-E0--SingleMuontrigger-E1--NmuGold-E1",
    #"Njet_S-E1--SingleMuontrigger-E1--NmuBronze-E1",
    #"Njet_S-E1--SingleMuontrigger-E1--NmuSilver-E1",
    #"Njet_S-E1--SingleMuontrigger-E1--NmuGold-E1",
    #"Njet_S-Ge2--SingleMuontrigger-E1--NmuBronze-E1",
    #"Njet_S-Ge2--SingleMuontrigger-E1--NmuSilver-E1",
    #"Njet_S-Ge2--SingleMuontrigger-E1--NmuGold-E1",
    #"EMutrigger-E1--Nmu-E1--Nele-E1",
    #"SingleElectrontrigger-E1--Nele-E1",
    #"SingleElectrontrigger-E1--NeleBronze-E1",
    #"SingleElectrontrigger-E1--NeleSilver-E1",
    #"SingleElectrontrigger-E1--NeleGold-E1",
    #"SingleMuontrigger-E1--Nmu-E1",
    #"SingleMuontrigger-E1--NmuBronze-E1",
    #"SingleMuontrigger-E1--NmuSilver-E1",
    #"SingleMuontrigger-E1--NmuGold-E1",
    #"DoubleElectrontrigger-E1--Nele-E2",
    #"DoubleMuontrigger-E1--Nmu-E2",
#HT Lowest Bin
    #"HT-Le600--Nlep-E0",
    #"HT-Le600--Njet_S-E0",
    #"HT-Le600--Njet_S-E1",
    #"HT-Le600--Njet_S-Ge2",
    #"HT-Le600--Njet_S-E0--Nlep-E0",
    #"HT-Le600--Njet_S-E1--Nlep-E0",
    #"HT-Le600--Njet_S-Ge2--Nlep-E0",
    #"HT-Le600--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Le600--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Le600--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Le600--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Le600--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Le600--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Le600--EMutrigger-E1--Nmu-E1--Nele-E1",
    #"HT-Le600--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Le600--SingleElectrontrigger-E1--NeleBronze-E1",
    #"HT-Le600--SingleElectrontrigger-E1--NeleSilver-E1",
    #"HT-Le600--SingleElectrontrigger-E1--NeleGold-E1",
    #"HT-Le600--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Le600--SingleMuontrigger-E1--NmuBronze-E1",
    #"HT-Le600--SingleMuontrigger-E1--NmuSilver-E1",
    #"HT-Le600--SingleMuontrigger-E1--NmuGold-E1",
    #"HT-Le600--DoubleElectrontrigger-E1--Nele-E2",
    #"HT-Le600--DoubleMuontrigger-E1--Nmu-E2",
#HT Middle Bin
    #"HT-G600--HT-L750--Nlep-E0",
    #"HT-G600--HT-L750--Njet_S-E0",
    #"HT-G600--HT-L750--Njet_S-E1",
    #"HT-G600--HT-L750--Njet_S-Ge2",
    #"HT-G600--HT-L750--Njet_S-E0--Nlep-E0",
    #"HT-G600--HT-L750--Njet_S-E1--Nlep-E0",
    #"HT-G600--HT-L750--Njet_S-Ge2--Nlep-E0",
    #"HT-G600--HT-L750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1",
    #"HT-G600--HT-L750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1",
    #"HT-G600--HT-L750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1",
    #"HT-G600--HT-L750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1",
    #"HT-G600--HT-L750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1",
    #"HT-G600--HT-L750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1",
    #"HT-G600--HT-L750--EMutrigger-E1--Nmu-E1--Nele-E1",
    #"HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",
    #"HT-G600--HT-L750--SingleElectrontrigger-E1--NeleBronze-E1",
    #"HT-G600--HT-L750--SingleElectrontrigger-E1--NeleSilver-E1",
    #"HT-G600--HT-L750--SingleElectrontrigger-E1--NeleGold-E1",
    #"HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",
    #"HT-G600--HT-L750--SingleMuontrigger-E1--NmuBronze-E1",
    #"HT-G600--HT-L750--SingleMuontrigger-E1--NmuSilver-E1",
    #"HT-G600--HT-L750--SingleMuontrigger-E1--NmuGold-E1",
    #"HT-G600--HT-L750--DoubleElectrontrigger-E1--Nele-E2",
    #"HT-G600--HT-L750--DoubleMuontrigger-E1--Nmu-E2",
#HT High Bin
    #"HT-Ge750--Nlep-E0",
    #"HT-Ge750--Njet_S-E0",
    #"HT-Ge750--Njet_S-E1",
    #"HT-Ge750--Njet_S-Ge2",
    #"HT-Ge750--Njet_S-E0--Nlep-E0",
    #"HT-Ge750--Njet_S-E1--Nlep-E0",
    #"HT-Ge750--Njet_S-Ge2--Nlep-E0",
    #"HT-Ge750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Ge750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Ge750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Ge750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Ge750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Ge750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Ge750--EMutrigger-E1--Nmu-E1--Nele-E1",
    #"HT-Ge750--SingleElectrontrigger-E1--Nele-E1",
    #"HT-Ge750--SingleElectrontrigger-E1--NeleBronze-E1",
    #"HT-Ge750--SingleElectrontrigger-E1--NeleSilver-E1",
    #"HT-Ge750--SingleElectrontrigger-E1--NeleGold-E1",
    #"HT-Ge750--SingleMuontrigger-E1--Nmu-E1",
    #"HT-Ge750--SingleMuontrigger-E1--NmuBronze-E1",
    #"HT-Ge750--SingleMuontrigger-E1--NmuSilver-E1",
    #"HT-Ge750--SingleMuontrigger-E1--NmuGold-E1",
    #"HT-Ge750--DoubleElectrontrigger-E1--Nele-E2",
    #"HT-Ge750--DoubleMuontrigger-E1--Nmu-E2",
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

list_tags_MET_2018 = [
    list_path+"Autumn18_102X_Data_MET.list",
]


#master list of samples to run over
list_list_eff = [
#    'SingleMuon_2016',list_tags_SingleMuon_2016,
#    'SingleElectron_2016',list_tags_SingleElectron_2016,
#    'DoubleMuon_2016',list_tags_DoubleMuon_2016,
#    'DoubleElectron_2016',list_tags_DoubleElectron_2016,
#    'Bkg_2016',list_tags_Bkg_2016,
#    'SingleMuon_2017',list_tags_SingleMuon_2017,
#    'SingleElectron_2017',list_tags_SingleElectron_2017,
#    'DoubleMuon_2017',list_tags_DoubleMuon_2017,
#    'DoubleElectron_2017',list_tags_DoubleElectron_2017,
#    'Bkg_2017',list_tags_Bkg_2017,
    'SingleMuon_2018',list_tags_SingleMuon_2018,
    'SingleElectron_2018',list_tags_SingleElectron_2018,
#    'DoubleMuon_2018',list_tags_DoubleMuon_2018,
#    'DoubleElectron_2018',list_tags_DoubleElectron_2018,
    'Bkg_2018',list_tags_Bkg_2018,
##    'Test_2017',list_tags_Test_2017,
]

list_list_hist = [
#    'Bkg_2018',list_tags_Bkg_2018,
    'MET_2018',list_tags_MET_2018,
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
        os.system("rm -rf "+cut_dir)

      

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
RUN_JOBS = int(get_jobs())
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
                    print("Waiting for "+str(get_jobs())+" jobs to finish...")
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
                    NHOLD = 0
                    os.system("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" -output "+output_dir+" -split "+str(SPLIT)+" --eff ")
                if(DO_HIST):
                    NHOLD = 0
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
    NJOBS = int(get_jobs())-RUN_JOBS
    while NJOBS > 0:
        NJOBS = int(get_jobs())-RUN_JOBS
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
