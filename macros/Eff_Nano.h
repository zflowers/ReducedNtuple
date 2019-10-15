#ifndef EFF_NANO_H
#define EFF_NANO_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>

void Analyze(vector<string> vect_string_Trigger, string x, string year, TTree* fChain, string outFile){
   TLeaf* x_leaf = fChain->GetLeaf(x.c_str());
   vector<TLeaf*> vect_leaf;
   vector<TEfficiency*> vect_Eff;
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(vect_string_Trigger.at(i).c_str(),(vect_string_Trigger.at(i)+";"+x+";Efficiency").c_str(),20,0.,600.);
    vect_Eff.push_back(eff);
    TLeaf* trig = fChain->GetLeaf(vect_string_Trigger.at(i).c_str());
    vect_leaf.push_back(trig);
   }

   Long64_t nentries = fChain->GetEntriesFast();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = fChain->LoadTree(jentry);
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      x_leaf->GetBranch()->GetEntry(jentry);    
      for(int i=0; i < int(vect_string_Trigger.size()); i++)
      {
       vect_leaf.at(i)->GetBranch()->GetEntry(jentry);
       vect_Eff.at(i)->Fill(vect_leaf.at(i)->GetValue(),x_leaf->GetValue());
      }
   }
   TFile* output = new TFile(outFile.c_str(),"UPDATE");
   output->mkdir(year.c_str());
   output->cd(year.c_str());
   for(int i=0; i < int(vect_string_Trigger.size()); i++)
   {
    vect_Eff.at(i)->Write();
    delete vect_Eff.at(i);
   }
   output->Close();
   delete output;
};

#endif
