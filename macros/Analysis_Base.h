#include <iostream>
#include <algorithm>
#include <TFile.h>
#include <TTree.h>
#include <TEfficiency.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include <vector>

#ifndef ANALYSIS_BASE_H
#define ANALYSIS_BASE_H

std::string get_str_between_two_str(const std::string &s, const std::string &start_delim, const std::string &stop_delim)
{
 unsigned first_delim_pos = s.find(start_delim);
 unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
 unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
 return s.substr(end_pos_of_first_delim,last_delim_pos - end_pos_of_first_delim);
}

void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
 size_t pos = mainStr.find(toErase);
 if (pos != std::string::npos)
 {
  mainStr.erase(pos, toErase.length());
 }
}

class Analysis_Base{
  private:
  protected:
   string m_outFile = "output_test.root";
   string m_Tag;
   TTree* m_Tree;
   string m_cut = "";
   virtual bool Get_Cut(const Long64_t& jentry, string name, string& current_cut);
   virtual bool global_cuts(const Long64_t& jentry);
  public:
   Analysis_Base();
   Analysis_Base(string outFile, string Tag, TTree*& Tree);
   ~Analysis_Base();
   virtual void Analyze();
   virtual void Set_Tag(const string& tag);
   virtual void Set_Tree(TTree*& tree);
   virtual void Set_Output(const string& outFile);
   virtual void Set_Cut(const string& cut);
};

inline Analysis_Base::Analysis_Base()
{
 m_Tag = "";
 m_Tree = NULL;
 m_cut = "";
}

inline Analysis_Base::Analysis_Base(string outFile, string Tag, TTree*& tree)
{
 m_outFile = outFile;
 m_Tag = Tag;
 m_Tree = tree;
}

inline Analysis_Base::~Analysis_Base()
{
// if(m_Tree != NULL) delete m_Tree;
}

inline void Analysis_Base::Set_Tag(const string& tag)
{
 m_Tag = tag;
}

inline void Analysis_Base::Set_Tree(TTree*& tree)
{
 m_Tree = tree;
}

inline void Analysis_Base::Set_Output(const string& outFile)
{
 m_outFile = outFile;
}

inline void Analysis_Base::Set_Cut(const string& cut)
{
 m_cut = cut+"_";
}

