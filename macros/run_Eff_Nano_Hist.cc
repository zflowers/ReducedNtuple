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
#include "Eff_Nano_Eff.C"
#include "Eff_Nano_Hist.C"

using namespace std;

//THIS WILL NOT COMPILE IF MAIN FUNCTIONS EXIST IN Eff_Nano_Eff.C and Eff_Nano_Hist.C !!!

void run_Eff_Nano_Hist()
{
 Long64_t start = gSystem->Now();
 vector<string> Files;
 string outFile = "Eff_output_";
 string x = "MET";
 //string x2 = "PTCM";

 vector<string> cut;

 cut.push_back("NoCuts");
 //cut.push_back("PTISRG200");
 //cut.push_back("PTISRG200_EventFilterE0");
 cut.push_back("NeleBronzeG0");
 cut.push_back("NeleSilverG0");
 cut.push_back("NeleGoldG0");
 cut.push_back("NmuBronzeG0");
 cut.push_back("NmuSilverG0");
 cut.push_back("NmuGoldG0");
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
//  Eff_Nano_Hist(outFile,cut[i]);
  outFile = "Hist_output_";
 }

// Stacker(Files,cut);

 Long64_t end = gSystem->Now();
 std::cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
}

int main()
{
 run_Eff_Nano_Hist();
 return 0;
}

