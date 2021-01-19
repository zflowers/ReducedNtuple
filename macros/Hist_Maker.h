#include "Analysis_Base.h"
#include "KUAnalysis.C"


class HistClass{

  public:

  HistClass();
  ~HistClass();

  virtual void init_hist(TTree* tree);
  virtual void fill_hist(Long64_t jentry);
  virtual void write_hist(string output, string Tag);

  protected:

  TH1F* hist1f;
  TH2F* hist2f;
  TH1D* hist1d;
  TH2D* hist2d;
  TH1F* preHEM_hist1f;
  TH2F* preHEM_hist2f;
  TH1D* preHEM_hist1d;
  TH2D* preHEM_hist2d;
  TH1F* postHEM_hist1f;
  TH2F* postHEM_hist2f;
  TH1D* postHEM_hist1d;
  TH2D* postHEM_hist2d;
  KUAnalysis selector;

};

HistClass::HistClass(){

  hist1f = NULL;
  hist2f = NULL;
  hist1d = NULL;
  hist2d = NULL;
  preHEM_hist1f = NULL;
  preHEM_hist2f = NULL;
  preHEM_hist1d = NULL;
  preHEM_hist2d = NULL;
  postHEM_hist1f = NULL;
  postHEM_hist2f = NULL;
  postHEM_hist1d = NULL;
  postHEM_hist2d = NULL;

}

HistClass::~HistClass(){

  if( hist1f ) delete hist1f;
  if( hist2f ) delete hist2f;
  if( hist1d ) delete hist1d;
  if( hist2d ) delete hist2d;
  if( preHEM_hist1f ) delete postHEM_hist1f;
  if( preHEM_hist2f ) delete postHEM_hist2f;
  if( preHEM_hist1d ) delete postHEM_hist1d;
  if( preHEM_hist2d ) delete postHEM_hist2d;
  if( postHEM_hist1f ) delete postHEM_hist1f;
  if( postHEM_hist2f ) delete postHEM_hist2f;
  if( postHEM_hist1d ) delete postHEM_hist1d;
  if( postHEM_hist2d ) delete postHEM_hist2d;

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

  if( hist1f ) {cout << hist1f->GetName() << endl; hist1f->SetDirectory(0); hist1f->Write();}
  if( hist2f ) {cout << hist2f->GetName() << endl; hist2f->SetDirectory(0); hist2f->Write();}
  if( hist1d ) {cout << hist1d->GetName() << endl; hist1d->SetDirectory(0); hist1d->Write();}
  if( hist2d ) {cout << hist2d->GetName() << endl; hist2d->SetDirectory(0); hist2d->Write();}
  if( preHEM_hist1f ) {cout << preHEM_hist1f->GetName() << endl; preHEM_hist1f->SetDirectory(0); preHEM_hist1f->Write();}
  if( preHEM_hist2f ) {cout << preHEM_hist2f->GetName() << endl; preHEM_hist2f->SetDirectory(0); preHEM_hist2f->Write();}
  if( preHEM_hist1d ) {cout << preHEM_hist1d->GetName() << endl; preHEM_hist1d->SetDirectory(0); preHEM_hist1d->Write();}
  if( preHEM_hist2d ) {cout << preHEM_hist2d->GetName() << endl; preHEM_hist2d->SetDirectory(0); preHEM_hist2d->Write();}
  if( postHEM_hist1f ) {cout << postHEM_hist1f->GetName() << endl; postHEM_hist1f->SetDirectory(0); postHEM_hist1f->Write();}
  if( postHEM_hist2f ) {cout << postHEM_hist2f->GetName() << endl; postHEM_hist2f->SetDirectory(0); postHEM_hist2f->Write();}
  if( postHEM_hist1d ) {cout << postHEM_hist1d->GetName() << endl; postHEM_hist1d->SetDirectory(0); postHEM_hist1d->Write();}
  if( postHEM_hist2d ) {cout << postHEM_hist2d->GetName() << endl; postHEM_hist2d->SetDirectory(0); postHEM_hist2d->Write();}
  output->Close();
  delete output;
}

vector<HistClass*> Setup_Hists(TTree* tree);

