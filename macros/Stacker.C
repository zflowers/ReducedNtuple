#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TColor.h>
#include <TColorWheel.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>

using namespace std;

double evaluateZbi(double Nsig, double Nbkg, double sys)
{
    double Nobs = Nsig+Nbkg;
    double tau = 1./Nbkg/(sys*sys/10000.);
    double aux = Nbkg*tau;
    double Pvalue = TMath::BetaIncomplete(1./(1.+tau),Nobs,aux+1.);
    return sqrt(2.)*TMath::ErfcInverse(Pvalue*2.);
}

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

vector<TH1D*> list_histos(string fname, vector<string> dir_names, string hist_name)
{
 std::vector<TH1D*> vect_hist;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
     cout << "Unable to open " << fname << " for reading..." << endl;
     return vect_hist;
 }
 for(int i = 0; i < int(dir_names.size()); i++)
 {
  TDirectoryFile* folder = nullptr;
  f->GetObject(dir_names[i].c_str(),folder);
  if(folder == NULL) continue;
  folder->cd();
  TH1D* h = nullptr;
  folder->GetObject(hist_name.c_str(),h);
  vect_hist.push_back(h);
 }
 return vect_hist;
}

vector<TH1D*> list_histos(vector<string> fname, vector<string> dir_names, string hist_name)
{
 std::vector<TH1D*> vect_hist;
 TKey *key;
 for(int j = 0; j < int(fname.size()); j++)
 {
  TFile *f = TFile::Open(fname[j].c_str(), "READ");
  if(!f || f->IsZombie())
  {
      cout << "Unable to open " << fname[j] << " for reading..." << endl;
      return vect_hist;
  }
  for(int i = 0; i < int(dir_names.size()); i++)
  {
   TDirectoryFile* folder = nullptr;
   f->GetObject(dir_names[i].c_str(),folder);
   if(folder == NULL) continue;
   folder->cd();
   TH1D* h = nullptr;
   folder->GetObject(hist_name.c_str(),h);
   vect_hist.push_back(h);
  }
 }
 return vect_hist;
}

vector<TH2D*> list_histos2D(string fname, vector<string> dir_names, string hist_name)
{
 std::vector<TH2D*> vect_hist;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
     cout << "Unable to open " << fname << " for reading..." << endl;
     return vect_hist;
 }
 for(int i = 0; i < int(dir_names.size()); i++)
 {
  TDirectoryFile* folder = nullptr;
  f->GetObject(dir_names[i].c_str(),folder);
  if(folder == NULL) continue;
  folder->cd();
  TH2D* h = nullptr;
  folder->GetObject(hist_name.c_str(),h);
  vect_hist.push_back(h);
 }
 return vect_hist;
}

vector<TH2D*> list_histos2D(vector<string> fname, vector<string> dir_names, string hist_name)
{
 std::vector<TH2D*> vect_hist;
 TKey *key;
 for(int j = 0; j < int(fname.size()); j++)
 {
  TFile *f = TFile::Open(fname[j].c_str(), "READ");
  if(!f || f->IsZombie())
  {
      cout << "Unable to open " << fname[j] << " for reading..." << endl;
      return vect_hist;
  }
  for(int i = 0; i < int(dir_names.size()); i++)
  {
   TDirectoryFile* folder = nullptr;
   f->GetObject(dir_names[i].c_str(),folder);
   if(folder == NULL) continue;
   folder->cd();
   TH2D* h = nullptr;
   folder->GetObject(hist_name.c_str(),h);
   vect_hist.push_back(h);
  }
 }
 return vect_hist;
}

