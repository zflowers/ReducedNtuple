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

int main(int argc, char* argv[])
{
 string outFile = "Eff_output_";
 string cut = "";

 if(argc < 1)
 {
  cout << "ERROR: Need to specify cut" << endl;
  cout << "Example: ./run_Eff_Nano_Hist -cut=NoCuts" << endl;
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

 Eff_Nano_Hist(outFile,cut);
 return 0;
}
