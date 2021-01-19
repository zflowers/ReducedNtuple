#!/usr/bin/env python
import os
import re
import argparse

path = "/stash/user/zflowers/CMSSW_10_2_20_UL/src/ReducedNtuple/macros/"
store = path+"EFF/"
log = path+"LOG_EFF/"
shell = path+"Shell_EFF/"
num = path+"Num_EFF/"
#input = "/home/t3-ku/crogan/NTUPLES/NANO/NEW_21_09_20/"
input_path = "/stash/user/zflowers/NTUPLES/Processing/"
#input_path = "/stash/user/zflowers/NTUPLES/temp/"

list_f = []
list_cuts = [
    "SingleElectrontriggerE1-NeleBronzeE1",
    "SingleElectrontriggerE1-NeleSilverE1",
    "SingleElectrontriggerE1-NeleGoldE1",
    "SingleElectrontriggerE1-NeleE1",
    "SingleMuontriggerE1-NmuBronzeE1",
    "SingleMuontriggerE1-NmuSilverE1",
    "SingleMuontriggerE1-NmuGoldE1",
    "SingleMuontriggerE1-NmuE1",
    "DoubleElectrontriggerE1-NeleBronzeE2",
    "DoubleElectrontriggerE1-NeleSilverE2",
    "DoubleElectrontriggerE1-NeleGoldE2",
    "DoubleElectrontriggerE1-NeleE2",
    "DoubleMuontriggerE1-NmuBronzeE2",
    "DoubleMuontriggerE1-NmuSilverE2",
    "DoubleMuontriggerE1-NmuGoldE2",
    "DoubleMuontriggerE1-NmuE2",
    "NeleBronzeE1",
    "NeleSilverE1",
    "NeleGoldE1",
    "NeleE1",
    "NmuBronzeE1",
    "NmuSilverE1",
    "NmuGoldE1",
    "NmuE1",
    "NeleBronzeE2",
    "NeleSilverE2",
    "NeleGoldE2",
    "NeleE2",
    "NmuBronzeE2",
    "NmuSilverE2",
    "NmuGoldE2",
    "NmuE2",
]

for cut in list_cuts:
    os.system("python setup.py -list -tree KUAnalysis -split 5 -cut "+cut+"")

print("Writing shell scripts")

with open(path+"Setup_Eff/Eff.txt") as cut_handle:
    for cut_line in cut_handle:
        Cut = cut_line.replace('\n','')
        if(Cut.startswith('#')):
            continue;
        with open(path+"Setup_Eff/Dir.txt") as dir_handle:
            for dir_line in dir_handle:
                Dir = dir_line.replace('\n','')
                for filename in os.listdir(path+"Setup_Eff/"+Dir+"/"):
                    File = filename.replace('.txt','')
                    with open(os.path.join(path+"Setup_Eff/"+Dir+"/",filename),'r') as tag_handle:
                        for tag_line in tag_handle:
                            Tag = tag_line.replace('\n','')
                            if "SMS" in Dir:
                                Num = ''
                                list_f.append(write_sh_sms(Cut,Dir,File,Tag))
                            else:
                                if(write_num):
                                    for num_line in os.listdir(input_path+Dir+"/"+File+"/"):
                                        Num = num_line.replace(File,'')
                                        Num = Num.replace('.root','')
                                        write_num_file(Dir,File,Tag,Num)
                                list_f.append(write_sh(Cut,Dir,File,Tag))
        write_num = False
        list_f = list(dict.fromkeys(list_f))
        for f in list_f:
            print("Submitting: "+f)
            os.system("condor_submit "+f)
        print("Clearing list")
        list_f = []

#os.system("rm -rf "+path+"config_eff/")
print("Finished Submitting Jobs")
