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
 hist1d = new TH1D("met_Hist","",100,300.,1000.);
 hist1d->GetXaxis()->SetTitle("MET");
}
void met_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 hist1d->Fill(selector.MET, selector.weight);
}

class met_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void met_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("met_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("MET_phi");
}
void met_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 hist1d->Fill(selector.MET_phi, selector.weight);
}

class PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("PTCM_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("PTCM");
}
void PTCM_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 hist1d->Fill(selector.PTCM, selector.weight);
}

class ele_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void ele_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("ele_PT_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("ele_PT");
}
void ele_PT_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.PT_lep->at(i), selector.weight);
  }
  break;
 }
}

class mu_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void mu_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("mu_PT_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("mu_PT");
}
void mu_PT_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.PT_lep->at(i), selector.weight);
  break;
 }
}

class ele_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void ele_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("ele_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("ele_Phi");
}
void ele_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.Phi_lep->at(i), selector.weight);
  }
  break;
 }
}

class mu_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void mu_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("mu_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("mu_Phi");
}
void mu_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.Phi_lep->at(i), selector.weight);
  break;
 }
}

class dphiMET_lep_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_lep_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_lep_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,lep}");
}
void dphiMET_lep_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 lep.SetPtEtaPhiM(selector.PT_lep->at(0),selector.Eta_lep->at(0),selector.Phi_lep->at(0),selector.M_lep->at(0));
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);

 hist1d->Fill(MET.DeltaPhi(lep.Vect()),selector.weight);
}

class dphiMET_ele_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_ele_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_ele_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
}
void dphiMET_ele_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(MET.DeltaPhi(lep.Vect()),selector.weight);
  }
  break;
 }
}

class dphiMET_mu_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_mu_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_mu_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
}
void dphiMET_mu_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(MET.DeltaPhi(lep.Vect()),selector.weight);
  }
  break;
 }
}

class dphiCMI_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiCMI_Hist","",100,0.,3.5);
 hist1d->GetXaxis()->SetTitle("dphiCMI");
}
void dphiCMI_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 hist1d->Fill(selector.dphiCMI,selector.weight);
}

class dphiCMI_v_PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_PTCM_Hist","",100,0.,3.5,100,0.,200.);
 hist2d->GetXaxis()->SetTitle("dphiCMI");
 hist2d->GetYaxis()->SetTitle("PTCM");
}
void dphiCMI_v_PTCM_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 hist2d->Fill(selector.dphiCMI,selector.PTCM,selector.weight);
}

class jet_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void jet_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("jet_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("jet_Phi");
}
void jet_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Njet->GetEntry(jentry);
 selector.b_Phi_jet->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Njet; i++)
 {
  hist1d->Fill(selector.Phi_jet->at(i), selector.weight);
 }
}

class jet_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void jet_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("jet_PT_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("jet_PT");
}
void jet_PT_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Njet->GetEntry(jentry);
 selector.b_PT_jet->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.Njet; i++)
 {
  hist1d->Fill(selector.PT_jet->at(i), selector.weight);
 }
}

class ele_PT_proj_MET_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void ele_PT_proj_MET_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("ele_PT_proj_MET_Hist","",100,0.,100.);
 hist1d->GetXaxis()->SetTitle("ele_PT_proj_MET");
}
void ele_PT_proj_MET_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(lep.Vect().Dot(MET.Unit()),selector.weight);
  }
  break;
 }
}

class ele_PT_proj_METperp_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void ele_PT_proj_METperp_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("ele_PT_proj_METperp_Hist","",100,0.,100.);
 hist1d->GetXaxis()->SetTitle("ele_PT_proj_METperp");
}
void ele_PT_proj_METperp_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 TVector3 zHat(0.,0.,1.);
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(lep.Vect().Dot(MET.Cross(zHat).Unit()),selector.weight);
  }
  break;
 }
}

class mu_PT_proj_MET_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void mu_PT_proj_MET_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("mu_PT_proj_MET_Hist","",100,0.,100.);
 hist1d->GetXaxis()->SetTitle("mu_PT_proj_MET");
}
void mu_PT_proj_MET_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(lep.Vect().Dot(MET.Unit()),selector.weight);
  }
  break;
 }
}