void Get_Stack(string hists_name, vector<string> labels_bkg, vector<string> labels_sig, vector<int> colors_bkg, vector<int> colors_sig, string outFile, string cut)
{
  vector<TH1D*> hists_bkg = list_histos(outFile, labels_bkg, hists_name);
  vector<TH1D*> hists_sig = list_histos(outFile, labels_sig, hists_name);
  TH1D* bkg_hist = (TH1D*)hists_bkg[0]->Clone("TOT_BKG");
  for(int i = 1; i < int(hists_bkg.size()); i++)
  {
   for(int k = 0; k < i; k++)
   {
    hists_bkg[k]->Add(hists_bkg[i]);
   }
   bkg_hist->Add(hists_bkg[i]);
  }
  double fmax = -1.;
  int imax = -1;
  for(int i = 0; i < int(hists_bkg.size()); i++){
    if(hists_bkg[i]->GetMaximum() > fmax){
      fmax = hists_bkg[i]->GetMaximum();
      imax = i;
    }
  }
  string Yname = "Events / bin";
  string Xname = hists_bkg[0]->GetXaxis()->GetTitle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11111111);

  string name = "can_";
  name+=hists_bkg[0]->GetName();
  TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
  can->SetLeftMargin(0.13);
  can->SetRightMargin(0.04);
  can->SetBottomMargin(0.15);
  can->SetTopMargin(0.085);
  can->SetGridx();
  can->SetGridy();
  can->Draw();
  can->cd();
  hists_bkg[imax]->Draw("hist");
  hists_bkg[imax]->GetXaxis()->CenterTitle();
  hists_bkg[imax]->GetXaxis()->SetTitleFont(132);
  hists_bkg[imax]->GetXaxis()->SetTitleSize(0.06);
  hists_bkg[imax]->GetXaxis()->SetTitleOffset(1.06);
  hists_bkg[imax]->GetXaxis()->SetLabelFont(132);
  hists_bkg[imax]->GetXaxis()->SetLabelSize(0.05);
  hists_bkg[imax]->GetXaxis()->SetTitle(Xname.c_str());
  hists_bkg[imax]->GetYaxis()->CenterTitle();
  hists_bkg[imax]->GetYaxis()->SetTitleFont(132);
  hists_bkg[imax]->GetYaxis()->SetTitleSize(0.06);
  hists_bkg[imax]->GetYaxis()->SetTitleOffset(1.);
  hists_bkg[imax]->GetYaxis()->SetLabelFont(132);
  hists_bkg[imax]->GetYaxis()->SetLabelSize(0.05);
  hists_bkg[imax]->GetYaxis()->SetTitle("a. u.");
  hists_bkg[imax]->GetYaxis()->SetTitle(Yname.c_str());
  
  for(int i = 0; i < int(hists_bkg.size()); i++)
  {
   hists_bkg[i]->SetFillColor(colors_bkg[i]);
   hists_bkg[i]->SetFillStyle(1001);
   hists_bkg[i]->SetLineColor(colors_bkg[i]);
   hists_bkg[i]->SetLineWidth(1);
   hists_bkg[i]->SetMarkerColor(colors_bkg[i]);
   hists_bkg[i]->SetMarkerSize(0);
   hists_bkg[i]->Draw("SAME HIST");
  }
  bkg_hist->SetLineWidth(3.0);
  bkg_hist->SetLineColor(kRed);
  bkg_hist->SetMarkerSize(0);
  bkg_hist->Draw("SAME HIST");
  gPad->RedrawAxis();
  gPad->RedrawAxis("G");
  
  for(int i = 0; i < int(hists_sig.size()); i++)
  {
    hists_sig[i]->SetLineWidth(3.0);
    hists_sig[i]->SetMarkerSize(0.);
    hists_sig[i]->SetMarkerColor(kBlack);
    hists_sig[i]->SetLineStyle(7);
    hists_sig[i]->SetLineColor(colors_sig[i]);
    hists_sig[i]->Draw("SAME HIST");
  }
  TLegend* leg = new TLegend(0.588,0.546,0.945,0.904);
  leg->SetTextFont(132);
  leg->SetTextSize(0.045);
  leg->SetFillColor(kWhite);
  leg->SetLineColor(kWhite);
  leg->SetShadowColor(kWhite);
  leg->AddEntry(bkg_hist, "SM total");
  for(int i = 0; i < int(hists_bkg.size()); i++)
  {
   leg->AddEntry(hists_bkg[i],labels_bkg[i].c_str(),"F");
  }
  for(int i = 0; i < int(hists_sig.size()); i++)
  { 
   leg->AddEntry(hists_sig[i],labels_sig[i].c_str());
  }
  leg->SetLineColor(kWhite);
  leg->SetFillColor(kWhite);
  leg->SetShadowColor(kWhite);
  leg->Draw("SAME");

  TLatex l;
  l.SetNDC();
  l.SetTextSize(0.05);
  l.SetTextFont(42);
  l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
  l.SetTextSize(0.05);
  l.SetTextFont(42);
  //string s_lumi = "#scale[0.6]{#int} #it{L dt} = "+to_string(int(137.0))+" fb^{-1}";
  //l.DrawLatex(0.72,0.94,s_lumi.c_str());
  l.DrawLatex(0.72,0.94,cut.c_str());
  
  TFile* output = new TFile(outFile.c_str(),"UPDATE");
  can->Write();
  output->Close();
  delete leg;
  delete can;
  delete output;  
}

