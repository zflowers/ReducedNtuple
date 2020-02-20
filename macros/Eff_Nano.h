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
   bool Lepton_Cut(const Long64_t& jentry);
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

inline bool Eff_Nano::Lepton_Cut(const Long64_t& jentry)
{
 //Setting Up Leaves
 TLeaf* nElectron_leaf = m_Tree->GetLeaf("nElectron");
 nElectron_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_pt_leaf = m_Tree->GetLeaf("Electron_pt");
 Electron_pt_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_eta_leaf = m_Tree->GetLeaf("Electron_eta");
 Electron_eta_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_phi_leaf = m_Tree->GetLeaf("Electron_phi");
 Electron_phi_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_mass_leaf = m_Tree->GetLeaf("Electron_mass");
 Electron_mass_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_pfRelIso03_all_leaf = m_Tree->GetLeaf("Electron_pfRelIso03_all");
 Electron_pfRelIso03_all_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_MiniIso_leaf = m_Tree->GetLeaf("Electron_miniPFRelIso_all");
 Electron_MiniIso_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_Charge_leaf = m_Tree->GetLeaf("Electron_charge");
 Electron_Charge_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_dxy_leaf = m_Tree->GetLeaf("Electron_dxy");
 Electron_dxy_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_dxyErr_leaf = m_Tree->GetLeaf("Electron_dxyErr");
 Electron_dxyErr_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_dz_leaf = m_Tree->GetLeaf("Electron_dz");
 Electron_dz_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_dzErr_leaf = m_Tree->GetLeaf("Electron_dzErr");
 Electron_dzErr_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_ip3d_leaf = m_Tree->GetLeaf("Electron_ip3d");
 Electron_ip3d_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_sip3d_leaf = m_Tree->GetLeaf("Electron_sip3d");
 Electron_sip3d_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_lostHits_leaf = m_Tree->GetLeaf("Electron_lostHits");
 Electron_lostHits_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_convVeto_leaf = m_Tree->GetLeaf("Electron_convVeto");
 Electron_convVeto_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_mvaFall17V1noIso_leaf = m_Tree->GetLeaf("Electron_mvaFall17V1noIso");
 Electron_mvaFall17V1noIso_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Electron_mvaFall17V2noIso_leaf = m_Tree->GetLeaf("Electron_mvaFall17V2noIso");
 Electron_mvaFall17V2noIso_leaf->GetBranch()->GetEntry(jentry);
 
 TLeaf* nMuon_leaf = m_Tree->GetLeaf("nMuon");
 nMuon_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_pt_leaf = m_Tree->GetLeaf("Muon_pt");
 Muon_pt_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_eta_leaf = m_Tree->GetLeaf("Muon_eta");
 Muon_eta_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_phi_leaf = m_Tree->GetLeaf("Muon_phi");
 Muon_phi_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_mass_leaf = m_Tree->GetLeaf("Muon_mass");
 Muon_mass_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_pfRelIso03_all_leaf = m_Tree->GetLeaf("Muon_pfRelIso03_all");
 Muon_pfRelIso03_all_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_MiniIso_leaf = m_Tree->GetLeaf("Muon_miniPFRelIso_all");
 Muon_MiniIso_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_Charge_leaf = m_Tree->GetLeaf("Muon_charge");
 Muon_Charge_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_dxy_leaf = m_Tree->GetLeaf("Muon_dxy");
 Muon_dxy_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_dxyErr_leaf = m_Tree->GetLeaf("Muon_dxyErr");
 Muon_dxyErr_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_dz_leaf = m_Tree->GetLeaf("Muon_dz");
 Muon_dz_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_dzErr_leaf = m_Tree->GetLeaf("Muon_dzErr");
 Muon_dzErr_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_ip3d_leaf = m_Tree->GetLeaf("Muon_ip3d");
 Muon_ip3d_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_sip3d_leaf = m_Tree->GetLeaf("Muon_sip3d");
 Muon_sip3d_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_softId_leaf = m_Tree->GetLeaf("Muon_softId"); 
 Muon_softId_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_mediumId_leaf = m_Tree->GetLeaf("Muon_mediumId"); 
 Muon_softId_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_tightId_leaf = m_Tree->GetLeaf("Muon_tightId"); 
 Muon_tightId_leaf->GetBranch()->GetEntry(jentry);
  
 //Electrons
 bool cut_Electron = false; //start by assuming we have no good electrons

  int year = 2017;
  if(m_Tag.find("16") != std::string::npos)
    year = 2016;
  if(m_Tag.find("18") != std::string::npos)
    year = 2018;

  for(int i = 0; i < nElectron_leaf->GetValue(); i++){
    // baseline lepton definition
    if(Electron_pt_leaf->GetValue(i) < 5. || fabs(Electron_eta_leaf->GetValue(i)) > 2.5)
      continue;
    // if(fabs(Electron_dxy_leaf->GetValue(i)) >= 0.05 || fabs(Electron_dz_leaf->GetValue(i)) >= 0.1 ||
    //    Electron_ip3d_leaf->GetValue(i) >= 0.0175 || Electron_sip3d_leaf->GetValue(i) >= 2.5)
    if(fabs(Electron_dxy_leaf->GetValue(i)) >= 0.05 || fabs(Electron_dz_leaf->GetValue(i)) >= 0.1 || Electron_sip3d_leaf->GetValue(i) >= 8)
      continue;
    if(Electron_pfRelIso03_all_leaf->GetValue(i)*Electron_pt_leaf->GetValue(i) >= 20. + 300./Electron_pt_leaf->GetValue(i))
      continue;

    // FO baseline criteria
    if(Electron_lostHits_leaf->GetValue(i) == 0 && Electron_convVeto_leaf->GetValue(i)){

      double mva = Electron_mvaFall17V1noIso_leaf->GetValue(i);
      if(year == 2016 || year == 2018)
	mva = Electron_mvaFall17V2noIso_leaf->GetValue(i);


      // convert to raw MVA output
      if(mva == -1.)
	mva = -999.;
      else if(mva == 1.)
	mva = 999.;
      else
	mva = -0.5*log((1.-mva)/(1.+mva));
          
      // signal lepton IDs baseline criteria
	// Tight electron
	if(year == 2016){ // Summer16_94X legacy
	  if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 1.309)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 3.447 + 0.063*(Electron_pt_leaf->GetValue(i)- 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 4.392)
		cut_Electron = true; break;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.373)
		cut_Electron = true; break; // just changed me
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 2.522 + 0.058*(Electron_pt_leaf->GetValue(i) - 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 3.392)
		cut_Electron = true; break;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.071)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 1.555 + 0.075*(Electron_pt_leaf->GetValue(i) - 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 2.680)
		cut_Electron = true; break;
	    }
	  }
	}

	if(year == 2017){ // Fall17_94X
	  if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.488)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 0.2+0.032*(Electron_pt_leaf->GetValue(i) - 10.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 0.68)
		cut_Electron = true; break;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > -0.045)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 0.1+0.025*(Electron_pt_leaf->GetValue(i) - 10.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 0.475)
		cut_Electron = true; break;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.176)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > -0.1+0.028*(Electron_pt_leaf->GetValue(i) - 10.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 0.32)
		cut_Electron = true; break;
	    }
	  }
	}

	if(year == 2018){ // Autumn18_102X
	  if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 1.320)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 4.277 + 0.112*(Electron_pt_leaf->GetValue(i) - 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 4.277)
		cut_Electron = true; break;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.192)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 3.152 + 0.060*(Electron_pt_leaf->GetValue(i) - 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 3.152)
		cut_Electron = true; break;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.362)
		cut_Electron = true; break;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 2.359 + 0.087*(Electron_pt_leaf->GetValue(i) - 25.))
		cut_Electron = true; break;
	    } else {
	      if(mva > 2.359)
		cut_Electron = true; break;
	    }
	  }
	}
  /*
      // FO VLoose Electron
      if(year == 2016){ // Summer16_94X legacy
	if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.259)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -0.388 + 0.109*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.388)
	      cut_Electron = true; break;
	  }
	} else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.256)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -0.696 + 0.106*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.696)
	      cut_Electron = true; break;
	  }
	} else { // eta < 2.5
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -1.630)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -1.219 + 0.148*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -1.219)
	      cut_Electron = true; break;
	  }
	}
      }

      if(year == 2017){ // Fall17_94X
	if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.135)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > (-0.93 + (0.043/15.)*(Electron_pt_leaf->GetValue(i)-10.)))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.887)
	      cut_Electron = true; break;
	  }
	} else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.417)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > (-0.93 + (0.04/15.)*(Electron_pt_leaf->GetValue(i)-10.)))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.89)
	      cut_Electron = true; break;
	  }
	} else { // eta < 2.5
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.470)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > (-0.942 + (0.032/15.)*(Electron_pt_leaf->GetValue(i)-10.)))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.91)
	      cut_Electron = true; break;
	  }
	}
      }

      if(year == 2018){ // Autumn18_102X
	if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > 0.053)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -0.106 + 0.062*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.106)
	      cut_Electron = true; break;
	  }
	} else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.434)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -0.769 + 0.038*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -0.769)
	      cut_Electron = true; break;
	  }
	} else { // eta < 2.5
	  if(Electron_pt_leaf->GetValue(i) < 10.){
	    if(mva > -0.956)
	      cut_Electron = true; break;
	  } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	    if(mva > -1.461 + 0.042*(Electron_pt_leaf->GetValue(i) - 25.))
	      cut_Electron = true; break;
	  } else {
	    if(mva > -1.461)
	      cut_Electron = true; break;
	  }
	}
      }
     */
    }
  }

  //Muon
  bool cut_Muon = false; //start by assuming we have no good muons
  for(int i = 0; i < nMuon_leaf->GetValue(); i++){
     // baseline lepton definition
    if(Muon_pt_leaf->GetValue(i) < 3. || fabs(Muon_eta_leaf->GetValue(i)) > 2.4)
      continue;
    // if(fabs(Muon_dxy_leaf->GetValue(i)) >= 0.05 || fabs(Muon_dz_leaf->GetValue(i)) >= 0.1 ||
    //    Muon_ip3d_leaf->GetValue(i) >= 0.0175 || Muon_sip3d_leaf->GetValue(i) >= 2.5)
    if(fabs(Muon_dxy_leaf->GetValue(i)) >= 0.05 || fabs(Muon_dz_leaf->GetValue(i)) >= 0.1 || Muon_sip3d_leaf->GetValue(i) >= 8.)
      continue;
    if(Muon_pfRelIso03_all_leaf->GetValue(i)*Muon_pt_leaf->GetValue(i) >= 20. + 300./Muon_pt_leaf->GetValue(i))
      continue;
    if(true){
      cut_Muon = true;
      // signal lep criteria
	if(Muon_tightId_leaf->GetValue(i))
          cut_Muon = true;
	else if(Electron_pt_leaf->GetValue(i) < 0.){
	  if(Muon_softId_leaf->GetValue(i))
            cut_Muon = true;
	} else {
	  if(Muon_mediumId_leaf->GetValue(i))
            cut_Muon = true;
	}
     }
   }
   if (cut_Electron || cut_Muon) {return true;}
   else {return false;}
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
 //if(HT < 300.) { cut = true; }
 
 //Lepton Cut(s)
 //Require at least one electron or muon (loose)
 if(!Lepton_Cut(jentry)) { cut = true; } 

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
   int bins = 24;
   //array size is the number of bins
   double bin_edges[25] = {0.,50.,75.,90.,100.,110.,120.,130.,140.0,150.,160.,170.,180.,190.,200.,210.,220.,230.,240.,250.,275.,300.,350.,400.,500.};
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
      if(jentry > 300000) break;
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
