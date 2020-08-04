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

 //2016
/*
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
  Hist_Maker Hist_2016_WJets(outFile,"WJets_2016",chain_2016_WJets);
  Hist_2016_WJets.Set_Cut(cut);
  Hist_2016_WJets.Analyze();
  delete chain_2016_WJets;

  //TTJets
  std::cout << "Processing TTJets 2016" << endl;
  TChain* chain_2016_TTJets = new TChain("KUAnalysis");
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  chain_2016_TTJets->Add((path+"Summer16_102X/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str(),0);
  Hist_Maker Hist_2016_TTJets(outFile,"TTJets_2016",chain_2016_TTJets);
  Hist_2016_TTJets.Set_Cut(cut);
  Hist_2016_TTJets.Analyze();
  delete chain_2016_TTJets;
*/
/*
  std::cout << "Processing WWTo2L2Nu 2016" << endl;
  TChain* chain_2016_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2016_WWTo2L2Nu->Add((path+"Summer16_102X/WWTo2L2Nu_13TeV-powheg_Summer16_102X.root").c_str(),0);
  Hist_Maker Hist_2016_WWTo2L2Nu(outFile,"WWTo2L2Nu_2016",chain_2016_WWTo2L2Nu);
  Hist_2016_WWTo2L2Nu.Set_Cut(cut);
  Hist_2016_WWTo2L2Nu.Analyze();
  delete chain_2016_WWTo2L2Nu;
*/
 
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
  Hist_Maker Hist_2017_WJets(outFile,"WJets_2017",chain_2017_WJets);
  Hist_2017_WJets.Set_Cut(cut);
  Hist_2017_WJets.Analyze();
  delete chain_2017_WJets;

  std::cout << "Processing Old WJets 2017" << endl;
  TChain* chain_2017_WJets_Old = new TChain("KUAnalysis");
  chain_2017_WJets_Old->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_WJets_Old(outFile,"WJets_2017_Old",chain_2017_WJets_Old);
  Hist_2017_WJets_Old.Set_Cut(cut);
  Hist_2017_WJets_Old.Analyze();
  delete chain_2017_WJets_Old;

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_TTJets(outFile,"TTJets_2017",chain_2017_TTJets);
  Hist_2017_TTJets.Set_Cut(cut);
  Hist_2017_TTJets.Analyze();
  delete chain_2017_TTJets;

 /*
  std::cout << "Processing WWTo2L2Nu 2017" << endl;
  TChain* chain_2017_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_WWTo2L2Nu->Add((path+"Fall17_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_WWTo2L2Nu(outFile,"WWTo2L2Nu_2017",chain_2017_WWTo2L2Nu);
  Hist_2017_WWTo2L2Nu.Set_Cut(cut);
  Hist_2017_WWTo2L2Nu.Analyze();
  delete chain_2017_WWTo2L2Nu;
*/ 

 //2018
 /*
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
  Hist_Maker Hist_2018_WJets(outFile,"WJets_2018",chain_2018_WJets);
  Hist_2018_WJets.Set_Cut(cut);
  Hist_2018_WJets.Analyze();
  delete chain_2018_WJets;

  //TTJets
  std::cout << "Processing TTJets 2018" << endl;
  TChain* chain_2018_TTJets = new TChain("KUAnalysis");
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  chain_2018_TTJets->Add((path+"Autumn18_102X/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str(),0);
  Hist_Maker Hist_2018_TTJets(outFile,"TTJets_2018",chain_2018_TTJets);
  Hist_2018_TTJets.Set_Cut(cut);
  Hist_2018_TTJets.Analyze();
  delete chain_2018_TTJets;

  std::cout << "Processing WWTo2L2Nu 2018" << endl;
  TChain* chain_2018_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2018_WWTo2L2Nu->Add((path+"Autumn18_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Autumn18_102X.root").c_str(),0);
  Hist_Maker Hist_2018_WWTo2L2Nu(outFile,"WWTo2L2Nu_2018",chain_2018_WWTo2L2Nu);
  Hist_2018_WWTo2L2Nu.Set_Cut(cut);
  Hist_2018_WWTo2L2Nu.Analyze();
  delete chain_2018_WWTo2L2Nu;
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