void Get2D_Plot(string hist_name, vector<string> directories, string outFile){
 vector<TH2D*> hist = list_histos2D(outFile, directories, hist_name);
 TFile* output = new TFile(outFile.c_str(),"UPDATE");
 for(int i = 0; i < int(hist.size()); i++)
 {
  string name = "can_";
  name+=directories[i];
  name+=hist[i]->GetName();
  TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
  can->SetLeftMargin(0.15);
  can->SetRightMargin(0.18);
  can->SetBottomMargin(0.15);
  can->SetGridx();
  can->SetGridy();
  can->SetLogz();
  can->Draw();
  can->cd();
  hist[i]->Draw("COLZ");
  TLatex l;
  l.SetNDC();
  l.SetTextSize(0.05);
  l.SetTextFont(42);
  l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
  l.SetTextSize(0.05);
  l.SetTextFont(42);
  string s_lumi = "#scale[0.6]{#int} #it{L dt} = "+to_string(int(137.0))+" fb^{-1}";
  l.DrawLatex(0.72,0.94,s_lumi.c_str());	
  gPad->RedrawAxis();
  gPad->RedrawAxis("G");
  can->Write();
  delete can;
 }
 output->Close();
 delete output;
}

void Get2D_Plot(string hist_name, vector<string> directories, vector<string> inFiles, vector<string> cuts, bool trigger){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetFrameFillColor(kBlack);
 gStyle->SetFrameLineColor(kWhite);
 vector<TH2D*> hist = list_histos2D(inFiles, directories, hist_name);
 TFile* output = new TFile(inFiles[0].c_str(),"UPDATE");
 for(int i = 0; i < int(cuts.size()); i++)
 {
  for(int j = 0; j < int(directories.size()); j++)
  {
   string name = "can_";
   name+=hist[i+j]->GetName();
   name+=directories[j];
   name+=cuts[i];
   string trigger_name = "";
   if(trigger)
   {
    string cut = cuts[i]+"_";
    if(cuts[i].find("METtriggerE0") != std::string::npos)
    {
     trigger_name="METtrigger Failed";
    }
    else if(cuts[i].find("METtriggerE1") != std::string::npos)
    {
     trigger_name="METtrigger Passed";
    }
    else if(cuts[i].find("METHTtriggerE0") != std::string::npos)
    {
     trigger_name="METHTtrigger Failed";
    }
    else if(cuts[i].find("METHTtriggerE1") != std::string::npos)
    {
     trigger_name="METHTtrigger Passed";
    }
    else if(cuts[i].find("METORtriggerE0") != std::string::npos)
    {
     trigger_name="METORtrigger Failed";
    }
    else if(cuts[i].find("METORtriggerE1") != std::string::npos)
    {
     trigger_name="METORtrigger Passed";
    }
    else if(cuts[i].find("SuperOR") != std::string::npos)
    {
     string trigger_cut = get_str_between_two_str(cut,"SuperOR","_");
     trigger_name=("SuperOR"+trigger_cut);
    }
    else
    {
     cout << "Could not find matching trigger: " << cut << endl;
    }
   }
   name+=trigger_name;
   TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
   can->SetLeftMargin(0.15);
   can->SetRightMargin(0.18);
   can->SetBottomMargin(0.15);
   can->SetGridx();
   can->SetGridy();
   can->SetLogz();
   can->SetFillColor(kBlack);
   can->Draw();
   can->cd();
   hist[i+j]->GetXaxis()->SetAxisColor(kWhite);
   hist[i+j]->GetYaxis()->SetAxisColor(kWhite);
   hist[i+j]->GetXaxis()->SetTitleColor(kWhite);
   hist[i+j]->GetYaxis()->SetTitleColor(kWhite);
   hist[i+j]->GetXaxis()->SetLabelColor(kWhite);
   hist[i+j]->GetYaxis()->SetLabelColor(kWhite);
   hist[i+j]->GetXaxis()->CenterTitle();
   hist[i+j]->GetXaxis()->SetTitleFont(132);
   hist[i+j]->GetXaxis()->SetTitleSize(0.06);
   hist[i+j]->GetXaxis()->SetTitleOffset(1.06);
   hist[i+j]->GetXaxis()->SetLabelFont(132);
   hist[i+j]->GetXaxis()->SetLabelSize(0.05);
   hist[i+j]->GetYaxis()->CenterTitle();
   hist[i+j]->GetYaxis()->SetTitleFont(132);
   hist[i+j]->GetYaxis()->SetTitleSize(0.06);
   hist[i+j]->GetYaxis()->SetTitleOffset(1.);
   hist[i+j]->GetYaxis()->SetLabelFont(132);
   hist[i+j]->GetYaxis()->SetLabelSize(0.05);
   hist[i+j]->Draw("COLZ");
   TLatex l;
   l.SetNDC();
   l.SetTextColor(kWhite);
   l.SetTextSize(0.05);
   l.SetTextFont(42);
   l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
   l.SetTextSize(0.05);
   l.SetTextFont(42);
   name = directories[j];
   name+=cuts[i];
   name+=trigger_name;
   l.DrawLatex(0.65,.94,name.c_str());
   gPad->RedrawAxis();
   gPad->RedrawAxis("G");
   can->Write();
   delete can;
  }
 }
 output->Close();
 delete output;
}

