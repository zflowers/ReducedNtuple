#include <TROOT.h>
void run_Eff_Nano_Hist(string outFile = "output_test.root"){
 Long64_t start = gSystem->Now();
 gROOT->ProcessLine(".L Eff_Nano.h++");
 gROOT->ProcessLine(".L MET_2016_Triggers.h");
 gROOT->ProcessLine(".L MET_2017_Triggers.h");
 gROOT->ProcessLine(".L MET_2018_Triggers.h");
 gROOT->ProcessLine("vector<string> Triggers_2016 = Get_2016_Triggers()");
 //gROOT->ProcessLine("vector<string> Triggers_2017 = Get_2017_Triggers()");
 //gROOT->ProcessLine("vector<string> Triggers_2018 = Get_2018_Triggers()");
 gROOT->ProcessLine("string x_2016 = \"MET_pt\"");
 //gROOT->ProcessLine(".L Plotter_Eff_Nano.C++"); 
 
  gROOT->ProcessLine("TChain* chain_2016_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_WJets->Add(\"../samples/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_WJets(\""+outFile+"\",Triggers_2016,\"WJets_2016\",x_2016,chain_2016_WJets)").c_str());
  gROOT->ProcessLine("Eff_2016_WJets.Analyze()");
  //gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016_WJets(chain_2016_WJets)");
  //gROOT->ProcessLine("Eff_Nano Eff_2016_WJets(MET_2016_WJets)");
  //gROOT->ProcessLine("Eff_2016_WJets.SetTag(\"WJets_2016\")");
  //gROOT->ProcessLine("Eff_2016_WJets.Run()");
  //gROOT->ProcessLine("MET_2016_WJets.GetEntry(0)");
  //gROOT->ProcessLine("MET_2016_WJets.Loop()");

/* 
 //2016
  //WJets
  gROOT->ProcessLine("TChain* chain_2016_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_WJets->Add(\"../samples/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016_WJets(chain_2016_WJets)");
  gROOT->ProcessLine("Eff_Nano Eff_2016_WJets(MET_2016_WJets)");
  gROOT->ProcessLine("Eff_2016_WJets.SetTag(\"WJets_2016\")");
  gROOT->ProcessLine("Eff_2016_WJets.Run()");
  //gROOT->ProcessLine("MET_2016_WJets.GetEntry(0)");
  //gROOT->ProcessLine("MET_2016_WJets.Loop()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2016_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_TTJets->SetName(\"TTJets_2016\")");
  gROOT->ProcessLine("chain_2016_TTJets->Add(\"../samples/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016_TTJets(chain_2016_TTJets)");
  gROOT->ProcessLine("MET_2016_TTJets.GetEntry(0)");
  gROOT->ProcessLine("MET_2016_TTJets.Loop()");

  //DY
  gROOT->ProcessLine("TChain* chain_2016_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_DY->SetName(\"DY_2016\")");
  gROOT->ProcessLine("chain_2016_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016_DY(chain_2016_DY)");
  gROOT->ProcessLine("MET_2016_DY.GetEntry(0)");
  gROOT->ProcessLine("MET_2016_DY.Loop()");
  
  //TChiWZ
  gROOT->ProcessLine("TChain* chain_2016_TChiWZ = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_TChiWZ->SetName(\"TChiWZ_2016\")");
  gROOT->ProcessLine("chain_2016_TChiWZ->Add(\"../samples/SMS-TChiWZ_ZToLL_mZMin-0p1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine("prod2016MC_reducedNANO_MET MET_2016_TChiWZ(chain_2016_TChiWZ)");
  gROOT->ProcessLine("MET_2016_TChiWZ.GetEntry(0)");
  gROOT->ProcessLine("MET_2016_TChiWZ.Loop()");

 //2017
  //WJets
  gROOT->ProcessLine("TChain* chain_2017_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_WJets->SetName(\"WJets_2017\")");
  gROOT->ProcessLine("chain_2017_WJets->Add(\"../samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root\")");
  gROOT->ProcessLine("prod2017MC_reducedNANO_MET MET_2017_WJets(chain_2017_WJets)");
  gROOT->ProcessLine("MET_2017_WJets.GetEntry(0)");
  gROOT->ProcessLine("MET_2017_WJets.Loop()");
  gROOT->ProcessLine("delete chain_2017_WJets");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2017_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_TTJets->SetName(\"TTJets_2017\")");
  gROOT->ProcessLine("chain_2017_TTJets->Add(\"../samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root\")");
  gROOT->ProcessLine("prod2017MC_reducedNANO_MET MET_2017_TTJets(chain_2017_TTJets)");
  gROOT->ProcessLine("MET_2017_TTJets.GetEntry(0)");
  gROOT->ProcessLine("MET_2017_TTJets.Loop()");

  //DY
  gROOT->ProcessLine("TChain* chain_2017_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_DY->SetName(\"DY_2017\")");
  gROOT->ProcessLine("chain_2017_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_2017.root\")");
  gROOT->ProcessLine("prod2017MC_reducedNANO_MET MET_2017_DY(chain_2017_DY)");
  gROOT->ProcessLine("MET_2017_DY.GetEntry(0)");
  gROOT->ProcessLine("MET_2017_DY.Loop()");

 //2018
  //WJets
  gROOT->ProcessLine("TChain* chain_2018_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_WJets->SetName(\"WJets_2018\")");
  gROOT->ProcessLine("chain_2018_WJets->Add(\"../samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine("prod2018MC_reducedNANO_MET MET_2018_WJets(chain_2018_WJets)");
  gROOT->ProcessLine("MET_2018_WJets.GetEntry(0)");
  gROOT->ProcessLine("MET_2018_WJets.Loop()");
 
  //TTJets
  gROOT->ProcessLine("TChain* chain_2018_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_TTJets->SetName(\"TTJets_2018\")");
  gROOT->ProcessLine("chain_2018_TTJets->Add(\"../samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine("prod2018MC_reducedNANO_MET MET_2018_TTJets(chain_2018_TTJets)");
  gROOT->ProcessLine("MET_2018_TTJets.GetEntry(0)");
  gROOT->ProcessLine("MET_2018_TTJets.Loop()");
 
  //DY
  gROOT->ProcessLine("TChain* chain_2018_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_DY->SetName(\"DY_2018\")");
  gROOT->ProcessLine("chain_2018_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine("prod2018MC_reducedNANO_MET MET_2018_DY(chain_2018_DY)");
  gROOT->ProcessLine("MET_2018_DY.GetEntry(0)");
  gROOT->ProcessLine("MET_2018_DY.Loop()");

 gROOT->ProcessLine(".x Plotter_Eff_Nano.C");
 */
 gSystem->Exec("make clean");
 Long64_t end = gSystem->Now();
 cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
 gROOT->ProcessLine(".qqqqqqq"); 
}
