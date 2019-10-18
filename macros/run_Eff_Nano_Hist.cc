#include <TROOT.h>
void run_Eff_Nano_Hist(string outFile = "output_test.root"){
 Long64_t start = gSystem->Now();
 gSystem->Exec(("rm "+outFile).c_str());
 gROOT->ProcessLine(".L Eff_Nano.h++");
 gROOT->ProcessLine(".x prod2016MC_reducedNANO_MET.C++");
 gROOT->ProcessLine(".x prod2017MC_reducedNANO_MET.C++");
 gROOT->ProcessLine(".x prod2018MC_reducedNANO_MET.C++");
 gROOT->ProcessLine(".L Plotter_Eff_Nano.C++"); 
  
 //2016
 gROOT->ProcessLine("TChain* chain_2016 = new TChain(\"Events\")");
 gROOT->ProcessLine("chain_2016->Add(\"../samples/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
 gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016(chain_2016)");
 gROOT->ProcessLine(("MET_2016.SetOutput(\""+outFile+"\")").c_str());
 gROOT->ProcessLine("MET_2016.GetEntry(0)");
 gROOT->ProcessLine("MET_2016.Loop()");
  
 //2017
 gROOT->ProcessLine("TChain* chain_2017 = new TChain(\"Events\")");
 gROOT->ProcessLine("chain_2017->Add(\"../samples/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root\")");
 gROOT->ProcessLine("prod2017MC_reducedNANO_MET MET_2017(chain_2017)");
 gROOT->ProcessLine(("MET_2017.SetOutput(\""+outFile+"\")").c_str());
 gROOT->ProcessLine("MET_2017.GetEntry(0)");
 gROOT->ProcessLine("MET_2017.Loop()");

 //2018
 gROOT->ProcessLine("TChain* chain_2018 = new TChain(\"Events\")");
 gROOT->ProcessLine("chain_2018->Add(\"../samples/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
 gROOT->ProcessLine("prod2018MC_reducedNANO_MET MET_2018(chain_2018)");
 gROOT->ProcessLine(("MET_2018.SetOutput(\""+outFile+"\")").c_str());
 gROOT->ProcessLine("MET_2018.GetEntry(0)");
 gROOT->ProcessLine("MET_2018.Loop()");
 
 gROOT->ProcessLine((".x Plotter_Eff_Nano.C(\""+outFile+"\")").c_str()); 
 gSystem->Exec("make clean");
 Long64_t end = gSystem->Now();
 cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
 gROOT->ProcessLine(".q"); 
}
