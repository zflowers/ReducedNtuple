//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 20 14:02:44 2021 by ROOT version 6.12/07
// from TTree KUAnalysis/KUAnalysis
// found on file: ../../../storage/NEW/Autumn18_102X_Data/MET_Run2018B-02Apr2020-v1_2018_Autumn18_102X.root
//////////////////////////////////////////////////////////

#ifndef KUAnalysis_h
#define KUAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class KUAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Bool_t          event_skipped;
   Double_t        weight;
   Double_t        PUweight;
   Double_t        PUweight_up;
   Double_t        PUweight_down;
   Double_t        BtagHFSFweight;
   Double_t        BtagHFSFweight_up;
   Double_t        BtagHFSFweight_down;
   Double_t        BtagLFSFweight;
   Double_t        BtagLFSFweight_up;
   Double_t        BtagLFSFweight_down;
   Double_t        MetTrigSFweight;
   Double_t        MetTrigSFweight_up;
   Double_t        MetTrigSFweight_down;
   Int_t           runnum;
   Int_t           luminum;
   Long64_t        eventnum;
   Int_t           NPV;
   Bool_t          EventFilter;
   Bool_t          EventFlag_FailJetID;
   Bool_t          EventFlag_JetInHEM;
   Bool_t          EventFlag_JetInHEM_Pt20;
   Bool_t          EventFlag_JetInHEM_Pt20_JetID;
   Bool_t          HEM_Veto;
   Bool_t          METtrigger;
   Bool_t          METHTtrigger;
   Bool_t          METORtrigger;
   Bool_t          SingleElectrontrigger;
   Bool_t          SingleMuontrigger;
   Bool_t          DoubleElectrontrigger;
   Bool_t          DoubleMuontrigger;
   Bool_t          EMutrigger;
   Double_t        MET;
   Double_t        MET_phi;
   Double_t        altMET;
   Double_t        altMET_phi;
   Double_t        HT_eta24;
   Double_t        HT_eta24_id;
   Double_t        HT_eta3;
   Double_t        HT_eta3_id;
   Double_t        HT_eta5;
   Double_t        HT_eta5_id;
   Int_t           Nele;
   Int_t           Nmu;
   Int_t           Nlep;
   vector<double>  *PT_lep;
   vector<double>  *Eta_lep;
   vector<double>  *Phi_lep;
   vector<double>  *M_lep;
   vector<int>     *Charge_lep;
   vector<int>     *PDGID_lep;
   vector<double>  *RelIso_lep;
   vector<double>  *MiniIso_lep;
   vector<double>  *Dxy_lep;
   vector<double>  *DxyErr_lep;
   vector<double>  *Dz_lep;
   vector<double>  *DzErr_lep;
   vector<double>  *IP3D_lep;
   vector<double>  *SIP3D_lep;
   vector<int>     *ID_lep;
   vector<int>     *SourceID_lep;
   vector<int>     *Index_lep;
   Int_t           Njet;
   Int_t           Nbjet;
   vector<double>  *PT_jet;
   vector<double>  *Eta_jet;
   vector<double>  *Phi_jet;
   vector<double>  *M_jet;
   vector<double>  *Btag_jet;
   vector<int>     *BtagID_jet;
   vector<double>  *Flavor_jet;
   vector<int>     *index_jet_a;
   vector<int>     *index_jet_b;
   vector<int>     *index_jet_ISR;
   vector<int>     *index_jet_S;
   Int_t           NSV;
   vector<double>  *PT_SV;
   vector<double>  *Eta_SV;
   vector<double>  *Phi_SV;
   vector<double>  *M_SV;
   vector<double>  *ProbB_SV;
   vector<double>  *ProbC_SV;
   Int_t           Njet_ISR;
   Int_t           Njet_S;
   Int_t           Nbjet_ISR;
   Int_t           Nbjet_S;
   Int_t           Nlep_ISR;
   Int_t           Nlep_S;
   Int_t           NSV_ISR;
   Int_t           NSV_S;
   vector<int>     *index_SV_ISR;
   vector<int>     *index_SV_S;
   vector<int>     *index_lep_ISR;
   vector<int>     *index_lep_S;
   vector<double>  *dphi_lep_S;
   vector<double>  *cos_lep_S;
   vector<double>  *dphi_jet_S;
   vector<double>  *cos_jet_S;
   vector<double>  *dphi_SV_S;
   vector<double>  *cos_SV_S;
   vector<double>  *dphiMET_lep_S;
   vector<double>  *dphiMET_jet_S;
   vector<double>  *dphiMET_SV_S;
   Int_t           Njet_a;
   Int_t           Njet_b;
   Int_t           Nbjet_a;
   Int_t           Nbjet_b;
   Int_t           Nlep_a;
   Int_t           Nlep_b;
   Int_t           NSV_a;
   Int_t           NSV_b;
   vector<int>     *index_lep_a;
   vector<int>     *index_lep_b;
   vector<int>     *index_SV_a;
   vector<int>     *index_SV_b;
   Double_t        PTCM;
   Double_t        PzCM;
   Double_t        cosCM;
   Double_t        dphiCM;
   Double_t        dphiCMI;
   Double_t        MS;
   Double_t        PS;
   Double_t        cosS;
   Double_t        dphiS;
   Double_t        dphiSI;
   Double_t        PTS;
   Double_t        PzS;
   Double_t        MX3a;
   Double_t        MX3b;
   Double_t        EVa;
   Double_t        EVb;
   Double_t        PVa;
   Double_t        PVb;
   Double_t        EJa;
   Double_t        EJb;
   Double_t        PJa;
   Double_t        PJb;
   Double_t        MX2a;
   Double_t        MX2b;
   Double_t        ELa;
   Double_t        ELb;
   Double_t        PLa;
   Double_t        PLb;
   Double_t        MV;
   Double_t        PV;
   Double_t        MVa;
   Double_t        MVb;
   Double_t        PV_lab;
   Double_t        dphiMET_V;
   Double_t        MJa;
   Double_t        MJb;
   Double_t        MLa;
   Double_t        MLb;
   Double_t        cosJa;
   Double_t        cosJb;
   Double_t        cosLa;
   Double_t        cosLb;
   Double_t        MJ;
   Double_t        ML;
   Double_t        EJ;
   Double_t        EL;
   Double_t        PJ;
   Double_t        PL;
   Double_t        PX3;
   Double_t        PX3_BoostT;
   Double_t        MX3a_BoostT;
   Double_t        MX3b_BoostT;
   Double_t        Mperp;
   Double_t        PV_BoostT;
   Double_t        EVa_BoostT;
   Double_t        EVb_BoostT;
   Double_t        PVa_BoostT;
   Double_t        PVb_BoostT;
   Double_t        EJ_BoostT;
   Double_t        EL_BoostT;
   Double_t        PJ_BoostT;
   Double_t        PL_BoostT;
   Double_t        H11S;
   Double_t        H21S;
   Double_t        HT21S;
   Double_t        H22S;
   Double_t        HT22S;
   Double_t        H42S;
   Double_t        HT42S;
   Double_t        H11X3a;
   Double_t        H11X3b;
   Double_t        H21X3a;
   Double_t        H21X3b;
   Double_t        PISR;
   Double_t        PTISR;
   Double_t        RISR;
   Double_t        RISRT;
   Double_t        MISR;

   // List of branches
   TBranch        *b_event_skipped;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_PUweight_up;   //!
   TBranch        *b_PUweight_down;   //!
   TBranch        *b_BtagHFSFweight;   //!
   TBranch        *b_BtagHFSFweight_up;   //!
   TBranch        *b_BtagHFSFweight_down;   //!
   TBranch        *b_BtagLFSFweight;   //!
   TBranch        *b_BtagLFSFweight_up;   //!
   TBranch        *b_BtagLFSFweight_down;   //!
   TBranch        *b_MetTrigSFweight;   //!
   TBranch        *b_MetTrigSFweight_up;   //!
   TBranch        *b_MetTrigSFweight_down;   //!
   TBranch        *b_runnum;   //!
   TBranch        *b_luminum;   //!
   TBranch        *b_eventnum;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_EventFilter;   //!
   TBranch        *b_EventFlag_FailJetID;   //!
   TBranch        *b_EventFlag_JetInHEM;   //!
   TBranch        *b_EventFlag_JetInHEM_Pt20;   //!
   TBranch        *b_EventFlag_JetInHEM_Pt20_JetID;   //!
   TBranch        *b_HEM_Veto;   //!
   TBranch        *b_METtrigger;   //!
   TBranch        *b_METHTtrigger;   //!
   TBranch        *b_METORtrigger;   //!
   TBranch        *b_SingleElectrontrigger;   //!
   TBranch        *b_SingleMuontrigger;   //!
   TBranch        *b_DoubleElectrontrigger;   //!
   TBranch        *b_DoubleMuontrigger;   //!
   TBranch        *b_EMutrigger;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_altMET;   //!
   TBranch        *b_altMET_phi;   //!
   TBranch        *b_HT_eta24;   //!
   TBranch        *b_HT_eta24_id;   //!
   TBranch        *b_HT_eta3;   //!
   TBranch        *b_HT_eta3_id;   //!
   TBranch        *b_HT_eta5;   //!
   TBranch        *b_HT_eta5_id;   //!
   TBranch        *b_Nele;   //!
   TBranch        *b_Nmu;   //!
   TBranch        *b_Nlep;   //!
   TBranch        *b_PT_lep;   //!
   TBranch        *b_Eta_lep;   //!
   TBranch        *b_Phi_lep;   //!
   TBranch        *b_M_lep;   //!
   TBranch        *b_Charge_lep;   //!
   TBranch        *b_PDGID_lep;   //!
   TBranch        *b_RelIso_lep;   //!
   TBranch        *b_MiniIso_lep;   //!
   TBranch        *b_Dxy_lep;   //!
   TBranch        *b_DxyErr_lep;   //!
   TBranch        *b_Dz_lep;   //!
   TBranch        *b_DzErr_lep;   //!
   TBranch        *b_IP3D_lep;   //!
   TBranch        *b_SIP3D_lep;   //!
   TBranch        *b_ID_lep;   //!
   TBranch        *b_SourceID_lep;   //!
   TBranch        *b_Index_lep;   //!
   TBranch        *b_Njet;   //!
   TBranch        *b_Nbjet;   //!
   TBranch        *b_PT_jet;   //!
   TBranch        *b_Eta_jet;   //!
   TBranch        *b_Phi_jet;   //!
   TBranch        *b_M_jet;   //!
   TBranch        *b_Btag_jet;   //!
   TBranch        *b_BtagID_jet;   //!
   TBranch        *b_Flavor_jet;   //!
   TBranch        *b_index_jet_a;   //!
   TBranch        *b_index_jet_b;   //!
   TBranch        *b_index_jet_ISR;   //!
   TBranch        *b_index_jet_S;   //!
   TBranch        *b_NSV;   //!
   TBranch        *b_PT_SV;   //!
   TBranch        *b_Eta_SV;   //!
   TBranch        *b_Phi_SV;   //!
   TBranch        *b_M_SV;   //!
   TBranch        *b_ProbB_SV;   //!
   TBranch        *b_ProbC_SV;   //!
   TBranch        *b_Njet_ISR;   //!
   TBranch        *b_Njet_S;   //!
   TBranch        *b_Nbjet_ISR;   //!
   TBranch        *b_Nbjet_S;   //!
   TBranch        *b_Nlep_ISR;   //!
   TBranch        *b_Nlep_S;   //!
   TBranch        *b_NSV_ISR;   //!
   TBranch        *b_NSV_S;   //!
   TBranch        *b_index_SV_ISR;   //!
   TBranch        *b_index_SV_S;   //!
   TBranch        *b_index_lep_ISR;   //!
   TBranch        *b_index_lep_S;   //!
   TBranch        *b_dphi_lep_S;   //!
   TBranch        *b_cos_lep_S;   //!
   TBranch        *b_dphi_jet_S;   //!
   TBranch        *b_cos_jet_S;   //!
   TBranch        *b_dphi_SV_S;   //!
   TBranch        *b_cos_SV_S;   //!
   TBranch        *b_dphiMET_lep_S;   //!
   TBranch        *b_dphiMET_jet_S;   //!
   TBranch        *b_dphiMET_SV_S;   //!
   TBranch        *b_Njet_a;   //!
   TBranch        *b_Njet_b;   //!
   TBranch        *b_Nbjet_a;   //!
   TBranch        *b_Nbjet_b;   //!
   TBranch        *b_Nlep_a;   //!
   TBranch        *b_Nlep_b;   //!
   TBranch        *b_NSV_a;   //!
   TBranch        *b_NSV_b;   //!
   TBranch        *b_index_lep_a;   //!
   TBranch        *b_index_lep_b;   //!
   TBranch        *b_index_SV_a;   //!
   TBranch        *b_index_SV_b;   //!
   TBranch        *b_PTCM;   //!
   TBranch        *b_PzCM;   //!
   TBranch        *b_cosCM;   //!
   TBranch        *b_dphiCM;   //!
   TBranch        *b_dphiCMI;   //!
   TBranch        *b_MS;   //!
   TBranch        *b_PS;   //!
   TBranch        *b_cosS;   //!
   TBranch        *b_dphiS;   //!
   TBranch        *b_dphiSI;   //!
   TBranch        *b_PTS;   //!
   TBranch        *b_PzS;   //!
   TBranch        *b_MX3a;   //!
   TBranch        *b_MX3b;   //!
   TBranch        *b_EVa;   //!
   TBranch        *b_EVb;   //!
   TBranch        *b_PVa;   //!
   TBranch        *b_PVb;   //!
   TBranch        *b_EJa;   //!
   TBranch        *b_EJb;   //!
   TBranch        *b_PJa;   //!
   TBranch        *b_PJb;   //!
   TBranch        *b_MX2a;   //!
   TBranch        *b_MX2b;   //!
   TBranch        *b_ELa;   //!
   TBranch        *b_ELb;   //!
   TBranch        *b_PLa;   //!
   TBranch        *b_PLb;   //!
   TBranch        *b_MV;   //!
   TBranch        *b_PV;   //!
   TBranch        *b_MVa;   //!
   TBranch        *b_MVb;   //!
   TBranch        *b_PV_lab;   //!
   TBranch        *b_dphiMET_V;   //!
   TBranch        *b_MJa;   //!
   TBranch        *b_MJb;   //!
   TBranch        *b_MLa;   //!
   TBranch        *b_MLb;   //!
   TBranch        *b_cosJa;   //!
   TBranch        *b_cosJb;   //!
   TBranch        *b_cosLa;   //!
   TBranch        *b_cosLb;   //!
   TBranch        *b_MJ;   //!
   TBranch        *b_ML;   //!
   TBranch        *b_EJ;   //!
   TBranch        *b_EL;   //!
   TBranch        *b_PJ;   //!
   TBranch        *b_PL;   //!
   TBranch        *b_PX3;   //!
   TBranch        *b_PX3_BoostT;   //!
   TBranch        *b_MX3a_BoostT;   //!
   TBranch        *b_MX3b_BoostT;   //!
   TBranch        *b_Mperp;   //!
   TBranch        *b_PV_BoostT;   //!
   TBranch        *b_EVa_BoostT;   //!
   TBranch        *b_EVb_BoostT;   //!
   TBranch        *b_PVa_BoostT;   //!
   TBranch        *b_PVb_BoostT;   //!
   TBranch        *b_EJ_BoostT;   //!
   TBranch        *b_EL_BoostT;   //!
   TBranch        *b_PJ_BoostT;   //!
   TBranch        *b_PL_BoostT;   //!
   TBranch        *b_H11S;   //!
   TBranch        *b_H21S;   //!
   TBranch        *b_HT21S;   //!
   TBranch        *b_H22S;   //!
   TBranch        *b_HT22S;   //!
   TBranch        *b_H42S;   //!
   TBranch        *b_HT42S;   //!
   TBranch        *b_H11X3a;   //!
   TBranch        *b_H11X3b;   //!
   TBranch        *b_H21X3a;   //!
   TBranch        *b_H21X3b;   //!
   TBranch        *b_PISR;   //!
   TBranch        *b_PTISR;   //!
   TBranch        *b_RISR;   //!
   TBranch        *b_RISRT;   //!
   TBranch        *b_MISR;   //!

   KUAnalysis(TTree *tree=0);
   virtual ~KUAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef KUAnalysis_cxx