#ifndef HISTCLASS_H
#define HISTCLASS_H

class Hist_Maker:public Analysis_Base{
  public:
   Hist_Maker();
   Hist_Maker(string outFile, string Tag, TTree* Tree, int ichunk, int nchunk);
   void Analyze();
};

inline Hist_Maker::Hist_Maker()
{
 m_Tag = "";
 m_Tree = NULL;
 m_cut = "";
}

inline Hist_Maker::Hist_Maker(string outFile, string Tag, TTree* Tree, int ichunk, int nchunk)
{
 m_outFile = outFile;
 m_Tag = Tag;
 m_Tree = Tree;
 m_ichunk = ichunk;
 m_nchunk = nchunk;
}

bool Clean_cut = false;
bool dPhiMET_V_cut = true;
bool RISR_uppercut = true;
double lumi = 1.; //store lumi for given year

inline void Hist_Maker::Analyze(){

   vector<HistClass*> Classes = Setup_Hists(m_Tree);
   Long64_t nentries = m_Tree->GetEntriesFast();
   Long64_t percent = 10.0;
   //set lumi
   if(m_Tag.find("DY") != std::string::npos || m_Tag.find("TTV") != std::string::npos || m_Tag.find("QCD") != std::string::npos || m_Tag.find("ST") != std::string::npos || m_Tag.find("ZJets") != std::string::npos || m_Tag.find("WJets") != std::string::npos || m_Tag.find("TTJets") != std::string::npos || m_Tag.find("Boson") != std::string::npos || m_Tag.find("Bkg") != std::string::npos)
   {
    if(m_Tag.find("2016") != std::string::npos) { lumi=35.922; }
    if(m_Tag.find("2017") != std::string::npos) { lumi=41.529; }
    if(m_Tag.find("2018") != std::string::npos) { lumi=59.74; }
   }

   if(m_cut.find("Clean") != std::string::npos) Clean_cut = true;
   eraseSubStr(m_cut,("Clean-"));
   TF1* left_para = new TF1("left para","-500.*sqrt(-2.777*x*x+1.388*x+0.8264)+575.",0.,TMath::Pi());
   TF1* right_para = new TF1("right para","-500.*sqrt((-1.5625*x*x+7.8125*x-8.766))+600.",0.,TMath::Pi());

   if(m_cut.find("dPhiMET_V") != std::string::npos) dPhiMET_V_cut = true;
   eraseSubStr(m_cut,("dPhiMET_V-"));

 //new splitting 

 if(m_nchunk < 1 || m_ichunk < 1 || m_ichunk > m_nchunk){
    m_ichunk = 1;
    m_nchunk = 1;
  }

  Long64_t NTOT = m_Tree->GetEntries();
  cout << NTOT << endl;
  Long64_t N1, N0;
  if(m_nchunk >= NTOT){
    N1 = m_ichunk;
    N0 = m_ichunk-1;
  } else {
    N1 = NTOT/m_nchunk;
    if(NTOT%m_nchunk > 0)
      N1++;
    N0 = (m_ichunk-1)*N1;
    N1 = N0 + N1;
  }

   //for (Long64_t jentry=0; jentry<nentries;jentry++) {
  for(Long64_t i = N0; i < N1 && i < NTOT; i++){
      Long64_t jentry = i;

      //if(jentry%((std::max(nentries,percent))/percent) == 0) { cout << "Processing Event: " << jentry << " out of: " << nentries << " Entries" << endl; }
      int mymod = (N1-N0)/10;
      if(mymod < 1)
      mymod = 1;
      if(i%mymod == 0)
      cout << " event = " << i << " : [" << N0 << " , " << N1 << "]" << endl;

      Long64_t ientry = m_Tree->LoadTree(jentry);

      if(Clean_cut)
      {
       TBranch* dphiCMI_branch = NULL;
       Double_t dphiCMI = 0.;
       TBranch* PTCM_branch = NULL;
       Double_t PTCM = 0.;
       m_Tree->SetBranchAddress("dphiCMI",&dphiCMI,&dphiCMI_branch);
       m_Tree->SetBranchAddress("PTCM",&PTCM,&PTCM_branch);
       dphiCMI_branch->GetEntry(jentry);
       PTCM_branch->GetEntry(jentry);
       if(dphiCMI < 0.25 && PTCM > 75.) continue;
       if(PTCM > left_para->Eval(dphiCMI)) continue;
       if(dphiCMI > 2.5 && PTCM > 100.) continue;
       if(PTCM > right_para->Eval(dphiCMI)) continue;
       dphiCMI_branch->ResetAddress();
       PTCM_branch->ResetAddress();
       m_Tree->ResetBranchAddresses();
      }

      if(dPhiMET_V_cut)
      {
       TBranch* dphiMET_V_branch = NULL;
       Double_t dphiMET_V = 0.;
       m_Tree->SetBranchAddress("dphiMET_V",&dphiMET_V,&dphiMET_V_branch);
       dphiMET_V_branch->GetEntry(jentry);
       if(fabs(dphiMET_V) > TMath::Pi()/2.) continue;
      }

      if(RISR_uppercut)
      {
       TBranch* RISR_branch = NULL;
       Double_t RISR = 0.;
       m_Tree->SetBranchAddress("RISR",&RISR,&RISR_branch);
       RISR_branch->GetEntry(jentry);
       if(RISR > 1.) continue;
      }
 
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
 postHEM_hist1d = new TH1D("met_Hist_postHEM","",100,300.,1000.);
 postHEM_hist1d->GetXaxis()->SetTitle("MET");
}
void met_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_MET->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 if(selector.runnum < 319077){ hist1d->Fill(selector.MET, lumi*selector.weight); }
 else { postHEM_hist1d->Fill(selector.MET, lumi*selector.weight); }
}

