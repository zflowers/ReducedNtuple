#!/usr/bin/env python
import os
import sys
import time

store = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/EFF/"
long_term = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/"
sleep_time = 60

def hadd(Cut,Dir,File,Tag):
    for l in range(len(Cut)):
        for j in range(len(Dir)):
            for k in range(len(Tag)):
                for i in range(len(File)):
                    if(os.path.exists(store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+"/"+File[i]+"/")):
                        os.system("hadd "+store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+"/"+File[i]+".root "+store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+"/"+File[i]+"/*.root")
                if(os.path.exists(store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+"/")):
                    os.system("hadd "+store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+".root "+store+Cut[l]+"/"+Dir[j]+"/"+Tag[k]+"/*.root")
            if(os.path.exists(store+Cut[l]+"/"+Dir[j]+"/")):
                os.system("hadd "+store+Cut[l]+"/"+Dir[j]+".root "+store+Cut[l]+"/"+Dir[j]+"/*.root")
        if(os.path.exists(store+Cut[l]+"/")):
            os.system("hadd "+store+"Eff_output_"+Cut[l]+".root "+store+Cut[l]+"/*.root")


def rm_dupes(List):
    return list(dict.fromkeys(List))

Cut = []
Dir = []
File = []
Tag = []

with open("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup_Eff/Eff.txt") as cut_handle:
    for cut_line in cut_handle:
        Cut.append(cut_line.replace('\n',''))
        with open("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup_Eff/Dir.txt") as dir_handle:
            for dir_line in dir_handle:
                Dir.append(dir_line.replace('\n',''))
                for filename in os.listdir("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup_Eff/"+dir_line.replace('\n','')+"/"):
                    File.append(filename.replace('.txt',''))
                    with open(os.path.join("/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/Setup_Eff/"+dir_line.replace('\n','')+"/",filename),'r') as tag_handle:
                        for tag_line in tag_handle:
                            Tag.append(tag_line.replace('\n',''))
Tag = rm_dupes(Tag)
File = rm_dupes(File)
Dir = rm_dupes(Dir)
Cut = rm_dupes(Cut)
hadd(Cut,Dir,File,Tag)
