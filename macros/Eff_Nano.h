#ifndef EFF_NANO_H
#define EFF_NANO_H

#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"
#include "Analysis_Base.h"

using namespace std;

class Eff_Nano:public Analysis_Base{
  private:
   bool Lepton_Cut(const Long64_t& jentry);
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
 TLeaf* Muon_minipfRelIso_all_leaf = m_Tree->GetLeaf("Muon_miniPFRelIso_all");
 Muon_minipfRelIso_all_leaf->GetBranch()->GetEntry(jentry);
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
 Muon_mediumId_leaf->GetBranch()->GetEntry(jentry);
 TLeaf* Muon_tightId_leaf = m_Tree->GetLeaf("Muon_tightId"); 
 Muon_tightId_leaf->GetBranch()->GetEntry(jentry);
  
 bool selection = false;
 int Nlep = 0;

 //Electrons

  int year = 2017;
  if(m_Tag.find("16") != std::string::npos)
    year = 2016;
  if(m_Tag.find("18") != std::string::npos)
    year = 2018;

  for(int i = 0; i < nElectron_leaf->GetValue(); i++){
    // baseline lepton definition
    if(Electron_pt_leaf->GetValue(i) < 5. || fabs(Electron_eta_leaf->GetValue(i)) > 2.5) continue;
    if(fabs(Electron_dxy_leaf->GetValue(i)) >= 0.05 || fabs(Electron_dz_leaf->GetValue(i)) >= 0.1 || Electron_sip3d_leaf->GetValue(i) >= 4.) continue;
    if(Electron_pfRelIso03_all_leaf->GetValue(i)*Electron_pt_leaf->GetValue(i) >= 20. + 300./Electron_pt_leaf->GetValue(i)) continue;

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
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 3.447 + 0.063*(Electron_pt_leaf->GetValue(i)- 25.))
		continue;
	    } else {
	      if(mva > 4.392)
		continue;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.373)
		continue; // just changed me
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 2.522 + 0.058*(Electron_pt_leaf->GetValue(i) - 25.))
		continue;
	    } else {
	      if(mva > 3.392)
		continue;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.071)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 40.) {
	      if(mva > 1.555 + 0.075*(Electron_pt_leaf->GetValue(i) - 25.))
		continue;
	    } else {
	      if(mva > 2.680)
		continue;
	    }
	  }
	}

	if(year == 2017){ // Fall17_94X
	  if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.488)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 0.2+0.032*(Electron_pt_leaf->GetValue(i) - 10.))
		continue;
	    } else {
	      if(mva > 0.68)
		continue;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > -0.045)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 0.1+0.025*(Electron_pt_leaf->GetValue(i) - 10.))
		continue;
	    } else {
	      if(mva > 0.475)
		continue;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.176)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > -0.1+0.028*(Electron_pt_leaf->GetValue(i) - 10.))
		continue;
	    } else {
	      if(mva > 0.32)
		continue;
	    }
	  }
	}

	if(year == 2018){ // Autumn18_102X
	  if(fabs(Electron_eta_leaf->GetValue(i)) < 0.8){ // eta < 0.8
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 1.320)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 4.277 + 0.112*(Electron_pt_leaf->GetValue(i) - 25.))
		continue;
	    } else {
	      if(mva > 4.277)
		continue;
	    }
	  } else if(fabs(Electron_eta_leaf->GetValue(i)) < 1.479){ // eta < 1.479
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.192)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 3.152 + 0.060*(Electron_pt_leaf->GetValue(i) - 25.))
		continue;
	    } else {
	      if(mva > 3.152)
		continue;
	    }
	  } else { // eta < 2.5
	    if(Electron_pt_leaf->GetValue(i) < 10.){ // using VLoose ID for low pT
	      if(mva > 0.362)
		continue;
	    } else if(Electron_pt_leaf->GetValue(i) < 25.) {
	      if(mva > 2.359 + 0.087*(Electron_pt_leaf->GetValue(i) - 25.))
		continue;
	    } else {
	      if(mva > 2.359)
		continue;
	    }
	  }
	}

    }
    //selection = true;
    Nlep++;
  }

  //Muon
  int Nmuons = nMuon_leaf->GetValue();
  //if(Nmuons != 2) selection = true;
   
  //TLorentzVector Muon1;
  //TLorentzVector Muon2;
  for(int i = 0; i < Nmuons; i++){
  
     // baseline lepton definition
    if(Muon_pt_leaf->GetValue(i) < 3. || fabs(Muon_eta_leaf->GetValue(i)) > 2.4) selection = true;
    if(fabs(Muon_dxy_leaf->GetValue(i)) >= 0.05) selection = true;
    if(fabs(Muon_dz_leaf->GetValue(i)) >= 0.1) selection = true;
    if(Muon_sip3d_leaf->GetValue(i) >= 8.) selection = true;
    if(Muon_minipfRelIso_all_leaf->GetValue(i)*Muon_pt_leaf->GetValue(i) > 6.) selection = true;//Margaret Iso
    //if(Muon_pfRelIso03_all_leaf->GetValue(i)*Muon_pt_leaf->GetValue(i) >= 20. + 300./Muon_pt_leaf->GetValue(i)) selection = true; //Chris Iso
   
    // signal lep criteria
    //if(!(Muon_tightId_leaf->GetValue(i))) selection = true;
    //if(!(Muon_softId_leaf->GetValue(i))) selection = true;
    if(!(Muon_mediumId_leaf->GetValue(i))) selection = true;
   }
   //Muon1.SetPtEtaPhiM(Muon_pt_leaf->GetValue(0),Muon_eta_leaf->GetValue(0),Muon_phi_leaf->GetValue(0),Muon_mass_leaf->GetValue(0));
   //Muon2.SetPtEtaPhiM(Muon_pt_leaf->GetValue(1),Muon_eta_leaf->GetValue(1),Muon_phi_leaf->GetValue(1),Muon_mass_leaf->GetValue(1));
   //if(Muon2.Pt() < 10.) selection = true;
   //if((Muon1+Muon2).M() < 4.) selection = true;
   //if((Muon1+Muon2).M() > 60.) selection = true;
   //if((Muon1+Muon2).Pt() < 3.) selection = true;
   
   if(Nlep > 0) selection = true;
   return selection; 
}