class mu_PT_proj_METperp_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void mu_PT_proj_METperp_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("mu_PT_proj_METperp_Hist","",100,0.,100.);
 hist1d->GetXaxis()->SetTitle("mu_PT_proj_METperp");
}
void mu_PT_proj_METperp_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 selector.b_PT_lep->GetEntry(jentry);
 selector.b_Eta_lep->GetEntry(jentry);
 selector.b_Phi_lep->GetEntry(jentry);
 selector.b_M_lep->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_Nlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector lep;
 TVector3 MET;
 TVector3 zHat(0.,0.,1.);
 MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   lep.SetPtEtaPhiM(selector.PT_lep->at(i),selector.Eta_lep->at(i),selector.Phi_lep->at(i),selector.M_lep->at(i));
   hist1d->Fill(lep.Vect().Dot(MET.Cross(zHat).Unit()),selector.weight);
  }
  break;
 }
}

//gen quantities
class genmet_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmet_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 hist1d = new TH1D("genmet_Hist","",100,0.,700.);
 hist1d->GetXaxis()->SetTitle("genMET");
}
void genmet_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_genMET->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 hist1d->Fill(selector.genMET, selector.weight);
}

class genmet_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmet_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genmet_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("genMET_phi");
}
void genmet_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genMET_phi->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 hist1d->Fill(selector.genMET_phi, selector.weight);
}

class genele_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genele_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genele_PT_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("genele_PT");
}
void genele_PT_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.genPT_lep->at(i), selector.weight);
  }
  break;
 }
}

class genmu_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmu_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genmu_PT_Hist","",100,0.,200.);
 hist1d->GetXaxis()->SetTitle("genmu_PT");
}
void genmu_PT_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.genPT_lep->at(i), selector.weight);
  break;
 }
}

class genele_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genele_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genele_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("genele_Phi");
}
void genele_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genPhi_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.genPhi_lep->at(i), selector.weight);
  }
  break;
 }
}

class genele_Eta_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genele_Eta_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genele_Eta_Hist","",100,-5.,5.);
 hist1d->GetXaxis()->SetTitle("genele_Eta");
}
void genele_Eta_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genEta_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.genEta_lep->at(i), selector.weight);
  }
  break;
 }
}

class genmu_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmu_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genmu_Phi_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("genmu_Phi");
}
void genmu_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genPhi_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.genPhi_lep->at(i), selector.weight);
  break;
 }
}

class genmu_Eta_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmu_Eta_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genmu_Eta_Hist","",100,-5.,5.);
 hist1d->GetXaxis()->SetTitle("genmu_Eta");
}
void genmu_Eta_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_genEta_lep->GetEntry(jentry);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.genEta_lep->at(i), selector.weight);
  break;
 }
}

class gendphiMET_lep_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void gendphiMET_lep_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("gendphiMET_lep_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("gen #Delta #phi_{MET,lep}");
}
void gendphiMET_lep_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_genEta_lep->GetEntry(jentry);
 selector.b_genPhi_lep->GetEntry(jentry);
 selector.b_genM_lep->GetEntry(jentry);
 selector.b_genMET->GetEntry(jentry);
 selector.b_genMET_phi->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 selector.b_genNlep->GetEntry(jentry);
 if(selector.genNlep == 0) return;
 TLorentzVector genlep;
 TVector3 genMET;
 genlep.SetPtEtaPhiM(selector.genPT_lep->at(0),selector.genEta_lep->at(0),selector.genPhi_lep->at(0),selector.genM_lep->at(0));
 genMET.SetPtEtaPhi(selector.genMET,0.,selector.genMET_phi);

 hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),selector.weight);
}

