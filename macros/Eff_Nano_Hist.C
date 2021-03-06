#include <TSystem.h>
#include <TChain.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MET_2016_Triggers.h"
#include "MET_2017_Triggers.h"
#include "MET_2018_Triggers.h"
#include "Hist_Maker.h"
#include "Eff_Nano.h"

using namespace std;

string tag = "";
string filename = "";
string dir = "";
string number = "";
string cut = "";
string tree = "KUAnalysis";
string input = "";
string output = "";
char inputListName[400];
bool Do_Input = false;
bool Do_Hist = false;
bool Do_Eff = false;
bool Do_SMS = false;
bool Do_List = false;
bool local = false;
int ICHUNK = 1;
int NCHUNK = 1;

std::string get_str_between_two_str_unique(const std::string &s, const std::string &start_delim, const std::string &stop_delim)
{
 unsigned first_delim_pos = s.find_first_of(start_delim);
 unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
 unsigned last_delim_pos = s.find(stop_delim, end_pos_of_first_delim);
    
 return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}

void Maker(){

 //string path = "/mnt/hadoop/user/uscms01/pnfs/unl.edu/data4/cms/store/user/zflowers/ReducedNtuple/output/";
 //string path = "~/../crogan/NTUPLES/NANO/NEW_31_05_20/";
 //string path = "~/../crogan/NTUPLES/NANO/NEW_21_09_20/";
 //string path = "~/Eff_NANO/ReducedNtuple/";
 //string path = "root://stash.osgconnect.net:1094//user/zflowers/NTUPLES/Processing/";
 string path = "root://xrootd.unl.edu//store/user/zflowers/";
 //string path = "root://xrootd.unl.edu//store/user/zflowers/FromChris/";

 if(tag == "") { cout << "Need to specify tag!" << endl; return; }
 TChain* chain;
 string dir_rm = dir;
 if(dir.find("SMS") != std::string::npos || filename.find("SMS") != std::string::npos)
 {
  chain = new TChain(("SMS_"+get_str_between_two_str_unique(tag,"_","_201")).c_str());
  eraseSubStr(dir_rm, "_SMS");
 }
 else
 {
  chain = new TChain(tree.c_str());
 }
 if(dir.find("Data") != std::string::npos)
 {
  eraseSubStr(dir_rm, "_Data");
 }
 if(dir.find("SMS") != std::string::npos)
 {
  input = path+dir+"/"+filename+".root";
 }
 else if(!Do_Input)
 {
  //input = path+dir+"/NoHadd/"+filename+"/"+filename+number+".root";
  input = path+dir+"/"+filename+"/"+filename+number+".root";
 }
 if(local)
 {
  input = dir+"/"+filename;
 }
 if(Do_List)
 {
  char Buffer[500];
  char MyRootFile[2000];
  vector<string> filenames;
  ifstream *inputFile = new ifstream(inputListName);
  while( !(inputFile->eof()) ){
   inputFile->getline(Buffer,500);
   if (!strstr(Buffer,"#") && !(strspn(Buffer," ") == strlen(Buffer))){
     sscanf(Buffer,"%s",MyRootFile);
     filenames.push_back(MyRootFile);
   }
  }
  inputFile->close();
  delete inputFile; 
  for(int i = 0; i < int(filenames.size()); i++){
    cout << filenames[i] << endl;
    chain->Add(filenames[i].c_str(),0);
  }
 }
 else
 {
  chain->Add(input.c_str(),0);
 }
 if(output.length() == 0)
 {
  output = cut+"_"+dir+"_"+tag+"_"+filename+number+".root";
 }
 if(local)
 {
  if(Do_Eff) { output = "Eff_output_"+cut+".root"; }
  else if(Do_Hist) { output = "Hist_output_"+cut+".root"; }
  else { cout << "Specify --eff or --hist in options!" << endl; }
 }
 cout << "Output file: " << output << endl;

 if(Do_Hist)
 {
  Hist_Maker Hist(output,tag,chain,ICHUNK,NCHUNK);
  Hist.Set_Cut(cut);
  Hist.Analyze();
 }
 else if(Do_Eff)
 {
  std::vector<string> Triggers;
  string x = "MET";
  if(tag.find("2016") != std::string::npos) { Triggers = Get_2016_Triggers(); }
  if(tag.find("2017") != std::string::npos) { Triggers = Get_2017_Triggers(); }
  if(tag.find("2018") != std::string::npos) { Triggers = Get_2018_Triggers(); }
  Eff_Nano Eff(output,Triggers,tag,x,chain,ICHUNK,NCHUNK);
  Eff.Set_Cut(cut);
  Eff.Analyze();
 }
 else
 {
  cout << "Need to specify what to analyze with!" << endl;
 }
 
 delete chain;

}

int main(int argc, char* argv[])
{
 if(argc < 1)
 {
  cout << "ERROR: Need to specify cut" << endl;
  cout << "Example: ./run_Hist_Maker_Hist -cut=PreSelection" << endl;
  return 1;
 }

 for(int i = 0; i < argc; i++)
 {
  if(strncmp(argv[i],"-cut",4)==0)
  {
   cut=argv[i];
   cut.erase(0,5);
  }
  else if(strncmp(argv[i],"-tag",4)==0)
  {
   tag=argv[i];
   tag.erase(0,5);
  }
  else if(strncmp(argv[i],"-filename",9)==0)
  {
   filename=argv[i];
   filename.erase(0,10);
  }
  else if(strncmp(argv[i],"-dir",4)==0)
  {
   dir=argv[i];
   dir.erase(0,5);
  }
  else if(strncmp(argv[i],"-num",4)==0)
  {
   number = argv[i];
   number.erase(0,5);
  }
  else if(strncmp(argv[i],"--hist",6)==0)
  {
   Do_Hist = true;
  }
  else if(strncmp(argv[i],"--eff",5)==0)
  {
   Do_Eff = true;
  }
  else if(strncmp(argv[i],"--sms",5)==0)
  {
   Do_SMS = true;
  }
  else if(strncmp(argv[i],"-tree",5)==0)
  {
   tree = argv[i];
   tree.erase(0,6);
  }
  else if(strncmp(argv[i],"-input",6)==0)
  {
   Do_Input = true;
   input = argv[i];
   input.erase(0,7);
  }
  else if(strncmp(argv[i],"-output",7)==0)
  {
   output = argv[i];
   output.erase(0,8);
  }
  else if(strncmp(argv[i],"-ilist",6)==0)
  {
   Do_List = true;
   sscanf(argv[i],"-ilist=%s",  inputListName);
  }
  else if(strncmp(argv[i],"-split",6)==0)
  {
   sscanf(argv[i],"-split=%d,%d", &ICHUNK, &NCHUNK);
  }
  else if(strncmp(argv[i],"--local",7)==0)
  {
   local = true;
  }
 }

 Maker();
 return 0;
}