class met_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void met_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("met_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("MET_phi");
 postHEM_hist1d = new TH1D("met_Phi_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("MET_phi");
}
void met_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_MET_phi->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 if(selector.runnum < 319077) { hist1d->Fill(selector.MET_phi, lumi*selector.weight); }
 else {postHEM_hist1d->Fill(selector.MET_phi, lumi*selector.weight); }
}

class PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("PTCM_Hist","",100,0.,500.);
 hist1d->GetXaxis()->SetTitle("PTCM");
 postHEM_hist1d = new TH1D("PTCM_Hist_postHEM","",100,0.,500.);
 postHEM_hist1d->GetXaxis()->SetTitle("PTCM");
}
void PTCM_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 if(selector.runnum < 319077) { hist1d->Fill(selector.PTCM, lumi*selector.weight); }
 else { postHEM_hist1d->Fill(selector.PTCM, lumi*selector.weight); }
}

class dphiMET_V_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_V_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_V_Hist","",100.,-6.5,6.5);
 hist1d->GetXaxis()->SetTitle("dphiMET_V");
 postHEM_hist1d = new TH1D("dphiMET_V_Hist_postHEM","",100.,-6.5,6.5);
 postHEM_hist1d->GetXaxis()->SetTitle("dphiMET_V");
}
void dphiMET_V_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
 //m_Tree->GetEntry(jentry);
 selector.b_dphiMET_V->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 if(selector.runnum < 319077) { hist1d->Fill(selector.dphiMET_V, lumi*selector.weight); }
 else { postHEM_hist1d->Fill(selector.dphiMET_V, lumi*selector.weight); }
}

