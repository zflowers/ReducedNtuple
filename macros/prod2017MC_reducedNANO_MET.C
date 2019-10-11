#define prod2017MC_reducedNANO_MET_cxx
#include "prod2017MC_reducedNANO_MET.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <iostream>

void prod2017MC_reducedNANO_MET::Loop()
{
   vector<string> vect_string_Trigger{
   "HLT_PFHT500_PFMET100_PFMHT100_IDTight",
   "HLT_PFHT500_PFMET110_PFMHT110_IDTight",
   "HLT_PFHT700_PFMET85_PFMHT85_IDTight",
   "HLT_PFHT700_PFMET95_PFMHT95_IDTight",
   "HLT_PFHT800_PFMET75_PFMHT75_IDTight",
   "HLT_PFHT800_PFMET85_PFMHT85_IDTight",
   "HLT_PFMET110_PFMHT110_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight",
   "HLT_PFMET130_PFMHT130_IDTight",
   "HLT_PFMET140_PFMHT140_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight_PFHT60",
   "HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60",
   "HLT_PFMETTypeOne110_PFMHT110_IDTight",
   "HLT_PFMETTypeOne120_PFMHT120_IDTight",
   "HLT_PFMETTypeOne130_PFMHT130_IDTight",
   "HLT_PFMETTypeOne140_PFMHT140_IDTight",
   "HLT_PFMET200_NotCleaned",
   "HLT_PFMET200_HBHECleaned",
   "HLT_PFMET250_HBHECleaned",
   "HLT_PFMET300_HBHECleaned",
   "HLT_PFMET200_HBHE_BeamHaloCleaned",
   "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
   "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
   "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
   };
   vector<TEfficiency*> vect_Eff;
   vector<bool> vect_bool;
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(vect_string_Trigger.at(i).c_str(),(vect_string_Trigger.at(i)+";METFixEE2017_pt;#epsilon").c_str(),40,0.,1000.);
    vect_Eff.push_back(eff);
    vect_bool.push_back(true);
   }

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      //loop through all triggers and see if it is true
      for(int i=0; i < int(vect_string_Trigger.size()); i++)
      {
       vect_bool.at(i) = *(fChain->GetBranch(vect_string_Trigger.at(i).c_str())->GetAddress());
       vect_Eff.at(i)->Fill(vect_bool.at(i),METFixEE2017_pt);
      }
   }
   TFile* output = new TFile(m_outFile.c_str(),"UPDATE"); 
   output->mkdir("2017");
   output->cd("2017");
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    TCanvas* canv = new TCanvas(vect_string_Trigger.at(i).c_str(),vect_string_Trigger.at(i).c_str(),750,500);
    canv->cd();
    vect_Eff.at(i)->Draw("AP");
    canv->Write();
    delete canv;
    delete vect_Eff.at(i);
   }
   output->Close();
   delete output;
}
