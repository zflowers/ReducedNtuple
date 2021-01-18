#!/usr/bin/env python
import os
import re
import argparse

path = "/stash/user/zflowers/CMSSW_10_2_20_UL/src/ReducedNtuple/macros/"
store = path+"HIST/"
log = path+"LOG_HIST/"
shell = path+"Shell_HIST/"
num = path+"Num_HIST/"
#input = "/home/t3-ku/crogan/NTUPLES/NANO/NEW_21_09_20/"
input_path = "/stash/user/zflowers/NTUPLES/Processing/"
#input_path = "/stash/user/zflowers/NTUPLES/temp/"

list_f = []

def write_sh_sms(Cut,Dir,File,Tag):
    os.system("mkdir -p "+store+Cut+"/"+Dir+"/"+Tag+"/"+File)
    os.system("mkdir -p "+log+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    os.system("mkdir -p "+shell+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    f = (shell+Cut+"/"+Dir+"/"+Tag+"/"+File+"/"+File+".sh").replace('\n','')
    fsrc = open(f,'w')
    fsrc.write('CUT = '+Cut+'\n')
    fsrc.write('DIR = '+Dir+'\n')
    fsrc.write('TAG = '+Tag+'\n')
    fsrc.write('FILENAME = '+File+'\n')
    #fsrc.write('NUM = '+Num+'\n')
    fsrc.write('universe = vanilla \n')
    fsrc.write('executable = execute_script_hist.sh \n')
    fsrc.write('#notify_user = z374f439@ku.edu \n')
    fsrc.write('#notification = Complete \n')
    fsrc.write('getenv = True \n')
    fsrc.write('priority = 10 \n')
    fsrc.write('use_x509userproxy = true \n')
    fsrc.write('+ProjectName=\"cms.org.ku\" \n')
    fsrc.write('+REQUIRED_OS=\"rhel7\" \n')
    fsrc.write('request_memory = 2000 \n')
    fsrc.write('output = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/out_$(FILENAME).log \n')
    fsrc.write('error = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/err_$(FILENAME).log \n')
    fsrc.write('log = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/log_$(FILENAME).log \n')
    fsrc.write('Requirements = (Machine != \"red-node000.unl.edu\") \n')
    fsrc.write('Arguments = \"-cut=$(CUT) -tag=$(TAG) -dir=$(DIR) -filename=$(FILENAME) -num= --hist\" \n')
    fsrc.write('transfer_input_files = '+path+'config_hist.tgz \n')
    fsrc.write('should_transfer_files = YES \n')
    fsrc.write('when_to_transfer_output = ON_EXIT \n')
    fsrc.write('transfer_output_files = $(CUT)_$(DIR)_$(TAG)_$(FILENAME).root \n')
    fsrc.write('transfer_output_remaps = \"$(CUT)_$(DIR)_$(TAG)_$(FILENAME).root = '+store+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/$(FILENAME).root\" \n')
    fsrc.write('queue \n')
    fsrc.close()
    return f

def write_sh(Cut,Dir,File,Tag):
    os.system("mkdir -p "+store+Cut+"/"+Dir+"/"+Tag+"/"+File)
    os.system("mkdir -p "+log+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    os.system("mkdir -p "+shell+Cut+"/"+Dir+"/"+Tag+"/"+File) 
    f = (shell+Cut+"/"+Dir+"/"+Tag+"/"+File+"/"+File+".sh").replace('\n','')
    fsrc = open(f,'w')
    fsrc.write('CUT = '+Cut+'\n')
    fsrc.write('DIR = '+Dir+'\n')
    fsrc.write('TAG = '+Tag+'\n')
    fsrc.write('FILENAME = '+File+'\n')
    fsrc.write('NUM = $(Item)\n')
    fsrc.write('universe = vanilla \n')
    fsrc.write('executable = execute_script_hist.sh \n')
    fsrc.write('#notify_user = z374f439@ku.edu \n')
    fsrc.write('#notification = Complete \n')
    fsrc.write('getenv = True \n')
    fsrc.write('priority = 10 \n')
    fsrc.write('use_x509userproxy = true \n')
    fsrc.write('+ProjectName=\"cms.org.ku\" \n')
    fsrc.write('+REQUIRED_OS=\"rhel7\" \n')
    #fsrc.write('+RequiresCVMFS = True \n')
    #fsrc.write('+RequiresSharedFS = True \n')
    fsrc.write('request_memory = 2000 \n')
    fsrc.write('output = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/out_$(FILENAME)$(NUM).log \n')
    fsrc.write('error = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/err_$(FILENAME)$(NUM).log \n')
    fsrc.write('log = '+log+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/log_$(FILENAME)$(NUM).log \n')
    fsrc.write('Requirements = (Machine != \"red-node000.unl.edu\") \n')
    fsrc.write('Arguments = \"-cut=$(CUT) -tag=$(TAG) -dir=$(DIR) -filename=$(FILENAME) -num=$(NUM) --hist\" \n')
    fsrc.write('transfer_input_files = '+path+'config_hist.tgz \n')
    fsrc.write('should_transfer_files = YES \n')
    fsrc.write('when_to_transfer_output = ON_EXIT \n')
    fsrc.write('transfer_output_files = $(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root \n')
    fsrc.write('transfer_output_remaps = \"$(CUT)_$(DIR)_$(TAG)_$(FILENAME)$(NUM).root = '+store+'$(CUT)/$(DIR)/$(TAG)/$(FILENAME)/$(FILENAME)$(NUM).root\" \n')
    #fsrc.write('queue \n')
    fsrc.write('queue from '+(num+Dir+"/"+Tag+"/"+File+"/"+File+".txt").replace('\n',''))
    fsrc.close()
    return f

def write_num_file(Dir,File,Tag,Num):
    os.system("mkdir -p "+num+"/"+Dir+"/"+Tag+"/"+File)
    f = (num+"/"+Dir+"/"+Tag+"/"+File+"/"+File+".txt").replace('\n','')
    fsrc = open(f,'a+')
    fsrc.write(Num+'\n')
    fsrc.close()

os.system("mkdir -p "+path+"config_hist")
os.system("cp "+path+"Eff_Nano_Hist.x "+path+"config_hist/")
os.system("cp /stash/user/zflowers/cmssw-sandbox/cmssw_setup.sh "+path+"config_hist/")
os.system("tar -C "+path+"config_hist/../ -czvf config_hist.tgz config_hist/")
#os.system("source "+path+"make_sandbox.sh")



print("Writing shell scripts")

write_num = True

with open(path+"Setup_Hist/Hist.txt") as cut_handle:
    for cut_line in cut_handle:
        Cut = cut_line.replace('\n','')
        if(Cut.startswith('#')):
            continue;
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

#os.system("rm -rf "+path+"config_hist/")
print("Finished Submitting Jobs")
