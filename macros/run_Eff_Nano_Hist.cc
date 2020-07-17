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
#include "Stacker.C"
#include "Hist_Maker.h"

using namespace std;

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
 //.L Plotter_Eff_Nano.C; //++
 
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

 //2016
 
  //WJets
  std::cout << "Processing WJets 2016" << endl;
  TChain* chain_2016_WJets = new TChain("KUAnalysis");
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_WJets(outFile,Triggers_2016,"WJets_2016",x_2016,chain_2016_WJets);
  Eff_2016_WJets.Set_Cut(cut);
  Eff_2016_WJets.Analyze();
  delete chain_2016_WJets;

  //TTJets
  std::cout << "Processing TTJets 2016" << endl;
  TChain* chain_2016_TTJets = new TChain("KUAnalysis");
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
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

 //Data 2016
 //
  std::cout << "Processing SingleElectron 2016" << endl;
  TChain* chain_2016_SingleElectron = new TChain("KUAnalysis");
  chain_2016_SingleElectron->Add((path+"Summer16_102X_Data/SingleElectron_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_SingleElectron(outFile,Triggers_2016,"SingleElectron_2016",x_2016,chain_2016_SingleElectron);
  Eff_2016_SingleElectron.Set_Cut(cut);
  Eff_2016_SingleElectron.Analyze();
  delete chain_2016_SingleElectron;

  std::cout << "Processing SingleMuon 2016" << endl;
  TChain* chain_2016_SingleMuon = new TChain("KUAnalysis");
  chain_2016_SingleMuon->Add((path+"Summer16_102X_Data/SingleMuon_Run2016C-Nano25Oct2019-v1_2016_Summer16_102X.root").c_str(),0);
  Eff_Nano Eff_2016_SingleMuon(outFile,Triggers_2016,"SingleMuon_2016",x_2016,chain_2016_SingleMuon);
  Eff_2016_SingleMuon.Set_Cut(cut);
  Eff_2016_SingleMuon.Analyze();
  delete chain_2016_SingleMuon;

 //2017
  //WJets
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_WJets(outFile,Triggers_2017,"WJets_2017",x_2017,chain_2017_WJets);
  Eff_2017_WJets.Set_Cut(cut);
  Eff_2017_WJets.Analyze();
  delete chain_2017_WJets;

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_TTJets(outFile,Triggers_2017,"TTJets_2017",x_2017,chain_2017_TTJets);
  Eff_2017_TTJets.Set_Cut(cut);
  Eff_2017_TTJets.Analyze();
  delete chain_2017_TTJets;

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
*/

/*
  std::cout << "Processing ZZTo2L2Nu 2017" << endl;
  TChain* chain_2017_ZZTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_ZZTo2L2Nu->Add((path+"Fall17_102X/ZZTo2L2Nu_13TeV_powheg_pythia8_Fall17_102X.root").c_str(),0);
  Eff_Nano Eff_2017_ZZTo2L2Nu(outFile,Triggers_2017,"ZZTo2L2Nu_2017",x_2017,chain_2017_ZZTo2L2Nu);
  Eff_2017_ZZTo2L2Nu.Set_Cut(cut);
  Eff_2017_ZZTo2L2Nu.Analyze();

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
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  Eff_Nano Eff_2018_WJets(outFile,Triggers_2018,"WJets_2018",x_2018,chain_2018_WJets);
  Eff_2018_WJets.Set_Cut(cut);
  Eff_2018_WJets.Analyze();
  delete chain_2018_WJets;

  //TTJets
  std::cout << "Processing TTJets 2018" << endl;
  TChain* chain_2018_TTJets = new TChain("KUAnalysis");
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
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

 //Data 2018
 //
 /*
  std::cout << "Processing SingleElectron 2018" << endl;
  TChain* chain_2018_SingleElectron = new TChain("KUAnalysis");
  chain_2018_SingleElectron->Add((path+"Autumn18_102X_Data/").c_str(),0);
  Eff_Nano Eff_2018_SingleElectron(outFile,Triggers_2018,"SingleElectron_2018",x_2018,chain_2018_SingleElectron);
  Eff_2018_SingleElectron.Set_Cut(cut);
  Eff_2018_SingleElectron.Analyze();
  delete chain_2018_SingleElectron;

  std::cout << "Processing SingleMuon 2018" << endl;
  TChain* chain_2018_SingleMuon = new TChain("KUAnalysis");
  chain_2018_SingleMuon->Add((path+"Autumn18_102X_Data/").c_str(),0);
  Eff_Nano Eff_2018_SingleMuon(outFile,Triggers_2018,"SingleMuon_2018",x_2018,chain_2018_SingleMuon);
  Eff_2018_SingleMuon.Set_Cut(cut);
  Eff_2018_SingleMuon.Analyze();
  delete chain_2018_SingleMuon;
*/

 //std::cout << "Running Plotter" << endl;
 //Plotter_Eff_Nano(outFile.c_str());
}

void Eff_Nano_Hist(string outFile = "output_test.root", string cut = ""){
 std::cout << "Outputting to: " << outFile << endl;
 gSystem->Exec(("rm "+outFile).c_str());

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 string path = "~/../crogan/NTUPLES/NANO/NEW_31_05_20/";

/* 
 //2016
  std::cout << "Processing WJets 2016" << endl;
  //WJets
  TChain* chain_2016_WJets = new TChain("KUAnalysis");
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  Hist_Maker Hist_2016_WJets(outFile,"WJets_2016",chain_2016_WJets);
  Hist_2016_WJets.Analyze();
*/

 //2017
 
  //WJets
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_WJets(outFile,"WJets_2017",chain_2017_WJets);
  Hist_2017_WJets.Set_Cut(cut);
  Hist_2017_WJets.Analyze();
  delete chain_2017_WJets;

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_TTJets(outFile,"TTJets_2017",chain_2017_TTJets);
  Hist_2017_TTJets.Set_Cut(cut);
  Hist_2017_TTJets.Analyze();
  delete chain_2017_TTJets;

  std::cout << "Processing SingleElectron 2017" << endl;
  TChain* chain_2017_SingleElectron = new TChain("KUAnalysis");
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017B-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017C-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017D-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017E-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  chain_2017_SingleElectron->Add((path+"Fall17_102X_Data/SingleElectron_Run2017F-Nano25Oct2019-v1_2017_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_SingleElectron(outFile,"SingleElectron_2017",chain_2017_SingleElectron);
  Hist_2017_SingleElectron.Set_Cut(cut);
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
  Hist_2017_SingleMuon.Set_Cut(cut);
  Hist_2017_SingleMuon.Analyze();
  delete chain_2017_SingleMuon;

/*
  std::cout << "Processing T2-4bd 500 490 2017" << endl;
  TChain* chain_2017_T2_4bd_500_490 = new TChain("SMS_500_490");
  chain_2017_T2_4bd_500_490->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_T2_4bd_500_490(outFile,"T2_4bd_500_490_2017",chain_2017_T2_4bd_500_490);
  Hist_2017_T2_4bd_500_490.Set_Cut(cut);
  Hist_2017_T2_4bd_500_490.Analyze();
  delete chain_2017_T2_4bd_500_490;

  std::cout << "Processing T2-4bd 500 420 2017" << endl;
  TChain* chain_2017_T2_4bd_500_420 = new TChain("SMS_500_420");
  chain_2017_T2_4bd_500_420->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_T2_4bd_500_420(outFile,"T2_4bd_500_420_2017",chain_2017_T2_4bd_500_420);
  Hist_2017_T2_4bd_500_420.Set_Cut(cut);
  Hist_2017_T2_4bd_500_420.Analyze();
  delete chain_2017_T2_4bd_500_420;
*/
/*
  std::cout << "Processing TChiWZ 2017" << endl;
  TChain* chain_2017_TChiWZ = new TChain("KUAnalysis");
  chain_2017_TChiWZ->Add((path+"Fall17_102X_SMS/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_TChiWZ(outFile,"TChiWZ_2017",chain_2017_TChiWZ);
  Hist_2017_TChiWZ.Set_Cut(cut);
  Hist_2017_TChiWZ.Analyze();

  std::cout << "Processing WWTo2L2Nu 2017" << endl;
  TChain* chain_2017_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_WWTo2L2Nu->Add((path+"Fall17_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_WWTo2L2Nu(outFile,"WWTo2L2Nu_2017",chain_2017_WWTo2L2Nu);
  Hist_2017_WWTo2L2Nu.Set_Cut(cut);
  Hist_2017_WWTo2L2Nu.Analyze();
  delete chain_2017_WWTo2L2Nu;

  std::cout << "Processing ZZTo2L2Nu 2017" << endl;
  TChain* chain_2017_ZZTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_ZZTo2L2Nu->Add((path+"Fall17_102X/ZZTo2L2Nu_13TeV_powheg_pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_ZZTo2L2Nu(outFile,"ZZTo2L2Nu_2017",chain_2017_ZZTo2L2Nu);
  Hist_2017_ZZTo2L2Nu.Set_Cut(cut);
  Hist_2017_ZZTo2L2Nu.Analyze();

  //DY
  std::cout << "Processing DY 2017" << endl;
  TChain* chain_2017_DY = new TChain("KUAnalysis");
  chain_2017_DY->Add((path+"Fall17_102X/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_DY(outFile,"DY_2017",chain_2017_DY);
  Hist_2017_DY.Set_Cut(cut);
  Hist_2017_DY.Analyze();
*/

/*
 //2018
  //WJets
  std::cout << "Processing WJets 2018" << endl;
  TChain* chain_2018_WJets = new TChain("KUAnalysis");
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  Hist_Maker Hist_2018_WJets(outFile,"WJets_2018",chain_2018_WJets);
  Hist_2018_WJets.Analyze();
*/
}

void run_Eff_Nano_Hist()
{
 Long64_t start = gSystem->Now();
 vector<string> Files;
 string outFile = "Eff_output_";
 string x = "MET";
 //string x2 = "PTCM";
 //string x = "Electron_Pt";

 vector<string> cut;

 //cut.push_back("NoCuts");
 cut.push_back("PTISRG200");
 cut.push_back("PTISRG200_EventFilterE0");
 cut.push_back("PTISRG200_NeleBronzeG0");
 cut.push_back("PTISRG200_NmuBronzeG0");
 cut.push_back("PTISRG200_NeleSilverG0");
 cut.push_back("PTISRG200_NmuSilverG0");
 cut.push_back("PTISRG200_NeleGoldG0");
 cut.push_back("PTISRG200_NmuGoldG0");
 //cut.push_back("PTISRG200_NlepG0");
 //cut.push_back("PTISRG200_PTCML50");
 //cut.push_back("PTISRG200_PTCML100");
 //cut.push_back("PTISRG200_PTCML50_dphiCMIG1");
 //cut.push_back("PTISRG200_NlepE0");
 //cut.push_back("PTISRG200_NlepE1");
 //cut.push_back("PTISRG200_NlepE2");
 //cut.push_back("METtriggerE0");
 //cut.push_back("PTISRG200_NlepG0_NjetG3");



 //cut.push_back("PTISRG200_METG300");
 //cut.push_back("PTISRG200_NjetGe4");
 //cut.push_back("PTISRG200_NjetL4");
 //cut.push_back("PTISR200_NmuE0_NJetSGe1_NeleE0");
 //cut.push_back("PTISR200_NmuGe1_NJetSE0_NeleGe1");
 //cut.push_back("PTISR200_NmuGe1_NJetSGe1_NeleGe1");

 for(int i = 0; i < int(cut.size()); i++)
 {
  outFile += (x + "_" + cut[i] + ".root");
  Files.push_back(outFile);
  Eff_Nano_Eff(outFile, x, cut[i]);
  outFile = "Eff_output_";
  //outFile += (x2 + "_" + cut[i] + ".root");
  //Files.push_back(outFile);
  //Eff_Nano_Eff(outFile, x2, cut[i]);
  //outFile = "Eff_output_";
 }

 Plotter_Eff_Nano(Files,cut);
 Files.clear();

 cut.clear();
 //cut.push_back("PTISRG200_NlepG0_METG300_METtriggerE0");
 //cut.push_back("PTISRG200_NlepG0_METG300_METtriggerE1");
 cut.push_back("PTISRG200_NlepG0_METG300_EventFilterE0");
 cut.push_back("PTISRG200_NlepG0_METG300_EventFilterE1");
 cut.push_back("PTISRG200_NlepG0_EventFilterE0");
 cut.push_back("PTISRG200_NlepG0_EventFilterE1");

 outFile = "Hist_output_";

 for(int i = 0; i < int(cut.size()); i++)
 {
  outFile += (cut[i] + ".root");
  Files.push_back(outFile);
  Eff_Nano_Hist(outFile,cut[i]);
  outFile = "Hist_output_";
 }

 Stacker(Files,cut);

 Long64_t end = gSystem->Now();
 std::cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
}

int main()
{
 run_Eff_Nano_Hist();
 return 0;
}

