#ifndef EFF_NANO_H
#define EFF_NANO_H

#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"
#include "Analysis_Base.h"

using namespace std;

class Eff_Nano:public Analysis_Base{
  private:
   bool Other_Bools(const Long64_t& jentry);
   vector<string> m_Triggers;
   string m_x;
  public:
   Eff_Nano();
   Eff_Nano(string outFile, vector<string> Triggers, string Tag, string x, TTree* Tree);
   void Analyze();
   void Set_Triggers_2016();
   void Set_Triggers_2017();
   void Set_Triggers_2018();
   void Set_x(string x);
};

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

inline void Eff_Nano::Set_x(string x)
{
 m_x = x;
}

inline void Eff_Nano::Analyze(){
   TBranch* weight_branch = NULL;
   Double_t weight = 0.;
   m_Tree->SetBranchAddress("weight",&weight,&weight_branch);
   TBranch* x_branch = NULL;
   Double_t x = 0.;
   m_Tree->SetBranchAddress(m_x.c_str(),&x,&x_branch);
   vector<TEfficiency*> vect_Eff;
   //bins is number of bins-1
   //array size is the number of bins
   int bins = 20;
   double* bin_edges_ptr = NULL;
   if(m_x == "MET")
   {
    bins = 23;
    double bin_edges[24] = {150.,160.,170.,175.,180.,185.,190.,195.,200.,205.,210.,215.,220.,225.,230.,235.,240.,245.,250.,275.,300.,350.,400.,500.};
    bin_edges_ptr = bin_edges;
   }
   else if(m_x == "RISR")
   {
    bins = 9;
    double bin_edges[10] = {.5,.6,.7,.8,.9,.95,1.,1.05,1.1,1.2};
    bin_edges_ptr = bin_edges;
   }
   else if(m_x == "PTCM")
   {
    bins = 23;
    double bin_edges[24] = {0.,10.,20.,30.,40.,50.,60.,70.,80.,90.,100.,110.,120.,130.,140.,150.,160.,170.,180.,190.,300.,350.,400.,500.};
    bin_edges_ptr = bin_edges;
   }
   else { cout << "Couldn't find x = " << m_x << " for binning " << endl; }
   for(int i=0; i < int(m_Triggers.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(m_Triggers.at(i).c_str(),(m_Triggers.at(i)+";"+m_x+";Efficiency").c_str(),bins,bin_edges_ptr);
    eff->SetUseWeightedEvents();
    eff->SetStatisticOption(TEfficiency::kBUniform);
    vect_Eff.push_back(eff);
   }
   TEfficiency* eff = new TEfficiency("SuperOR",("SuperOR;"+m_x+";Efficiency").c_str(),bins,bin_edges_ptr);
   eff->SetUseWeightedEvents();
   eff->SetStatisticOption(TEfficiency::kBUniform);
   vect_Eff.push_back(eff);

   Long64_t nentries = m_Tree->GetEntriesFast();
   Long64_t percent = 20.0;
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = m_Tree->LoadTree(jentry);
      //nb = m_Tree->GetEntry(jentry);   nbytes += nb;
      x_branch->GetEntry(jentry);    
      weight_branch->GetEntry(jentry);    
      if(jentry%((std::max(nentries,percent))/percent) == 0) { cout << "Processing Event: " << jentry << " out of: " << nentries << " Entries" << endl; }
      if(global_cuts(jentry)) continue;
      bool SuperOR = false;
      for(int i=0; i < int(m_Triggers.size()); i++)
      {
       TBranch* branch = NULL;
       Bool_t trig = 0;
       m_Tree->SetBranchAddress(m_Triggers.at(i).c_str(),&trig,&branch);
       branch->GetEntry(jentry);
       vect_Eff.at(i)->FillWeighted(trig,weight,x);
       SuperOR = (SuperOR || trig);
      }
      vect_Eff.at(int(vect_Eff.size()-1))->FillWeighted(SuperOR,weight,x);
   }
   cout << "Finished Event Loop" << endl;
   TFile* output = new TFile(m_outFile.c_str(),"UPDATE");
   output->mkdir(m_Tag.c_str());
   output->cd(m_Tag.c_str());
   for(int i=0; i < int(vect_Eff.size()); i++)
   {
    vect_Eff.at(i)->SetDirectory(0);
    vect_Eff.at(i)->Write();
    delete vect_Eff.at(i);
   }
   output->Close();
   delete output;
}

#endif