class ele_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void ele_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("ele_PT_Hist","",50,0.,20.);
 hist1d->GetXaxis()->SetTitle("Electron PT");
 postHEM_hist1d = new TH1D("ele_PT_Hist_postHEM","",50,0.,20.);
 postHEM_hist1d->GetXaxis()->SetTitle("Electron PT");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11)
  {
   if(selector.runnum < 319077) { hist1d->Fill(selector.PT_lep->at(i), lumi*selector.weight); }
   else { postHEM_hist1d->Fill(selector.PT_lep->at(i), lumi*selector.weight); }
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
 hist1d = new TH1D("mu_PT_Hist","",50,0.,20.);
 hist1d->GetXaxis()->SetTitle("Muon PT");
 postHEM_hist1d = new TH1D("mu_PT_Hist_postHEM","",50,0.,20.);
 postHEM_hist1d->GetXaxis()->SetTitle("Muon PT");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13)
  {
   if(selector.runnum < 319077) { hist1d->Fill(selector.PT_lep->at(i), lumi*selector.weight); }
   else { postHEM_hist1d->Fill(selector.PT_lep->at(i), lumi*selector.weight); }
  }
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
 hist1d = new TH1D("ele_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("ele_Phi");
 postHEM_hist1d = new TH1D("ele_Phi_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("ele_Phi");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   if(selector.runnum < 319077) { hist1d->Fill(selector.Phi_lep->at(i), lumi*selector.weight); }
   else { postHEM_hist1d->Fill(selector.Phi_lep->at(i), lumi*selector.weight); }
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
 hist1d = new TH1D("mu_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("mu_Phi");
 postHEM_hist1d = new TH1D("mu_Phi_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("mu_Phi");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Nlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.PT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  if(selector.runnum < 319077) { hist1d->Fill(selector.Phi_lep->at(i), lumi*selector.weight); }
  else { postHEM_hist1d->Fill(selector.Phi_lep->at(i), lumi*selector.weight); }
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
 hist1d = new TH1D("dphiMET_lep_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,lep}");
 postHEM_hist1d = new TH1D("dphiMET_lep_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,lep}");
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
 selector.b_Nlep->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.Nlep > 0)
 {
  TLorentzVector lep;
  TVector3 MET;
  lep.SetPtEtaPhiM(selector.PT_lep->at(0),selector.Eta_lep->at(0),selector.Phi_lep->at(0),selector.M_lep->at(0));
  MET.SetPtEtaPhi(selector.MET,0.,selector.MET_phi);

  if(selector.runnum < 319077) { hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
  else { postHEM_hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
 }
}

class dphiMET_ele_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_ele_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("dphiMET_ele_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
 postHEM_hist1d = new TH1D("dphiMET_ele_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
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
 selector.b_runnum->GetEntry(jentry);
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
   if(selector.runnum < 319077) { hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
   else { postHEM_hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
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
 hist1d = new TH1D("dphiMET_mu_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
 postHEM_hist1d = new TH1D("dphiMET_mu_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("#Delta #phi_{MET,ele}");
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
 selector.b_runnum->GetEntry(jentry);
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
   if(selector.runnum < 319077) { hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
   else { postHEM_hist1d->Fill(MET.DeltaPhi(lep.Vect()),lumi*selector.weight); }
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
 hist1d = new TH1D("dphiCMI_Hist","",100,0.,TMath::Pi());
 hist1d->GetXaxis()->SetTitle("dphiCMI");
 postHEM_hist1d = new TH1D("dphiCMI_Hist_postHEM","",100,0.,TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("dphiCMI");
}
void dphiCMI_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist1d->Fill(selector.dphiCMI,lumi*selector.weight); }
 else { postHEM_hist1d->Fill(selector.dphiCMI,lumi*selector.weight); }
}

class dphiCMI_v_Mperp_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_Mperp_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_Mperp_Hist","",50,0.,TMath::Pi(),50,0.,50.);
 hist2d->GetXaxis()->SetTitle("dphiCMI");
 hist2d->GetYaxis()->SetTitle("Mperp");
 postHEM_hist2d = new TH2D("dphiCMI_v_Mperp_Hist_postHEM","",50,0.,TMath::Pi(),50,0.,50.);
 postHEM_hist2d->GetXaxis()->SetTitle("dphiCMI");
 postHEM_hist2d->GetYaxis()->SetTitle("Mperp");
}
void dphiCMI_v_Mperp_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_Mperp->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiCMI,selector.Mperp,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiCMI,selector.Mperp,lumi*selector.weight); }
}

class dphiCMI_v_RISR_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_RISR_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_RISR_Hist","",50,0.,TMath::Pi(),50,0.6,1.1);
 hist2d->GetXaxis()->SetTitle("dphiCMI");
 hist2d->GetYaxis()->SetTitle("RISR");
 postHEM_hist2d = new TH2D("dphiCMI_v_RISR_Hist_postHEM","",50,0.,TMath::Pi(),50,0.6,1.1);
 postHEM_hist2d->GetXaxis()->SetTitle("dphiCMI");
 postHEM_hist2d->GetYaxis()->SetTitle("RISR");
}
void dphiCMI_v_RISR_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_RISR->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiCMI,selector.RISR,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiCMI,selector.RISR,lumi*selector.weight); }
}

class Mperp_v_RISR_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void Mperp_v_RISR_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("Mperp_v_RISR_Hist","",50,0.,60,50,0.6,1.1);
 hist2d->GetXaxis()->SetTitle("M_{#perp}");
 hist2d->GetYaxis()->SetTitle("RISR");
 postHEM_hist2d = new TH2D("Mperp_v_RISR_Hist_postHEM","",50,0.,60,50,0.6,1.1);
 postHEM_hist2d->GetXaxis()->SetTitle("M_{#perp}");
 postHEM_hist2d->GetYaxis()->SetTitle("RISR");
}
void Mperp_v_RISR_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_Mperp->GetEntry(jentry);
 selector.b_RISR->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.Mperp,selector.RISR,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.Mperp,selector.RISR,lumi*selector.weight); }
}

