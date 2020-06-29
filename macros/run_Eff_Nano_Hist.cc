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

/* 
 //2016
  std::cout << "Processing WJets 2016" << endl;
  //WJets
  TChain* chain_2016_WJets = new TChain("KUAnalysis");
  chain_2016_WJets->Add((path+"Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X.root").c_str());
  Eff_Nano Eff_2016_WJets(outFile,Triggers_2016,"WJets_2016",x_2016,chain_2016_WJets);
  Eff_2016_WJets.Analyze();
*/

 //2017
 
  //WJets
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_WJets(outFile,Triggers_2017,"WJets_2017",x_2017,chain_2017_WJets);
  Eff_2017_WJets.Set_Cut(cut);
  Eff_2017_WJets.Analyze();
  delete chain_2017_WJets;

  //TTJets
  std::cout << "Processing TTJets 2017" << endl;
  TChain* chain_2017_TTJets = new TChain("KUAnalysis");
  chain_2017_TTJets->Add((path+"Fall17_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_TTJets(outFile,Triggers_2017,"TTJets_2017",x_2017,chain_2017_TTJets);
  Eff_2017_TTJets.Set_Cut(cut);
  Eff_2017_TTJets.Analyze();
  delete chain_2017_TTJets;

  std::cout << "Processing T2-4bd 500 490 2017" << endl;
  TChain* chain_2017_T2_4bd_500_490 = new TChain("SMS_500_490");
  chain_2017_T2_4bd_500_490->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-490_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_T2_4bd_500_490(outFile,Triggers_2017,"T2_4bd_500_490_2017",x_2017,chain_2017_T2_4bd_500_490);
  Eff_2017_T2_4bd_500_490.Set_Cut(cut);
  Eff_2017_T2_4bd_500_490.Analyze();
  delete chain_2017_T2_4bd_500_490;

  std::cout << "Processing T2-4bd 500 420 2017" << endl;
  TChain* chain_2017_T2_4bd_500_420 = new TChain("SMS_500_420");
  chain_2017_T2_4bd_500_420->Add((path+"Fall17_102X_SMS/SMS-T2-4bd_genMET-80_mStop-500_mLSP-420_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_T2_4bd_500_420(outFile,Triggers_2017,"T2_4bd_500_420_2017",x_2017,chain_2017_T2_4bd_500_420);
  Eff_2017_T2_4bd_500_420.Set_Cut(cut);
  Eff_2017_T2_4bd_500_420.Analyze();
  delete chain_2017_T2_4bd_500_420;
/*
  std::cout << "Processing TChiWZ 2017" << endl;
  TChain* chain_2017_TChiWZ = new TChain("KUAnalysis");
  chain_2017_TChiWZ->Add((path+"Fall17_102X_SMS/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_TChiWZ(outFile,Triggers_2017,"TChiWZ_2017",x_2017,chain_2017_TChiWZ);
  Eff_2017_TChiWZ.Set_Cut(cut);
  Eff_2017_TChiWZ.Analyze();
*/
  std::cout << "Processing WWTo2L2Nu 2017" << endl;
  TChain* chain_2017_WWTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_WWTo2L2Nu->Add((path+"Fall17_102X/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_WWTo2L2Nu(outFile,Triggers_2017,"WWTo2L2Nu_2017",x_2017,chain_2017_WWTo2L2Nu);
  Eff_2017_WWTo2L2Nu.Set_Cut(cut);
  Eff_2017_WWTo2L2Nu.Analyze();
  delete chain_2017_WWTo2L2Nu;
/*
  std::cout << "Processing ZZTo2L2Nu 2017" << endl;
  TChain* chain_2017_ZZTo2L2Nu = new TChain("KUAnalysis");
  chain_2017_ZZTo2L2Nu->Add((path+"Fall17_102X/ZZTo2L2Nu_13TeV_powheg_pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_ZZTo2L2Nu(outFile,Triggers_2017,"ZZTo2L2Nu_2017",x_2017,chain_2017_ZZTo2L2Nu);
  Eff_2017_ZZTo2L2Nu.Set_Cut(cut);
  Eff_2017_ZZTo2L2Nu.Analyze();

  //DY
  std::cout << "Processing DY 2017" << endl;
  TChain* chain_2017_DY = new TChain("KUAnalysis");
  chain_2017_DY->Add((path+"Fall17_102X/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_Fall17_102X.root").c_str());
  Eff_Nano Eff_2017_DY(outFile,Triggers_2017,"DY_2017",x_2017,chain_2017_DY);
  Eff_2017_DY.Set_Cut(cut);
  Eff_2017_DY.Analyze();
*/

/*
 //2018
  //WJets
  std::cout << "Processing WJets 2018" << endl;
  TChain* chain_2018_WJets = new TChain("KUAnalysis");
  chain_2018_WJets->Add((path+"Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X.root").c_str());
  Eff_Nano Eff_2018_WJets(outFile,Triggers_2018,"WJets_2018",x_2018,chain_2018_WJets);
  Eff_2018_WJets.Analyze();
*/

 //std::cout << "Running Plotter" << endl;
 //Plotter_Eff_Nano(outFile.c_str());
}

void Eff_Nano_Hist(string outFile = "output_test.root", string cut = ""){
 std::cout << "Outputting to: " << outFile << endl;
 gSystem->Exec(("rm "+outFile).c_str());

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 string path = "~/../crogan/NTUPLES/NANO/NEW_31_05_20/";

 //2017
  //WJets
  std::cout << "Processing WJets 2017" << endl;
  TChain* chain_2017_WJets = new TChain("KUAnalysis");
  chain_2017_WJets->Add((path+"Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X.root").c_str(),0);
  Hist_Maker Hist_2017_WJets(outFile,"WJets_2017",chain_2017_WJets);
  Hist_2017_WJets.Set_Cut(cut);
  Hist_2017_WJets.Analyze();
  delete chain_2017_WJets;

}

void run_Eff_Nano_Hist()
{
 Long64_t start = gSystem->Now();
 vector<string> Files;
 string outFile = "Eff_output_";
 string x = "MET";

 vector<string> cut;

 //cut.push_back("NoCuts");
 //cut.push_back("PTISRG200");
 cut.push_back("PTISRG200_NlepG0_METtriggerE0_METG300");
 cut.push_back("PTISRG200_NlepG0_METtriggerE1_METG300");
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
//  Eff_Nano_Eff(outFile, x, cut[i]);
  outFile = "Eff_output_";
 }
 std::cout << "Running Plotter" << endl;
// Plotter_Eff_Nano(Files,cut);

 outFile = "Hist_output_";

 for(int i = 0; i < int(cut.size()); i++)
 {
  outFile += (cut[i] + ".root");
  Eff_Nano_Hist(outFile,cut[i]);
  outFile = "Hist_output_";
 }

 Long64_t end = gSystem->Now();
 std::cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
}

int main()
{
 run_Eff_Nano_Hist();
 return 0;
}

