#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <string>
#include <vector>
#include <iostream>
#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"
#include "Eff_Nano.h"

using namespace std;

void MemCheck()
{
 ProcInfo_t procInfo;
 gSystem->GetProcInfo(&procInfo);
 cout << "Memory Used: " << procInfo.fMemVirtual/1.e6 << endl;
}

bool Scale = false;


void Eff_Nano_Eff(string outFile = "output_test.root", string x = "MET", string cut = ""){
 std::cout << "Outputting to: " << outFile << endl;
 gSystem->Exec(("rm "+outFile).c_str());
 string FitFile = "output_Fits.root";
 gSystem->Exec(("rm "+FitFile).c_str());
 string Fit_Parameters_Output = "Fit_Parameters_Output.csv";
 gSystem->Exec(("rm "+Fit_Parameters_Output).c_str());
 
 //.L Eff_Nano.h; //++
 //.L MET_2016_Triggers.h;
 //.L MET_2017_Triggers.h;
 //.L MET_2018_Triggers.h;
 //std::vector<string> Triggers_2016 = Get_2016_Triggers();
 //std::vector<string> Triggers_2017 = Get_2017_Triggers();
 //std::vector<string> Triggers_2018 = Get_2018_Triggers();
 //string x_2016 = "MET_pt";
 //string x_2017 = "METFixEE2017_pt";
 //string x_2018 = "MET_pt";
 
 std::vector<string> Triggers_2016 = Get_2016_Triggers();
 std::vector<string> Triggers_2017 = Get_2017_Triggers();
 std::vector<string> Triggers_2018 = Get_2018_Triggers();
 //string x_2016 = "MET_pt";
 //string x_2017 = "METFixEE2017_pt";
 //string x_2018 = "MET_pt";

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 string path = "~/../crogan/NTUPLES/NANO/NEW_31_05_20/";
 string x_2016 = x;
 string x_2017 = x;
 string x_2018 = x;

 //Combination For Scale Factors
 if(Scale)
 {
  std::cout << "Processing 2016 Background" << endl;
  TChain* chain_2016_Bkg = new TChain("KUAnalysis");
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_Bkg->Add((path+"Summer16_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_Bkg(outFile,Triggers_2016,"Bkg_2016",x_2016,chain_2016_Bkg);
  Eff_2016_Bkg.Set_Cut(cut);
  Eff_2016_Bkg.Analyze();

  std::cout << "Processing Data 2016" << endl;
  TChain* chain_2016_Data = new TChain("KUAnalysis");
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleElectron_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_Data->Add((path+"Summer16_102X_Data/SingleMuon_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_Data(outFile,Triggers_2016,"Data_2016",x_2016,chain_2016_Data);
  Eff_2016_Data.Set_Cut(cut);
  Eff_2016_Data.Analyze();
  delete chain_2016_Data;
 
  std::cout << "Processing 2017 Background" << endl;
  TChain* chain_2017_Bkg = new TChain("KUAnalysis");
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_Bkg->Add((path+"Fall17_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_Bkg(outFile,Triggers_2017,"Bkg_2017",x_2017,chain_2017_Bkg);
  Eff_2017_Bkg.Set_Cut(cut);
  Eff_2017_Bkg.Analyze();

  std::cout << "Processing Data 2017" << endl;
  TChain* chain_2017_Data = new TChain("KUAnalysis");
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleElectron_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleElectron_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleElectron_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleElectron_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleElectron_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleMuon_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleMuon_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleMuon_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleMuon_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_Data->Add((path+"Fall17_102X_Data/SingleMuon_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_Data(outFile,Triggers_2017,"Data_2017",x_2017,chain_2017_Data);
  Eff_2017_Data.Set_Cut(cut);
  Eff_2017_Data.Analyze();
  delete chain_2017_Data;

  std::cout << "Processing 2018 Background" << endl;
  TChain* chain_2018_Bkg = new TChain("KUAnalysis");
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_Bkg->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_Bkg(outFile,Triggers_2018,"Bkg_2018",x_2018,chain_2018_Bkg);
  Eff_2018_Bkg.Set_Cut(cut);
  Eff_2018_Bkg.Analyze();

  std::cout << "Processing Data 2018" << endl;
  TChain* chain_2018_Data = new TChain("KUAnalysis");
//  chain_2018_Data->Add((path+"Autumn18_102X_Data/EGamma_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_Data->Add((path+"Autumn18_102X_Data/EGamma_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_Data->Add((path+"Autumn18_102X_Data/EGamma_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
//  chain_2018_Data->Add((path+"Autumn18_102X_Data/EGamma_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_Data->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_Data->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_Data->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
//  chain_2018_Data->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_Data(outFile,Triggers_2018,"Data_2018",x_2018,chain_2018_Data);
  Eff_2018_Data.Set_Cut(cut);
  Eff_2018_Data.Analyze();
  delete chain_2018_Data;

 }

 if(!Scale)
 {
/*
 //2016
  //WJets
  std::cout << "Processing WJets 2016" << endl;
  TChain* chain_2016_WJets = new TChain("KUAnalysis");
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_WJets(outFile,Triggers_2016,"WJets_2016",x_2016,chain_2016_WJets);
  Eff_2016_WJets.Set_Cut(cut);
  Eff_2016_WJets.Analyze();
  delete chain_2016_WJets;

  //TTJets
  std::cout << "Processing TTJets 2016" << endl;
  TChain* chain_2016_TTJets = new TChain("KUAnalysis");
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_TTJets(outFile,Triggers_2016,"TTJets_2016",x_2016,chain_2016_TTJets);
  Eff_2016_TTJets.Set_Cut(cut);
  Eff_2016_TTJets.Analyze();
  delete chain_2016_TTJets;

  std::cout << "Processing WWTo2L2Nu 2016" << endl;
  TChain* chain_2016_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2016_WWTo2L2Nu->Add((path+"Summer16_102X/WWTo2L2Nu_13TeV-powheg_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_WWTo2L2Nu(outFile,Triggers_2016,"WWTo2L2Nu_2016",x_2016,chain_2016_WWTo2L2Nu);
  Eff_2016_WWTo2L2Nu.Set_Cut(cut);
  Eff_2016_WWTo2L2Nu.Analyze();
  delete chain_2016_WWTo2L2Nu;

  std::cout << "Processing ZJetsToNuNu 2016" << endl;
  TChain* chain_2016_ZJetsToNuNu = new TChain("KUAnalysis");
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  chain_2016_ZJetsToNuNu->Add((path+"Summer16_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_ZJetsToNuNu(outFile,Triggers_2016,"ZJetsToNuNu_2016",x_2016,chain_2016_ZJetsToNuNu);
  Eff_2016_ZJetsToNuNu.Set_Cut(cut);
  Eff_2016_ZJetsToNuNu.Analyze();
*/
 //Data 2016
 //
  std::cout << "Processing SingleElectron 2016" << endl;
  TChain* chain_2016_SingleElectron = new TChain("KUAnalysis");
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016B_ver2-Nano25Oct2019_ver2-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016D-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016E-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016F-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016G-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016H-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_SingleElectron(outFile,Triggers_2016,"SingleElectron_2016",x_2016,chain_2016_SingleElectron);
  Eff_2016_SingleElectron.Set_Cut(cut);
  Eff_2016_SingleElectron.Analyze();
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
  Eff_Nano Eff_2016_SingleMuon(outFile,Triggers_2016,"SingleMuon_2016",x_2016,chain_2016_SingleMuon);
  Eff_2016_SingleMuon.Set_Cut(cut);
  Eff_2016_SingleMuon.Analyze();
  delete chain_2016_SingleMuon;

 
 //2017
  //WJets
  
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets(outFile,Triggers_2017,"WJets_2017",x_2017,chain_2017_WJets);
  Eff_2017_WJets.Set_Cut(cut);
  Eff_2017_WJets.Analyze();
  delete chain_2017_WJets;

  TChain* chain_2017_WJets70To100 = new TChain("KUAnalysis");
  chain_2017_WJets70To100->Add((path+"Fall17_102X/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets70To100(outFile,Triggers_2017,"WJets70To100_2017",x_2017,chain_2017_WJets70To100);
  Eff_2017_WJets70To100.Set_Cut(cut);
  Eff_2017_WJets70To100.Analyze();
  delete chain_2017_WJets70To100;

  TChain* chain_2017_WJets100To200 = new TChain("KUAnalysis");
  chain_2017_WJets100To200->Add((path+"Fall17_102X/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets100To200(outFile,Triggers_2017,"WJets100To200_2017",x_2017,chain_2017_WJets100To200);
  Eff_2017_WJets100To200.Set_Cut(cut);
  Eff_2017_WJets100To200.Analyze();
  delete chain_2017_WJets100To200;

  TChain* chain_2017_WJets200To400 = new TChain("KUAnalysis");
  chain_2017_WJets200To400->Add((path+"Fall17_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets200To400(outFile,Triggers_2017,"WJets200To400_2017",x_2017,chain_2017_WJets200To400);
  Eff_2017_WJets200To400.Set_Cut(cut);
  Eff_2017_WJets200To400.Analyze();
  delete chain_2017_WJets200To400;

  TChain* chain_2017_WJets400To600 = new TChain("KUAnalysis");
  chain_2017_WJets400To600->Add((path+"Fall17_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets400To600(outFile,Triggers_2017,"WJets400To600_2017",x_2017,chain_2017_WJets400To600);
  Eff_2017_WJets400To600.Set_Cut(cut);
  Eff_2017_WJets400To600.Analyze();
  delete chain_2017_WJets400To600;

  TChain* chain_2017_WJets600To800 = new TChain("KUAnalysis");
  chain_2017_WJets600To800->Add((path+"Fall17_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets600To800(outFile,Triggers_2017,"WJets600To800_2017",x_2017,chain_2017_WJets600To800);
  Eff_2017_WJets600To800.Set_Cut(cut);
  Eff_2017_WJets600To800.Analyze();
  delete chain_2017_WJets600To800;

  TChain* chain_2017_WJets800To1200 = new TChain("KUAnalysis");
  chain_2017_WJets800To1200->Add((path+"Fall17_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets800To1200(outFile,Triggers_2017,"WJets800To1200_2017",x_2017,chain_2017_WJets800To1200);
  Eff_2017_WJets800To1200.Set_Cut(cut);
  Eff_2017_WJets800To1200.Analyze();
  delete chain_2017_WJets800To1200;

  std::cout << "Processing WJets1200To2500 2017" << endl;
  TChain* chain_2017_WJets1200To2500 = new TChain("KUAnalysis");
  chain_2017_WJets1200To2500->Add((path+"Fall17_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets1200To2500(outFile,Triggers_2017,"WJets1200To2500_2017",x_2017,chain_2017_WJets1200To2500);
  Eff_2017_WJets1200To2500.Set_Cut(cut);
  Eff_2017_WJets1200To2500.Analyze();
  delete chain_2017_WJets1200To2500;

  std::cout << "Processing WJets2500ToInf 2017" << endl;
  TChain* chain_2017_WJets2500ToInf = new TChain("KUAnalysis");
  chain_2017_WJets2500ToInf->Add((path+"Fall17_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets2500ToInf(outFile,Triggers_2017,"WJets2500ToInf_2017",x_2017,chain_2017_WJets2500ToInf);
  Eff_2017_WJets2500ToInf.Set_Cut(cut);
  Eff_2017_WJets2500ToInf.Analyze();
  delete chain_2017_WJets2500ToInf;

  std::cout << "Processing Old WJets 2017" << endl;
  TChain* chain_2017_WJets_Old = new TChain("KUAnalysis");
  chain_2017_WJets_Old->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets_Old(outFile,Triggers_2017,"WJets_2017_Old",x_2017,chain_2017_WJets_Old);
  Eff_2017_WJets_Old.Set_Cut(cut);
  Eff_2017_WJets_Old.Analyze();
  delete chain_2017_WJets_Old;

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_TTJets(outFile,Triggers_2017,"TTJets_2017",x_2017,chain_2017_TTJets);
  Eff_2017_TTJets.Set_Cut(cut);
  Eff_2017_TTJets.Analyze();
  delete chain_2017_TTJets;

  std::cout << "Processing ZJetsToNuNu 2017" << endl;
  TChain* chain_2017_ZJetsToNuNu = new TChain("KUAnalysis");
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  chain_2017_ZJetsToNuNu->Add((path+"Fall17_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_ZJetsToNuNu(outFile,Triggers_2017,"ZJetsToNuNu_2017",x_2017,chain_2017_ZJetsToNuNu);
  Eff_2017_ZJetsToNuNu.Set_Cut(cut);
  Eff_2017_ZJetsToNuNu.Analyze();
 
/*
  std::cout << "Processing T2-4bd 500 490 2017" << endl;
  TChain* chain_2017_T2_4bd_500_490 = new TChain("SMS_500_490");
  chain_2017_T2_4bd_500_490->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_T2_4bd_500_490(outFile,Triggers_2017,"T2_4bd_500_490_2017",x_2017,chain_2017_T2_4bd_500_490);
  Eff_2017_T2_4bd_500_490.Set_Cut(cut);
  Eff_2017_T2_4bd_500_490.Analyze();
  delete chain_2017_T2_4bd_500_490;

  std::cout << "Processing T2-4bd 500 420 2017" << endl;
  TChain* chain_2017_T2_4bd_500_420 = new TChain("SMS_500_420");
  chain_2017_T2_4bd_500_420->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_T2_4bd_500_420(outFile,Triggers_2017,"T2_4bd_500_420_2017",x_2017,chain_2017_T2_4bd_500_420);
  Eff_2017_T2_4bd_500_420.Set_Cut(cut);
  Eff_2017_T2_4bd_500_420.Analyze();
  delete chain_2017_T2_4bd_500_420;
*/
 
  std::cout << "Processing WWTo2L2Nu 2017" << endl;
  TChain* chain_2017_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_WWTo2L2Nu->Add((path+"Fall17_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WWTo2L2Nu(outFile,Triggers_2017,"WWTo2L2Nu_2017",x_2017,chain_2017_WWTo2L2Nu);
  Eff_2017_WWTo2L2Nu.Set_Cut(cut);
  Eff_2017_WWTo2L2Nu.Analyze();
  delete chain_2017_WWTo2L2Nu;
 
/*
  std::cout << "Processing TChiWZ 2017" << endl;
  TChain* chain_2017_TChiWZ = new TChain("KUAnalysis");
  chain_2017_TChiWZ->Add((path+"Fall17_102X_SMS/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_TChiWZ(outFile,Triggers_2017,"TChiWZ_2017",x_2017,chain_2017_TChiWZ);
  Eff_2017_TChiWZ.Set_Cut(cut);
  Eff_2017_TChiWZ.Analyze();

  //DY
  std::cout << "Processing DY 2017" << endl;
  TChain* chain_2017_DY = new TChain("KUAnalysis");
  chain_2017_DY->Add((path+"Fall17_102X/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_DY(outFile,Triggers_2017,"DY_2017",x_2017,chain_2017_DY);
  Eff_2017_DY.Set_Cut(cut);
  Eff_2017_DY.Analyze();
*/
 //Data 2017
 //
 
  std::cout << "Processing SingleElectron 2017" << endl;
  TChain* chain_2017_SingleElectron = new TChain("KUAnalysis");
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_SingleElectron(outFile,Triggers_2017,"SingleElectron_2017",x_2017,chain_2017_SingleElectron);
  Eff_2017_SingleElectron.Set_Cut(cut); //+"_NeleBronzeG0"
  Eff_2017_SingleElectron.Analyze();
  delete chain_2017_SingleElectron;

  std::cout << "Processing SingleMuon 2017" << endl;
  TChain* chain_2017_SingleMuon = new TChain("KUAnalysis");
  chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleMuon->Add((path+"Fall17_102X_Data/SingleMuon_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_SingleMuon(outFile,Triggers_2017,"SingleMuon_2017",x_2017,chain_2017_SingleMuon);
  Eff_2017_SingleMuon.Set_Cut(cut); //+"_NmuBronzeG0"
  Eff_2017_SingleMuon.Analyze();
  delete chain_2017_SingleMuon;

 //2018
  //WJets
  std::cout << "Processing WJets 2018" << endl;
  TChain* chain_2018_WJets = new TChain("KUAnalysis");
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_WJets(outFile,Triggers_2018,"WJets_2018",x_2018,chain_2018_WJets);
  Eff_2018_WJets.Set_Cut(cut);
  Eff_2018_WJets.Analyze();
  delete chain_2018_WJets;

  //TTJets
  std::cout << "Processing TTJets 2018" << endl;
  TChain* chain_2018_TTJets = new TChain("KUAnalysis");
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_TTJets(outFile,Triggers_2018,"TTJets_2018",x_2018,chain_2018_TTJets);
  Eff_2018_TTJets.Set_Cut(cut);
  Eff_2018_TTJets.Analyze();
  delete chain_2018_TTJets;

  std::cout << "Processing WWTo2L2Nu 2018" << endl;
  TChain* chain_2018_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2018_WWTo2L2Nu->Add((path+"Autumn18_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_WWTo2L2Nu(outFile,Triggers_2018,"WWTo2L2Nu_2018",x_2018,chain_2018_WWTo2L2Nu);
  Eff_2018_WWTo2L2Nu.Set_Cut(cut);
  Eff_2018_WWTo2L2Nu.Analyze();
  delete chain_2018_WWTo2L2Nu;

  std::cout << "Processing ZJetsToNuNu 2018" << endl;
  TChain* chain_2018_ZJetsToNuNu = new TChain("KUAnalysis");
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-100To200_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-400To600_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-600To800_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-800To1200_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  chain_2018_ZJetsToNuNu->Add((path+"Autumn18_102X/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_ZJetsToNuNu(outFile,Triggers_2018,"ZJetsToNuNu_2018",x_2018,chain_2018_ZJetsToNuNu);
  Eff_2018_ZJetsToNuNu.Set_Cut(cut);
  Eff_2018_ZJetsToNuNu.Analyze();

 //Data 2018
 //
 
  std::cout << "Processing SingleElectron 2018" << endl;
  TChain* chain_2018_SingleElectron = new TChain("KUAnalysis");
//  chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
//  chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/EGamma_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_SingleElectron(outFile,Triggers_2018,"SingleElectron_2018",x_2018,chain_2018_SingleElectron);
  Eff_2018_SingleElectron.Set_Cut(cut);
  Eff_2018_SingleElectron.Analyze();
  delete chain_2018_SingleElectron;

  std::cout << "Processing SingleMuon 2018" << endl;
  TChain* chain_2018_SingleMuon = new TChain("KUAnalysis");
  chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018A-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018B-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018C-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
//  chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/SingleMuon_Run2018D-Nano25Oct2019-v1_2018_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_SingleMuon(outFile,Triggers_2018,"SingleMuon_2018",x_2018,chain_2018_SingleMuon);
  Eff_2018_SingleMuon.Set_Cut(cut);
  Eff_2018_SingleMuon.Analyze();
  delete chain_2018_SingleMuon;
 }  

}

int main(int argc, char* argv[])
{
 string outFile = "Eff_output_";
 string x = "";
 string cut = "";

 if(argc < 2)
 {
  cout << "ERROR: Need to specify x and cut" << endl;
  cout << "Example: ./run_Eff_Nano_Eff -x=MET -cut=PreSelection" << endl;
  return 1;
 }

 for(int i = 1; i < argc; i++)
 {
  if(strncmp(argv[i],"-x",2)==0)
  {
   x=argv[i];
   x.erase(0,3);
  }
  else if(strncmp(argv[i],"-cut",4)==0)
  {
   cut=argv[i];
   cut.erase(0,5);
  }
  else if(strncmp(argv[i],"-oFile",6)==0)
  {
   outFile=argv[i];
   outFile.erase(0,7);
  }
  else if(strncmp(argv[i],"--scale",7)==0)
  {
   Scale = true;
  }
 }
 if(Scale) outFile+="Scale_";
 outFile += x+"_"+cut+".root";

 Eff_Nano_Eff(outFile,x,cut);
 return 0;
}
