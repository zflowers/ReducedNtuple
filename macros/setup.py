#! /usr/bin/env python

import os, sys, commands, time

#look for the current directory
#######################################
pwd = os.environ['PWD']
home = os.environ['HOME']
#######################################
RUN_DIR = pwd
TEMP = pwd
jobEXE  = "execute_script.sh"
EXE  = "Eff_Nano_Hist.x"
CMSSW_SETUP = '/home/t3-ku/z374f439/cmssw-sandbox/cmssw_setup.sh'
SANDBOX = '/home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/macros/sandbox-CMSSW_10_2_20_UL-9d39de6.tar.bz2'
TREE = "KUAnalysis"
OUT  = pwd
#OUT = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/eschmitz/EWKino/Processing"
#OUT =  "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/t3-ku/erichjs/EWKino/Processing"
LIST = "default.list"
QUEUE = ""
MAXN = 1
SPLIT = 1
CUT = ""
TAG = ""

def new_listfile(rootlist, listfile):
    mylist = open(listfile,'w')
    for f in rootlist:
        mylist.write(f+" \n")
    mylist.close()

def create_filelist(rootlist, dataset, filetag):
    listlist = []
    listcount = 0
    
    sublist = []
    for f in rootlist:
        sublist.append(f)
        if len(sublist) >= MAXN and MAXN > 0:
            listfile = "%s/%s_%s_%d.list" % (listdir_sam, dataset, filetag, listcount)
            new_listfile(sublist, listfile)
            listlist.append(listfile)
            sublist = []
            listcount += 1

    if len(sublist) > 0:
        listfile = "%s/%s_%s_%d.list" % (listdir_sam, dataset, filetag, listcount)
        new_listfile(sublist, listfile)
        listlist.append(listfile)

    return listlist

def write_sh(srcfile,ifile,ofile,logfile,outfile,errfile,dataset,filetag,n,CUT,TAG):
    fsrc = open(srcfile,'w')
    fsrc.write('universe = vanilla \n')
    fsrc.write('executable = '+jobEXE+" \n")
    fsrc.write('use_x509userproxy = true \n')
    fsrc.write('Arguments = ');
    fsrc.write('-ilist=$(Item) ')
    fsrc.write('-output='+ofile.split('/')[-1]+" ")
    if DO_SMS == 1:
        fsrc.write('--sms ')
    #if DO_DATA == 1:
    #    fsrc.write('--data ')
    fsrc.write('-tree='+TREE+" ")
    fsrc.write('-filename='+dataset+" ")
    fsrc.write('-dir='+filetag+" ")
    fsrc.write('-cut='+CUT+" ")
    fsrc.write('-tag='+TAG+" ")
    if DO_EFF == 1:
        fsrc.write('--eff ')
    if DO_HIST == 1:
        fsrc.write('--hist ')
    
    splitstring = '-split=%s,%d\n' % ('$$([$(Step)+1])', n)
    fsrc.write(splitstring)

    outlog = outfile+".out"
    errlog = errfile+".err"
    loglog = logfile+".log"
    fsrc.write('output = '+outlog+" \n")
    fsrc.write('error = '+errlog+" \n")
    fsrc.write('log = '+loglog+" \n")
    fsrc.write('Requirements = (Machine != "red-node000.unl.edu")\n')
    fsrc.write('request_memory = 2 GB \n')

    transfer_input = 'transfer_input_files = '+TARGET+'config.tgz\n'
    fsrc.write(transfer_input)

    fsrc.write('should_transfer_files = YES\n')
    fsrc.write('when_to_transfer_output = ON_EXIT\n')

    transfer_out_files = 'transfer_output_files = '+ofile.split('/')[-1]+'\n'
    fsrc.write(transfer_out_files)

    transfer_out_remap = 'transfer_output_remaps = "'+ofile.split('/')[-1]+'='+ofile
    transfer_out_remap += '"\n'
    fsrc.write(transfer_out_remap)
    
    fsrc.write('+ProjectName="cms.org.ku"\n')
    fsrc.write('+REQUIRED_OS="rhel7"\n')
    fsrc.write('+RequiresCVMFS=True\n')
    fsrc.write('queue '+str(n)+' from '+ifile+'\n')
    fsrc.close()

