#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <TTree.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TColor.h>
#include <TStyle.h>
#include <TEfficiency.h>
#include "Fitter_Eff_Nano.C"

using namespace std;

string states = "";
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, string outFile, string name, string option);
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cut, string name, string option);
TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
string RewriteCut(std::string cut);
string GetCut(string found_cut, string current_cut);
std::string get_str_between_two_str(const std::string &s, const std::string &start_delim, const std::string &stop_delim);
string get_cut_type(string& cut);

void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
 size_t pos = mainStr.find(toErase);
 if (pos != std::string::npos)
 {
  mainStr.erase(pos, toErase.length());
 }
}

void Plotter_Eff_Nano(vector<string> inFile, vector<string> cut){
 //string inFile ="output_quick.root";
 //vector<string> tags_2016 = {"QCD_2016", "WJets_2016", "TTJets_2016", "ZJetsToNuNu_2016", "SingleElectron_2016", "SingleMuon_2016"};
 //vector<string> tags_2017 = {"QCD_2017", "WJets_2017", "TTJets_2017", "ZJetsToNuNu_2017", "SingleElectron_2017", "SingleMuon_2017"};
 //vector<string> tags_2018 = {"QCD_2018", "WJets_2018", "TTJets_2018", "ZJetsToNuNu_2018", "SingleElectron_2018", "SingleMuon_2018"};
 //vector<string> tags_bkg_2016 = {"QCD_2016", "WJets_2016", "TTJets_2016", "ZJetsToNuNu_2016"};
 //vector<string> tags_bkg_2017 = {"QCD_2017", "WJets_2017", "TTJets_2017", "ZJetsToNuNu_2017"};
 //vector<string> tags_bkg_2018 = {"QCD_2018", "WJets_2018", "TTJets_2018", "ZJetsToNuNu_2018"};
 //vector<string> tags_data_2016 = {"SingleElectron_2016", "SingleMuon_2016"};
 //vector<string> tags_data_2017 = {"SingleElectron_2017", "SingleMuon_2017"};
 //vector<string> tags_data_2018 = {"SingleElectron_2018", "SingleMuon_2018"};
 //vector<string> tags_MET_2016 = {"MET_2016","MET_2017","MET_2018"};
 //vector<string> tags_SingleElectron_2016 = {"SingleElectron_2016"};
 //vector<string> tags_SingleElectron_2017 = {"SingleElectron_2017"};
 //vector<string> tags_SingleElectron_2018 = {"SingleElectron_2018"};
 //vector<string> tags_SingleMuon_2016 = {"SingleMuon_2016"};
 //vector<string> tags_SingleMuon_2017 = {"SingleMuon_2017"};
 //vector<string> tags_SingleMuon_2018 = {"SingleMuon_2018"};
 //vector<string> tags_TTJets_2016 = {"TTJets_2016"};
 //vector<string> tags_ZJets_2016 = {"ZJetsToNuNu_2016"};
 //vector<string> tags_WJets_2016 = {"WJets_2016"};
 //vector<string> tags_QCD_2016 = {"WJets_2016"};
 //vector<string> tags_TTJets_2017 = {"TTJets_2017"};
 //vector<string> tags_ZJets_2017 = {"ZJetsToNuNu_2017"};
 //vector<string> tags_WJets_2017 = {"WJets_2017"};
 //vector<string> tags_QCD_2017 = {"WJets_2017"};
 //vector<string> tags_TTJets_2018 = {"TTJets_2018"};
 //vector<string> tags_ZJets_2018 = {"ZJetsToNuNu_2018"};
 //vector<string> tags_WJets_2018 = {"WJets_2018"};
 //vector<string> tags_QCD_2018 = {"WJets_2018"};
 //vector<string> SingleMuon = {"SingleMuon_2016","SingleMuon_2017","SingleMuon_2018"};
 //vector<string> SingleElectron = {"SingleElectron_2016","SingleElectron_2017","SingleElectron_2018"};
 //vector<string> WJets_years = {"WJets_2016","WJets_2017","WJets_2018"};
 //vector<string> TTJets_years = {"TTJets_2016","TTJets_2017","TTJets_2018"};
 //vector<string> WWTo2L2Nu_years = {"WWTo2L2Nu_2016","WWTo2L2Nu_2017","WWTo2L2Nu_2018"};
 //vector<string> ZJets_years = {"ZJetsToNuNu_2016","ZJetsToNuNu_2017","ZJetsToNuNu_2018"};

 vector<int> colors = {kBlue+1, kRed+1, kGreen+1, kMagenta, kCyan, kOrange, kViolet+2, kAzure+7, kPink, kGreen, kGray};

 vector<string> METtrigger{ "METtrigger" };
 vector<string> METHTtrigger{ "METHTtrigger" };
 vector<string> METORtrigger{ "METORtrigger" };
 vector<string> METAlltrigger { "METtrigger", "METHTtrigger", "METORtrigger" };
 vector<string> SuperOR { "SuperOR" };

 //Get_Plot(tags_2017a,Triggers_100,colors,inFile,tags_2017a[0],"Tag");
 //Get_Plot(tags_2017b,Triggers_100,colors,inFile,tags_2017b[0],"Tag");
 //Get_Plot(tags_2017c,Triggers_100,colors,inFile,tags_2017c[0],"Tag");
 //Get_Plot(tags_2017d,Triggers_100,colors,inFile,tags_2017d[0],"Tag");
 //Get_Plot(tags_2017e,METtrigger,colors,inFile,tags_2017e[0],"Tag");
 //Get_Plot(tags_2017,Triggers_100,colors,inFile,"2017_HLT_PFMET100","Trigger");
 //Get_Plot(tags_2017,Triggers_100_TypeOne,colors,inFile,"2017_HLT_PFMET100_TypeOne","Trigger");
 //Get_Plot(tags_2017,Triggers_100_NoMu,colors,inFile,"2017_HLT_PFMET100_NoMu","Trigger");
 
 //Get_Plot(tags_2017,METtrigger,colors,inFile,"METtrigger_2017","Trigger");
 //Get_Plot(tags_2017,METHTtrigger,colors,inFile,"METHTtrigger_2017","Trigger");
 //Get_Plot(tags_2017,METORtrigger,colors,inFile,"METORtrigger_2017","Trigger");
 
// for(int i = 0; i < inFile.size(); i++)
// {
 // Get_Plot(tags_2016,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2016","Trigger");
 // Get_Plot(tags_2017,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2017","Trigger");
 // Get_Plot(tags_2018,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2018","Trigger");

//  Get_Plot(SingleMuon,METtrigger,colors,inFile[i],METtrigger[0]+"SingleMuon"+cut[i]+"_","Trigger");
//  Get_Plot(SingleElectron,METtrigger,colors,inFile[i],METtrigger[0]+"SingleElectron"+"_"+cut[i],"Trigger");
//  Get_Plot(WJets_years,METtrigger,colors,inFile[i],METtrigger[0]+"WJets"+"_"+cut[i],"Trigger");
//  Get_Plot(TTJets_years,METtrigger,colors,inFile[i],METtrigger[0]+"TTJets"+"_"+cut[i],"Trigger");
//  Get_Plot(WWTo2L2Nu_years,METtrigger,colors,inFile[i],METtrigger[0]+"WWTo2L2Nu"+"_"+cut[i],"Trigger");
//  Get_Plot(ZJetsToNuNu_years,METtrigger,colors,inFile[i],METtrigger[0]+"ZJetsToNuNu"+"_"+cut[i],"Trigger");

// }
 
 //Get_Plot(tags_TTJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_TTJets","FinalState");
 //Get_Plot(tags_ZJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_ZJets","FinalState");
 //Get_Plot(tags_WJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_WJets","FinalState");
 //Get_Plot(tags_QCD_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_QCD","FinalState");
 //Get_Plot(tags_TTJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_TTJets","FinalState");
 //Get_Plot(tags_ZJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_ZJets","FinalState");
 //Get_Plot(tags_WJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_WJets","FinalState");
 //Get_Plot(tags_QCD_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_QCD","FinalState");
 //Get_Plot(tags_TTJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_TTJets","FinalState");
 //Get_Plot(tags_ZJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_ZJets","FinalState");
 //Get_Plot(tags_WJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_WJets","FinalState");
 //Get_Plot(tags_QCD_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_QCD","FinalState");
 
 vector<string> tags_bkg_2016 = {"Bkg_2016"};
 vector<string> tags_SingleElectron_2016 = {"SingleElectron_2016"};
 vector<string> tags_SingleMuon_2016 = {"SingleMuon_2016"};
 vector<string> tags_bkg_2017 = {"Bkg_2017"};
 vector<string> tags_SingleElectron_2017 = {"SingleElectron_2017"};
 vector<string> tags_SingleMuon_2017 = {"SingleMuon_2017"};
 vector<string> tags_bkg_2018 = {"Bkg_2018"};
 vector<string> tags_SingleElectron_2018 = {"SingleElectron_2018"};
 vector<string> tags_SingleMuon_2018 = {"SingleMuon_2018"};
 vector<string> tags_bkg_years = {"Bkg_2016","Bkg_2017","Bkg_2018"};
 vector<string> tags_SingleElectron_years = {"SingleElectron_2016","SingleElectron_2017","SingleElectron_2018"};
 vector<string> tags_SingleMuon_years = {"SingleMuon_2016","SingleMuon_2017","SingleMuon_2018"};
 for(int i = 0; i < int(cut.size()); i++)
 {
  states += ("_"+cut[i]);
 } 

 //Get_Plot(tags_bkg_2016,METtrigger,colors,inFile,cut,"Bkg_2016","FinalState");
 //Get_Plot(tags_SingleElectron_2016,METtrigger,colors,inFile,cut,"SingleElectron_2016","FinalState");
 //Get_Plot(tags_SingleMuon_2016,METtrigger,colors,inFile,cut,"SingleMuon_2016","FinalState");
 Get_Plot(tags_bkg_2017,METtrigger,colors,inFile,cut,"Bkg_2017","FinalState");
 Get_Plot(tags_SingleElectron_2017,METtrigger,colors,inFile,cut,"SingleElectron_2017","FinalState");
 Get_Plot(tags_SingleMuon_2017,METtrigger,colors,inFile,cut,"SingleMuon_2017","FinalState");
 //Get_Plot(tags_bkg_2018,METtrigger,colors,inFile,cut,"Bkg_2018","FinalState");
 //Get_Plot(tags_SingleElectron_2018,METtrigger,colors,inFile,cut,"SingleElectron_2018","FinalState");
 //Get_Plot(tags_SingleMuon_2018,METtrigger,colors,inFile,cut,"SingleMuon_2018","FinalState");
 for(int i = 0; i < inFile.size(); i++)
 {
 // Get_Plot(tags_bkg_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
 // Get_Plot(tags_SingleElectron_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
 // Get_Plot(tags_SingleMuon_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
 }
}