class Mperp_v_PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void Mperp_v_PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("Mperp_v_PTCM_Hist","",50,0.,50.,50,0.,500.);
 hist2d->GetXaxis()->SetTitle("Mperp");
 hist2d->GetYaxis()->SetTitle("PTCM");
 postHEM_hist2d = new TH2D("Mperp_v_PTCM_Hist_postHEM","",50,0.,50.,50,0.,500.);
 postHEM_hist2d->GetXaxis()->SetTitle("Mperp");
 postHEM_hist2d->GetYaxis()->SetTitle("PTCM");
}
void Mperp_v_PTCM_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_Mperp->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.Mperp,selector.PTCM,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.Mperp,selector.PTCM,lumi*selector.weight); }
}

class RISR_v_PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void RISR_v_PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("RISR_v_PTCM_Hist","",50,0.6,1.1,50,0.,500.);
 hist2d->GetXaxis()->SetTitle("RISR");
 hist2d->GetYaxis()->SetTitle("PTCM");
 postHEM_hist2d = new TH2D("RISR_v_PTCM_Hist_postHEM","",50,0.6,1.1,50,0.,500.);
 postHEM_hist2d->GetXaxis()->SetTitle("RISR");
 postHEM_hist2d->GetYaxis()->SetTitle("PTCM");
}
void RISR_v_PTCM_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_RISR->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.RISR,selector.PTCM,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.RISR,selector.PTCM,lumi*selector.weight); }
}

class dphiCMI_v_PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_PTCM_Hist","",64,0.,TMath::Pi(),80,0.,500.);
 hist2d->GetXaxis()->SetTitle("#Delta #phi_{CM,I}");
 hist2d->GetYaxis()->SetTitle("p_{T}^{CM} [GeV]");
 preHEM_hist2d = new TH2D("dphiCMI_v_PTCM_Hist_preHEM","",64,0.,TMath::Pi(),80,0.,500.);
 preHEM_hist2d->GetXaxis()->SetTitle("#Delta #phi_{CM,I}");
 preHEM_hist2d->GetYaxis()->SetTitle("p_{T}^{CM} [GeV]");
 postHEM_hist2d = new TH2D("dphiCMI_v_PTCM_Hist_postHEM","",64,0.,TMath::Pi(),80,0.,500.);
 postHEM_hist2d->GetXaxis()->SetTitle("#Delta #phi_{CM,I}");
 postHEM_hist2d->GetYaxis()->SetTitle("p_{T}^{CM} [GeV]");
}
void dphiCMI_v_PTCM_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 hist2d->Fill(selector.dphiCMI,selector.PTCM,lumi*selector.weight);
 if(selector.runnum < 319077) { preHEM_hist2d->Fill(selector.dphiCMI,selector.PTCM,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiCMI,selector.PTCM,lumi*selector.weight); }
}