if __name__ == "__main__":
    if not len(sys.argv) > 1 or '-h' in sys.argv or '--help' in sys.argv:
        print "Usage: %s [-q queue] [-tree treename] [-list listfile.list] [-maxN N] [--sms]" % sys.argv[0]
        print
        sys.exit(1)

    argv_pos = 1
    DO_SMS = 0
    DO_DATA = 0
    DO_HIST = 0
    DO_EFF = 0
  
    if '-q' in sys.argv:
        p = sys.argv.index('-q')
        QUEUE = sys.argv[p+1]
        argv_pos += 2
    if '-list' in sys.argv:
        p = sys.argv.index('-list')
        LIST = sys.argv[p+1]
        argv_pos += 2
    if '-tree' in sys.argv:
        p = sys.argv.index('-tree')
        TREE = sys.argv[p+1]
        argv_pos += 2
    if '-maxN' in sys.argv:
        p = sys.argv.index('-maxN')
        MAXN = int(sys.argv[p+1])
        argv_pos += 2
    if '-split' in sys.argv:
        p = sys.argv.index('-split')
        SPLIT = int(sys.argv[p+1])
        argv_pos += 2
    if '--sms' in sys.argv:
        DO_SMS = 1
        argv_pos += 1
    if '--data' in sys.argv:
        DO_DATA = 1
        argv_pos += 1
    if '--eff' in sys.argv:
        DO_EFF = 1
        argv_pos += 1
    if '--hist' in sys.argv:
        DO_HIST = 1
        argv_pos += 1
    if '-cut' in sys.argv:
        p = sys.argv.index('-cut')
        CUT = sys.argv[p+1]
        argv_pos += 2
    if '-tag' in sys.argv:
        p = sys.argv.index('-tag')
        TAG = sys.argv[p+1]
        argv_pos += 2
    if '-output' in sys.argv:
        p = sys.argv.index('-output')
        OUT = sys.argv[p+1]
        argv_pos += 2
        
    
    if SPLIT <= 1:
        SPLIT = 1
    else:
        MAXN = 1
    
    print "maxN is %d" % MAXN
    print "split is %d" % SPLIT

    if DO_DATA:
        print "Processing Data"

    if DO_SMS:
        print "Processing as SMS"

    if DO_EFF:
        OUT+="/EFF/"

    if DO_HIST:
        OUT+="/HIST/"

    # input sample list
    listfile = LIST
    listname = listfile.split("/")
    listname = listname[-1]

    print listname

    NAME = listname.replace(".list",'')
    
    print NAME
    print RUN_DIR
        
    # create and organize output folders
    TARGET  = RUN_DIR+"/"+"Shell/"+CUT+"/"+NAME+"/"
    os.system("rm -rf "+TARGET)
    os.system("mkdir -p "+TARGET)
    listdir = TARGET+"list/"
    srcdir  = TARGET+"src/"
    logdir  = TARGET+"log/"
    outdir  = TARGET+"out/"
    errdir  = TARGET+"err/"
    os.system("mkdir -p "+listdir)
    os.system("mkdir -p "+logdir)
    os.system("mkdir -p "+outdir)
    os.system("mkdir -p "+errdir)
    os.system("mkdir -p "+srcdir)

    # make config directory
    config = TARGET+"config/"
    os.system("mkdir -p "+config)

    
    os.system("cp "+EXE+" "+config+".")
    os.system("cp "+CMSSW_SETUP+" "+config+".")
    os.system("cp "+SANDBOX+" "+config+".")

    print TARGET
    #os.system("tar -czf "+TARGET+"/config.tgz "+config)

    # output root files
    ROOT = OUT+"/"+CUT+"/"+TAG+"/"+NAME+"/"
    if ROOT == TARGET:
        ROOT = ROOT+"root/"

    # make output folders
    os.system("rm -rf "+ROOT)
    os.system("mkdir -p "+ROOT)

    datasetlist = []

    knowntags = ["Fall17_94X","Autumn18_102X","Summer16_94X","Fall17_102X","Summer16_102X"]
    
    with open(listfile,'r') as mylist:
        inputlist = mylist.readlines()

        for flist in inputlist:
            if '#' in flist: continue
            flist = flist.strip('\n\r')
            print "Processing list from %s" % flist

            listfile = LIST
            listname = listfile.split("/")
            listname = listname[-1]

            dataset = flist.split("/")
            dataset = dataset[-1]
            dataset = dataset.replace(".txt",'')

            filetag = ""
            for ktag in knowntags:
                if ktag in flist:
                    filetag = ktag

            rootlist = []
            with open(flist,'r') as myflist:
                inputfilelist = myflist.readlines();

                for afile in inputfilelist:
                    afile = afile.strip('\n\r')
                    rootlist.append(afile);

            if len(datasetlist) == 0:
                datasetlist.append((dataset,filetag,rootlist))
                os.system("mkdir -p "+ROOT+dataset+"_"+filetag+"/")
                continue
            
            tagtuple = [item for item in datasetlist if item[0] == dataset]
            if len(tagtuple) == 0:
                datasetlist.append((dataset,filetag,rootlist))
                os.system("mkdir -p "+ROOT+dataset+"_"+filetag+"/")
                continue

            p = datasetlist.index(tagtuple[0])
            datasetlist[p][2].extend(rootlist)

    for (dataset,filetag,rootlist) in datasetlist:
        os.system("mkdir -p "+os.path.join(listdir, dataset+'_'+filetag))
        listdir_sam = os.path.join(listdir, dataset+'_'+filetag)
        listlist = create_filelist(rootlist, dataset, filetag)
        overlist_name = listdir_sam+'/'+dataset+'_'+filetag+'_list.list'
        with open(overlist_name,'w') as overlist:
            newlistlist = ['config/'+'/'.join(l.split('/')[-3:])+'\n' for l in listlist]
            overlist.writelines(newlistlist)
            overlist.close()

        os.system("mkdir -p "+os.path.join(logdir, dataset+'_'+filetag))
        os.system("mkdir -p "+os.path.join(outdir, dataset+'_'+filetag))
        os.system("mkdir -p "+os.path.join(errdir, dataset+'_'+filetag))

        file_name = os.path.join(ROOT, dataset+'_'+filetag, overlist_name.split('/')[-1].replace('_list.list', '_$(ItemIndex)_$(Step)'))
        print(file_name)

        logfile = os.path.join(logdir, dataset+'_'+filetag, file_name.split('/')[-1])
        outfile= os.path.join(outdir, dataset+'_'+filetag, file_name.split('/')[-1])
        errfile = os.path.join(errdir, dataset+'_'+filetag, file_name.split('/')[-1])

        script_name = srcdir+CUT+'_'+'_'.join([dataset, filetag])+'.submit'
        write_sh(script_name, overlist_name, file_name+'.root', logfile, outfile, errfile, dataset, filetag, SPLIT, CUT, TAG)
        #os.system('condor_submit '+script_name)

    print listdir
    os.system("cp -r "+listdir+" "+config)
    print "creating tarbal from: ", TARGET

    os.system("tar -C "+config+"/../ -czvf "+TARGET+"/config.tgz config")

    submit_dir = srcdir        
    submit_list = [os.path.join(submit_dir, f) for f in os.listdir(submit_dir) if (os.path.isfile(os.path.join(submit_dir, f)) and ('.submit' in f))]

    for f in submit_list:
        print "submitting: ", f
        os.system('condor_submit ' + f)
