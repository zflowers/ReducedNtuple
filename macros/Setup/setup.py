#!/usr/bin/env python
import os

Cut = ''
Tag = ''
Dir = ''
File = ''
Num = ''
with open("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/Cuts.txt") as cut_handle:
    for cut_line in cut_handle:
        Cut = cut_line
        with open("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/Num.txt") as num_handle:
            for num_line in num_handle:
                Num = num_line
                with open("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/Dir.txt") as dir_handle:
                    for dir_line in dir_handle:
                        Dir = dir_line.replace('\n','')
                        for filename in os.listdir("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/"+Dir+"/"):
                            File = filename.replace('.txt','')
                            with open(os.path.join("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup/"+Dir+"/",filename),'r') as tag_handle:
                                for tag_line in tag_handle:
                                    Tag = tag_line
                                    print((Cut+","+Tag+","+Dir+","+File+","+Num).replace('\n',''))



#print("PreSelection,Bkg_2017,Fall17_102X,WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8,_0_0")
