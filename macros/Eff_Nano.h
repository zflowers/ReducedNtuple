#ifndef EFF_NANO_H
#define EFF_NANO_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>

class Eff_Nano{
  private:
   bool global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val);
   prod2016MC_reducedNANO_MET m_MET_2016(NULL);
   prod2017MC_reducedNANO_MET m_MET_2017(NULL);
   prod2018MC_reducedNANO_MET m_MET_2018(NULL);
   string m_outFile = "output_test.root";
   string m_Tag;
   string x;
  public:
   Eff_Nano();
   Eff_Nano(prod2016MC_reducedNANO_MET MET_2016);
   Eff_Nano(prod2017MC_reducedNANO_MET MET_2017);
   Eff_Nano(prod2018MC_reducedNANO_MET MET_2018);
   void Analyze(vector<string> vect_string_Trigger, string x, TTree* fChain);
   void SetOutput(string outFile);
};

#endif

#define Eff_Nano_cxx

inline Eff_Nano::Eff_Nano()
{
 m_outFile = "output_test.root";
}

inline Eff_Nano::Eff_Nano(prod2016MC_reducedNANO_MET MET_2016)
{
 m_MET_2016 = MET_2016;
}

inline Eff_Nano::Eff_Nano(prod2017MC_reducedNANO_MET MET_2017)
{
 m_MET_2017 = MET_2017;
}

inline Eff_Nano::Eff_Nano(prod2018MC_reducedNANO_MET MET_2018)
{
 m_MET_2018 = MET_2018;
}

inline void Eff_Nano::Run()
{
 if(MET_2016 != NULL){ LoadTriggers_MET_2016() }
}

inline vector<string> LoadTriggers_MET_2016()
{
 //load vector of triggers
 //call Analyze
}

inline bool Eff_Nano::global_cuts(TTree*& fChain, const Long64_t& jentry, double x_val)
{
 bool cut = true;
 TLeaf* CaloMET_pt_leaf = fChain->GetLeaf("CaloMET_pt");
 CaloMET_pt_leaf->GetBranch()->GetEntry(jentry);
 if(x_val/CaloMET_pt_leaf->GetValue() < 5.) cut = false;
 return cut;
}

inline void Eff_Nano::Analyze(vector<string> vect_string_Trigger, string x, TTree* fChain){
   TLeaf* x_leaf = fChain->GetLeaf(x.c_str());
   TLeaf* weight_leaf = fChain->GetLeaf("Generator_weight");
   vector<TLeaf*> vect_leaf;
   vector<TEfficiency*> vect_Eff;
   int bins = 32;
   double bin_edges[33] = {0.,50.,60.,70.,80.,90.,100.,110.,120.,130.,140.,150.,160.,170.,180.,190.,200.,210.,220.,230.,240.,250.,260.,270.,280.,290.,300.,350.,400.,450.,500.,600.,1000.};
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(vect_string_Trigger.at(i).c_str(),(vect_string_Trigger.at(i)+";"+x+";Efficiency").c_str(),bins,bin_edges);
    vect_Eff.push_back(eff);
    TLeaf* trig = fChain->GetLeaf(vect_string_Trigger.at(i).c_str());
    vect_leaf.push_back(trig);
   }

   Long64_t nentries = fChain->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = fChain->LoadTree(jentry);
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      x_leaf->GetBranch()->GetEntry(jentry);    
      weight_leaf->GetBranch()->GetEntry(jentry);    
      if(global_cuts(fChain,jentry,x_leaf->GetValue())) continue;
      for(int i=0; i < int(vect_string_Trigger.size()); i++)
      {
       vect_leaf.at(i)->GetBranch()->GetEntry(jentry);
       vect_Eff.at(i)->FillWeighted(vect_leaf.at(i)->GetValue(),weight_leaf->GetValue(),x_leaf->GetValue());
      }
   }
   TFile* output = new TFile(m_outFile.c_str(),"UPDATE");
   output->mkdir(fChain->GetName());
   output->cd(fChain->GetName());
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    vect_Eff.at(i)->Write();
    delete vect_Eff.at(i);
   }
   output->Close();
   delete output;
}