class gendphiMET_ele_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void gendphiMET_ele_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("gendphiMET_ele_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("gen #Delta #phi_{MET,ele}");
}
void gendphiMET_ele_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_genEta_lep->GetEntry(jentry);
 selector.b_genPhi_lep->GetEntry(jentry);
 selector.b_genM_lep->GetEntry(jentry);
 selector.b_genMET->GetEntry(jentry);
 selector.b_genMET_phi->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 selector.b_genNlep->GetEntry(jentry);
 if(selector.genNlep == 0) return;
 TLorentzVector genlep;
 TVector3 genMET;
 genMET.SetPtEtaPhi(selector.genMET,0.,selector.genMET_phi);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   genlep.SetPtEtaPhiM(selector.genPT_lep->at(i),selector.genEta_lep->at(i),selector.genPhi_lep->at(i),selector.genM_lep->at(i));
   hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),selector.weight);
  }
  break;
 }
}

class gendphiMET_mu_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void gendphiMET_mu_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("gendphiMET_mu_Hist","",100,-3.5,3.5);
 hist1d->GetXaxis()->SetTitle("gen #Delta #phi_{MET,mu}");
}
void gendphiMET_mu_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_genPT_lep->GetEntry(jentry);
 selector.b_genEta_lep->GetEntry(jentry);
 selector.b_genPhi_lep->GetEntry(jentry);
 selector.b_genM_lep->GetEntry(jentry);
 selector.b_genMET->GetEntry(jentry);
 selector.b_genMET_phi->GetEntry(jentry);
 selector.b_genNlep->GetEntry(jentry);
 selector.b_PDGID_lep->GetEntry(jentry);
 selector.b_ID_lep->GetEntry(jentry);
 selector.b_MiniIso_lep->GetEntry(jentry);
 selector.b_SIP3D_lep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 selector.b_genNlep->GetEntry(jentry);
 if(selector.genNlep == 0) return;
 TLorentzVector genlep;
 TVector3 genMET;
 genMET.SetPtEtaPhi(selector.genMET,0.,selector.genMET_phi);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   genlep.SetPtEtaPhiM(selector.genPT_lep->at(i),selector.genEta_lep->at(i),selector.genPhi_lep->at(i),selector.genM_lep->at(i));
   hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),selector.weight);
  }
  break;
 }
}

vector<HistClass*> Setup_Hists(TTree* tree){
 vector<HistClass*> Classes;
 Classes.push_back(new met_Hist);
 Classes.push_back(new met_Phi_Hist);
 Classes.push_back(new PTCM_Hist);
 //Classes.push_back(new dphiMET_lep_Hist);
 //Classes.push_back(new ele_PT_Hist);
 //Classes.push_back(new mu_PT_Hist);
 //Classes.push_back(new ele_Phi_Hist);
 //Classes.push_back(new mu_Phi_Hist);
 //Classes.push_back(new dphiMET_ele_Hist);
 //Classes.push_back(new dphiMET_mu_Hist);
 Classes.push_back(new dphiCMI_Hist);
 //Classes.push_back(new jet_PT_Hist);
 //Classes.push_back(new jet_Phi_Hist);
 //Classes.push_back(new ele_PT_proj_MET_Hist);
 //Classes.push_back(new ele_PT_proj_METperp_Hist);
 //Classes.push_back(new mu_PT_proj_MET_Hist);
 //Classes.push_back(new mu_PT_proj_METperp_Hist);
 Classes.push_back(new dphiCMI_v_PTCM_Hist);

//gen hists
// Classes.push_back(new genmet_Hist);
// Classes.push_back(new genmet_Phi_Hist);
 //Classes.push_back(new gendphiMET_lep_Hist);
 //Classes.push_back(new genele_PT_Hist);
 //Classes.push_back(new genmu_PT_Hist);
 //Classes.push_back(new genele_Phi_Hist);
 //Classes.push_back(new genmu_Phi_Hist);
 //Classes.push_back(new genele_Eta_Hist);
 //Classes.push_back(new genmu_Eta_Hist);
 //Classes.push_back(new gendphiMET_ele_Hist);
 //Classes.push_back(new gendphiMET_mu_Hist);
 for( auto histclass : Classes ){ histclass->init_hist(tree); }
 return Classes;
}

#endif