//get all Eff on one plot
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, string outFile, string name, string option)
{
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }

 TLegend* leg = new TLegend(0.5,0.2,0.95,0.5); 
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 
 TLatex l;
 TCanvas* can = new TCanvas((name).c_str(),"",600.,500);
 can->SetLeftMargin(0.13);
 can->SetRightMargin(0.04);
 can->SetBottomMargin(0.15);
 can->SetTopMargin(0.085);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 TMultiGraph* mg = get_mg(outFile,tags,Triggers,colors,leg,can,option);
 can->Clear();

 mg->Draw("AP"); 
 mg->GetXaxis()->CenterTitle(true);
 mg->GetXaxis()->SetTitleFont(132);
 mg->GetXaxis()->SetTitleSize(0.06);
 mg->GetXaxis()->SetTitleOffset(1.06);
 mg->GetXaxis()->SetLabelFont(132);
 mg->GetXaxis()->SetLabelSize(0.05);
 mg->GetYaxis()->CenterTitle(true);
 mg->GetYaxis()->SetTitleFont(132);
 mg->GetYaxis()->SetTitleSize(0.06);
 mg->GetYaxis()->SetTitleOffset(1.);
 mg->GetYaxis()->SetLabelFont(132);
 mg->GetYaxis()->SetLabelSize(0.05);

 if(invert_colors)
 {
  mg->GetXaxis()->SetAxisColor(kWhite);
  mg->GetYaxis()->SetAxisColor(kWhite);
  mg->GetXaxis()->SetTitleColor(kWhite);
  mg->GetYaxis()->SetTitleColor(kWhite);
  mg->GetXaxis()->SetLabelColor(kWhite);
  mg->GetYaxis()->SetLabelColor(kWhite);
  can->SetFillColor(kBlack);
  leg->SetTextColor(kWhite);
  leg->SetFillColor(kBlack);
  leg->SetLineColor(kBlack);
  leg->SetShadowColor(kBlack); 
  l.SetTextColor(kWhite);
 }

 leg->Draw("SAME");

 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.4,0.93,RewriteCut(name).c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Preliminary 13 TeV");
 can->Modified();
 can->Update();

 TFile* output = TFile::Open("output_Plots.root","UPDATE");
 can->Write();
 output->Close();
 delete leg;
 delete mg;
 delete can;
 delete output;
}

TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option)
{
 TMultiGraph* mg = new TMultiGraph();
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return mg;
 }
 for(int i = 0; i < int(tags.size()); i++)
 {
  TDirectoryFile* folder = nullptr;
  f->GetObject(tags[i].c_str(),folder);
  folder->cd();
  for(int j = 0; j < int(Triggers.size()); j++)
  {
   TEfficiency* eff = nullptr;
   folder->GetObject(Triggers.at(j).c_str(),eff);
   eff->Draw("AP");
   can->Update();
   TGraphAsymmErrors* gr = eff->GetPaintedGraph();
   if((i+j) == 0)
   {
    string title = " ;";
    mg->SetTitle((title+gr->GetXaxis()->GetTitle()+";"+gr->GetYaxis()->GetTitle()).c_str());
   }
   if(option.compare("Tag") == 0)
   {
    leg->AddEntry(gr,Triggers.at(j).c_str(),"PL");
   }
   else if(option.compare("Trigger") == 0)
   {
    leg->AddEntry(gr,tags.at(i).c_str(),"PL");
   }
   gr->SetMarkerStyle(20);
   gr->SetMarkerColor(colors[i+j]);
   gr->SetLineColor(colors[i+j]);
   mg->Add(gr);
  }
 }
 f->Close();
 delete f;
 return mg;
}

