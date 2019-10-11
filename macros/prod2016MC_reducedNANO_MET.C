#define prod2016MC_reducedNANO_MET_cxx
#include "prod2016MC_reducedNANO_MET.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <iostream>

void prod2016MC_reducedNANO_MET::Loop()
{
   vector<string> vect_string_Trigger{
   "HLT_PFHT300_PFMET100",
   "HLT_PFHT300_PFMET110",
   "HLT_PFMET170_NotCleaned",
   "HLT_PFMET170_NoiseCleaned",
   "HLT_PFMET170_HBHECleaned",
   "HLT_PFMET170_JetIdCleaned",
   "HLT_PFMET170_BeamHaloCleaned",
   "HLT_PFMET170_HBHE_BeamHaloCleaned",
   "HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned",
   "HLT_PFMET90_PFMHT90_IDTight",
   "HLT_PFMET100_PFMHT100_IDTight",
   "HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned",
   "HLT_PFMET110_PFMHT110_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight",
   "HLT_MET100",
   "HLT_MET150",
   "HLT_MET200",
   "HLT_MET250",
   "HLT_MET300",
   "HLT_MET600",
   "HLT_MET700",
   "HLT_PFMET300",
   "HLT_PFMET400",
   "HLT_PFMET500",
   "HLT_PFMET600",
   };
   vector<TEfficiency*> vect_Eff;
   vector<bool> vect_bool;
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(vect_string_Trigger.at(i).c_str(),(vect_string_Trigger.at(i)+";MET_pt;#epsilon").c_str(),40,0.,1000.);
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
       vect_Eff.at(i)->Fill(vect_bool.at(i),MET_pt);
      }
   }
   TFile* output = new TFile(m_outFile.c_str(),"UPDATE"); 
   output->mkdir("2016");
   output->cd("2016");
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
