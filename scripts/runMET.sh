cd /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/

#TTJets
#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Autumn18_102X_v1/PreProcessed_22March2019/TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/2018_Data_RunIIAutumn18MiniAOD-102X_v15-v1/190404_202423/0000/prod2018MC_NANO_1-1.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root

#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Fall17_94X_v2_NanAOD_MC/PreProcessed_25Apr2019/TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/2017_MC_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1/190529_145552/0000/prod2017MC_NANO_1.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Summer16_94X_v3/PreProcessed_22Feb2019/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/2016_MINIAODv3_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-ext1/190225_171346/0000/prod2016MC_NANO_3-126.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#WJets_LNu
#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Autumn18_102X_v1/PreProcessed_22March2019/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/2018_Data_RunIIAutumn18MiniAOD-102X_v15-v1/190325_060236/0000/prod2018MC_NANO_1-1.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root

#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Fall17_94X_v2_NanAOD_MC/PreProcessed_15Jan2019/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/2017_MC_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1/190111_193237/0000/prod2017MC_NANO_1-1.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#./MakeReducedNtuple.x -ifile=root://cmseos.fnal.gov//eos/uscms/store/user/lpcsusyhad/Stop_production/Summer16_94X_v3/PreProcessed_22Feb2019/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/2016_MINIAODv3_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-ext1/190225_173104/0000/prod2016MC_NANO_10.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root


#Everything above this line works

#Stops
#No Triggers
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv4/SMS-T2bW_X05_dM-10to80_2Lfilter_mWMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUFall18Fast_Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/270000/52F5DE42-DC76-2749-B6D8-D7585DA8B101.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-T2bW_X05_dM-10to80_2Lfilter_mWMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/110000/7D503526-1D50-0C47-8C14-2EB9882BAC65.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv4/SMS-T2bW_X05_dM-10to80_2Lfilter_mWMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUSummer16v3Fast_Nano14Dec2018_102X_mcRun2_asymptotic_v6-v1/610000/6BB609ED-5809-EE4D-A81D-2B410AE4F09B.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/SMS-T2bW_X05_dM-10to80_2Lfilter_mWMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#Finished
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_102X_mc2017_realistic_v7-v1/120000/7AC57957-442A-5B42-90AA-4F33928053EA.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root

#TChiWZ
#Redirect Limit
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017_12Apr2018_Nano1June2019_GridpackScan_102X_mc2017_realistic_v7-v1/30000/964FB3E4-EE48-714E-8158-87B2717C13C8.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2017.root

#No Servers
./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv5/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_GridpackScan_102X_upgrade2018_realistic_v19-v2/70000/05F792AA-8723-7944-83AD-F8FC4C595049.root -selector=prod2018MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_2018.root

#Finished
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv4/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_Nano14Dec2018_GridpackScan_102X_mcRun2_asymptotic_v6-v1/50000/87331B68-DD6D-994F-95F8-148EFA90A1A8.root -selector=prod2016MC_reducedNANO_MET -ofile=./samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root

#TChiWW
#No Triggers
#./MakeReducedNtuple.x -ifile=root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv4/SMS-TChipmWW_WWTo2LNu_TuneCP2_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUFall17Fast_Nano14Dec2018_102X_mc2017_realistic_v6-v1/260000/9CD01FA8-434C-9E41-A6C0-FEC5C634726A.root -selector=prod2017MC_reducedNANO_MET -ofile=./samples/SMS-TChipmWW_WWTo2LNu_TuneCP2_13TeV-madgraphMLM-pythia8_2017.root