inline void Eff_Nano::Analyze(){
   TLeaf* x_leaf = m_Tree->GetLeaf(m_x.c_str());
   TLeaf* weight_leaf = m_Tree->GetLeaf("weight");
   vector<TLeaf*> vect_leaf;
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
   for(int i=0; i < int(m_Triggers.size()); i++)
   {
    TEfficiency* eff = new TEfficiency(m_Triggers.at(i).c_str(),(m_Triggers.at(i)+";"+m_x+";Efficiency").c_str(),bins,bin_edges_ptr);
    eff->SetUseWeightedEvents();
    eff->SetStatisticOption(TEfficiency::kBUniform);
    vect_Eff.push_back(eff);
    TLeaf* trig = m_Tree->GetLeaf(m_Triggers.at(i).c_str());
    vect_leaf.push_back(trig);
   }
   TEfficiency* eff = new TEfficiency("SuperOR",("SuperOR;"+m_x+";Efficiency").c_str(),bins,bin_edges_ptr);
   eff->SetUseWeightedEvents();
   eff->SetStatisticOption(TEfficiency::kBUniform);
   vect_Eff.push_back(eff);

   Long64_t nentries = m_Tree->GetEntriesFast();
   Long64_t percent = 10.0;
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = m_Tree->LoadTree(jentry);
      //nb = m_Tree->GetEntry(jentry);   nbytes += nb;
      x_leaf->GetBranch()->GetEntry(jentry);    
      weight_leaf->GetBranch()->GetEntry(jentry);    
      if(jentry%((std::max(nentries,percent))/percent) == 0) { cout << "Processing Event: " << jentry << " out of: " << nentries << " Entries" << endl; }
      if(global_cuts(jentry)) continue;
      bool SuperOR = false;
      for(int i=0; i < int(m_Triggers.size()); i++)
      {
       vect_leaf.at(i)->GetBranch()->GetEntry(jentry);
       vect_Eff.at(i)->FillWeighted(vect_leaf.at(i)->GetValue(),weight_leaf->GetValue(),x_leaf->GetValue());
       SuperOR = (SuperOR || vect_leaf.at(i)->GetValue());
       //vect_Eff.at(i)->Fill((vect_leaf.at(i)->GetValue() && Other_Bools(jentry)),x_leaf->GetValue());
       //vect_Eff.at(i)->Fill(vect_leaf.at(i)->GetValue(),x_leaf->GetValue());
      }
      vect_Eff.at(int(vect_Eff.size()-1))->FillWeighted(SuperOR,weight_leaf->GetValue(),x_leaf->GetValue());
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
