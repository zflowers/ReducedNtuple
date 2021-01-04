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

void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, string outFile, string name, string option);
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cut, string name, string option);
TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);

void Plotter_Eff_Nano(vector<string> inFile, vector<string> cut){
 //string inFile ="output_quick.root";
 vector<string> tags_2016 = {"QCD_2016", "WJets_2016", "TTJets_2016", "ZJetsToNuNu_2016", "SingleElectron_2016", "SingleMuon_2016"};
 vector<string> tags_2017 = {"QCD_2017", "WJets_2017", "TTJets_2017", "ZJetsToNuNu_2017", "SingleElectron_2017", "SingleMuon_2017"};
 vector<string> tags_2018 = {"QCD_2018", "WJets_2018", "TTJets_2018", "ZJetsToNuNu_2018", "SingleElectron_2018", "SingleMuon_2018"};
 vector<string> tags_bkg_2016 = {"QCD_2016", "WJets_2016", "TTJets_2016", "ZJetsToNuNu_2016"};
 vector<string> tags_bkg_2017 = {"QCD_2017", "WJets_2017", "TTJets_2017", "ZJetsToNuNu_2017"};
 vector<string> tags_bkg_2018 = {"QCD_2018", "WJets_2018", "TTJets_2018", "ZJetsToNuNu_2018"};
 vector<string> tags_data_2016 = {"SingleElectron_2016", "SingleMuon_2016"};
 vector<string> tags_data_2017 = {"SingleElectron_2017", "SingleMuon_2017"};
 vector<string> tags_data_2018 = {"SingleElectron_2018", "SingleMuon_2018"};
 vector<string> tags_bkg_2016 = {"Bkg_2016","Bkg_2017","Bkg_2018"};
 vector<string> tags_MET_2016 = {"MET_2016","MET_2017","MET_2018"};
 vector<string> tags_SingleElectron_2016 = {"SingleElectron_2016"};
 vector<string> tags_SingleElectron_2017 = {"SingleElectron_2017"};
 vector<string> tags_SingleElectron_2018 = {"SingleElectron_2018"};
 vector<string> tags_SingleMuon_2016 = {"SingleMuon_2016"};
 vector<string> tags_SingleMuon_2017 = {"SingleMuon_2017"};
 vector<string> tags_SingleMuon_2018 = {"SingleMuon_2018"};
 vector<string> tags_TTJets_2016 = {"TTJets_2016"};
 vector<string> tags_ZJets_2016 = {"ZJetsToNuNu_2016"};
 vector<string> tags_WJets_2016 = {"WJets_2016"};
 vector<string> tags_QCD_2016 = {"WJets_2016"};
 vector<string> tags_TTJets_2017 = {"TTJets_2017"};
 vector<string> tags_ZJets_2017 = {"ZJetsToNuNu_2017"};
 vector<string> tags_WJets_2017 = {"WJets_2017"};
 vector<string> tags_QCD_2017 = {"WJets_2017"};
 vector<string> tags_TTJets_2018 = {"TTJets_2018"};
 vector<string> tags_ZJets_2018 = {"ZJetsToNuNu_2018"};
 vector<string> tags_WJets_2018 = {"WJets_2018"};
 vector<string> tags_QCD_2018 = {"WJets_2018"};
 vector<string> SingleMuon = {"SingleMuon_2016","SingleMuon_2017","SingleMuon_2018"};
 vector<string> SingleElectron = {"SingleElectron_2016","SingleElectron_2017","SingleElectron_2018"};
 vector<string> WJets_years = {"WJets_2016","WJets_2017","WJets_2018"};
 vector<string> TTJets_years = {"TTJets_2016","TTJets_2017","TTJets_2018"};
 vector<string> WWTo2L2Nu_years = {"WWTo2L2Nu_2016","WWTo2L2Nu_2017","WWTo2L2Nu_2018"};
 vector<string> ZJets_years = {"ZJetsToNuNu_2016","ZJetsToNuNu_2017","ZJetsToNuNu_2018"};

 vector<int> colors = {kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};

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
 
 for(int i = 0; i < inFile.size(); i++)
 {
  Get_Plot(tags_2016,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2016","Trigger");
  Get_Plot(tags_2017,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2017","Trigger");
  Get_Plot(tags_2018,METtrigger,colors,inFile[i],METtrigger[0]+"_"+cut[i]+"_2018","Trigger");

//  Get_Plot(SingleMuon,METtrigger,colors,inFile[i],METtrigger[0]+"SingleMuon"+cut[i]+"_","Trigger");
//  Get_Plot(SingleElectron,METtrigger,colors,inFile[i],METtrigger[0]+"SingleElectron"+"_"+cut[i],"Trigger");
//  Get_Plot(WJets_years,METtrigger,colors,inFile[i],METtrigger[0]+"WJets"+"_"+cut[i],"Trigger");
//  Get_Plot(TTJets_years,METtrigger,colors,inFile[i],METtrigger[0]+"TTJets"+"_"+cut[i],"Trigger");
//  Get_Plot(WWTo2L2Nu_years,METtrigger,colors,inFile[i],METtrigger[0]+"WWTo2L2Nu"+"_"+cut[i],"Trigger");
//  Get_Plot(ZJetsToNuNu_years,METtrigger,colors,inFile[i],METtrigger[0]+"ZJetsToNuNu"+"_"+cut[i],"Trigger");

 }
 
 Get_Plot(tags_TTJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_TTJets","FinalState");
 Get_Plot(tags_ZJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_ZJets","FinalState");
 Get_Plot(tags_WJets_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_WJets","FinalState");
 Get_Plot(tags_QCD_2016,METtrigger,colors,inFile,cut,"METtrigger_2016_QCD","FinalState");
 Get_Plot(tags_TTJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_TTJets","FinalState");
 Get_Plot(tags_ZJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_ZJets","FinalState");
 Get_Plot(tags_WJets_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_WJets","FinalState");
 Get_Plot(tags_QCD_2017,METtrigger,colors,inFile,cut,"METtrigger_2017_QCD","FinalState");
 Get_Plot(tags_TTJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_TTJets","FinalState");
 Get_Plot(tags_ZJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_ZJets","FinalState");
 Get_Plot(tags_WJets_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_WJets","FinalState");
 Get_Plot(tags_QCD_2018,METtrigger,colors,inFile,cut,"METtrigger_2018_QCD","FinalState");
 

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

 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.65,0.93,name.c_str());
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
 l.DrawLatex(0.62,0.93,name.c_str());
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
    Fitter_Eff_Nano(gr,colors,Triggers[j]+"_"+tags[i]+"_"+cut[k]);
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
    else if(option.compare("FinalState") == 0)
    {
     leg->AddEntry(gr,cut.at(k).c_str(),"PL");
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
  files.push_back("Eff_output_MET_"+cut+".root");
 }

 Plotter_Eff_Nano(files,cuts);
 return 0;
}