KUAnalysis::KUAnalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../storage/NEW/Autumn18_102X_Data/MET_Run2018B-02Apr2020-v1_2018_Autumn18_102X.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../storage/NEW/Autumn18_102X_Data/MET_Run2018B-02Apr2020-v1_2018_Autumn18_102X.root");
      }
      f->GetObject("KUAnalysis",tree);

   }
   Init(tree);
}

KUAnalysis::~KUAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t KUAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t KUAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void KUAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PT_lep = 0;
   Eta_lep = 0;
   Phi_lep = 0;
   M_lep = 0;
   Charge_lep = 0;
   PDGID_lep = 0;
   RelIso_lep = 0;
   MiniIso_lep = 0;
   Dxy_lep = 0;
   DxyErr_lep = 0;
   Dz_lep = 0;
   DzErr_lep = 0;
   IP3D_lep = 0;
   SIP3D_lep = 0;
   ID_lep = 0;
   SourceID_lep = 0;
   Index_lep = 0;
   PT_jet = 0;
   Eta_jet = 0;
   Phi_jet = 0;
   M_jet = 0;
   Btag_jet = 0;
   BtagID_jet = 0;
   Flavor_jet = 0;
   index_jet_a = 0;
   index_jet_b = 0;
   index_jet_ISR = 0;
   index_jet_S = 0;
   PT_SV = 0;
   Eta_SV = 0;
   Phi_SV = 0;
   M_SV = 0;
   ProbB_SV = 0;
   ProbC_SV = 0;
   index_SV_ISR = 0;
   index_SV_S = 0;
   index_lep_ISR = 0;
   index_lep_S = 0;
   dphi_lep_S = 0;
   cos_lep_S = 0;
   dphi_jet_S = 0;
   cos_jet_S = 0;
   dphi_SV_S = 0;
   cos_SV_S = 0;
   dphiMET_lep_S = 0;
   dphiMET_jet_S = 0;
   dphiMET_SV_S = 0;
   index_lep_a = 0;
   index_lep_b = 0;
   index_SV_a = 0;
   index_SV_b = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event_skipped", &event_skipped, &b_event_skipped);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("PUweight_up", &PUweight_up, &b_PUweight_up);
   fChain->SetBranchAddress("PUweight_down", &PUweight_down, &b_PUweight_down);
   fChain->SetBranchAddress("BtagHFSFweight", &BtagHFSFweight, &b_BtagHFSFweight);
   fChain->SetBranchAddress("BtagHFSFweight_up", &BtagHFSFweight_up, &b_BtagHFSFweight_up);
   fChain->SetBranchAddress("BtagHFSFweight_down", &BtagHFSFweight_down, &b_BtagHFSFweight_down);
   fChain->SetBranchAddress("BtagLFSFweight", &BtagLFSFweight, &b_BtagLFSFweight);
   fChain->SetBranchAddress("BtagLFSFweight_up", &BtagLFSFweight_up, &b_BtagLFSFweight_up);
   fChain->SetBranchAddress("BtagLFSFweight_down", &BtagLFSFweight_down, &b_BtagLFSFweight_down);
   fChain->SetBranchAddress("MetTrigSFweight", &MetTrigSFweight, &b_MetTrigSFweight);
   fChain->SetBranchAddress("MetTrigSFweight_up", &MetTrigSFweight_up, &b_MetTrigSFweight_up);
   fChain->SetBranchAddress("MetTrigSFweight_down", &MetTrigSFweight_down, &b_MetTrigSFweight_down);
   fChain->SetBranchAddress("runnum", &runnum, &b_runnum);
   fChain->SetBranchAddress("luminum", &luminum, &b_luminum);
   fChain->SetBranchAddress("eventnum", &eventnum, &b_eventnum);
   fChain->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain->SetBranchAddress("EventFilter", &EventFilter, &b_EventFilter);
   fChain->SetBranchAddress("EventFlag_FailJetID", &EventFlag_FailJetID, &b_EventFlag_FailJetID);
   fChain->SetBranchAddress("EventFlag_JetInHEM", &EventFlag_JetInHEM, &b_EventFlag_JetInHEM);
   fChain->SetBranchAddress("EventFlag_JetInHEM_Pt20", &EventFlag_JetInHEM_Pt20, &b_EventFlag_JetInHEM_Pt20);
   fChain->SetBranchAddress("EventFlag_JetInHEM_Pt20_JetID", &EventFlag_JetInHEM_Pt20_JetID, &b_EventFlag_JetInHEM_Pt20_JetID);
   fChain->SetBranchAddress("HEM_Veto", &HEM_Veto, &b_HEM_Veto);
   fChain->SetBranchAddress("METtrigger", &METtrigger, &b_METtrigger);
   fChain->SetBranchAddress("METHTtrigger", &METHTtrigger, &b_METHTtrigger);
   fChain->SetBranchAddress("METORtrigger", &METORtrigger, &b_METORtrigger);
   fChain->SetBranchAddress("SingleElectrontrigger", &SingleElectrontrigger, &b_SingleElectrontrigger);
   fChain->SetBranchAddress("SingleMuontrigger", &SingleMuontrigger, &b_SingleMuontrigger);
   fChain->SetBranchAddress("DoubleElectrontrigger", &DoubleElectrontrigger, &b_DoubleElectrontrigger);
   fChain->SetBranchAddress("DoubleMuontrigger", &DoubleMuontrigger, &b_DoubleMuontrigger);
   fChain->SetBranchAddress("EMutrigger", &EMutrigger, &b_EMutrigger);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("altMET", &altMET, &b_altMET);
   fChain->SetBranchAddress("altMET_phi", &altMET_phi, &b_altMET_phi);
   fChain->SetBranchAddress("HT_eta24", &HT_eta24, &b_HT_eta24);
   fChain->SetBranchAddress("HT_eta24_id", &HT_eta24_id, &b_HT_eta24_id);
   fChain->SetBranchAddress("HT_eta3", &HT_eta3, &b_HT_eta3);
   fChain->SetBranchAddress("HT_eta3_id", &HT_eta3_id, &b_HT_eta3_id);
   fChain->SetBranchAddress("HT_eta5", &HT_eta5, &b_HT_eta5);
   fChain->SetBranchAddress("HT_eta5_id", &HT_eta5_id, &b_HT_eta5_id);
   fChain->SetBranchAddress("Nele", &Nele, &b_Nele);
   fChain->SetBranchAddress("Nmu", &Nmu, &b_Nmu);
   fChain->SetBranchAddress("Nlep", &Nlep, &b_Nlep);
   fChain->SetBranchAddress("PT_lep", &PT_lep, &b_PT_lep);
   fChain->SetBranchAddress("Eta_lep", &Eta_lep, &b_Eta_lep);
   fChain->SetBranchAddress("Phi_lep", &Phi_lep, &b_Phi_lep);
   fChain->SetBranchAddress("M_lep", &M_lep, &b_M_lep);
   fChain->SetBranchAddress("Charge_lep", &Charge_lep, &b_Charge_lep);
   fChain->SetBranchAddress("PDGID_lep", &PDGID_lep, &b_PDGID_lep);
   fChain->SetBranchAddress("RelIso_lep", &RelIso_lep, &b_RelIso_lep);
   fChain->SetBranchAddress("MiniIso_lep", &MiniIso_lep, &b_MiniIso_lep);
   fChain->SetBranchAddress("Dxy_lep", &Dxy_lep, &b_Dxy_lep);
   fChain->SetBranchAddress("DxyErr_lep", &DxyErr_lep, &b_DxyErr_lep);
   fChain->SetBranchAddress("Dz_lep", &Dz_lep, &b_Dz_lep);
   fChain->SetBranchAddress("DzErr_lep", &DzErr_lep, &b_DzErr_lep);
   fChain->SetBranchAddress("IP3D_lep", &IP3D_lep, &b_IP3D_lep);
   fChain->SetBranchAddress("SIP3D_lep", &SIP3D_lep, &b_SIP3D_lep);
   fChain->SetBranchAddress("ID_lep", &ID_lep, &b_ID_lep);
   fChain->SetBranchAddress("SourceID_lep", &SourceID_lep, &b_SourceID_lep);
   fChain->SetBranchAddress("Index_lep", &Index_lep, &b_Index_lep);
   fChain->SetBranchAddress("Njet", &Njet, &b_Njet);
   fChain->SetBranchAddress("Nbjet", &Nbjet, &b_Nbjet);
   fChain->SetBranchAddress("PT_jet", &PT_jet, &b_PT_jet);
   fChain->SetBranchAddress("Eta_jet", &Eta_jet, &b_Eta_jet);
   fChain->SetBranchAddress("Phi_jet", &Phi_jet, &b_Phi_jet);
   fChain->SetBranchAddress("M_jet", &M_jet, &b_M_jet);
   fChain->SetBranchAddress("Btag_jet", &Btag_jet, &b_Btag_jet);
   fChain->SetBranchAddress("BtagID_jet", &BtagID_jet, &b_BtagID_jet);
   fChain->SetBranchAddress("Flavor_jet", &Flavor_jet, &b_Flavor_jet);
   fChain->SetBranchAddress("index_jet_a", &index_jet_a, &b_index_jet_a);
   fChain->SetBranchAddress("index_jet_b", &index_jet_b, &b_index_jet_b);
   fChain->SetBranchAddress("index_jet_ISR", &index_jet_ISR, &b_index_jet_ISR);
   fChain->SetBranchAddress("index_jet_S", &index_jet_S, &b_index_jet_S);
   fChain->SetBranchAddress("NSV", &NSV, &b_NSV);
   fChain->SetBranchAddress("PT_SV", &PT_SV, &b_PT_SV);
   fChain->SetBranchAddress("Eta_SV", &Eta_SV, &b_Eta_SV);
   fChain->SetBranchAddress("Phi_SV", &Phi_SV, &b_Phi_SV);
   fChain->SetBranchAddress("M_SV", &M_SV, &b_M_SV);
   fChain->SetBranchAddress("ProbB_SV", &ProbB_SV, &b_ProbB_SV);
   fChain->SetBranchAddress("ProbC_SV", &ProbC_SV, &b_ProbC_SV);
   fChain->SetBranchAddress("Njet_ISR", &Njet_ISR, &b_Njet_ISR);
   fChain->SetBranchAddress("Njet_S", &Njet_S, &b_Njet_S);
   fChain->SetBranchAddress("Nbjet_ISR", &Nbjet_ISR, &b_Nbjet_ISR);
   fChain->SetBranchAddress("Nbjet_S", &Nbjet_S, &b_Nbjet_S);
   fChain->SetBranchAddress("Nlep_ISR", &Nlep_ISR, &b_Nlep_ISR);
   fChain->SetBranchAddress("Nlep_S", &Nlep_S, &b_Nlep_S);
   fChain->SetBranchAddress("NSV_ISR", &NSV_ISR, &b_NSV_ISR);
   fChain->SetBranchAddress("NSV_S", &NSV_S, &b_NSV_S);
   fChain->SetBranchAddress("index_SV_ISR", &index_SV_ISR, &b_index_SV_ISR);
   fChain->SetBranchAddress("index_SV_S", &index_SV_S, &b_index_SV_S);
   fChain->SetBranchAddress("index_lep_ISR", &index_lep_ISR, &b_index_lep_ISR);
   fChain->SetBranchAddress("index_lep_S", &index_lep_S, &b_index_lep_S);
   fChain->SetBranchAddress("dphi_lep_S", &dphi_lep_S, &b_dphi_lep_S);
   fChain->SetBranchAddress("cos_lep_S", &cos_lep_S, &b_cos_lep_S);
   fChain->SetBranchAddress("dphi_jet_S", &dphi_jet_S, &b_dphi_jet_S);
   fChain->SetBranchAddress("cos_jet_S", &cos_jet_S, &b_cos_jet_S);
   fChain->SetBranchAddress("dphi_SV_S", &dphi_SV_S, &b_dphi_SV_S);
   fChain->SetBranchAddress("cos_SV_S", &cos_SV_S, &b_cos_SV_S);
   fChain->SetBranchAddress("dphiMET_lep_S", &dphiMET_lep_S, &b_dphiMET_lep_S);
   fChain->SetBranchAddress("dphiMET_jet_S", &dphiMET_jet_S, &b_dphiMET_jet_S);
   fChain->SetBranchAddress("dphiMET_SV_S", &dphiMET_SV_S, &b_dphiMET_SV_S);
   fChain->SetBranchAddress("Njet_a", &Njet_a, &b_Njet_a);
   fChain->SetBranchAddress("Njet_b", &Njet_b, &b_Njet_b);
   fChain->SetBranchAddress("Nbjet_a", &Nbjet_a, &b_Nbjet_a);
   fChain->SetBranchAddress("Nbjet_b", &Nbjet_b, &b_Nbjet_b);
   fChain->SetBranchAddress("Nlep_a", &Nlep_a, &b_Nlep_a);
   fChain->SetBranchAddress("Nlep_b", &Nlep_b, &b_Nlep_b);
   fChain->SetBranchAddress("NSV_a", &NSV_a, &b_NSV_a);
   fChain->SetBranchAddress("NSV_b", &NSV_b, &b_NSV_b);
   fChain->SetBranchAddress("index_lep_a", &index_lep_a, &b_index_lep_a);
   fChain->SetBranchAddress("index_lep_b", &index_lep_b, &b_index_lep_b);
   fChain->SetBranchAddress("index_SV_a", &index_SV_a, &b_index_SV_a);
   fChain->SetBranchAddress("index_SV_b", &index_SV_b, &b_index_SV_b);
   fChain->SetBranchAddress("PTCM", &PTCM, &b_PTCM);
   fChain->SetBranchAddress("PzCM", &PzCM, &b_PzCM);
   fChain->SetBranchAddress("cosCM", &cosCM, &b_cosCM);
   fChain->SetBranchAddress("dphiCM", &dphiCM, &b_dphiCM);
   fChain->SetBranchAddress("dphiCMI", &dphiCMI, &b_dphiCMI);
   fChain->SetBranchAddress("MS", &MS, &b_MS);
   fChain->SetBranchAddress("PS", &PS, &b_PS);
   fChain->SetBranchAddress("cosS", &cosS, &b_cosS);
   fChain->SetBranchAddress("dphiS", &dphiS, &b_dphiS);
   fChain->SetBranchAddress("dphiSI", &dphiSI, &b_dphiSI);
   fChain->SetBranchAddress("PTS", &PTS, &b_PTS);
   fChain->SetBranchAddress("PzS", &PzS, &b_PzS);
   fChain->SetBranchAddress("MX3a", &MX3a, &b_MX3a);
   fChain->SetBranchAddress("MX3b", &MX3b, &b_MX3b);
   fChain->SetBranchAddress("EVa", &EVa, &b_EVa);
   fChain->SetBranchAddress("EVb", &EVb, &b_EVb);
   fChain->SetBranchAddress("PVa", &PVa, &b_PVa);
   fChain->SetBranchAddress("PVb", &PVb, &b_PVb);
   fChain->SetBranchAddress("EJa", &EJa, &b_EJa);
   fChain->SetBranchAddress("EJb", &EJb, &b_EJb);
   fChain->SetBranchAddress("PJa", &PJa, &b_PJa);
   fChain->SetBranchAddress("PJb", &PJb, &b_PJb);
   fChain->SetBranchAddress("MX2a", &MX2a, &b_MX2a);
   fChain->SetBranchAddress("MX2b", &MX2b, &b_MX2b);
   fChain->SetBranchAddress("ELa", &ELa, &b_ELa);
   fChain->SetBranchAddress("ELb", &ELb, &b_ELb);
   fChain->SetBranchAddress("PLa", &PLa, &b_PLa);
   fChain->SetBranchAddress("PLb", &PLb, &b_PLb);
   fChain->SetBranchAddress("MV", &MV, &b_MV);
   fChain->SetBranchAddress("PV", &PV, &b_PV);
   fChain->SetBranchAddress("MVa", &MVa, &b_MVa);
   fChain->SetBranchAddress("MVb", &MVb, &b_MVb);
   fChain->SetBranchAddress("PV_lab", &PV_lab, &b_PV_lab);
   fChain->SetBranchAddress("dphiMET_V", &dphiMET_V, &b_dphiMET_V);
   fChain->SetBranchAddress("MJa", &MJa, &b_MJa);
   fChain->SetBranchAddress("MJb", &MJb, &b_MJb);
   fChain->SetBranchAddress("MLa", &MLa, &b_MLa);
   fChain->SetBranchAddress("MLb", &MLb, &b_MLb);
   fChain->SetBranchAddress("cosJa", &cosJa, &b_cosJa);
   fChain->SetBranchAddress("cosJb", &cosJb, &b_cosJb);
   fChain->SetBranchAddress("cosLa", &cosLa, &b_cosLa);
   fChain->SetBranchAddress("cosLb", &cosLb, &b_cosLb);
   fChain->SetBranchAddress("MJ", &MJ, &b_MJ);
   fChain->SetBranchAddress("ML", &ML, &b_ML);
   fChain->SetBranchAddress("EJ", &EJ, &b_EJ);
   fChain->SetBranchAddress("EL", &EL, &b_EL);
   fChain->SetBranchAddress("PJ", &PJ, &b_PJ);
   fChain->SetBranchAddress("PL", &PL, &b_PL);
   fChain->SetBranchAddress("PX3", &PX3, &b_PX3);
   fChain->SetBranchAddress("PX3_BoostT", &PX3_BoostT, &b_PX3_BoostT);
   fChain->SetBranchAddress("MX3a_BoostT", &MX3a_BoostT, &b_MX3a_BoostT);
   fChain->SetBranchAddress("MX3b_BoostT", &MX3b_BoostT, &b_MX3b_BoostT);
   fChain->SetBranchAddress("Mperp", &Mperp, &b_Mperp);
   fChain->SetBranchAddress("PV_BoostT", &PV_BoostT, &b_PV_BoostT);
   fChain->SetBranchAddress("EVa_BoostT", &EVa_BoostT, &b_EVa_BoostT);
   fChain->SetBranchAddress("EVb_BoostT", &EVb_BoostT, &b_EVb_BoostT);
   fChain->SetBranchAddress("PVa_BoostT", &PVa_BoostT, &b_PVa_BoostT);
   fChain->SetBranchAddress("PVb_BoostT", &PVb_BoostT, &b_PVb_BoostT);
   fChain->SetBranchAddress("EJ_BoostT", &EJ_BoostT, &b_EJ_BoostT);
   fChain->SetBranchAddress("EL_BoostT", &EL_BoostT, &b_EL_BoostT);
   fChain->SetBranchAddress("PJ_BoostT", &PJ_BoostT, &b_PJ_BoostT);
   fChain->SetBranchAddress("PL_BoostT", &PL_BoostT, &b_PL_BoostT);
   fChain->SetBranchAddress("H11S", &H11S, &b_H11S);
   fChain->SetBranchAddress("H21S", &H21S, &b_H21S);
   fChain->SetBranchAddress("HT21S", &HT21S, &b_HT21S);
   fChain->SetBranchAddress("H22S", &H22S, &b_H22S);
   fChain->SetBranchAddress("HT22S", &HT22S, &b_HT22S);
   fChain->SetBranchAddress("H42S", &H42S, &b_H42S);
   fChain->SetBranchAddress("HT42S", &HT42S, &b_HT42S);
   fChain->SetBranchAddress("H11X3a", &H11X3a, &b_H11X3a);
   fChain->SetBranchAddress("H11X3b", &H11X3b, &b_H11X3b);
   fChain->SetBranchAddress("H21X3a", &H21X3a, &b_H21X3a);
   fChain->SetBranchAddress("H21X3b", &H21X3b, &b_H21X3b);
   fChain->SetBranchAddress("PISR", &PISR, &b_PISR);
   fChain->SetBranchAddress("PTISR", &PTISR, &b_PTISR);
   fChain->SetBranchAddress("RISR", &RISR, &b_RISR);
   fChain->SetBranchAddress("RISRT", &RISRT, &b_RISRT);
   fChain->SetBranchAddress("MISR", &MISR, &b_MISR);
   Notify();
}

Bool_t KUAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void KUAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t KUAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef KUAnalysis_cxx
