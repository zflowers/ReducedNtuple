#include <TROOT.h>
void run_Eff_Nano_Hist(string outFile = "output_test.root"){
 Long64_t start = gSystem->Now();
 gSystem->Exec(("rm "+outFile).c_str());
 gROOT->ProcessLine(".L Eff_Nano.h++");
 gROOT->ProcessLine(".L MET_2016_Triggers.h");
 gROOT->ProcessLine(".L MET_2017_Triggers.h");
 gROOT->ProcessLine(".L MET_2018_Triggers.h");
 gROOT->ProcessLine("vector<string> Triggers_2016 = Get_2016_Triggers()");
 gROOT->ProcessLine("vector<string> Triggers_2017 = Get_2017_Triggers()");
 gROOT->ProcessLine("vector<string> Triggers_2018 = Get_2018_Triggers()");
 gROOT->ProcessLine("string x_2016 = \"MET_pt\"");
 gROOT->ProcessLine("string x_2017 = \"METFixEE2017_pt\"");
 gROOT->ProcessLine("string x_2018 = \"MET_pt\"");
 gROOT->ProcessLine(".L Plotter_Eff_Nano.C++"); 
 
 //2016
  //WJets
  gROOT->ProcessLine("TChain* chain_2016_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_WJets->Add(\"../samples/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_WJets(\""+outFile+"\",Triggers_2016,\"WJets_2016\",x_2016,chain_2016_WJets)").c_str());
  gROOT->ProcessLine("Eff_2016_WJets.Analyze()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2016_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_TTJets->Add(\"../samples/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_TTJets(\""+outFile+"\",Triggers_2016,\"TTJets_2016\",x_2016,chain_2016_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2016_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2016_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2016.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_DY(\""+outFile+"\",Triggers_2016,\"DY_2016\",x_2016,chain_2016_DY)").c_str());
  gROOT->ProcessLine("Eff_2016_DY.Analyze()");
 /* 
  //TChiWZ
  gROOT->ProcessLine("TChain* chain_2016_TChiWZ = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_TChiWZ->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_TChiWZ(\""+outFile+"\",Triggers_2016,\"TChiWZ_2016\",x_2016,chain_2016_TChiWZ)").c_str());
  gROOT->ProcessLine("Eff_2016_TChiWZ.Analyze()");

  //Stops
  gROOT->ProcessLine("TChain* chain_2016_Stops = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_Stops->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_Stops(\""+outFile+"\",Triggers_2016,\"Stops_2016\",x_2016,chain_2016_Stops)").c_str());
  gROOT->ProcessLine("Eff_2016_Stops.Analyze()");
*/
 //2017
  //WJets
  gROOT->ProcessLine("TChain* chain_2017_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_WJets->Add(\"../samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_WJets(\""+outFile+"\",Triggers_2017,\"WJets_2017\",x_2017,chain_2017_WJets)").c_str());
  gROOT->ProcessLine("Eff_2017_WJets.Analyze()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2017_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_TTJets->Add(\"../samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2017.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_TTJets(\""+outFile+"\",Triggers_2017,\"TTJets_2017\",x_2017,chain_2017_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2017_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2017_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_2017.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_DY(\""+outFile+"\",Triggers_2017,\"DY_2017\",x_2017,chain_2017_DY)").c_str());
  gROOT->ProcessLine("Eff_2017_DY.Analyze()");
/*  
  //TChiWZ
  gROOT->ProcessLine("TChain* chain_2017_TChiWZ = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_TChiWZ->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_TChiWZ(\""+outFile+"\",Triggers_2017,\"TChiWZ_2017\",x_2017,chain_2017_TChiWZ)").c_str());
  gROOT->ProcessLine("Eff_2017_TChiWZ.Analyze()");

  //Stops
  gROOT->ProcessLine("TChain* chain_2017_Stops = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_Stops->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_Stops(\""+outFile+"\",Triggers_2017,\"Stops_2017\",x_2017,chain_2017_Stops)").c_str());
  gROOT->ProcessLine("Eff_2017_Stops.Analyze()");
*/
 //2018
  //WJets
  gROOT->ProcessLine("TChain* chain_2018_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_WJets->Add(\"../samples/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_WJets(\""+outFile+"\",Triggers_2018,\"WJets_2018\",x_2018,chain_2018_WJets)").c_str());
  gROOT->ProcessLine("Eff_2018_WJets.Analyze()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2018_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_TTJets->Add(\"../samples/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_TTJets(\""+outFile+"\",Triggers_2018,\"TTJets_2018\",x_2018,chain_2018_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2018_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2018_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_DY->Add(\"../samples/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_2018.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_DY(\""+outFile+"\",Triggers_2018,\"DY_2018\",x_2018,chain_2018_DY)").c_str());
  gROOT->ProcessLine("Eff_2018_DY.Analyze()");
 /* 
  //TChiWZ
  gROOT->ProcessLine("TChain* chain_2018_TChiWZ = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_TChiWZ->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_TChiWZ(\""+outFile+"\",Triggers_2018,\"TChiWZ_2018\",x_2018,chain_2018_TChiWZ)").c_str());
  gROOT->ProcessLine("Eff_2018_TChiWZ.Analyze()");

  //Stops
  gROOT->ProcessLine("TChain* chain_2018_Stops = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_Stops->Add(\"../samples/\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_Stops(\""+outFile+"\",Triggers_2018,\"Stops_2018\",x_2018,chain_2018_Stops)").c_str());
  gROOT->ProcessLine("Eff_2018_Stops.Analyze()");
*/
 gROOT->ProcessLine(".x Plotter_Eff_Nano.C");
 gSystem->Exec("make clean");
 Long64_t end = gSystem->Now();
 cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
 gROOT->ProcessLine(".qqqqqqq"); 
}
