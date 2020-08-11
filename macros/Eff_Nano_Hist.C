#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <string>
#include <vector>
#include <iostream>
#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"
#include "Hist_Maker.h"

using namespace std;

void Hist_Maker_Hist(string outFile = "output_test.root", string cut = ""){
 std::cout << "Outputting to: " << outFile << endl;
 gSystem->Exec(("rm "+outFile).c_str());

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 string path = "~/../crogan/NTUPLES/NANO/NEW_31_05_20/";

 std::cout << "Processing 2016 Background" << endl;
 TChain* chain_2016_Bkg = new TChain("KUAnalysis");
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Summer16_102X.root").c_str(),0);
 Hist_Maker Hist_2016_Bkg(outFile,"Bkg_2016",chain_2016_Bkg);
 Hist_2016_Bkg.Set_Cut(cut);
 Hist_2016_Bkg.Analyze();

 std::cout << "Processing MET 2016" << endl;
 TChain* chain_2016_MET = new TChain("KUAnalysis");
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_MET->Add((path+"Summer16_102X_Data/MET_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 Hist_Maker Hist_2016_MET(outFile,"MET_2016",chain_2016_MET);
 Hist_2016_MET.Set_Cut(cut);
 Hist_2016_MET.Analyze();
 
 std::cout << "Processing Signal: T2bW " << endl;
 TChain* chain_2016_T2bW = new TChain("SMS_500_480");
 chain_2016_T2bW->Add((path+"Summer16_102X_SMS/SMS-T2tt_dM-10to80_genHT-160_genMET-80_mWMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
 Hist_Maker Hist_2016_T2bW(outFile,"T2bW_2016",chain_2016_T2bW);
 Hist_2016_T2bW.Set_Cut(cut);
 Hist_2016_T2bW.Analyze();

/*
 std::cout << "Processing SingleElectron 2016" << endl;
 TChain* chain_2016_SingleElectron = new TChain("KUAnalysis");
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 Hist_Maker Hist_2016_SingleElectron(outFile,"SingleElectron_2016",chain_2016_SingleElectron);
 Hist_2016_SingleElectron.Set_Cut(cut);
 Hist_2016_SingleElectron.Analyze();
 delete chain_2016_SingleElectron;

 std::cout << "Processing SingleMuon 2016" << endl;
 TChain* chain_2016_SingleMuon = new TChain("KUAnalysis");
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
 Hist_Maker Hist_2016_SingleMuon(outFile,"SingleMuon_2016",chain_2016_SingleMuon);
 Hist_2016_SingleMuon.Set_Cut(cut);
 Hist_2016_SingleMuon.Analyze();
 delete chain_2016_SingleMuon;
*/

 std::cout << "Processing 2017 Background" << endl;
 TChain* chain_2017_Bkg = new TChain("KUAnalysis");
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Fall17_102X.root").c_str(),0);
 Hist_Maker Hist_2017_Bkg(outFile,"Bkg_2017",chain_2017_Bkg);
 Hist_2017_Bkg.Set_Cut(cut);
 Hist_2017_Bkg.Analyze();

 std::cout << "Processing MET 2017" << endl;
 TChain* chain_2017_MET = new TChain("KUAnalysis");
 chain_2017_MET->Add((path+"Fall17_102X_Data/MET_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_MET->Add((path+"Fall17_102X_Data/MET_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_MET->Add((path+"Fall17_102X_Data/MET_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_MET->Add((path+"Fall17_102X_Data/MET_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_MET->Add((path+"Fall17_102X_Data/MET_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 Hist_Maker Hist_2017_MET(outFile,"MET_2017",chain_2017_MET);
 Hist_2017_MET.Set_Cut(cut);
 Hist_2017_MET.Analyze();
 delete chain_2017_MET;

 std::cout << "Processing Signal: T2bW " << endl;
 TChain* chain_2017_T2bW = new TChain("SMS_500_480");
 chain_2017_T2bW->Add((path+"Fall17_102X_SMS/SMS-T2bW_X05_dM-10to80_genHT-160_genMET-80_mWMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
 Hist_Maker Hist_2017_T2bW(outFile,"T2bW_2017",chain_2017_T2bW);
 Hist_2017_T2bW.Set_Cut(cut);
 Hist_2017_T2bW.Analyze();

/*
 std::cout << "Processing SingleElectron 2017" << endl;
 TChain* chain_2017_SingleElectron = new TChain("KUAnalysis");
 chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 Hist_Maker Hist_2017_SingleElectron(outFile,"SingleElectron_2017",chain_2017_SingleElectron);
 Hist_2017_SingleElectron.Set_Cut(cut); //+"_NeleBronzeG0"
 Hist_2017_SingleElectron.Analyze();
 delete chain_2017_SingleElectron;

 std::cout << "Processing SingleMuon 2017" << endl;
 TChain* chain_2017_SingleMuon = new TChain("KUAnalysis");
 chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
 Hist_Maker Hist_2017_SingleMuon(outFile,"SingleMuon_2017",chain_2017_SingleMuon);
 Hist_2017_SingleMuon.Set_Cut(cut); //+"_NmuBronzeG0"
 Hist_2017_SingleMuon.Analyze();
 delete chain_2017_SingleMuon;
*/

 std::cout << "Processing 2018 Background" << endl;
 TChain* chain_2018_Bkg = new TChain("KUAnalysis");
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
 Hist_Maker Hist_2018_Bkg(outFile,"Bkg_2018",chain_2018_Bkg);
 Hist_2018_Bkg.Set_Cut(cut);
 Hist_2018_Bkg.Analyze();

 std::cout << "Processing MET 2018" << endl;
 TChain* chain_2018_MET = new TChain("KUAnalysis");
 chain_2018_MET->Add((path+"Autumn18_102X_Data/MET_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_MET->Add((path+"Autumn18_102X_Data/MET_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_MET->Add((path+"Autumn18_102X_Data/MET_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_MET->Add((path+"Autumn18_102X_Data/MET_Run2018D-Nano25Oct2019_ver2-v1_2018_Autumn18_102X.root").c_str(),0);
 Hist_Maker Hist_2018_MET(outFile,"MET_2018",chain_2018_MET);
 Hist_2018_MET.Set_Cut(cut);
 Hist_2018_MET.Analyze();
 delete chain_2018_MET;

 std::cout << "Processing Signal: T2bW " << endl;
 TChain* chain_2018_T2bW = new TChain("SMS_500_300");
 chain_2018_T2bW->Add((path+"Autumn18_102X_SMS/SMS-T2bW_TuneCP2_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
 Hist_Maker Hist_2018_T2bW(outFile,"T2bW_2018",chain_2018_T2bW);
 Hist_2018_T2bW.Set_Cut(cut);
 Hist_2018_T2bW.Analyze();

/*
 std::cout << "Processing SingleElectron 2018" << endl;
 TChain* chain_2018_SingleElectron = new TChain("KUAnalysis");
 chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 Hist_Maker Hist_2018_SingleElectron(outFile,"SingleElectron_2018",chain_2018_SingleElectron);
 Hist_2018_SingleElectron.Set_Cut(cut);
 Hist_2018_SingleElectron.Analyze();
 delete chain_2018_SingleElectron;

 std::cout << "Processing SingleMuon 2018" << endl;
 TChain* chain_2018_SingleMuon = new TChain("KUAnalysis");
 chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
 Hist_Maker Hist_2018_SingleMuon(outFile,"SingleMuon_2018",chain_2018_SingleMuon);
 Hist_2018_SingleMuon.Set_Cut(cut);
 Hist_2018_SingleMuon.Analyze();
 delete chain_2018_SingleMuon;
*/


}

int main(int argc, char* argv[])
{
 string outFile = "Hist_output_";
 string cut = "";

 if(argc < 1)
 {
  cout << "ERROR: Need to specify cut" << endl;
  cout << "Example: ./run_Hist_Maker_Hist -cut=PreSelection" << endl;
  return 1;
 }

 for(int i = 0; i < argc; i++)
 {
  if(strncmp(argv[i],"-cut",4)==0)
  {
   cut=argv[i];
   cut.erase(0,5);
  }
  else if(strncmp(argv[i],"-oFile",6)==0)
  {
   outFile=argv[i];
   outFile.erase(0,7);
  }
 }
 outFile += cut+".root";

 Hist_Maker_Hist(outFile,cut);
 return 0;
}