//get all Eff on one plot
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cut, string name, string option)
{
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }

 TLegend* leg = new TLegend(0.3,0.2,0.95,0.5); 
 leg->SetTextFont(132);
 leg->SetTextSize(0.033);
 
 TLatex l;
 TCanvas* can = new TCanvas((name).c_str(),"",600.,500);
 can->SetLeftMargin(0.13);
 can->SetRightMargin(0.04);
 can->SetBottomMargin(0.15);
 can->SetTopMargin(0.085);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 TMultiGraph* mg = get_mg(cut,tags,Triggers,inFile,colors,leg,can,option);
 can->Clear();

 mg->Draw("AP"); 
 mg->GetXaxis()->CenterTitle(true);
 mg->GetXaxis()->SetTitleFont(132);
 mg->GetXaxis()->SetTitleSize(0.06);
 mg->GetXaxis()->SetTitleOffset(1.06);
 mg->GetXaxis()->SetLabelFont(132);
 mg->GetXaxis()->SetLabelSize(0.05);
 mg->GetYaxis()->CenterTitle(true);
 mg->GetYaxis()->SetTitleFont(132);
 mg->GetYaxis()->SetTitleSize(0.06);
 mg->GetYaxis()->SetTitleOffset(1.);
 mg->GetYaxis()->SetLabelFont(132);
 mg->GetYaxis()->SetLabelSize(0.05);

 if(invert_colors)
 {
  mg->GetXaxis()->SetAxisColor(kWhite);
  mg->GetYaxis()->SetAxisColor(kWhite);
  mg->GetXaxis()->SetTitleColor(kWhite);
  mg->GetYaxis()->SetTitleColor(kWhite);
  mg->GetXaxis()->SetLabelColor(kWhite);
  mg->GetYaxis()->SetLabelColor(kWhite);
  can->SetFillColor(kBlack);
  leg->SetTextColor(kWhite);
  leg->SetFillColor(kBlack);
  leg->SetLineColor(kBlack);
  leg->SetShadowColor(kBlack); 
  l.SetTextColor(kWhite);
 }

 leg->Draw("SAME");

 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 eraseSubStr(name,states);
 
 name+=": ";
 vector<string> known_cuts;
 known_cuts.push_back("HT");
 string current_cut = cut[0]+"--";
 vector<string> found_cuts;
 for(int i = 0; i < int(known_cuts.size()); i++)
 {
  int nPos = current_cut.find(known_cuts[i]+"-", 0); 
  while (nPos != string::npos)
  {
   nPos = current_cut.find(known_cuts[i]+"-", nPos+(known_cuts[i]+"-").size());
   found_cuts.push_back(known_cuts[i]);
  }
 }

 for(int i = 0; i < int(found_cuts.size()); i++)
 {
  name += GetCut(found_cuts[i]+"-"+get_str_between_two_str(current_cut,found_cuts[i]+"-","--")+"--",current_cut);
  eraseSubStr(current_cut,(found_cuts[i]+"-"+get_str_between_two_str(current_cut,found_cuts[i]+"-","--")+"--"));
 }
 if(name.back() == '&') name.pop_back();
 l.DrawLatex(0.41,0.93,name.c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Internal 13 TeV Simulation");
 can->Modified();
 can->Update();

 TFile* output = TFile::Open("output_Plots.root","UPDATE");
 can->Write();
 output->Close();
 delete leg;
 delete mg;
 delete can;
 delete output;
}

TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option)
{
 TMultiGraph* mg = new TMultiGraph();
 for(int k = 0; k < int(fname.size()); k++)
 {
  TKey *key;
  TFile *f = TFile::Open(fname[k].c_str(), "READ");
  if(!f || f->IsZombie())
  {
   cout << "Unable to open " << fname[k] << " for reading..." << endl;
   return mg;
  }
  for(int i = 0; i < int(tags.size()); i++)
  {
   TDirectoryFile* folder = nullptr;
   f->GetObject(tags[i].c_str(),folder);
   folder->cd();
   if(folder == nullptr) continue;
   for(int j = 0; j < int(Triggers.size()); j++)
   {
    TEfficiency* eff = nullptr;
    folder->GetObject(Triggers.at(j).c_str(),eff);
    eff->Draw("AP");
    can->Update();
    TGraphAsymmErrors* gr = eff->GetPaintedGraph();
    //call Fitter
    //Fitter_Eff_Nano(gr,colors,Triggers[j]+"_"+tags[i]+"_"+cut[k]);
    if((i+j) == 0)
    {
     string title = " ;";
     mg->SetTitle((title+gr->GetXaxis()->GetTitle()+";"+gr->GetYaxis()->GetTitle()).c_str());
    }
    string new_cut = RewriteCut(cut.at(k));
    //string new_cut = cut.at(k);
    if(option.compare("Tag") == 0)
    {
     leg->AddEntry(gr,Triggers.at(j).c_str(),"PL");
    }
    else if(option.compare("Trigger") == 0)
    {
     leg->AddEntry(gr,tags.at(i).c_str(),"PL");
     can->SetName((new_cut+"_"+tags.at(i)).c_str());
    }
    else if(option.compare("FinalState") == 0)
    {
     leg->AddEntry(gr,new_cut.c_str(),"PL");
    }
    gr->SetMarkerStyle(20);
    gr->SetMarkerColor(colors[i+j+k]);
    gr->SetLineColor(colors[i+j+k]);
    mg->Add(gr);
   }
  }
  f->Close();
  delete f;
 }
 return mg;
}

