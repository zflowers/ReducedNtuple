#ifndef EFF_NANO_H
#define EFF_NANO_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"

class Eff_Nano{
  private:
   bool global_cuts(const Long64_t& jentry, double x_val);
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
 bool cut = true;
 TLeaf* CaloMET_pt_leaf = m_Tree->GetLeaf("CaloMET_pt");
 CaloMET_pt_leaf->GetBranch()->GetEntry(jentry);
 if(x_val/CaloMET_pt_leaf->GetValue() < 5.) cut = false;
 return cut;
}

inline void Eff_Nano::Analyze(){
   TLeaf* x_leaf = m_Tree->GetLeaf(m_x.c_str());
   TLeaf* weight_leaf = m_Tree->GetLeaf("Generator_weight");
   vector<TLeaf*> vect_leaf;
   vector<TEfficiency*> vect_Eff;
   int bins = 32;
   double bin_edges[33] = {0.,50.,60.,70.,80.,90.,100.,110.,120.,130.,140.,150.,160.,170.,180.,190.,200.,210.,220.,230.,240.,250.,260.,270.,280.,290.,300.,350.,400.,450.,500.,600.,1000.};
   for(int i=0; i < int(m_Triggers.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(m_Triggers.at(i).c_str(),(m_Triggers.at(i)+";"+m_x+";Efficiency").c_str(),bins,bin_edges);
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
      for(int i=0; i < int(m_Triggers.size()); i++)
      {
       vect_leaf.at(i)->GetBranch()->GetEntry(jentry);
       vect_Eff.at(i)->FillWeighted(vect_leaf.at(i)->GetValue(),weight_leaf->GetValue(),x_leaf->GetValue());
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