void Get_Overlay(vector<string> outFiles, string hist_name, vector<string> samples, vector<string> cuts, vector<int> colors, string option, bool trigger)
{
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetFrameFillColor(kBlack);
 gStyle->SetFrameLineColor(kWhite);
 vector<TH1D*> hists = list_histos(outFiles,samples,hist_name);
 TCanvas* can = new TCanvas(("can_"+hist_name+samples[0]+cuts[0]).c_str(),"",864.,468.);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 can->SetFillColor(kBlack);
 can->Draw();
 can->cd();
 for(int i = 0; i < hists.size(); i++)
 {
  hists[i]->Scale(1./hists[i]->GetEntries());
  string x_title = hists[i]->GetXaxis()->GetTitle();
  string y_title = "#frac{1}{N} #frac{dN}{d("+x_title+")}";
  hists[i]->GetYaxis()->SetTitle(y_title.c_str());
  hists[i]->Draw("HIST SAMES");
  hists[i]->SetLineWidth(2);
  hists[i]->GetXaxis()->SetAxisColor(kWhite);
  hists[i]->GetYaxis()->SetAxisColor(kWhite);
  hists[i]->GetXaxis()->SetTitleColor(kWhite);
  hists[i]->GetYaxis()->SetTitleColor(kWhite);
  hists[i]->GetXaxis()->SetLabelColor(kWhite);
  hists[i]->GetYaxis()->SetLabelColor(kWhite);
  hists[i]->SetLineColor(colors[i]);
  hists[i]->GetXaxis()->CenterTitle();
  hists[i]->GetXaxis()->SetTitleFont(132);
  hists[i]->GetXaxis()->SetTitleSize(0.06);
  hists[i]->GetXaxis()->SetTitleOffset(1.06);
  hists[i]->GetXaxis()->SetLabelFont(132);
  hists[i]->GetXaxis()->SetLabelSize(0.05);
  //hists[i]->GetXaxis()->SetTitle(Xname.c_str());
  hists[i]->GetYaxis()->CenterTitle();
  hists[i]->GetYaxis()->SetTitleFont(132);
  hists[i]->GetYaxis()->SetTitleSize(0.06);
  hists[i]->GetYaxis()->SetTitleOffset(1.);
  hists[i]->GetYaxis()->SetLabelFont(132);
  hists[i]->GetYaxis()->SetLabelSize(0.05);
  //hists[i]->GetYaxis()->SetTitle("a. u.");
  //hists[i]->GetYaxis()->SetTitle(Yname.c_str());
 }
 TLatex l;
 l.SetTextColor(kWhite);
 l.SetNDC();
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
 l.SetTextSize(0.05);
 l.SetTextFont(42);

 TLegend* leg = new TLegend(0.6,0.7,0.85,0.9);
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 leg->SetTextColor(kWhite);
 leg->SetFillColor(kBlack);
 leg->SetLineColor(kBlack);
 leg->SetShadowColor(kBlack);
 if(option.compare("Cuts") == 0)
 {
  for(int i = 0; i < int(cuts.size()); i++)
  {
   if(trigger)
   {
    string cut = cuts[i]+"_";
    if(cuts[i].find("METtriggerE0") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METtrigger Failed","L");
    }
    else if(cuts[i].find("METtriggerE1") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METtrigger Passed","L");
    }
    else if(cuts[i].find("METHTtriggerE0") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METHTtrigger Failed","L");
    }
    else if(cuts[i].find("METHTtriggerE1") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METHTtrigger Passed","L");
    }
    else if(cuts[i].find("METORtriggerE0") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METORtrigger Failed","L");
    }
    else if(cuts[i].find("METORtriggerE1") != std::string::npos)
    {
     leg->AddEntry(hists[i],"METORtrigger Passed","L");
    }
    else if(cuts[i].find("SuperOR") != std::string::npos)
    {
     string trigger_cut = get_str_between_two_str(cut,"SuperOR","_");
     leg->AddEntry(hists[i],("SuperOR"+trigger_cut).c_str(),"L");
    }
    else
    {
     cout << "Could not find matching trigger" << endl;
    }
   }
   else
   {
    leg->AddEntry(hists[i],cuts[i].c_str(),"L");
   }
  }
  l.DrawLatex(.65,.94,(samples[0]).c_str());
 }
 else if(option.compare("Samples") == 0)
 {
  for(int i = 0; i < int(samples.size()); i++)
  {
   leg->AddEntry(hists[i],samples[i].c_str(),"L");
  }
  l.DrawLatex(.65,.94,cuts[0].c_str());
 }
 else cout << "Couldn't find option: " << option << endl;
 leg->Draw("SAMES");

 cout << "Saving Plots to: " << outFiles[0] << endl;
 TFile* output = new TFile(outFiles[0].c_str(),"UPDATE");
 can->Update();
 can->Write();
 output->Close();
 delete can;
 delete leg;
 delete output;

 //string s_lumi = "#scale[0.6]{#int} #it{L dt} = "+to_string(int(137.0))+" fb^{-1}";
 //l.DrawLatex(0.72,0.94,s_lumi.c_str());
}

