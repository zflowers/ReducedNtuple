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
   Analysis_Base(string outFile, string Tag, TTree* Tree);
   ~Analysis_Base();
   virtual void Analyze();
   virtual void Set_Tag(const string& tag);
   virtual void Set_Tree(TTree* tree);
   virtual void Set_Output(const string& outFile);
   virtual void Set_Cut(const string& cut);
};

inline Analysis_Base::Analysis_Base()
{
 m_Tag = "";
 m_Tree = NULL;
 m_cut = "";
}

inline Analysis_Base::Analysis_Base(string outFile, string Tag, TTree* Tree)
{
 m_outFile = outFile;
 m_Tag = Tag;
 m_Tree = Tree;
}

inline Analysis_Base::~Analysis_Base()
{
 //if(m_Tree != NULL) delete m_Tree;
}

inline void Analysis_Base::Set_Tag(const string& tag)
{
 m_Tag = tag;
}

inline void Analysis_Base::Set_Tree(TTree* tree)
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
 TBranch* branch = NULL;
 if(current_cut.find(name) != std::string::npos)
 {
  string cut_value = get_str_between_two_str(current_cut,name,"_");
  string cut_type = get_str_between_two_str(current_cut,name,"_");
  double val = 0.;

  string type = m_Tree->GetBranch(name.c_str())->GetLeaf(name.c_str())->GetTypeName();

  if(type == "Long64_t")
  {
   Long64_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "ULong64_t")
  {
   ULong64_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Double32_t")
  {
   Double32_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Double_t")
  {
   Double_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Float16_t")
  {
   Float16_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Float_t")
  {
   Float_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "UInt_t")
  {
   UInt_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Int_t")
  {
   Int_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "UShort_t")
  {
   UShort_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Short_t")
  {
   Short_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "UChar_t")
  {
   UChar_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Char_t")
  {
   Char_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else if(type == "Bool_t")
  {
   Bool_t val_type = 0.;
   m_Tree->SetBranchAddress(name.c_str(),&val_type,&branch);
   branch->GetEntry(jentry);
   val = val_type;
  }
  else
  {
   cout << "Could not find type: " << type << "!" << endl;
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
 branch->ResetAddress();
 return cut;
}

inline bool Analysis_Base::global_cuts(const Long64_t& jentry)
{
 //return false to keep the event
 
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

 if(PTISR_cut && MET_cut && Nmu_cut && Nele_cut && Nlep_cut && Njet_cut && METtrigger_cut && METORtrigger_cut && METHTtrigger_cut)
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

