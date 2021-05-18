#script to get lists from location of input files
import os

#path to lists

#unl
#input_path = "/home/t3-ku/crogan/CMSSW_10_6_5/src/KUEWKinoAnalysis/samples/NANO/"
input_path = "/home/t3-ku/z374f439/CMSSW_10_6_5/src/KUEWKinoAnalysis/samples/NANO/"
output_path = "/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/samples/NANO/"

#lxplus
#input_path = "/afs/cern.ch/user/z/zflowers/storage/private/KUEWKinoAnalysis/samples/NANO/"
#output_path = "/afs/cern.ch/user/z/zflowers/storage/private/ReducedNtuple/macros/samples/NANO/"

file_path = "root://xrootd.unl.edu//store/user/zflowers/NEW/" #xrootd option
#file_path = "/home/t3-ku/z374f439/storage/" #local option unl

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
#os.system('cp -r '+input_path+'Lists/ '+output_path)
