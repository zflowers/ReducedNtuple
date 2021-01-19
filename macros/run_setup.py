#!/usr/bin/env python
import os
import sys

list_cuts = [
    "SingleElectrontriggerE1-NeleBronzeE1",
    "SingleElectrontriggerE1-NeleSilverE1",
    "SingleElectrontriggerE1-NeleGoldE1",
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

list_list = [
    'SingleMuon_2017',list_tags_SingleMuon_2017,
    'SingleElectron_2017',list_tags_SingleElectron_2017,
    'DoubleMuon_2017',list_tags_DoubleMuon_2017,
    'DoubleElectron_2017',list_tags_DoubleElectron_2017,
]



if __name__ == "__main__":
    if not len(sys.argv) > 1 or '-h' in sys.argv or '--help' in sys.argv:
        print "Usage: %s -split n [--eff] [--hist]" % sys.argv[0]
        print
        sys.exit(1)

    argv_pos = 1
    DO_HIST = 0
    DO_EFF = 0
    SPLIT = 1
  
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



#run python
current_tag = ''
for cut in list_cuts:
    for tag in list_list:
        if isinstance(tag,list):
            for list_tag in tag:
                if(DO_EFF):
                    print("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" split "+str(SPLIT)+" --eff ")
                if(DO_HIST):
                    print("python setup.py "+"-list "+list_tag+" -cut "+cut+" -tag "+current_tag+" split "+str(SPLIT)+" --hist ")
        else:
            current_tag = tag

print("Finished Submitting Jobs")
