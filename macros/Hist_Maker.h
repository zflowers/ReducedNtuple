#include "Analysis_Base.h"
#include "KUAnalysis.C"

class HistClass{

  public:

  HistClass();
  ~HistClass();

  virtual void init_hist(TTree* tree);
  virtual void fill_hist(Long64_t jentry);
  virtual void write_hist( string output, string Tag );

  protected:

  TH1F* hist1f;
  TH2F* hist2f;
  TH1D* hist1d;
  TH2D* hist2d;
  KUAnalysis selector;

};

HistClass::HistClass(){

  hist1f = NULL;
  hist2f = NULL;
  hist1d = NULL;
  hist2d = NULL;

}

HistClass::~HistClass(){

  if( hist1f ) delete hist1f;
  if( hist2f ) delete hist2f;
  if( hist1d ) delete hist1d;
  if( hist2d ) delete hist2d;

}

void HistClass::init_hist(TTree* tree){
  // hist1d = new TH1D("HistClass","selectorHistClass", 2, -0.5, 1.5 );
  std::cout << "In Init from BaseClass !" << std::endl;
}

void HistClass::fill_hist(Long64_t jentry){
  std::cout << "Filling from BaseClass !" << std::endl;
}

void HistClass::write_hist( string outFile, string Tag ){
  TFile* output = new TFile(outFile.c_str(),"UPDATE");
  if(!(output->cd(Tag.c_str())))
  {  
   output->mkdir(Tag.c_str());
   output->cd(Tag.c_str());
  }
  else
  {
   output->cd(Tag.c_str());
  }
//  if( hist1f ) {cout << hist1f->GetName() << endl; hist1f->Write();}
//  if( hist2f ) {cout << hist2f->GetName() << endl; hist2f->Write();}
//  if( hist1d ) {cout << hist1d->GetName() << endl; hist1d->Write();}
//  if( hist2d ) {cout << hist2d->GetName() << endl; hist2d->Write();}

  if( hist1f ) {cout << hist1f->GetName() << endl; hist1f->SetDirectory(0); hist1f->Write();}
  if( hist2f ) {cout << hist2f->GetName() << endl; hist2f->SetDirectory(0); hist2f->Write();}
  if( hist1d ) {cout << hist1d->GetName() << endl; hist1d->SetDirectory(0); hist1d->Write();}
  if( hist2d ) {cout << hist2d->GetName() << endl; hist2d->SetDirectory(0); hist2d->Write();}
  output->Close();
  delete output;
}

vector<HistClass*> Setup_Hists(TTree* tree);

#ifndef HISTCLASS_H
#define HISTCLASS_H

class Hist_Maker:public Analysis_Base{
  public:
   Hist_Maker();
   Hist_Maker(string outFile, string Tag, TTree* Tree);
   void Analyze();
};

inline Hist_Maker::Hist_Maker()
{
 m_Tag = "";
 m_Tree = NULL;
 m_cut = "";
}

inline Hist_Maker::Hist_Maker(string outFile, string Tag, TTree* Tree)
{
 m_outFile = outFile;
 m_Tag = Tag;
 m_Tree = Tree;
}

inline void Hist_Maker::Analyze(){

   vector<HistClass*> Classes = Setup_Hists(m_Tree);
   Long64_t nentries = m_Tree->GetEntriesFast();
   Long64_t percent = 10.0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {      
      if(jentry%((std::max(nentries,percent))/percent) == 0) { cout << "Processing Event: " << jentry << " out of: " << nentries << " Entries" << endl; }

      Long64_t ientry = m_Tree->LoadTree(jentry);
      if(global_cuts(jentry)) continue;

      for( auto histclass : Classes ){ histclass->fill_hist(jentry); }
   }
   cout << "Finished Event Loop" << endl;

   for( auto histclass : Classes ){ histclass->write_hist(m_outFile,m_Tag); }
   for( auto histclass : Classes ){ delete histclass; }
}

class met_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void met_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("met_Hist","met_Hist",100,300.,1000.);
}
void met_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 m_Tree->GetEntry(jentry);
 hist1d->Fill(selector.MET, selector.weight*137.);
}

class dphiMET_lep_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_lep_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_lep_Hist","dphiMET_lep_Hist",100,-3.5,3.5);
}
void dphiMET_lep_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
// selector.b_PT_lep->GetEntry(jentry);
// selector.b_Eta_lep->GetEntry(jentry);
// selector.b_Phi_lep->GetEntry(jentry);
// selector.b_M_lep->GetEntry(jentry);
// selector.b_MET->GetEntry(jentry);
// selector.b_MET_phi->GetEntry(jentry);
// selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 lep.SetPtEtaPhiM(selector.PT_lep->at(0),selector.Eta_lep->at(0),selector.Phi_lep->at(0),selector.M_lep->at(0));
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);

 hist1d->Fill(MET.DeltaPhi(lep.Vect()),selector.weight*137.);
}

vector<HistClass*> Setup_Hists(TTree* tree){
 vector<HistClass*> Classes;
 Classes.push_back(new met_Hist);
 Classes.push_back(new dphiMET_lep_Hist);
 for( auto histclass : Classes ){ histclass->init_hist(tree); }
 return Classes;
}

#endif