inline bool Analysis_Base::Get_Cut(const Long64_t& jentry, string name, string& current_cut)
{
 bool cut = false;

 bool Bronze = false;
 bool Silver = false;
 bool Gold = false;
 int numBronze = 0;
 int numSilver = 0;
 int numGold = 0;
 if(name.find("Bronze") != std::string::npos)
 {
  Bronze = true;
  eraseSubStr(name,("Bronze"));
  eraseSubStr(current_cut,("Bronze"));
  if(name.find("Nlep") != std::string::npos)
  {
   TBranch* b_Nlep = NULL;
   Int_t Nlep = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nlep,&b_Nlep);
   b_Nlep->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nlep; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11)
    {
     if(ID_lep->at(i) >= 1 )
     {
      numBronze++;
     }
    }
    else if(abs(PDGID_lep->at(i)) == 13)
    {
     if(ID_lep->at(i) >= 1 )
     {
      numBronze++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nlep->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
  else if(name.find("Nele") != std::string::npos)
  {
   TBranch* b_Nele = NULL;
   Int_t Nele = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nele,&b_Nele);
   b_Nele->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nele; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11)
    {
     if(ID_lep->at(i) >= 1 )
     {
      numBronze++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nele->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
  else if(name.find("Nmu") != std::string::npos)
  {
   TBranch* b_Nmu = NULL;
   Int_t Nmu = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nmu,&b_Nmu);
   b_Nmu->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nmu; i++)
   {
    if(abs(PDGID_lep->at(i)) == 13)
    {
     if(ID_lep->at(i) >= 1 )
     {
      numBronze++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nmu->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
 }
 else if(name.find("Silver") != std::string::npos)
 {
  Silver = true;
  eraseSubStr(name,("Silver"));
  eraseSubStr(current_cut,("Silver"));
  if(name.find("Nlep") != std::string::npos)
  {
   TBranch* b_Nlep = NULL;
   Int_t Nlep = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nlep,&b_Nlep);
   b_Nlep->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nlep; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11)
    {
     if(ID_lep->at(i) >= 4)
     {
      numSilver++;
     }
    }
    else if(abs(PDGID_lep->at(i)) == 13)
    {
     if(ID_lep->at(i) >= 3)
     {
      numSilver++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nlep->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
  else if(name.find("Nele") != std::string::npos)
  {
   TBranch* b_Nele = NULL;
   Int_t Nele = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nele,&b_Nele);
   b_Nele->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nele; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11)
    {
     if(ID_lep->at(i) >= 4)
     {
      numSilver++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nele->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
  else if(name.find("Nmu") != std::string::npos)
  {
   TBranch* b_Nmu = NULL;
   Int_t Nmu = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nmu,&b_Nmu);
   b_Nmu->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   for(int i = 0; i < Nmu; i++)
   {
    if(abs(PDGID_lep->at(i)) == 13)
    {
     if(ID_lep->at(i) >= 3)
     {
      numSilver++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   b_Nmu->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
  }
 }
 if(name.find("Gold") != std::string::npos)
 {
  Gold = true;
  eraseSubStr(name,("Gold"));
  eraseSubStr(current_cut,("Gold"));
  if(name.find("Nlep") != std::string::npos)
  {
   TBranch* b_Nlep = NULL;
   Int_t Nlep = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nlep,&b_Nlep);
   b_Nlep->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   TBranch* b_MiniIso_lep = NULL;
   vector<double>* MiniIso_lep = 0;
   m_Tree->SetBranchAddress("MiniIso_lep",&MiniIso_lep,&b_MiniIso_lep);
   b_MiniIso_lep->GetEntry(jentry);
   TBranch* b_SIP3D_lep = NULL;
   vector<double>* SIP3D_lep = 0;
   m_Tree->SetBranchAddress("SIP3D_lep",&SIP3D_lep,&b_SIP3D_lep);
   b_SIP3D_lep->GetEntry(jentry);
   TBranch* b_PT_lep = NULL;
   vector<double>* PT_lep = 0;
   m_Tree->SetBranchAddress("PT_lep",&PT_lep,&b_PT_lep);
   b_PT_lep->GetEntry(jentry);
   for(int i = 0; i < Nlep; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11)
    {
     if(ID_lep->at(i) >= 4 && PT_lep->at(i)*MiniIso_lep->at(i) < 5. && SIP3D_lep->at(i) < 4.)
     {
      numGold++;
     }
    }
    else if(abs(PDGID_lep->at(i)) == 13)
    {
     if(ID_lep->at(i) >= 3 && PT_lep->at(i)*MiniIso_lep->at(i) < 5. && SIP3D_lep->at(i) < 4.)
     {
      numGold++;
     }
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   MiniIso_lep->clear();
   SIP3D_lep->clear();
   PT_lep->clear();
   b_Nlep->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
   b_MiniIso_lep->ResetAddress();
   b_SIP3D_lep->ResetAddress();
   b_PT_lep->ResetAddress();
  }
  else if(name.find("Nele") != std::string::npos)
  {
   TBranch* b_Nele = NULL;
   Int_t Nele = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nele,&b_Nele);
   b_Nele->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   TBranch* b_MiniIso_lep = NULL;
   vector<double>* MiniIso_lep = 0;
   m_Tree->SetBranchAddress("MiniIso_lep",&MiniIso_lep,&b_MiniIso_lep);
   b_MiniIso_lep->GetEntry(jentry);
   TBranch* b_SIP3D_lep = NULL;
   vector<double>* SIP3D_lep = 0;
   m_Tree->SetBranchAddress("SIP3D_lep",&SIP3D_lep,&b_SIP3D_lep);
   b_SIP3D_lep->GetEntry(jentry);
   TBranch* b_PT_lep = NULL;
   vector<double>* PT_lep = 0;
   m_Tree->SetBranchAddress("PT_lep",&PT_lep,&b_PT_lep);
   b_PT_lep->GetEntry(jentry);
   for(int i = 0; i < Nele; i++)
   {
    if(abs(PDGID_lep->at(i)) == 11 && ID_lep->at(i) >= 4 && PT_lep->at(i)*MiniIso_lep->at(i) < 5. && SIP3D_lep->at(i) < 4.)
    {
     numGold++;
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   MiniIso_lep->clear();
   SIP3D_lep->clear();
   PT_lep->clear();
   b_Nele->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
   b_MiniIso_lep->ResetAddress();
   b_SIP3D_lep->ResetAddress();
   b_PT_lep->ResetAddress();
  }
  else if(name.find("Nmu") != std::string::npos)
  {
   TBranch* b_Nmu = NULL;
   Int_t Nmu = 0;
   m_Tree->SetBranchAddress(name.c_str(),&Nmu,&b_Nmu);
   b_Nmu->GetEntry(jentry);
   TBranch* b_PDGID_lep = NULL;
   vector<int>* PDGID_lep = 0;
   m_Tree->SetBranchAddress("PDGID_lep",&PDGID_lep,&b_PDGID_lep);
   b_PDGID_lep->GetEntry(jentry);
   TBranch* b_ID_lep = NULL;
   vector<int>* ID_lep = 0;
   m_Tree->SetBranchAddress("ID_lep",&ID_lep,&b_ID_lep);
   b_ID_lep->GetEntry(jentry);
   TBranch* b_MiniIso_lep = NULL;
   vector<double>* MiniIso_lep = 0;
   m_Tree->SetBranchAddress("MiniIso_lep",&MiniIso_lep,&b_MiniIso_lep);
   b_MiniIso_lep->GetEntry(jentry);
   TBranch* b_SIP3D_lep = NULL;
   vector<double>* SIP3D_lep = 0;
   m_Tree->SetBranchAddress("SIP3D_lep",&SIP3D_lep,&b_SIP3D_lep);
   b_SIP3D_lep->GetEntry(jentry);
   TBranch* b_PT_lep = NULL;
   vector<double>* PT_lep = 0;
   m_Tree->SetBranchAddress("PT_lep",&PT_lep,&b_PT_lep);
   b_PT_lep->GetEntry(jentry);
   for(int i = 0; i < Nmu; i++)
   {
    if(abs(PDGID_lep->at(i)) == 13 && ID_lep->at(i) >= 3 && PT_lep->at(i)*MiniIso_lep->at(i) < 5. && SIP3D_lep->at(i) < 4.)
    {
     numGold++;
    }
   }
   PDGID_lep->clear();
   ID_lep->clear();
   MiniIso_lep->clear();
   SIP3D_lep->clear();
   PT_lep->clear();
   b_Nmu->ResetAddress();
   b_PDGID_lep->ResetAddress();
   b_ID_lep->ResetAddress();
   b_MiniIso_lep->ResetAddress();
   b_SIP3D_lep->ResetAddress();
   b_PT_lep->ResetAddress();
  }
 }

 if(current_cut.find(name) != std::string::npos)
 {
  string cut_value = get_str_between_two_str(current_cut,name,"_");
  string cut_type = get_str_between_two_str(current_cut,name,"_");

  string type = m_Tree->GetBranch(name.c_str())->GetLeaf(name.c_str())->GetTypeName();

  double val = 0.;
  if(type == "Long64_t")
  {
   TBranch* branch = NULL;
   Long64_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "ULong64_t")
  {
   TBranch* branch = NULL;
   ULong64_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Double32_t")
  {
   TBranch* branch = NULL;
   Double32_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Double_t")
  {
   TBranch* branch = NULL;
   Double_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Float16_t")
  {
   TBranch* branch = NULL;
   Float16_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Float_t")
  {
   TBranch* branch = NULL;
   Float_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "UInt_t")
  {
   TBranch* branch = NULL;
   UInt_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Int_t")
  {
   TBranch* branch = NULL;
   Int_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "UShort_t")
  {
   TBranch* branch = NULL;
   UShort_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Short_t")
  {
   TBranch* branch = NULL;
   Short_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "UChar_t")
  {
   TBranch* branch = NULL;
   UChar_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Char_t")
  {
   TBranch* branch = NULL;
   Char_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else if(type == "Bool_t")
  {
   TBranch* branch = NULL;
   Bool_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
   branch->ResetAddress();
   //delete branch;
  }
  else
  {
   cout << "Could not find type: " << type << "!" << endl;
  }

  if(Bronze)
  {
   val = numBronze;
  }
  else if(Silver)
  {
   val = numSilver;
  }
  else if(Gold)
  {
   val = numGold;
  }

  if(cut_type.find("E") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(val == std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("Ge") != std::string::npos)
  {
   cut_value.erase(0,1);
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(val >= std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("G") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(val > std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("Le") != std::string::npos)
  {
   cut_value.erase(0,1);
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(val <= std::stod(cut_value))
   {
    cut = true;
   }
  }
  else if(cut_type.find("L") != std::string::npos)
  {
   cut_value.erase(0,1);
   eraseSubStr(cut_type,cut_value);
   if(val < std::stod(cut_value))
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
 //m_Tree->ResetBranchAddresses();
 return cut;
}

inline bool Analysis_Base::global_cuts(const Long64_t& jentry)
{
 //return false to keep the event
 
 string current_cut = m_cut;

 bool PTISR_cut = true;
 bool PTCM_cut = true;
 bool RISR_cut = true;
 bool dphiCMI_cut = true;
 bool MET_cut = true;
 bool Nmu_cut = true;
 bool Nele_cut = true;
 bool Nlep_cut = true;

 bool NmuBronze_cut = true;
 bool NeleBronze_cut = true;
 bool NlepBronze_cut = true;

 bool NmuSilver_cut = true;
 bool NeleSilver_cut = true;
 bool NlepSilver_cut = true;

 bool NmuGold_cut = true;
 bool NeleGold_cut = true;
 bool NlepGold_cut = true;

 bool Njet_cut = true;
 bool METtrigger_cut = true;
 bool METORtrigger_cut = true;
 bool METHTtrigger_cut = true;
 bool EventFilter_cut = true;

 if(m_Tag.find("SingleElectron")) current_cut += "_NeleBronzeG0";
 if(m_Tag.find("SingleMuon")) current_cut += "_NmuBronzeG0";

 string PTISR_str = "PTISRG200";
 PTISR_cut = Get_Cut(jentry,"PTISR",PTISR_str);
 if(current_cut.find("PTISR") != std::string::npos)
 {
  PTISR_cut = Get_Cut(jentry,"PTISR",current_cut);
 }

 string RISR_str = "RISRG0.5";
 RISR_cut = Get_Cut(jentry,"RISR",RISR_str);
 if(current_cut.find("RISR") != std::string::npos)
 {
  RISR_cut = Get_Cut(jentry,"RISR",current_cut);
 }

 string PTCM_str = "PTCML100";
 PTCM_cut = Get_Cut(jentry,"PTCM",PTCM_str);
 if(current_cut.find("PTCM") != std::string::npos)
 {
  PTCM_cut = Get_Cut(jentry,"PTCM",current_cut);
 }

 if(current_cut.find("dphiCMI") != std::string::npos)
 {
  dphiCMI_cut = Get_Cut(jentry,"dphiCMI",current_cut);
 }

 if(current_cut.find("Nmu") != std::string::npos)
 {
  if(current_cut.find("NmuBronze") != std::string::npos) { NmuBronze_cut = Get_Cut(jentry,"NmuBronze",current_cut); }
  else if(current_cut.find("NmuSilver") != std::string::npos) { NmuSilver_cut = Get_Cut(jentry,"NmuSilver",current_cut); }
  else if(current_cut.find("NmuGold") != std::string::npos) { NmuGold_cut = Get_Cut(jentry,"NmuGold",current_cut); }
  else { Nmu_cut = Get_Cut(jentry,"Nmu",current_cut); }
 }

 if(current_cut.find("Nele") != std::string::npos)
 {
  if(current_cut.find("NeleBronze") != std::string::npos) { NeleBronze_cut = Get_Cut(jentry,"NeleBronze",current_cut); }
  else if(current_cut.find("NeleSilver") != std::string::npos) { NeleSilver_cut = Get_Cut(jentry,"NeleSilver",current_cut); }
  else if(current_cut.find("NeleGold") != std::string::npos) { NeleGold_cut = Get_Cut(jentry,"NeleGold",current_cut); }
  else { Nele_cut = Get_Cut(jentry,"Nele",current_cut); }
 }

 if(current_cut.find("Nlep") != std::string::npos)
 {
  if(current_cut.find("NlepBronze") != std::string::npos) { NlepBronze_cut = Get_Cut(jentry,"NlepBronze",current_cut); }
  else if(current_cut.find("NlepSilver") != std::string::npos) { NlepSilver_cut = Get_Cut(jentry,"NlepSilver",current_cut); }
  else if(current_cut.find("NlepGold") != std::string::npos) { NlepGold_cut = Get_Cut(jentry,"NlepGold",current_cut); }
  else { Nlep_cut = Get_Cut(jentry,"Nlep",current_cut); }
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

 string EventFilter_str = "EventFilterE1";
 EventFilter_cut = Get_Cut(jentry,"EventFilter",EventFilter_str);
 if(current_cut.find("EventFilter") != std::string::npos)
 {
  EventFilter_cut = Get_Cut(jentry,"EventFilter",current_cut);
 }

 if(current_cut.find("MET") != std::string::npos)
 {
  MET_cut = Get_Cut(jentry,"MET",current_cut);
 }

 if(current_cut.find("NoCuts") == 0)
 {
  current_cut = "";
  if(PTISR_cut && RISR_cut && PTCM_cut && dphiCMI_cut && MET_cut && Nmu_cut && Nele_cut && Nlep_cut && NmuBronze_cut && NeleBronze_cut && NlepBronze_cut && NmuSilver_cut && NeleSilver_cut && NlepSilver_cut && NmuGold_cut && NeleGold_cut && NlepGold_cut && Njet_cut && METtrigger_cut && METORtrigger_cut && METHTtrigger_cut && EventFilter_cut)
  {
   return false;
  }
 }

 if(current_cut.compare("") != 0)
 {
  cout << "ERROR: Some cuts not applied: " << current_cut << endl;
 }

 if(PTISR_cut && RISR_cut && PTCM_cut && dphiCMI_cut && MET_cut && Nmu_cut && Nele_cut && Nlep_cut && NmuBronze_cut && NeleBronze_cut && NlepBronze_cut && NmuSilver_cut && NeleSilver_cut && NlepSilver_cut && NmuGold_cut && NeleGold_cut && NlepGold_cut && Njet_cut && METtrigger_cut && METORtrigger_cut && METHTtrigger_cut && EventFilter_cut)
 {
  return false;
 }
 return true;

}

inline void Analysis_Base::Analyze(){
   cout << "Analyzing with Analysis_Base!" << endl;

   Long64_t nentries = m_Tree->GetEntriesFast();
   Long64_t percent = 10.0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {      
      if(jentry%((std::max(nentries,percent))/percent) == 0) { cout << "Processing Event: " << jentry << " out of: " << nentries << " Entries" << endl; }

      Long64_t ientry = m_Tree->LoadTree(jentry);
      if(global_cuts(jentry)) continue;

   }
   cout << "Finished Event Loop" << endl;

}

#endif

