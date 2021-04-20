#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <Math/DistFunc.h>
#include <TMath.h>

#ifndef MET_TRIGGER_SF_H
#define MET_TRIGGER_SF_H

//class for all things MET triggers

class MET_Trigger_SF{
  private:
   std::string m_filename;
   std::map<std::string,std::vector<double>> m_map;
  public:
   MET_Trigger_SF();
   MET_Trigger_SF(std::string filename);
   ~MET_Trigger_SF();
   void Set_CSV(std::string filename);
   double Get_EFF(const double& MET=0., const double& HT=0., const int& year=2017, const bool& electron=false, const bool& muon=false, const bool& data=false, const int& updown=0);
   double Get_EFF(std::string name = "HT-Le600--SingleElectrontrigger-E1--Nele-E1_SingleElectron_2016_Electron", const double& MET=150., const int& updown=0);
   double Get_SF(const double& MET=0., const double& HT=0., const int& year=2017, const bool& electron=false, const bool& muon=false, const int& updown=0);
   void ParseCSV();
};

#endif

#define MET_Trigger_SF_cxx

inline MET_Trigger_SF::MET_Trigger_SF()
{
 m_filename = "Parameters.csv";
}

inline MET_Trigger_SF::MET_Trigger_SF(std::string filename)
{
 m_filename = filename;
}

inline MET_Trigger_SF::~MET_Trigger_SF(){}

inline void MET_Trigger_SF::Set_CSV(std::string filename)
{
 m_filename = filename;
}

std::string Get_Name(double HT, int year, bool electron, bool muon, bool data)
{
 std::string name = "";
 if(HT <= 600.) { name+="HT-Le600--"; } 
 else if(HT > 600. && HT < 750.) { name+="HT-G600--HT-L750--"; }
 else if(HT > 750.) { name+="HT-Ge750--"; }
 if(electron) { name+="SingleElectrontrigger-E1--Nele-E1_"; }
 else if(muon) { name+="SingleMuontrigger-E1--Nmu-E1_"; }
 else { name+="Nlep-E0_"; }
 if(data)
 {
  if(electron) { name+="SingleElectron_"+std::to_string(year)+"_Electron"; }
  else if(muon) { name+="SingleMuon_"+std::to_string(year)+"_Muon"; }
  else { std::cout << "Check Booleans!" << std::endl << "Trying to use data for 0 leptons!" << std::endl << "Using electrons for now..." << std::endl;
   name+="Bkg_"+std::to_string(year)+"_Electron"; }
 }
 else
 {
  name+="Bkg_"+std::to_string(year)+"_";
  if(electron) { name+="Electron"; }
  else if(muon) { name+="Muon"; }
  else { name+="ZeroLepton"; }
 }
 return name;
}

inline double MET_Trigger_SF::Get_EFF(std::string name, const double& MET, const int& updown)
{
 double EFF = 0.;
 if(m_map[name][9] == 0 && m_map[name][10] == 0)
 { 
  EFF = m_map[name][6]*ROOT::Math::normal_cdf(MET, m_map[name][8], m_map[name][7]); 
 }
 else
 {
  EFF = m_map[name][6]*(TMath::Cos(m_map[name][10])*TMath::Cos(m_map[name][10])*ROOT::Math::normal_cdf(MET, m_map[name][8], m_map[name][7])+TMath::Sin(m_map[name][10])*TMath::Sin(m_map[name][10])*ROOT::Math::normal_cdf(MET, m_map[name][8]*m_map[name][9], m_map[name][7]));
 }
 if(updown == 0) { return EFF; }
 else if(updown > 0) { return std::min(1., EFF*(m_map[name][4] + (MET < m_map[name][2] ? m_map[name][0]*(MET-m_map[name][2])*(MET-m_map[name][2]) : 0.))); }
 else if(updown < 0) { return std::min(1., EFF*(m_map[name][5] + (MET < m_map[name][3] ? m_map[name][1]*(MET-m_map[name][3])*(MET-m_map[name][3]) : 0.))); }

 return 1.;
}

inline double MET_Trigger_SF::Get_EFF(const double& MET, const double& HT, const int& year, const bool& electron, const bool& muon, const bool& data, const int& updown)
{
 std::string name = Get_Name(HT,year,electron,muon,data);
 return Get_EFF(name,MET,updown);
}

inline double MET_Trigger_SF::Get_SF(const double& MET, const double& HT, const int& year, const bool& electron, const bool& muon, const int& updown)
{
 std::string data_name, bkg_name;
 if(!electron && !muon)
 {
  data_name = Get_Name(HT,year,electron,muon,false); 
  bkg_name = Get_Name(HT,year,electron,muon,false);
 }
 else
 {
  data_name = Get_Name(HT,year,electron,muon,true); 
  bkg_name = Get_Name(HT,year,electron,muon,false);
 }
 double SF = Get_EFF(data_name,MET,updown)/Get_EFF(bkg_name,MET,updown);
 if(updown == 0) { return SF; }
 else if(updown > 0) { return std::min(1., SF*(m_map[data_name][4] + (MET < m_map[data_name][2] ? m_map[data_name][0]*(MET-m_map[data_name][2])*(MET-m_map[data_name][2]) : 0.))); }
 else if(updown < 0) { return std::min(1., SF*(m_map[data_name][5] + (MET < m_map[data_name][3] ? m_map[data_name][1]*(MET-m_map[data_name][3])*(MET-m_map[data_name][3]) : 0.))); }

 return 1.;
}

double Get_Value(std::string& line)
{
 size_t comma_pos = line.find(",");
 std::string value = line.substr(0,comma_pos);
 line.erase(0,comma_pos+1);
 return std::stod(value);
}

inline void MET_Trigger_SF::ParseCSV()
{
  std::ifstream ifile(m_filename);
  if(!ifile.is_open()){
    std::cout << "can't open csv file " << std::endl;
    return;
  }
  std::string line;
  //discard first line
  getline(ifile,line);
  while(getline(ifile,line)){
   size_t comma = line.find(",");
   std::string name = "";
   std::vector<double> values;
   name = line.substr(0,comma);
   line.erase(0,(name+",").length());
   while(line.length() > 0) { 
    values.push_back(Get_Value(line)); 
   }
   m_map.insert(std::make_pair(name,values));
  }
}