class dphiCMI_v_Njet_S_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_Njet_S_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_Njet_S_Hist","",50,0.,TMath::Pi(),9,0,10);
 hist2d->GetXaxis()->SetTitle("dphiCMI");
 hist2d->GetYaxis()->SetTitle("Njet_S");
 postHEM_hist2d = new TH2D("dphiCMI_v_Njet_S_Hist_postHEM","",50,0.,TMath::Pi(),9,0,10);
 postHEM_hist2d->GetXaxis()->SetTitle("dphiCMI");
 postHEM_hist2d->GetYaxis()->SetTitle("Njet_S");
}
void dphiCMI_v_Njet_S_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_Njet_S->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiCMI,selector.Njet_S,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiCMI,selector.Njet_S,lumi*selector.weight); }
}

class PTCM_v_Njet_S_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void PTCM_v_Njet_S_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("PTCM_v_Njet_S_Hist","",100,0.,500.,9,0,10);
 hist2d->GetXaxis()->SetTitle("PTCM");
 hist2d->GetYaxis()->SetTitle("Njet_S");
}
void PTCM_v_Njet_S_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_Njet_S->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 hist2d->Fill(selector.PTCM,selector.Njet_S,lumi*selector.weight);
}

class dphiCMI_v_dphiMET_V_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiCMI_v_dphiMET_V_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiCMI_v_dphiMET_V_Hist","",50,0.,TMath::Pi(),50,-TMath::Pi(),TMath::Pi());
 hist2d->GetXaxis()->SetTitle("dphiCMI");
 hist2d->GetYaxis()->SetTitle("dphiMET_V");
 postHEM_hist2d = new TH2D("dphiCMI_v_dphiMET_V_Hist_postHEM","",50,0.,TMath::Pi(),50,-TMath::Pi(),TMath::Pi());
 postHEM_hist2d->GetXaxis()->SetTitle("dphiCMI");
 postHEM_hist2d->GetYaxis()->SetTitle("dphiMET_V");
}
void dphiCMI_v_dphiMET_V_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiCMI->GetEntry(jentry);
 selector.b_dphiMET_V->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiCMI,selector.dphiMET_V,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiCMI,selector.dphiMET_V,lumi*selector.weight); }
}

class dphiMET_V_v_RISR_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_V_v_RISR_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiMET_V_v_RISR_Hist","",50,-TMath::Pi(),TMath::Pi(),50,0.6,1.1);
 hist2d->GetXaxis()->SetTitle("dphiMET_V");
 hist2d->GetYaxis()->SetTitle("RISR");
 postHEM_hist2d = new TH2D("dphiMET_V_v_RISR_Hist_postHEM","",50,-TMath::Pi(),TMath::Pi(),50,0.6,1.1);
 postHEM_hist2d->GetXaxis()->SetTitle("dphiMET_V");
 postHEM_hist2d->GetYaxis()->SetTitle("RISR");
}
void dphiMET_V_v_RISR_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiMET_V->GetEntry(jentry);
 selector.b_RISR->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiMET_V,selector.RISR,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiMET_V,selector.RISR,lumi*selector.weight); }
}

class Mperp_v_dphiMET_V_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void Mperp_v_dphiMET_V_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("Mperp_v_dphiMET_V_Hist","",50,0.,50.,50,-TMath::Pi(),TMath::Pi());
 hist2d->GetXaxis()->SetTitle("Mperp");
 hist2d->GetYaxis()->SetTitle("dphiMET_V");
 postHEM_hist2d = new TH2D("Mperp_v_dphiMET_V_Hist_postHEM","",50,0.,50.,50,-TMath::Pi(),TMath::Pi());
 postHEM_hist2d->GetXaxis()->SetTitle("Mperp");
 postHEM_hist2d->GetYaxis()->SetTitle("dphiMET_V");
}
void Mperp_v_dphiMET_V_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_Mperp->GetEntry(jentry);
 selector.b_dphiMET_V->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.Mperp,selector.dphiMET_V,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.Mperp,selector.dphiMET_V,lumi*selector.weight); }
}

