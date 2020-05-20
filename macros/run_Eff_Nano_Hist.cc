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
#include "Plotter_Eff_Nano.C"
using namespace std;

void run_Eff_Nano_Hist(string outFile = "output_test_KU.root"){
 Long64_t start = gSystem->Now();
 gSystem->Exec(("rm "+outFile).c_str());
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
 //.L Plotter_Eff_Nano.C; //++
 
 std::vector<string> Triggers_2016 = Get_2016_Triggers();
 std::vector<string> Triggers_2017 = Get_2017_Triggers();
 std::vector<string> Triggers_2018 = Get_2018_Triggers();
 string x_2016 = "MET_pt";
 string x_2017 = "METFixEE2017_pt";
 string x_2018 = "MET_pt";

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 string path = "~/../crogan/NTUPLES/NANO/NEW_12_05_20/";
 x_2016 = "MET";
 x_2017 = "MET";
 x_2018 = "MET";

/* 
 //2016
  std::cout << "Processing WJets 2016" << endl;
  //WJets
  TChain* chain_2016_WJets = new TChain("KUAnalysis");
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str());
  Eff_Nano Eff_2016_WJets(outFile,Triggers_2016,"WJets_2016",x_2016,chain_2016_WJets);
  Eff_2016_WJets.Analyze();

  //TTJets
  std::cout << "Processing TTJets 2016" << endl;
  TChain* chain_2016_TTJets = new TChain("KUAnalysis");
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str());
  Eff_Nano Eff_2016_TTJets(outFile,Triggers_2016,"TTJets_2016",x_2016,chain_2016_TTJets);
  Eff_2016_TTJets.Analyze();

  //DY
  std::cout << "Processing DY 2016" << endl;
  TChain* chain_2016_DY = new TChain("KUAnalysis");
  chain_2016_DY->Add((path+"Summer16_102X/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str());
  Eff_Nano Eff_2016_DY(outFile,Triggers_2016,"DY_2016",x_2016,chain_2016_DY);
  Eff_2016_DY.Analyze();
*/

 //2017
 
  //WJets
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_WJets(outFile,Triggers_2017,"WJets_2017",x_2017,chain_2017_WJets);
  Eff_2017_WJets.Analyze();

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_TTJets(outFile,Triggers_2017,"TTJets_2017",x_2017,chain_2017_TTJets);
  Eff_2017_TTJets.Analyze();

  std::cout << "Processing T2-4bd 500 490 2017" << endl;
  TChain* chain_2017_T2_4bd_500_490 = new TChain("SMS_500_490");
  chain_2017_T2_4bd_500_490->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_T2_4bd_500_490(outFile,Triggers_2017,"T2_4bd_500_490_2017",x_2017,chain_2017_T2_4bd_500_490);
  Eff_2017_T2_4bd_500_490.Analyze();

  std::cout << "Processing T2-4bd 500 420 2017" << endl;
  TChain* chain_2017_T2_4bd_500_420 = new TChain("SMS_500_420");
  chain_2017_T2_4bd_500_420->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_T2_4bd_500_420(outFile,Triggers_2017,"T2_4bd_500_420_2017",x_2017,chain_2017_T2_4bd_500_420);
  Eff_2017_T2_4bd_500_420.Analyze();
/*
  std::cout << "Processing TChiWZ 2017" << endl;
  TChain* chain_2017_TChiWZ = new TChain("KUAnalysis");
  chain_2017_TChiWZ->Add((path+"Fall17_102X_SMS/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_TChiWZ(outFile,Triggers_2017,"TChiWZ_2017",x_2017,chain_2017_TChiWZ);
  Eff_2017_TChiWZ.Analyze();
*/
  std::cout << "Processing WWTo2L2Nu 2017" << endl;
  TChain* chain_2017_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_WWTo2L2Nu->Add((path+"Fall17_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_WWTo2L2Nu(outFile,Triggers_2017,"WWTo2L2Nu_2017",x_2017,chain_2017_WWTo2L2Nu);
  Eff_2017_WWTo2L2Nu.Analyze();

  std::cout << "Processing ZZTo2L2Nu 2017" << endl;
  TChain* chain_2017_ZZTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_ZZTo2L2Nu->Add((path+"Fall17_102X/ZZTo2L2Nu_13TeV_powheg_pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_ZZTo2L2Nu(outFile,Triggers_2017,"ZZTo2L2Nu_2017",x_2017,chain_2017_ZZTo2L2Nu);
  Eff_2017_ZZTo2L2Nu.Analyze();

  //DY
  std::cout << "Processing DY 2017" << endl;
  TChain* chain_2017_DY = new TChain("KUAnalysis");
  chain_2017_DY->Add((path+"Fall17_102X/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_DY(outFile,Triggers_2017,"DY_2017",x_2017,chain_2017_DY);
  Eff_2017_DY.Analyze();


/*
 //2018
  //WJets
  std::cout << "Processing WJets 2018" << endl;
  TChain* chain_2018_WJets = new TChain("KUAnalysis");
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str());
  Eff_Nano Eff_2018_WJets(outFile,Triggers_2018,"WJets_2018",x_2018,chain_2018_WJets);
  Eff_2018_WJets.Analyze();

  //TTJets
  std::cout << "Processing TTJets 2018" << endl;
  TChain* chain_2018_TTJets = new TChain("KUAnalysis");
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str());
  Eff_Nano Eff_2018_TTJets(outFile,Triggers_2018,"TTJets_2018",x_2018,chain_2018_TTJets);
  Eff_2018_TTJets.Analyze();

  //DY
  std::cout << "Processing DY 2018" << endl;
  TChain* chain_2018_DY = new TChain("KUAnalysis");
  chain_2018_DY->Add((path+"Autumn18_102X/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str());
  Eff_Nano Eff_2018_DY(outFile,Triggers_2018,"DY_2018",x_2018,chain_2018_DY);
  Eff_2018_DY.Analyze();
*/

 std::cout << "Running Plotter" << endl;
 Plotter_Eff_Nano(outFile.c_str());
 Long64_t end = gSystem->Now();
 std::cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
}

int main()
{
 run_Eff_Nano_Hist("output_test_KU.root");
 return 0;
}

