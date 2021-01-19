#script to get lists from location of input files
import os

#path to input lists
input_path = "/home/t3-ku/crogan/CMSSW_10_6_5/src/KUEWKinoAnalysis/samples/NANO/"
#path to store new lists
output_path = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/samples/NANO/"
#file_path = "root://xrootd.unl.edu//store/user/zflowers/" #xrootd option
file_path = "/home/t3-ku/z374f439/storage/" #local option
subdirs = os.listdir(input_path)
subdirs.remove('Lists')
subdirs[:] = [x for x in subdirs if "Data" not in x]
for subdir in subdirs:
    os.system("mkdir -p "+output_path+subdir)
    files = os.listdir(input_path+subdir)
    for filename in files:
        new_file = output_path+subdir+"/"+filename
        fsrc = open(new_file,'w')
        if('_SMS') in subdir:
            fsrc.write(file_path+subdir.replace('_SMS.txt','')+"/"+filename.replace('.txt','')+'_'+subdir.replace('_SMS','')+'.root \n')
        else:
            fsrc.write(file_path+subdir.replace('.txt','')+"/"+filename.replace('.txt','')+'_'+subdir+'.root \n')
        fsrc.close()
subdirs = os.listdir(input_path)
subdirs.remove('Lists')
subdirs[:] = [x for x in subdirs if "Data" in x]
for subdir in subdirs:
    subsubdirs = os.listdir(input_path+subdir)
    for subsubdir in subsubdirs:
        os.system("mkdir -p "+output_path+subdir+"/"+subsubdir)
        files = os.listdir(input_path+subdir+"/"+subsubdir)
        for filename in files:
            new_file = output_path+subdir+"/"+subsubdir+"/"+filename
            fsrc = open(new_file,'w')
            fsrc.write(file_path+subdir.replace('_Data.txt','')+"/"+filename.replace('.txt','')+'_'+subdir.replace('_Data','')+'.root \n')
            fsrc.close()
os.system('cp -r '+input_path+'Lists/ '+output_path)