class dphiMET_V_v_PTCM_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void dphiMET_V_v_PTCM_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist2d = new TH2D("dphiMET_V_v_PTCM_Hist","",50,-TMath::Pi(),TMath::Pi(),50,0.,500.);
 hist2d->GetXaxis()->SetTitle("dphiMET_V");
 hist2d->GetYaxis()->SetTitle("PTCM");
 postHEM_hist2d = new TH2D("dphiMET_V_v_PTCM_Hist_postHEM","",50,-TMath::Pi(),TMath::Pi(),50,0.,500.);
 postHEM_hist2d->GetXaxis()->SetTitle("dphiMET_V");
 postHEM_hist2d->GetYaxis()->SetTitle("PTCM");
}
void dphiMET_V_v_PTCM_Hist::fill_hist(Long64_t jentry){
//Option A: Load only the branches we need:
//
 selector.Init(m_Tree);
 selector.b_dphiMET_V->GetEntry(jentry);
 selector.b_PTCM->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 if(selector.runnum < 319077) { hist2d->Fill(selector.dphiMET_V,selector.PTCM,lumi*selector.weight); }
 else { postHEM_hist2d->Fill(selector.dphiMET_V,selector.PTCM,lumi*selector.weight); }
}

class jet_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void jet_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("jet_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("jet_Phi");
 postHEM_hist1d = new TH1D("jet_Phi_Hist_postHEM","",100,-TMath::Pi(),TMath::Pi());
 postHEM_hist1d->GetXaxis()->SetTitle("jet_Phi");
}
void jet_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_Njet->GetEntry(jentry);
 selector.b_Phi_jet->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Njet; i++)
 {
  if(selector.runnum < 319077) { hist1d->Fill(selector.Phi_jet->at(i), lumi*selector.weight); }
  else { postHEM_hist1d->Fill(selector.Phi_jet->at(i), lumi*selector.weight); }
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.Njet; i++)
 {
  hist1d->Fill(selector.PT_jet->at(i), lumi*selector.weight);
 }
}

/*
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
 selector.b_runnum->GetEntry(jentry);
 hist1d->Fill(selector.genMET, lumi*selector.weight);
}

class genmet_Phi_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genmet_Phi_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genmet_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
 hist1d->GetXaxis()->SetTitle("genMET_phi");
}
void genmet_Phi_Hist::fill_hist(Long64_t jentry){
 selector.Init(m_Tree);
// m_Tree->GetEntry(jentry);
 selector.b_genMET_phi->GetEntry(jentry);
 selector.b_weight->GetEntry(jentry);
 selector.b_runnum->GetEntry(jentry);
 hist1d->Fill(selector.genMET_phi, lumi*selector.weight);
}

class genele_PT_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void genele_PT_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("genele_PT_Hist","",50,0.,20.);
 hist1d->GetXaxis()->SetTitle("Generated Electron PT");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11)
  {
   hist1d->Fill(selector.genPT_lep->at(i), lumi*selector.weight);
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
 hist1d = new TH1D("genmu_PT_Hist","",50,0.,20.);
 hist1d->GetXaxis()->SetTitle("Generated Muon PT");
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13)
  {
   hist1d->Fill(selector.genPT_lep->at(i), lumi*selector.weight);
  }
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
 hist1d = new TH1D("genele_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.genPhi_lep->at(i), lumi*selector.weight);
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 11 && selector.ID_lep->at(i) >= 4 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   hist1d->Fill(selector.genEta_lep->at(i), lumi*selector.weight);
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
 hist1d = new TH1D("genmu_Phi_Hist","",100,-TMath::Pi(),TMath::Pi());
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.genPhi_lep->at(i), lumi*selector.weight);
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
 selector.b_runnum->GetEntry(jentry);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  hist1d->Fill(selector.genEta_lep->at(i), lumi*selector.weight);
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
 hist1d = new TH1D("gendphiMET_lep_Hist","",100,-TMath::Pi(),TMath::Pi());
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
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 selector.b_genNlep->GetEntry(jentry);
 if(selector.genNlep > 0)
 {
  TLorentzVector genlep;
  TVector3 genMET;
  genlep.SetPtEtaPhiM(selector.genPT_lep->at(0),selector.genEta_lep->at(0),selector.genPhi_lep->at(0),selector.genM_lep->at(0));
  genMET.SetPtEtaPhi(selector.genMET,0.,selector.genMET_phi);

  hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),lumi*selector.weight);
 }
}

class gendphiMET_ele_Hist:public HistClass, public Hist_Maker{
 public:
 void init_hist(TTree* tree);
 void fill_hist(Long64_t jentry);
};
void gendphiMET_ele_Hist::init_hist(TTree* tree){
 m_Tree = tree;
 selector = KUAnalysis(m_Tree);
 hist1d = new TH1D("gendphiMET_ele_Hist","",100,-TMath::Pi(),TMath::Pi());
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
 selector.b_runnum->GetEntry(jentry);
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
   hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),lumi*selector.weight);
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
 hist1d = new TH1D("gendphiMET_mu_Hist","",100,-TMath::Pi(),TMath::Pi());
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
 selector.b_runnum->GetEntry(jentry);
//
//Option B: Load all branches:
//
 m_Tree->GetEntry(jentry);
//
 TLorentzVector genlep;
 TVector3 genMET;
 genMET.SetPtEtaPhi(selector.genMET,0.,selector.genMET_phi);
 for(int i = 0; i < selector.genNlep; i++)
 {
  if(abs(selector.PDGID_lep->at(i)) == 13 && selector.ID_lep->at(i) >= 3 && selector.genPT_lep->at(i)*selector.MiniIso_lep->at(i) < 5. && selector.SIP3D_lep->at(i) < 4.)
  {
   genlep.SetPtEtaPhiM(selector.genPT_lep->at(i),selector.genEta_lep->at(i),selector.genPhi_lep->at(i),selector.genM_lep->at(i));
   hist1d->Fill(genMET.DeltaPhi(genlep.Vect()),lumi*selector.weight);
  }
  break;
 }
 
}
//end gen plots
*/

