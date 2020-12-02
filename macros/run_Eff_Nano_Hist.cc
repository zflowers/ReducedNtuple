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

 cut.push_back("NmuGoldE1");

 for(int i = 0; i < int(cut.size()); i++)
 {
  outFile += (x + "_" + cut[i] + ".root");
  Files.push_back(outFile);
  Eff_Nano_Hist(outFile, x, cut[i]);
 }

 Files.clear();
 cut.clear();

/*
 cut.push_back("PreSelection");

 outFile = "Hist_output_";

 for(int i = 0; i < int(cut.size()); i++)
 {
  outFile += (cut[i] + ".root");
  Files.push_back(outFile);
  Eff_Nano_Hist(outFile,cut[i]);
  outFile = "Hist_output_";
 }
*/
 Long64_t end = gSystem->Now();
 std::cout << "Time to Run: " << (end-start)/1000.0 << " seconds" << endl;
}

/*
int main()
{
 run_Eff_Nano_Hist();
 return 0;
}
*/
