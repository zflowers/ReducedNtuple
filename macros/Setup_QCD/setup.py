#!/usr/bin/env python
import os
import re
import argparse

path = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/"
store = path+"HIST/"
log = path+"LOG_HIST/"
shell = path+"Shell_HIST/"
#input = "/home/t3-ku/crogan/NTUPLES/NANO/NEW_21_09_20/"
input_path = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/"

print("Writing shell scripts")

list_f = []

def write_sh(Cut,Num,Dir,File,Tag):
    os.system("mkdir -p "+store+Cut+"/"+Dir+"/"+Tag+"/"+File)
    os.system("mkdir -p "+log+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    os.system("mkdir -p "+shell+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    f = (shell+Cut+"/"+Dir+"/"+Tag+"/"+File+"/"+File+Num+".sh").replace('\n','')
    fsrc = open(f,'w')
    fsrc.write('CUT = '+Cut+'\n')
    fsrc.write('DIR = '+Dir+'\n')
    fsrc.write('TAG = '+Tag+'\n')
    fsrc.write('FILENAME = '+File+'\n')
    fsrc.write('NUM = '+Num+'\n')
    fsrc.write('universe = vanilla \n')
    fsrc.write('executable = '+path+'Eff_Nano_Hist.x \n')
    fsrc.write('#notify_user = z374f439@ku.edu \n')
    fsrc.write('#notification = Complete \n')
    fsrc.write('getenv = True \n')
    fsrc.write('priority = 10 \n')
    fsrc.write('use_x509userproxy = true \n')
    fsrc.write('request_memory = 4000 \n')
    fsrc.write('output = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/out_$(FILENAME)$(NUM).log \n')
    fsrc.write('error = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/err_$(FILENAME)$(NUM).log \n')
    fsrc.write('log = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/log_$(FILENAME)$(NUM).log \n')
    fsrc.write('Requirements = (Machine != \"red-node000.unl.edu\") \n')
    fsrc.write('Arguments = \"-cut=$(CUT) -tag=$(TAG) -dir=$(DIR) -filename=$(FILENAME) -num=$(NUM) --hist\" \n')
    fsrc.write('should_transfer_files = YES \n')
    fsrc.write('when_to_transfer_output = ON_EXIT \n')
    fsrc.write('transfer_output_files = $(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root \n')
    fsrc.write('transfer_output_remaps = \"$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root = '+store+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/$(FILENAME)$(NUM).root\" \n')
    fsrc.write('queue \n')
    fsrc.close()
    return f


with open(path+"Setup_Hist/Hist.txt") as cut_handle:
    for cut_line in cut_handle:
        Cut = cut_line.replace('\n','')
        with open(path+"Setup_Hist/Dir.txt") as dir_handle:
            for dir_line in dir_handle:
                Dir = dir_line.replace('\n','')
                for filename in os.listdir(path+"Setup_Hist/"+Dir+"/"):
                    File = filename.replace('.txt','')
                    with open(os.path.join(path+"Setup_Hist/"+Dir+"/",filename),'r') as tag_handle:
                        for tag_line in tag_handle:
                            Tag = tag_line.replace('\n','')
                            if "SMS" in Dir:
                                Num = ''
                                list_f.append(write_sh(Cut,Num,Dir,File,Tag))
                            else:
                                for num_line in os.listdir(input+Dir+"/NoHadd/"+File+"/"):
                                    Num = num_line.replace(File,'')
                                    Num = Num.replace('.root','')
                                    list_f.append(write_sh(Cut,Num,Dir,File,Tag))

print("Submitting Jobs")
list_f = list(dict.fromkeys(list_f))
for f in list_f:
    os.system("condor_submit "+f)
print("Finished Submitting Jobs")
