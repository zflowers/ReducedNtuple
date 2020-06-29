#include <iostream>
#include <algorithm>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include <vector>
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
  if( hist1f ) {cout << hist1f->GetName() << endl; hist1f->Write();}
  if( hist2f ) {cout << hist2f->GetName() << endl; hist2f->Write();}
  if( hist1d ) {cout << hist1d->GetName() << endl; hist1d->Write();}
  if( hist2d ) {cout << hist2d->GetName() << endl; hist2d->Write();}
  output->Close();
  delete output;
}

vector<HistClass*> Setup_Hists(TTree* tree);

#ifndef HISTCLASS_H
#define HISTCLASS_H

class Hist_Maker{
  private:
   string m_outFile = "output_test.root";
  protected:
   string m_Tag;
   TTree* m_Tree;
   string m_cut = "";
  public:
   Hist_Maker();
   Hist_Maker(string outFile, string Tag, TTree* Tree);
   void Analyze();
   void Set_Tag(string tag);
   void Set_Tree(TTree* tree);
   void Set_Output(string outFile);
   void Set_Cut(string cut);
   bool Get_Cut(const Long64_t& jentry, string name, string& current_cut);
   bool global_cuts(const Long64_t& jentry);
};

#endif

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

inline void Hist_Maker::Set_Tag(string tag)
{
 m_Tag = tag;
}

inline void Hist_Maker::Set_Tree(TTree* Tree)
{
 m_Tree = Tree;
}

inline void Hist_Maker::Set_Output(string outFile)
{
 m_outFile = outFile;
}

inline void Hist_Maker::Set_Cut(string cut)
{
 m_cut = cut+"_";
}

inline bool Hist_Maker::Get_Cut(const Long64_t& jentry, string name, string& current_cut)
{
 bool cut = false;
 if(current_cut.find(name) != std::string::npos)
 {
  TLeaf* leaf = m_Tree->GetLeaf(name.c_str());
  leaf->GetBranch()->GetEntry(jentry);
  string cut_value = get_str_between_two_str(current_cut,name,"_");
  string cut_type = get_str_between_two_str(current_cut,name,"_");
  if(cut_type.find("E") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(leaf->GetValue() == std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("Ge") != std::string::npos)
  {
   cut_value.erase(0,1);
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(leaf->GetValue() >= std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("G") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(leaf->GetValue() > std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("Le") != std::string::npos)
  {
   cut_value.erase(0,1);
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(leaf->GetValue() <= std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("L") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(leaf->GetValue() < std::stod(cut_value))
   {
    cut = true;
   }
  }
  eraseSubStr(current_cut,(name+cut_type+cut_value+"_"));
 }
 else
 {
  cout << "Couldn't find: " << name << " in: " << current_cut << "!" << endl;
 }
 return cut;
}

inline bool Hist_Maker::global_cuts(const Long64_t& jentry)
{
 //return false to keep the event
 //Example Cut
 ///////////////////////////////////////////////////////
 //TLeaf* CaloMET_pt_leaf = m_Tree->GetLeaf("CaloMET_pt");
 //CaloMET_pt_leaf->GetBranch()->GetEntry(jentry);
 //if(x_val/CaloMET_pt_leaf->GetValue() > 5.) cut = true;
 //this skips every event with MET/CaloMET > 5.
 ///////////////////////////////////////////////////////
 //
 //Calculate PFMHT
 //TLeaf* nJet_leaf = m_Tree->GetLeaf("nJet");
 //nJet_leaf->GetBranch()->GetEntry(jentry);
 //TLeaf* Jet_pt_leaf = m_Tree->GetLeaf("Jet_pt");
 //Jet_pt_leaf->GetBranch()->GetEntry(jentry);
 //TLeaf* Jet_eta_leaf = m_Tree->GetLeaf("Jet_eta");
 //Jet_eta_leaf->GetBranch()->GetEntry(jentry);
 //TLeaf* Jet_phi_leaf = m_Tree->GetLeaf("Jet_phi");
 //Jet_phi_leaf->GetBranch()->GetEntry(jentry);
 //TLeaf* Jet_mass_leaf = m_Tree->GetLeaf("Jet_mass");
 //Jet_mass_leaf->GetBranch()->GetEntry(jentry);
 //TLorentzVector MHT(0.,0.,0.,0.);
 //double HT = 0.;
 //for(int i = 0; i < nJet_leaf->GetValue(); i++)
 //{
 // HT+=Jet_pt_leaf->GetValue(i);
 // TLorentzVector dummy;
 // dummy.SetPtEtaPhiM(Jet_pt_leaf->GetValue(i),Jet_eta_leaf->GetValue(i),Jet_phi_leaf->GetValue(i),Jet_mass_leaf->GetValue(i));
 // MHT -= dummy;
 //}
 
 string current_cut = m_cut;

 bool PTISR_cut = true;
 bool MET_cut = true;
 bool Nmu_cut = true;
 bool Nele_cut = true;
 bool Nlep_cut = true;
 bool Njet_cut = true;
 bool METtrigger_cut = true;
 bool METORtrigger_cut = true;
 bool METHTtrigger_cut = true;

 if(current_cut.find("PTISR") != std::string::npos)
 {
  PTISR_cut = Get_Cut(jentry,"PTISR",current_cut);
 }

 if(current_cut.find("Nmu") != std::string::npos)
 {
  Nmu_cut = Get_Cut(jentry,"Nmu",current_cut);
 }

 if(current_cut.find("Nele") != std::string::npos)
 {
  Nele_cut = Get_Cut(jentry,"Nele",current_cut);
 }

 if(current_cut.find("Nlep") != std::string::npos)
 {
  Nlep_cut = Get_Cut(jentry,"Nlep",current_cut);
 }

 if(current_cut.find("Njet") != std::string::npos)
 {
  Njet_cut = Get_Cut(jentry,"Njet",current_cut);
 }

 if(current_cut.find("METtrigger") != std::string::npos)
 {
  METtrigger_cut = Get_Cut(jentry,"METtrigger",current_cut);
 }

 if(current_cut.find("METORtrigger") != std::string::npos)
 {
  METORtrigger_cut = Get_Cut(jentry,"METORtrigger",current_cut);
 }

 if(current_cut.find("METHTtrigger") != std::string::npos)
 {
  METHTtrigger_cut = Get_Cut(jentry,"METHTtrigger",current_cut);
 }

 if(current_cut.find("MET") != std::string::npos)
 {
  MET_cut = Get_Cut(jentry,"MET",current_cut);
 }

 if(current_cut.compare("NoCuts_") == 0)
 {
  return false;
 }

 if(current_cut.compare("") != 0)
 {
  cout << "ERROR: Some cuts not applied: " << current_cut << endl;
 }

 if(PTISR_cut && Nmu_cut && Nele_cut && Nlep_cut && Njet_cut && METtrigger_cut && METORtrigger_cut && METHTtrigger_cut)
 {
  return false;
 }
 return true;

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
