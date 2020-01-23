#ifndef EFF_NANO_H
#define EFF_NANO_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"

class Eff_Nano{
  private:
   bool global_cuts(const Long64_t& jentry, double x_val);
   bool Other_Bools(const Long64_t& jentry);
   string m_outFile = "output_test.root";
   vector<string> m_Triggers;
   string m_Tag;
   string m_x;
   TTree* m_Tree;
  public:
   Eff_Nano();
   Eff_Nano(string outFile, vector<string> Triggers, string Tag, string x, TTree* Tree);
   void Analyze();
   void Set_Triggers_2016();
   void Set_Triggers_2017();
   void Set_Triggers_2018();
   void Set_Tag(string tag);
   void Set_x(string x);
   void Set_Tree(TTree* tree);
   void Set_Output(string outFile);
};

#endif

#define Eff_Nano_cxx

inline Eff_Nano::Eff_Nano()
{
 cout << "Do Not Use This Constructor!" << endl;
 cout << "Use This One: " << endl;
 cout << "Eff_Nano(string outFile, vector<string> Triggers, string Tag, string x, TTree* Tree)" << endl;
 cout << "Probably Going To Crash Now... " << endl;
}

inline Eff_Nano::Eff_Nano(string outFile, vector<string> Triggers, string Tag, string x, TTree* Tree)
{
 m_outFile = outFile;
 m_Triggers = Triggers;
 m_Tag = Tag;
 m_x = x;
 m_Tree = Tree;
}

inline void Eff_Nano::Set_Triggers_2016()
{
 m_Triggers = Get_2016_Triggers(); 
}

inline void Eff_Nano::Set_Triggers_2017()
{
 m_Triggers = Get_2017_Triggers(); 
}

inline void Eff_Nano::Set_Triggers_2018()
{
 m_Triggers = Get_2018_Triggers(); 
}

inline void Eff_Nano::Set_Tag(string tag)
{
 m_Tag = tag;
}

inline void Eff_Nano::Set_x(string x)
{
 m_x = x;
}

inline void Eff_Nano::Set_Tree(TTree* Tree)
{
 m_Tree = Tree;
}

inline void Eff_Nano::Set_Output(string outFile)
{
 m_outFile = outFile;
}

inline bool Eff_Nano::global_cuts(const Long64_t& jentry, double x_val)
{
 bool cut = false;
 //Example Cut
 //cut = true means skip that event
 ///////////////////////////////////////////////////////
 //TLeaf* CaloMET_pt_leaf = m_Tree->GetLeaf("CaloMET_pt");
 //CaloMET_pt_leaf->GetBranch()->GetEntry(jentry);
 //if(x_val/CaloMET_pt_leaf->GetValue() > 5.) cut = true;
 ///////////////////////////////////////////////////////
 //Calculate PFMHT
 TLeaf* nJet_leaf = m_Tree->GetLeaf("nJet");
 nJet_leaf->GetBranch()->GetEntry(jentry);

 TLeaf* Jet_pt_leaf = m_Tree->GetLeaf("Jet_pt");
 Jet_pt_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Jet_eta_leaf = m_Tree->GetLeaf("Jet_eta");
 Jet_eta_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Jet_phi_leaf = m_Tree->GetLeaf("Jet_phi");
 Jet_phi_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Jet_mass_leaf = m_Tree->GetLeaf("Jet_mass");
 Jet_mass_leaf->GetBranch()->GetEntry(jentry);

 TLorentzVector MHT(0.,0.,0.,0.);
 double HT = 0.;
 for(int i = 0; i < nJet_leaf->GetValue(); i++)
 {
  HT+=Jet_pt_leaf->GetValue(i);
  TLorentzVector dummy;
  dummy.SetPtEtaPhiM(Jet_pt_leaf->GetValue(i),Jet_eta_leaf->GetValue(i),Jet_phi_leaf->GetValue(i),Jet_mass_leaf->GetValue(i));
  MHT -= dummy;
 }
 //if (MHT.Pt() < 300.) { cut = true; }
 if(HT < 300.) { cut = true; }
 
 return cut;
}

inline bool Eff_Nano::Other_Bools(const Long64_t& jentry)
{
 bool other = false;
 //Example Other
 ///////////////////////////////////////////////////////
 //TLeaf* CaloMET_pt_leaf = m_Tree->GetLeaf("CaloMET_pt");
 //CaloMET_pt_leaf->GetBranch()->GetEntry(jentry);
 //if(x_val/CaloMET_pt_leaf->GetValue() > 5.) other = true;
 /////////////////////////////////////////////////////// 
 return other;
}

inline void Eff_Nano::Analyze(){
   TLeaf* x_leaf = m_Tree->GetLeaf(m_x.c_str());
   TLeaf* weight_leaf = m_Tree->GetLeaf("Generator_weight");
   vector<TLeaf*> vect_leaf;
   vector<TEfficiency*> vect_Eff;
   //bins is number of bins-1
   int bins = 15;
   //array size is the number of bins
   double bin_edges[16] = {0.,50.,75.,100.,125.,150.,175.,200.,225.,250.,275.,300.,350.,400.,500.,750.};
   for(int i=0; i < int(m_Triggers.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(m_Triggers.at(i).c_str(),(m_Triggers.at(i)+";"+m_x+";Efficiency").c_str(),bins,bin_edges);
    //eff->SetUseWeightedEvents();
    //eff->SetStatisticOption(TEfficiency::kFNormal);
    vect_Eff.push_back(eff);
    TLeaf* trig = m_Tree->GetLeaf(m_Triggers.at(i).c_str());
    vect_leaf.push_back(trig);
   }

   Long64_t nentries = m_Tree->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = m_Tree->LoadTree(jentry);
      //nb = m_Tree->GetEntry(jentry);   nbytes += nb;
      x_leaf->GetBranch()->GetEntry(jentry);    
      weight_leaf->GetBranch()->GetEntry(jentry);    
      if(global_cuts(jentry,x_leaf->GetValue())) continue;
      if(jentry > 250000) break;
      for(int i=0; i < int(m_Triggers.size()); i++)
      {
       vect_leaf.at(i)->GetBranch()->GetEntry(jentry);
       //vect_Eff.at(i)->FillWeighted(vect_leaf.at(i)->GetValue(),weight_leaf->GetValue(),x_leaf->GetValue());
       //vect_Eff.at(i)->Fill((vect_leaf.at(i)->GetValue() && Other_Bools(jentry)),x_leaf->GetValue());
       vect_Eff.at(i)->Fill(vect_leaf.at(i)->GetValue(),x_leaf->GetValue());
      }
   }
   TFile* output = new TFile(m_outFile.c_str(),"UPDATE");
   output->mkdir(m_Tag.c_str());
   output->cd(m_Tag.c_str());
   for(int i=0; i < int(m_Triggers.size()); i++)
   {
    vect_Eff.at(i)->Write();
    delete vect_Eff.at(i);
   }
   output->Close();
   delete output;
}