void Stacker(vector<string> inFiles, vector<string> cuts){
 cout << "Running Stacker..." << endl;
 vector<string> WJets_directories{"WJets_2017"};
 vector<string> WJets_Old_directories{"WJets_2017_Old"};
 vector<string> TTJets_directories{"TTJets_2017"};
 vector<string> sig_directories{""};
 //vector<string> sig_directories{"TChiWW_SMS_275_235"};
 //vector<string> directories_2D{"TChiWW_SMS_275_235", "TTJets", "WJets", "DiBoson", "DYJetsToLL", "ST"};
 vector<string> directories_2D{"TTJets_2017", "WJets_2017", "WJets_2017_Old"};
 vector<int> colors = {kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};
 vector<int> colors_bkg = { kAzure+1, kGreen-9, kPink, kTeal+2, kYellow-4 };
 vector<int> colors_sig = { kMagenta, kCyan+2, };

// Get_Stack("met_Hist",bkg_directories,sig_directories,colors_bkg,colors_sig,inFile,cut);
// Get_Stack("dphiMET_lep_Hist",bkg_directories,sig_directories,colors_bkg,colors_sig,inFile,cut);

//compare across: sample, selection/final state, hist?, ..., 
 Get_Overlay(inFiles,"met_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"met_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"met_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"met_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"met_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"met_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"PTCM_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"PTCM_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"PTCM_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_lep_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_lep_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_ele_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_ele_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_mu_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_mu_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"jet_PT_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"jet_PT_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"jet_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"jet_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_proj_MET_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_proj_MET_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_proj_METperp_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"ele_PT_proj_METperp_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_proj_MET_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_proj_MET_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_proj_METperp_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"mu_PT_proj_METperp_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"dphiCMI_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"dphiCMI_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"dphiCMI_Hist",TTJets_directories,cuts,colors,"Cuts",false);

 Get_Overlay(inFiles,"genmet_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"genmet_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"genmet_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"genmet_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"genmet_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",false);
 Get_Overlay(inFiles,"genmet_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_lep_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_lep_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_ele_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_ele_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_mu_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"gendphiMET_mu_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_PT_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_PT_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_PT_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_PT_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_Phi_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_Eta_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genele_Eta_Hist",TTJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_Eta_Hist",WJets_directories,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"genmu_Eta_Hist",TTJets_directories,cuts,colors,"Cuts",false);

 Get2D_Plot("dphiCMI_v_PTCM_Hist",directories_2D,inFiles,cuts,false);

/*
 double bkg_Entries = 0.0;
 for(int i = 0; i < int(bkg_directories.size()); i++)
 {
  bkg_Entries+=met_hists_bkg[i]->GetEntries();
 }
 cout << "Zbi TChiWW_SMS_275_235: " << evaluateZbi(met_hists_sig[1]->GetEntries(),bkg_Entries,10.) << endl << "TChiWZ_SMS_275_235 Events: " << met_hists_sig[1]->GetEntries() << endl;
 cout << "BKG Events: " << bkg_Entries << endl;
*/
}

int main(int argc, char* argv[])
{
 string cutsFile = "cuts.txt";
 vector<string> cuts;
 vector<string> files;

 if(argc < 1)
 {
  cout << "ERROR: Need to specify cuts file" << endl;
  cout << "Example: ./Stacker.x -cuts=cuts.txt" << endl;
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
  cuts.push_back(cut);
  files.push_back("Hist_output_"+cut+".root");
 }

 Stacker(files,cuts);
 return 0;
}

