cd /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/

#TTJets
./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Autumn18_102X_v1/PreProcessed_22March2019/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/2018_Data_RunIIAutumn18MiniAOD-102X_v15-v1/190404_202044/0000/prod2018MC_NANO_1-1.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Fall17_94X_v2_NanAOD_MC/PreProcessed_15Jan2019/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/2017_MC_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1/190111_191334/0000/prod2017MC_NANO_1-1.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Summer16_94X_v3/PreProcessed_22Feb2019/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/2016_MINIAODv3_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1/190225_171743/0000/prod2016MC_NANO_1-1.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#WJets_LNu
./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Autumn18_102X_v1/PreProcessed_25Apr2019/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/2018_MINIAODv1_RunIIAutumn18MiniAOD-102X_v15-v2/190426_001324/0000/prod2018MC_NANO_1.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Fall17_94X_v2_NanAOD_MC/PreProcessed_15Jan2019/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/2017_MC_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-ext1/190111_193109/0000/prod2017MC_NANO_1-1.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Summer16_94X_v3/PreProcessed_22Feb2019/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/2016_MINIAODv3_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-ext2/190225_212418/0000/prod2016MC_NANO_1.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#DY
./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Autumn18_102X_v1/PreProcessed_22March2019/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/2018_Data_RunIIAutumn18MiniAOD-102X_v15-v1/190326_032843/0000/prod2018MC_NANO_1-1.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Fall17_94X_v2_NanAOD_MC/PreProcessed_15Jan2019/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/2017_MC_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-ext1/190111_041446/0000/prod2017MC_NANO_177.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_2017.root

./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Summer16_94X_v3/PreProcessed_22Feb2019/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/2016_MINIAODv3_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-ext1/190301_191048/0000/prod2016MC_NANO_1.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root


#Everything above this line works

#Stops

#2018

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-T2tt_mStop-1200_mLSP-100_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/70000/5962F59D-5E63-1247-937F-5466FCDCA924.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-1200_mLSP-100_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Permission Denied
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-T2tt_mStop-650_mLSP-350_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/120000/62779032-B2A6-4943-BE97-ED468B990102.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-650_mLSP-350_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Permission Denied
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-T2tt_mStop-1000_mLSP-600_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/270000/FEDF99CF-FAFE-F948-843E-F5BD55B63F99.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-1000_mLSP-600_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-T2tt_mStop-1000_mLSP-400_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/50000/39AC445B-CF7D-B04E-AD03-A42C71B5FC98.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-1000_mLSP-400_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Works
./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_GridpackScan_102X_upgrade2018_realistic_v19-v2/70000/05F792AA-8723-7944-83AD-F8FC4C595049.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#2017

#Permission Denied
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-T2tt_mStop-850_mLSP-100_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/40000/39D1E99F-F847-A243-A32D-DC174BD2422C.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-850_mLSP-100_TuneCP2_13TeV-madgraphMLM-pythia8_2017.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/110000/EC9411D3-C6DB-0C48-AB2E-5F7DD0F42B4B.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#Works
./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/120000/7AC57957-442A-5B42-90AA-4F33928053EA.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_GridpackScan_102X_mc2017_realistic_v7-v1/30000/7C4DB2B4-1994-E14C-97E3-9B5A575B4D66.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2017.root

#2016

./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv3/SMS-T2tt_mStop-425_mLSP-325_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/80000/56096210-C6F0-E811-96F9-C0BFC0E56816.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-425_mLSP-325_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv5/SMS-T2tt_mStop-150_mLSP-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_Nano1June2019_102X_mcRun2_asymptotic_v7-v1/250000/63B10524-D574-254A-96C1-FD404DB3A115.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/SMS-T2tt_mStop-150_mLSP-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#TChiWZ
#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_GridpackScan_102X_mc2017_realistic_v7-v1/30000/964FB3E4-EE48-714E-8158-87B2717C13C8.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2017.root

#Works
./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_GridpackScan_102X_upgrade2018_realistic_v19-v2/70000/05F792AA-8723-7944-83AD-F8FC4C595049.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Works
./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv4/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_Nano14Dec2018_GridpackScan_102X_mcRun2_asymptotic_v6-v1/50000/87331B68-DD6D-994F-95F8-148EFA90A1A8.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root