vector<HistClass*> Setup_Hists(TTree* tree){
 vector<HistClass*> Classes;
 //Classes.push_back(new met_Hist);
 //Classes.push_back(new met_Phi_Hist);
 //Classes.push_back(new PTCM_Hist);
 //Classes.push_back(new dphiMET_V_Hist);
 //Classes.push_back(new dphiMET_lep_Hist);
 //Classes.push_back(new ele_PT_Hist);
 //Classes.push_back(new mu_PT_Hist);
 //Classes.push_back(new ele_Phi_Hist);
 //Classes.push_back(new mu_Phi_Hist);
 //Classes.push_back(new dphiMET_ele_Hist);
 //Classes.push_back(new dphiMET_mu_Hist);
 //Classes.push_back(new dphiCMI_Hist);
 //Classes.push_back(new jet_PT_Hist);
 //Classes.push_back(new jet_Phi_Hist);
 //Classes.push_back(new ele_PT_proj_MET_Hist);
 //Classes.push_back(new ele_PT_proj_METperp_Hist);
 //Classes.push_back(new mu_PT_proj_MET_Hist);
 //Classes.push_back(new mu_PT_proj_METperp_Hist);
 //
 Classes.push_back(new dphiCMI_v_PTCM_Hist);
 //Classes.push_back(new dphiCMI_v_Mperp_Hist);
 //Classes.push_back(new dphiCMI_v_RISR_Hist);
 //Classes.push_back(new Mperp_v_PTCM_Hist);
 //Classes.push_back(new RISR_v_PTCM_Hist);
 //Classes.push_back(new dphiCMI_v_dphiMET_V_Hist);
 //Classes.push_back(new dphiMET_V_v_RISR_Hist);
 //Classes.push_back(new Mperp_v_dphiMET_V_Hist);
 //Classes.push_back(new dphiMET_V_v_PTCM_Hist);
 //Classes.push_back(new Mperp_v_RISR_Hist);
 //Classes.push_back(new PTCM_v_Njet_S_Hist);
 //Classes.push_back(new dphiCMI_v_Njet_S_Hist);

//gen hists
 //Classes.push_back(new genmet_Hist);
 //Classes.push_back(new genmet_Phi_Hist);
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