string GetCut(string found_cut, string current_cut)
{
 string cut = found_cut;

 if(found_cut.find("SingleElectrontrigger-E1") != std::string::npos)
 {
  cut =  " Passed Single Electron Trigger &";
 }
 if(found_cut.find("DoubleElectrontrigger-E1") != std::string::npos)
 {
  cut =  " Passed Double Electron Trigger &";
 }
 if(found_cut.find("SingleMuontrigger-E1") != std::string::npos)
 {
  cut =  " Passed Single Muon Trigger &";
 }
 if(found_cut.find("DoubleMuontrigger-E1") != std::string::npos)
 {
  cut =  " Passed Double Muon Trigger &";
 }
 if(found_cut.find("Nlep-E0") != std::string::npos)
 {
  cut =  " No Leptons &";
 }
 if(found_cut.find("Nele-E0") != std::string::npos)
 {
  cut =  " No Electrons &";
 }
 if(found_cut.find("Nmu-E0") != std::string::npos)
 {
  cut =  " No Muons &";
 }
 if(found_cut.find("Nmu-E1") != std::string::npos)
 {
  cut =  " One Muon &";
 }
 if(found_cut.find("Nmu-E2") != std::string::npos)
 {
  cut =  " Two Muons &";
 }
 if(found_cut.find("Nele-E1") != std::string::npos)
 {
  cut =  " One Electron &";
 }
 if(found_cut.find("Nele-E2") != std::string::npos)
 {
  cut =  " Two Electrons &";
 }
 if(found_cut.find("NmuBronze-E1") != std::string::npos)
 {
  cut =  " One Bronze Muon &";
 }
 if(found_cut.find("NmuBronze-E2") != std::string::npos)
 {
  cut =  " Two Bronze Muons &";
 }
 if(found_cut.find("NeleBronze-E1") != std::string::npos)
 {
  cut =  " One Bronze Electron &";
 }
 if(found_cut.find("NeleBronze-E2") != std::string::npos)
 {
  cut =  " Two Bronze Electrons &";
 }
 if(found_cut.find("NmuSilver-E1") != std::string::npos)
 {
  cut =  " One Silver Muon &";
 }
 if(found_cut.find("NmuSilver-E2") != std::string::npos)
 {
  cut =  " Two Silver Muons &";
 }
 if(found_cut.find("NeleSilver-E1") != std::string::npos)
 {
  cut =  " One Silver Electron &";
 }
 if(found_cut.find("NeleSilver-E2") != std::string::npos)
 {
  cut =  " Two Silver Electrons &";
 }
 if(found_cut.find("NmuGold-E1") != std::string::npos)
 {
  cut =  " One Gold Muon &";
 }
 if(found_cut.find("NmuGold-E2") != std::string::npos)
 {
  cut =  " Two Gold Muons &";
 }
 if(found_cut.find("NeleGold-E1") != std::string::npos)
 {
  cut =  " One Gold Electron &";
 }
 if(found_cut.find("NeleGold-E2") != std::string::npos)
 {
  cut =  " Two Gold Electrons &";
 }
 if(found_cut.find("Njet_S-E0") != std::string::npos)
 {
  cut =  " No S Jets &";
 }
 if(found_cut.find("Njet_S-E1") != std::string::npos)
 {
  cut =  " One S Jets &";
 }
 if(found_cut.find("Njet_S-Ge2") != std::string::npos)
 {
  cut =  " At Least 2 S Jets &";
 }
 if(found_cut.find("HT-") != std::string::npos)
 {
  string current_cut = get_str_between_two_str(found_cut,"HT-","--");
  string cut_type = get_cut_type(current_cut);
  string cut_value = current_cut;
  cut = " HT "+cut_type+" "+cut_value+" &";
 }
 if(found_cut.find("HTMedium-") != std::string::npos)
 {
  string current_cut = get_str_between_two_str(found_cut,"HTMedium-","--");
  string cut_type = get_cut_type(current_cut);
  string cut_value = current_cut;
  cut = " HTMedium "+cut_type+" "+cut_value+" &";
 }
 if(found_cut.find("HTLoose-") != std::string::npos)
 {
  string current_cut = get_str_between_two_str(found_cut,"HTLoose-","--");
  string cut_type = get_cut_type(current_cut);
  string cut_value = current_cut;
  cut = " HTLoose "+cut_type+" "+cut_value+" &";
 }
 if(found_cut.find("HTVeryLoose-") != std::string::npos)
 {
  string current_cut = get_str_between_two_str(found_cut,"HTVeryLoose-","--");
  string cut_type = get_cut_type(current_cut);
  string cut_value = current_cut;
  cut = " HTVeryLoose "+cut_type+" "+cut_value+" &";
 }
 return cut;
}

