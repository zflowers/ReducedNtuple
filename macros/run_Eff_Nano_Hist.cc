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
  gROOT->ProcessLine("chain_2016_WJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Summer16_102X/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_WJets(\""+outFile+"\",Triggers_2016,\"WJets_2016\",x_2016,chain_2016_WJets)").c_str());
  gROOT->ProcessLine("Eff_2016_WJets.Analyze()");
/*
  //TTJets
  gROOT->ProcessLine("TChain* chain_2016_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_TTJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Summer16_102X/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_TTJets(\""+outFile+"\",Triggers_2016,\"TTJets_2016\",x_2016,chain_2016_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2016_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2016_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2016_DY->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Summer16_102X/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2016_DY(\""+outFile+"\",Triggers_2016,\"DY_2016\",x_2016,chain_2016_DY)").c_str());
  gROOT->ProcessLine("Eff_2016_DY.Analyze()");

 //2017
  //WJets
  gROOT->ProcessLine("TChain* chain_2017_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_WJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Fall17_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_WJets(\""+outFile+"\",Triggers_2017,\"WJets_2017\",x_2017,chain_2017_WJets)").c_str());
  gROOT->ProcessLine("Eff_2017_WJets.Analyze()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2017_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_TTJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Fall17_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_TTJets(\""+outFile+"\",Triggers_2017,\"TTJets_2017\",x_2017,chain_2017_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2017_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2017_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2017_DY->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Fall17_102X/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_Fall17_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2017_DY(\""+outFile+"\",Triggers_2017,\"DY_2017\",x_2017,chain_2017_DY)").c_str());
  gROOT->ProcessLine("Eff_2017_DY.Analyze()");

 //2018
  //WJets
  gROOT->ProcessLine("TChain* chain_2018_WJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_WJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_WJets(\""+outFile+"\",Triggers_2018,\"WJets_2018\",x_2018,chain_2018_WJets)").c_str());
  gROOT->ProcessLine("Eff_2018_WJets.Analyze()");

  //TTJets
  gROOT->ProcessLine("TChain* chain_2018_TTJets = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_TTJets->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Autumn18_102X/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_TTJets(\""+outFile+"\",Triggers_2018,\"TTJets_2018\",x_2018,chain_2018_TTJets)").c_str());
  gROOT->ProcessLine("Eff_2018_TTJets.Analyze()");

  //DY
  gROOT->ProcessLine("TChain* chain_2018_DY = new TChain(\"Events\")");
  gROOT->ProcessLine("chain_2018_DY->Add(\"/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/root/Autumn18_102X/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/*.root\")");
  gROOT->ProcessLine(("Eff_Nano Eff_2018_DY(\""+outFile+"\",Triggers_2018,\"DY_2018\",x_2018,chain_2018_DY)").c_str());
  gROOT->ProcessLine("Eff_2018_DY.Analyze()");
*/
 //gROOT->ProcessLine(".x Plotter_Eff_Nano.C");
 gSystem->Exec("make clean");
 Long64_t end = gSystem->Now();
 cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
 gROOT->ProcessLine(".qqqqqqq"); 
}