string RewriteCut(std::string cut)
{
 if(cut.find("PreSelection") != std::string::npos)
 {
  return "PreSelection";
 }

 vector<string> known_cuts;

 known_cuts.push_back("PTISR");
 //known_cuts.push_back("HTVeryLoose");
 //known_cuts.push_back("HTLoose");
 //known_cuts.push_back("HTMedium");
 //known_cuts.push_back("HT");
 known_cuts.push_back("PTCM");
 known_cuts.push_back("RISR");
 known_cuts.push_back("dphiCMI");
 known_cuts.push_back("MET");
 known_cuts.push_back("Nmu");
 known_cuts.push_back("Nele");
 known_cuts.push_back("Nlep");
 known_cuts.push_back("Njet_S");
 known_cuts.push_back("Nbjet_ISR");

 known_cuts.push_back("NmuBronze");
 known_cuts.push_back("NeleBronze");
 known_cuts.push_back("NlepBronze");

 known_cuts.push_back("NmuSilver");
 known_cuts.push_back("NeleSilver");
 known_cuts.push_back("NlepSilver");

 known_cuts.push_back("NmuGold");
 known_cuts.push_back("NeleGold");
 known_cuts.push_back("NlepGold");

 known_cuts.push_back("Njet");

 known_cuts.push_back("METtrigger");
 known_cuts.push_back("METORtrigger");
 known_cuts.push_back("METHTtrigger");

 known_cuts.push_back("SingleElectrontrigger");
 known_cuts.push_back("SingleMuontrigger");
 known_cuts.push_back("DoubleElectrontrigger");
 known_cuts.push_back("DoubleMuontrigger");

 known_cuts.push_back("EventFilter");

 known_cuts.push_back("EventFlag_FailJetID");
 known_cuts.push_back("EventFlag_JetInHEM");
 known_cuts.push_back("EventFlag_JetInHEM_Pt20");
 known_cuts.push_back("EventFlag_JetInHEM_Pt20_JetID");
 known_cuts.push_back("HEM_Veto");

 string current_cut = cut+"--";

 vector<string> found_cuts;
 for(int i = 0; i < int(known_cuts.size()); i++)
 {
  int nPos = cut.find(known_cuts[i]+"-", 0); 
  while (nPos != string::npos)
  {
   nPos = cut.find(known_cuts[i]+"-", nPos+(known_cuts[i]+"-").size());
   found_cuts.push_back(known_cuts[i]);
  }
 }

 string new_cut = "";
 for(int i = 0; i < int(found_cuts.size()); i++)
 {
  new_cut += GetCut(found_cuts[i]+"-"+get_str_between_two_str(current_cut,found_cuts[i]+"-","--")+"--",current_cut);
 }

 if(new_cut.back() == '&') new_cut.pop_back();

 return new_cut;
}

std::string get_str_between_two_str(const std::string &s, const std::string &start_delim, const std::string &stop_delim)
{
 unsigned first_delim_pos = s.find(start_delim);
 unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
 unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
 return s.substr(end_pos_of_first_delim,last_delim_pos - end_pos_of_first_delim);
}

string get_cut_type(string& cut)
{
 string type = "";
 if(cut.find("E") != std::string::npos) { cut.erase(0,1); type = "=="; }
 else if(cut.find("Ge") != std::string::npos) { cut.erase(0,1); cut.erase(0,1); type = ">="; }
 else if(cut.find("G") != std::string::npos) { cut.erase(0,1); type = ">"; }
 else if(cut.find("Le") != std::string::npos) { cut.erase(0,1); cut.erase(0,1); type = "<="; }
 else if(cut.find("L") != std::string::npos) { cut.erase(0,1); type = "<"; }
 return type;
}

int main(int argc, char* argv[])
{
 string cutsFile = "cuts.txt";
 vector<string> cuts;
 vector<string> files;

 if(argc < 1)
 {
  cout << "ERROR: Need to specify cuts file" << endl;
  cout << "Example: ./Plotter.x -cuts=cuts.txt" << endl;
  return 1;
 }

 for(int i = 0; i < argc; i++)
 {
  if(strncmp(argv[i],"-cuts",5)==0)
  {
   cutsFile=argv[i];
   cutsFile.erase(0,6);
  }
 }
 
 string cut = "";
 std::ifstream fs(cutsFile);
 while(std::getline(fs,cut))
 {
  if(cut.rfind("#", 0) == 0) continue;
  cuts.push_back(cut);
  files.push_back("Eff_output_"+cut+".root");
 }

 Plotter_Eff_Nano(files,cuts);
 return 0;
}
