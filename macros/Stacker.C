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
#include <TPaveStats.h>
#include <TCut.h>

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

TGraph* Get_Graph_From_Func(double x_min, double x_max, TF1* Func)
{
 int N = 1000;
 TGraph* gr = new TGraph(N);
 double x = 0.;
 for(int i = 0; i < N; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  gr->SetPoint(i,x,Func->Eval(x));
 }
 return gr;
}

TH2F* get_hist_TreeDraw_2D(string fname, string x, string y, string cut, string tag, int BinsX, double xmin, double xmax, int BinsY, double ymin, double ymax, string tree_name)
{
 //TH2F* hist = new TH2F((x+"_"+y+tag+"_Hist").c_str(),"",BinsX,xmin,xmax,BinsY,ymin,ymax);
 TH2F* hist = NULL;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
     cout << "Unable to open " << fname << " for reading..." << endl;
     return hist;
 }
 TCanvas* can = new TCanvas(tag.c_str(),"",750,600);
 can->cd();
 TTree* tree=(TTree*)f->Get(tree_name.c_str());
 //tree->Draw((x+":"+y+">>"+x+"_"+y+tag+"_Hist("+std::to_string(BinsX)+","+std::to_string(xmin)+","+std::to_string(xmax)+","+std::to_string(BinsY)+","+std::to_string(ymin)+","+std::to_string(ymax)+")").c_str(),cut.c_str(),"");
 tree->Draw("PTCM:dphiCMI>>h(64,0.,3.14,80,0.,500.)","weight*(PTISR>200. && RISR>0.5 && EventFilter==1 && METtrigger==1 && MET>175. && TMath::Abs(dphiMET_V)<(3.14/2.) && RISR<1.)","COLZ"); 
 //hist = (TH2F*)gDirectory->Get((x+"_"+y+tag+"_Hist").c_str());
 hist = (TH2F*)gDirectory->Get("h");
 //hist->Draw("COLZ");
 can->SaveAs((tag+".pdf").c_str()); 
 delete can;
 return hist;
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

TH1D* get_hist(string fname, string dir_name, string hist_name)
{
 TH1D* h = nullptr;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return h;
 }
 TDirectoryFile* folder = nullptr;
 f->GetObject(dir_name.c_str(),folder);
 if(folder == NULL) return h;
 folder->cd();
 folder->GetObject(hist_name.c_str(),h);
 return h;
}

TH2D* get_hist_2D(string fname, string dir_name, string hist_name)
{
 TH2D* h = nullptr;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return h;
 }
 TDirectoryFile* folder = nullptr;
 f->GetObject(dir_name.c_str(),folder);
 if(folder == NULL) return h;
 folder->cd();
 folder->GetObject(hist_name.c_str(),h);
 if(strcmp(h->GetXaxis()->GetTitle(),"dphiCMI") == 0) {h->GetXaxis()->SetTitle("#Delta #phi_{CM,I}");}
 if(strcmp(h->GetYaxis()->GetTitle(),"PTCM") == 0) {h->GetYaxis()->SetTitle("p_{T}^{CM} [GeV]");}
 return h;
}

TH2D* get_hist_2D(string fname, string hist_name)
{
 TH2D* h = nullptr;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return h;
 }
 h = (TH2D*)f->Get(hist_name.c_str());
 if(strcmp(h->GetXaxis()->GetTitle(),"dphiCMI") == 0) {h->GetXaxis()->SetTitle("#Delta #phi_{CM,I}");}
 if(strcmp(h->GetYaxis()->GetTitle(),"PTCM") == 0) {h->GetYaxis()->SetTitle("p_{T}^{CM} [GeV]");}
 return h;
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
  
  TFile* output = new TFile("output_Stack.root","UPDATE");
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
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 for(int i = 0; i < int(cuts.size()); i++)
 {
  for(int j = 0; j < int(directories.size()); j++)
  {
   TH2D* hist = get_hist_2D(inFiles[i], directories[j], hist_name);
   string name = "can_";
   name+=hist->GetName();
   name+=("_"+cuts[i]);
   name+="_"+directories[j];
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
   //can->SetFillColor(kBlack);
   can->Draw();
   can->cd();
   //hist->GetXaxis()->SetAxisColor(kWhite);
   //hist->GetYaxis()->SetAxisColor(kWhite);
   //hist->GetXaxis()->SetTitleColor(kWhite);
   //hist->GetYaxis()->SetTitleColor(kWhite);
   //hist->GetXaxis()->SetLabelColor(kWhite);
   //hist->GetYaxis()->SetLabelColor(kWhite);
   //hist->GetZaxis()->SetLabelColor(kWhite);
   hist->GetXaxis()->CenterTitle();
   hist->GetXaxis()->SetTitleFont(132);
   hist->GetXaxis()->SetTitleSize(0.06);
   hist->GetXaxis()->SetTitleOffset(1.06);
   hist->GetXaxis()->SetLabelFont(132);
   hist->GetXaxis()->SetLabelSize(0.05);
   hist->GetYaxis()->CenterTitle();
   hist->GetYaxis()->SetTitleFont(132);
   hist->GetYaxis()->SetTitleSize(0.06);
   hist->GetYaxis()->SetTitleOffset(1.);
   hist->GetYaxis()->SetLabelFont(132);
   hist->GetYaxis()->SetLabelSize(0.05);
   hist->Draw("COLZ");
   TLatex l;
   l.SetNDC();
   //l.SetTextColor(kWhite);
   l.SetTextSize(0.04);
   l.SetTextFont(42);
   l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Preliminary 13 TeV");
   l.SetTextSize(0.04);
   l.SetTextFont(42);
   name = "Sample: "+directories[j];
   name+= " Cut: "+cuts[i];
   string hist_name = hist->GetName();
   //if(hist_name.find("HEM") != std::string::npos) { name +=", postHEM"; }
   //else { name +=", preHEM"; }
   //eraseSubStr(name,"PTISRG200-");
   //name+=trigger_name;
   l.DrawLatex(0.4,.94,name.c_str());
   gPad->RedrawAxis();
   gPad->RedrawAxis("G");
   TFile* output = new TFile("output_Stack.root","UPDATE");
   can->Write();
   output->Close();
   delete output;
   delete can;
  }
 }
}

void Get2D_Ratio(string hist_name, vector<string> directories, vector<string> cuts, string cut, string directory){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 TH2D* hist_denom = get_hist_2D(("Hist_output_"+cut+".root"), directory, hist_name);
 hist_denom->Scale(1./hist_denom->GetEntries());
 for(int i = 0; i < int(cuts.size()); i++)
 {
  for(int j = 0; j < int(directories.size()); j++)
  {
   TH2D* hist = get_hist_2D(("Hist_output_"+cuts[i]+".root"), directories[j], hist_name);
   hist->Scale(1./hist->GetEntries());
   string name = "can_ratio_";
   name+=hist->GetName();
   name+=directories[j];
   name+=cuts[i];
   TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
   can->SetLeftMargin(0.15);
   can->SetRightMargin(0.18);
   can->SetBottomMargin(0.15);
   can->SetGridx();
   can->SetGridy();
   can->SetLogz();
   //can->SetFillColor(kBlack);
   can->Draw();
   can->cd();
   TH2D* hist_ratio = (TH2D*)hist->Clone();
   hist_ratio->Divide(hist_denom);
   //hist_ratio->GetXaxis()->SetAxisColor(kWhite);
   //hist_ratio->GetYaxis()->SetAxisColor(kWhite);
   //hist_ratio->GetXaxis()->SetTitleColor(kWhite);
   //hist_ratio->GetYaxis()->SetTitleColor(kWhite);
   //hist_ratio->GetXaxis()->SetLabelColor(kWhite);
   //hist_ratio->GetYaxis()->SetLabelColor(kWhite);
   //hist_ratio->GetZaxis()->SetLabelColor(kWhite);
   hist_ratio->GetXaxis()->CenterTitle();
   hist_ratio->GetXaxis()->SetTitleFont(132);
   hist_ratio->GetXaxis()->SetTitleSize(0.06);
   hist_ratio->GetXaxis()->SetTitleOffset(1.06);
   hist_ratio->GetXaxis()->SetLabelFont(132);
   hist_ratio->GetXaxis()->SetLabelSize(0.05);
   hist_ratio->GetYaxis()->CenterTitle();
   hist_ratio->GetYaxis()->SetTitleFont(132);
   hist_ratio->GetYaxis()->SetTitleSize(0.06);
   hist_ratio->GetYaxis()->SetTitleOffset(1.);
   hist_ratio->GetYaxis()->SetLabelFont(132);
   hist_ratio->GetYaxis()->SetLabelSize(0.05);
   hist_ratio->Draw("COLZ");
   TLatex l;
   l.SetNDC();
   //l.SetTextColor(kWhite);
   l.SetTextSize(0.05);
   l.SetTextFont(42);
   l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
   l.SetTextSize(0.05);
   l.SetTextFont(42);
   //name = directories[j];
   name = ("Ratio "+cuts[i]);
   l.DrawLatex(0.65,.94,name.c_str());
   gPad->RedrawAxis();
   gPad->RedrawAxis("G");
   TFile* output = new TFile("output_Stack.root","UPDATE");
   can->Write();
   output->Close();
   delete output;
   delete can;
  }
 }
}

void Get2D_Ratio(string hist_name, string cut1, string cut2, string directory){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 TH2D* hist_denom = get_hist_2D(("Hist_output_"+cut1+".root"), directory, hist_name);
 hist_denom->Scale(1./hist_denom->Integral(19,36,0,6));
 TH2D* hist = get_hist_2D(("Hist_output_"+cut2+".root"), directory, hist_name);
 hist->Scale(1./hist->Integral(19,36,0,6));
 string name = "can_ratio_";
 name+=hist->GetName();
 name+=cut1+cut2+directory;
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 //can->SetFillColor(kBlack);
 can->Draw();
 can->cd();
 TH2D* hist_ratio = (TH2D*)hist->Clone();
 //hist_ratio->Divide(hist_denom);
 //hist_ratio->GetXaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetYaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetXaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetYaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetXaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetYaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetZaxis()->SetLabelColor(kWhite);
 hist_ratio->GetXaxis()->CenterTitle();
 hist_ratio->GetXaxis()->SetTitleFont(132);
 hist_ratio->GetXaxis()->SetTitleSize(0.06);
 hist_ratio->GetXaxis()->SetTitleOffset(1.06);
 hist_ratio->GetXaxis()->SetLabelFont(132);
 hist_ratio->GetXaxis()->SetLabelSize(0.05);
 hist_ratio->GetYaxis()->CenterTitle();
 hist_ratio->GetYaxis()->SetTitleFont(132);
 hist_ratio->GetYaxis()->SetTitleSize(0.06);
 hist_ratio->GetYaxis()->SetTitleOffset(1.);
 hist_ratio->GetYaxis()->SetLabelFont(132);
 hist_ratio->GetYaxis()->SetLabelSize(0.05);
 hist_ratio->Draw("COLZ");
 TLatex l;
 l.SetNDC();
 //l.SetTextColor(kWhite);
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 //name = directories[j];
 string cut_name = cut1;
 eraseSubStr(cut_name,"-EventFilterE0");
 eraseSubStr(cut_name,"PTISRG200-");
 name = ("Ratio: "+cut_name);
 l.DrawLatex(0.65,.94,name.c_str());
 gPad->RedrawAxis();
 gPad->RedrawAxis("G");
 TFile* output = new TFile("output_Stack.root","UPDATE");
 can->Write();
 output->Close();
 delete output;
 delete can;
}

void Get2D_Ratio(TH2D* hist_denom, TH2D* hist, string cut1, string cut2, string directory1, string directory2, bool zoom){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 string hist_name1 = hist_denom->GetName();
 string hist_name2 = hist->GetName();
 //hist_denom->Rebin2D(4,4);
 hist_denom->Scale(1./hist_denom->Integral());
 //hist->Rebin2D(4,4);
 hist->Scale(1./hist->Integral());
 string name = "can_ratio_"+hist_name1+"_"+hist_name2+"_"+cut1+"_"+cut2+"_"+directory1+"_"+directory2;
 if(zoom) { name = "can_ratio_zoom_"+hist_name1+"_"+hist_name2+"_"+cut1+"_"+cut2+"_"+directory1+"_"+directory2; }
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 //can->SetFillColor(kBlack);
 can->Draw();
 can->cd();
 TH2D* hist_ratio = (TH2D*)hist->Clone();
 hist_ratio->Divide(hist_denom);
 //hist_ratio->GetXaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetYaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetXaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetYaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetXaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetYaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetZaxis()->SetLabelColor(kWhite);
 hist_ratio->GetXaxis()->CenterTitle();
 hist_ratio->GetXaxis()->SetTitleFont(132);
 hist_ratio->GetXaxis()->SetTitleSize(0.06);
 hist_ratio->GetXaxis()->SetTitleOffset(1.06);
 hist_ratio->GetXaxis()->SetLabelFont(132);
 hist_ratio->GetXaxis()->SetLabelSize(0.05);
 hist_ratio->GetYaxis()->CenterTitle();
 hist_ratio->GetYaxis()->SetTitleFont(132);
 hist_ratio->GetYaxis()->SetTitleSize(0.06);
 hist_ratio->GetYaxis()->SetTitleOffset(1.);
 hist_ratio->GetYaxis()->SetLabelFont(132);
 hist_ratio->GetYaxis()->SetLabelSize(0.05);
 if(zoom)
 {
  hist_ratio->GetZaxis()->SetRangeUser(.0,2.);
  hist_ratio->SetContour(20);
  can->SetLogz(0);
 }
 hist_ratio->Draw("COLZ");
 TLatex l;
 l.SetNDC();
 //l.SetTextColor(kWhite);
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV");
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 //name = directories[j];
 name = "";
 /*
 if(hist_name2.find("HEM") != std::string::npos) { name += cut2+", postHEM / "; }
  else { name += cut2+", preHEM / "; }
 if(hist_name1.find("HEM") != std::string::npos) { name += cut1+", postHEM"; }
  else { name += cut1+", preHEM"; }
 */
 name = cut2+" "+directory2+"/"+cut1+" "+directory1;
 l.DrawLatex(0.42,.94,name.c_str());
 gPad->RedrawAxis();
 gPad->RedrawAxis("G");
 TF1* left_para = new TF1("left para","-500.*sqrt(-2.777*x*x+1.388*x+0.8264)+575.",0.,TMath::Pi());
 TF1* right_para = new TF1("right para","-500.*sqrt((-1.5625*x*x+7.8125*x-8.766))+600.",0.,TMath::Pi());
 double x_min = 0.;
 double x_max = TMath::Pi();
 int N = 1000;
 TGraph* gr_left_para = new TGraph(N);
 TGraph* gr_right_para = new TGraph(N);
 double x = 0.;
 for(int i = 0; i < N; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  gr_left_para->SetPoint(i,x,x < 0.25 ? 75. : left_para->Eval(x));
  gr_right_para->SetPoint(i,x,x > 2.5 ? 100. : right_para->Eval(x));
 }
 gr_left_para->Draw("P");
 gr_left_para->SetMarkerColor(kRed);
 gr_left_para->SetMarkerSize(0.4);
 gr_left_para->SetMarkerStyle(20.);
 gr_right_para->SetMarkerColor(kRed);
 gr_right_para->SetMarkerSize(0.4);
 gr_right_para->SetMarkerStyle(20.);
 gr_right_para->Draw("P");
 TFile* output = new TFile("Ratios.root","UPDATE");
 can->Write();
/*
 if(!(output->cd(directory1.c_str())))
 {  
  output->mkdir(directory1.c_str());
  output->cd(directory1.c_str());
 }
 else
 {
  output->cd(directory1.c_str());
 }
 hist_denom->Write();
 if(!(output->cd(directory2.c_str())))
 {  
  output->mkdir(directory2.c_str());
  output->cd(directory2.c_str());
 }
 else
 {
  output->cd(directory2.c_str());
 }
 hist->Write();
*/
 output->Close();
 delete output;
 delete can;
}

void Get2D_Ratio(string hist_name1, string hist_name2, string cut1, string cut2, string directory1, string directory2, bool zoom){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 TH2D* hist_denom = get_hist_2D(("Hist_output_"+cut1+".root"), directory1, hist_name1);
 //hist_denom->Rebin2D(4,4);
 hist_denom->Scale(1./hist_denom->Integral());
 TH2D* hist = get_hist_2D(("Hist_output_"+cut2+".root"), directory2, hist_name2);
 //hist->Rebin2D(4,4);
 hist->Scale(1./hist->Integral());
 string name = "can_ratio_"+hist_name1+"_"+hist_name2+"_"+cut1+"_"+cut2+"_"+directory1+"_"+directory2;
 if(zoom) { name = "can_ratio_zoom_"+hist_name1+"_"+hist_name2+"_"+cut1+"_"+cut2+"_"+directory1+"_"+directory2; }
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 //can->SetFillColor(kBlack);
 can->Draw();
 can->cd();
 TH2D* hist_ratio = (TH2D*)hist->Clone();
 hist_ratio->Divide(hist_denom);
 //hist_ratio->GetXaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetYaxis()->SetAxisColor(kWhite);
 //hist_ratio->GetXaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetYaxis()->SetTitleColor(kWhite);
 //hist_ratio->GetXaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetYaxis()->SetLabelColor(kWhite);
 //hist_ratio->GetZaxis()->SetLabelColor(kWhite);
 hist_ratio->GetXaxis()->CenterTitle();
 hist_ratio->GetXaxis()->SetTitleFont(132);
 hist_ratio->GetXaxis()->SetTitleSize(0.06);
 hist_ratio->GetXaxis()->SetTitleOffset(1.06);
 hist_ratio->GetXaxis()->SetLabelFont(132);
 hist_ratio->GetXaxis()->SetLabelSize(0.05);
 hist_ratio->GetYaxis()->CenterTitle();
 hist_ratio->GetYaxis()->SetTitleFont(132);
 hist_ratio->GetYaxis()->SetTitleSize(0.06);
 hist_ratio->GetYaxis()->SetTitleOffset(1.);
 hist_ratio->GetYaxis()->SetLabelFont(132);
 hist_ratio->GetYaxis()->SetLabelSize(0.05);
 if(zoom)
 {
  hist_ratio->GetZaxis()->SetRangeUser(.0,2.);
  hist_ratio->SetContour(20);
  can->SetLogz(0);
 }
 hist_ratio->Draw("COLZ");
 TLatex l;
 l.SetNDC();
 //l.SetTextColor(kWhite);
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV");
 l.SetTextSize(0.025);
 l.SetTextFont(42);
 //name = directories[j];
 name = "";
 if(hist_name2.find("postHEM") != std::string::npos) { name += cut2+", postHEM / "; }
  else { name += cut2+", preHEM / "; }
 if(hist_name1.find("postHEM") != std::string::npos) { name += cut1+", postHEM"; }
  else { name += cut1+", preHEM"; }
 //name = cut2+" "+directory2+"/"+cut1+" "+directory1;
 l.DrawLatex(0.36,.94,name.c_str());
 gPad->RedrawAxis();
 gPad->RedrawAxis("G");
 TF1* left_para = new TF1("left para","-500.*sqrt(-2.777*x*x+1.388*x+0.8264)+575.",0.,TMath::Pi());
 TF1* right_para = new TF1("right para","-500.*sqrt((-1.5625*x*x+7.8125*x-8.766))+600.",0.,TMath::Pi());
 double x_min = 0.;
 double x_max = TMath::Pi();
 int N = 1000;
 TGraph* gr_left_para = new TGraph(N);
 TGraph* gr_right_para = new TGraph(N);
 double x = 0.;
 for(int i = 0; i < N; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  gr_left_para->SetPoint(i,x,x < 0.25 ? 75. : left_para->Eval(x));
  gr_right_para->SetPoint(i,x,x > 2.5 ? 100. : right_para->Eval(x));
 }
 gr_left_para->Draw("P");
 gr_left_para->SetMarkerColor(kRed);
 gr_left_para->SetMarkerSize(0.4);
 gr_left_para->SetMarkerStyle(20.);
 gr_right_para->SetMarkerColor(kRed);
 gr_right_para->SetMarkerSize(0.4);
 gr_right_para->SetMarkerStyle(20.);
 gr_right_para->Draw("P");
 TFile* output = new TFile("output_Stack.root","UPDATE");
 can->Write();
 output->Close();
 delete output;
 delete can;
}

void Get1D_Ratio(string hist_name, string cut1, string cut2_hist_name2, string directory, bool option){
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 TH1D* hist_denom = get_hist(("Hist_output_"+cut1+".root"), directory, hist_name);
 hist_denom->Scale(1./hist_denom->Integral());
 TH1D* hist = NULL;
 //compare between cuts with same hist
 if(option) { hist = get_hist(("Hist_output_"+cut2_hist_name2+".root"), directory, hist_name); }
 //compare between hists with same cut
 else { hist = get_hist(("Hist_output_"+cut1+".root"), directory, cut2_hist_name2); }
 hist->Scale(1./hist->Integral());
 string name = "can_ratio_";
 name+=hist->GetName();
 name+=option;
 name+=cut1+cut2_hist_name2+directory;
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 //can->SetFillColor(kBlack);
 can->Draw();
 can->cd();
 TH1D* hist_ratio = (TH1D*)hist->Clone();
 hist_ratio->Divide(hist_denom);
 hist_ratio->GetXaxis()->SetAxisColor(kWhite);
 hist_ratio->GetYaxis()->SetAxisColor(kWhite);
 hist_ratio->GetXaxis()->SetTitleColor(kWhite);
 hist_ratio->GetYaxis()->SetTitleColor(kWhite);
 hist_ratio->GetXaxis()->SetLabelColor(kWhite);
 hist_ratio->GetYaxis()->SetLabelColor(kWhite);
 hist_ratio->GetZaxis()->SetLabelColor(kWhite);
 hist_ratio->GetXaxis()->CenterTitle();
 hist_ratio->GetXaxis()->SetTitleFont(132);
 hist_ratio->GetXaxis()->SetTitleSize(0.06);
 hist_ratio->GetXaxis()->SetTitleOffset(1.06);
 hist_ratio->GetXaxis()->SetLabelFont(132);
 hist_ratio->GetXaxis()->SetLabelSize(0.05);
 hist_ratio->GetYaxis()->CenterTitle();
 hist_ratio->GetYaxis()->SetTitleFont(132);
 hist_ratio->GetYaxis()->SetTitleSize(0.06);
 hist_ratio->GetYaxis()->SetTitleOffset(1.);
 hist_ratio->GetYaxis()->SetLabelFont(132);
 hist_ratio->GetYaxis()->SetLabelSize(0.05);
 hist_ratio->Draw("COLZ");
 TLatex l;
 l.SetNDC();
 //l.SetTextColor(kWhite);
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 //name = directories[j];
 string cut_name = cut1;
 eraseSubStr(cut_name,"-EventFilterE0");
 eraseSubStr(cut_name,"PTISRG200-");
 name = ("Ratio: "+cut_name);
 l.DrawLatex(0.65,.94,name.c_str());
 gPad->RedrawAxis();
 gPad->RedrawAxis("G");
 TFile* output = new TFile("output_Stack.root","UPDATE");
 can->Write();
 output->Close();
 delete output;
 delete can;
}

void Get_Overlay(vector<string> outFiles, vector<string> hist_names, vector<string> samples, vector<string> cuts, vector<int> colors, string option, bool trigger)
{
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 string name = "can";
 vector<TH1D*> hists;
 for(int j = 0; j < cuts.size(); j++)
 {
  name += "_"+cuts[j];
  for(int i = 0; i < samples.size(); i++)
  {
   name += "_"+samples[i];
   for(int k = 0; k < hist_names.size(); k++)
   {
    name += "_"+hist_names[k];
    hists.push_back(get_hist(outFiles[j],samples[i],hist_names[k]));
   }
  }
 }
 TCanvas* can = new TCanvas(("can_"+hist_names[0]+samples[0]+cuts[0]).c_str(),"",864.,468.);
 can->SetLeftMargin(0.15);
 can->SetRightMargin(0.18);
 can->SetBottomMargin(0.15);
 can->SetGridx();
 can->SetGridy();
 can->SetLogz();
 //can->SetFillColor(kBlack);
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
 //l.SetTextColor(kWhite);
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
 //leg->SetFillColor(kBlack);
 //leg->SetLineColor(kBlack);
 //leg->SetShadowColor(kBlack);
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

 TFile* output = new TFile("output_Stack.root","UPDATE");
 can->Update();
 can->Write();
 output->Close();
 delete can;
 delete leg;
 delete output;

 //string s_lumi = "#scale[0.6]{#int} #it{L dt} = "+to_string(int(137.0))+" fb^{-1}";
 //l.DrawLatex(0.72,0.94,s_lumi.c_str());
}

void Get1D_Plot(vector<string> outFiles, string hist_name, vector<string> samples, vector<string> cuts, vector<int> colors)
{
 gStyle->SetOptTitle(0);
 //gStyle->SetFrameFillColor(kBlack);
 //gStyle->SetFrameLineColor(kWhite);
 for(int j = 0; j < cuts.size(); j++)
 {
  for(int i = 0; i < samples.size(); i++)
  {
   TH1D* hists = get_hist(outFiles[j],samples[i],hist_name);
   TCanvas* can = new TCanvas(("can_"+hist_name+samples[i]+"_"+cuts[j]).c_str(),"",864.,468.);
   can->SetLeftMargin(0.15);
   can->SetRightMargin(0.18);
   can->SetBottomMargin(0.15);
   can->SetGridx();
   can->SetGridy();
   can->SetLogz();
   //can->SetFillColor(kBlack);
   can->Draw();
   can->cd();
   string x_title = hists->GetXaxis()->GetTitle();
   string y_title = "#frac{1}{N} #frac{dN}{d("+x_title+")}";
   //hists->GetYaxis()->SetTitle(y_title.c_str());
   //hists->Scale(1./hists->GetEntries());
   hists->GetYaxis()->SetTitle("Number of Events");
   hists->Draw("HIST SAMES");
   hists->SetLineWidth(2);
   hists->GetXaxis()->SetAxisColor(kWhite);
   hists->GetYaxis()->SetAxisColor(kWhite);
   hists->GetXaxis()->SetTitleColor(kWhite);
   hists->GetYaxis()->SetTitleColor(kWhite);
   hists->GetXaxis()->SetLabelColor(kWhite);
   hists->GetYaxis()->SetLabelColor(kWhite);
   hists->SetLineColor(colors[i]);
   hists->GetXaxis()->CenterTitle();
   hists->GetXaxis()->SetTitleFont(132);
   hists->GetXaxis()->SetTitleSize(0.06);
   hists->GetXaxis()->SetTitleOffset(1.06);
   hists->GetXaxis()->SetLabelFont(132);
   hists->GetXaxis()->SetLabelSize(0.05);
   //hists->GetXaxis()->SetTitle(Xname.c_str());
   hists->GetYaxis()->CenterTitle();
   hists->GetYaxis()->SetTitleFont(132);
   hists->GetYaxis()->SetTitleSize(0.06);
   hists->GetYaxis()->SetTitleOffset(1.);
   hists->GetYaxis()->SetLabelFont(132);
   hists->GetYaxis()->SetLabelSize(0.05);
   //hists->GetYaxis()->SetTitle("a. u.");
   //hists->GetYaxis()->SetTitle(Yname.c_str());
   can->Update();
   TPaveStats* stats = (TPaveStats*)hists->FindObject("stats");
   //stats->SetFillColor(kBlack);
   //stats->SetLineColor(kWhite);
   //stats->SetTextColor(kWhite);
   stats->SetX1NDC(.62);
   stats->SetY1NDC(.7);
   stats->SetX2NDC(.82);
   stats->SetY2NDC(.9);
   
   TLatex l;
   //l.SetTextColor(kWhite);
   l.SetNDC();
   l.SetTextSize(0.04);
   l.SetTextFont(42);
   l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
   l.SetTextSize(0.04);
   l.SetTextFont(42);
   l.DrawLatex(.50,.94,(samples[i]+"   "+cuts[j]).c_str());

   TFile* output = new TFile("output_Stack.root","UPDATE");
   can->Update();
   can->Write();
   output->Close();
   delete can;
   delete output;
  }
 }

 //string s_lumi = "#scale[0.6]{#int} #it{L dt} = "+to_string(int(137.0))+" fb^{-1}";
 //l.DrawLatex(0.72,0.94,s_lumi.c_str());
}

void Stacker(vector<string> inFiles, vector<string> cuts){
 cout << "Running Stacker..." << endl;
 bool trigger = false;
 vector<string> WJets_directories = {"WJets_2017"};
 vector<string> WJets_Old_directories = {"WJets_2017_Old"};
 vector<string> TTJets_directories = {"TTJets_2017"};
 vector<string> directories_2016 = {"MET_2016","Bkg_2016"};
 vector<string> directories_2017 = {"MET_2017","Bkg_2017"};
 vector<string> directories_2018 = {"MET_2018","Bkg_2018"};
 vector<string> sig_directories{"T2tt_500_490_2017","TChiWZ_300_297_2016","TSlepSlep_300_299_2016"};
 //vector<string> directories_2D{"TChiWW_SMS_275_235", "TTJets", "WJets", "DiBoson", "DYJetsToLL", "ST"};
 //vector<string> directories_2D{"Bkg_2016","MET_2016","Bkg_2017","MET_2017","Bkg_2018","MET_2018","QCD_2017","TTJets_2017","WJets_2017","ZJetsToNuNu_2017","T2bW_500_490_2016","T2bW_500_490_2017","T2bW_500_300_2018"};
 //vector<string> directories_2D{"Bkg_2017","Bkg_QCD_RM_2017","MET_2017","QCD_2017","TTJets_2017","WJets_2017","ZJetsToNuNu_2017","T2bW_500_490_2017","Bkg_QCD200_RM_2017","Bkg_QCD300_RM_2017","Bkg_QCD500_RM_2017","Bkg_QCD700_RM_2017","Bkg_QCD1000_RM_2017","Bkg_QCD1500_RM_2017","Bkg_QCD2000_RM_2017","QCD_100to200_2017","QCD_200to300_2017","QCD_300to500_2017","QCD_500to700_2017","QCD_700to1000_2017","QCD_1000to1500_2017","QCD_1500to2000_2017","QCD_2000toInf_2017"};
 vector<string> directories_2D{"SingleElectron_2017","SingleMuon_2017","Bkg_2017"};
 vector<int> colors = {kBlue+1, kRed+1, kGreen+1, kMagenta, kCyan, kOrange, kViolet+2, kAzure+7, kPink, kGreen, kGray};
 vector<int> colors_bkg = { kAzure+1, kGreen-9, kPink, kTeal+2, kYellow-4 };
 vector<int> colors_sig = { kMagenta, kCyan+2, };

// Get_Stack("met_Hist",bkg_directories,sig_directories,colors_bkg,colors_sig,inFile,cut);
// Get_Stack("dphiMET_lep_Hist",bkg_directories,sig_directories,colors_bkg,colors_sig,inFile,cut);

//compare across: sample, selection/final state, hist?, ..., 
/*
 Get_Overlay(inFiles,"PTCM_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"PTCM_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"PTCM_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_lep_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_lep_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_lep_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_ele_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_ele_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_ele_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_mu_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_mu_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiMET_mu_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_PT_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_PT_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_PT_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"jet_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_MET_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_MET_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_MET_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_METperp_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_METperp_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"ele_PT_proj_METperp_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_MET_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_MET_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_MET_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_METperp_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_METperp_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"mu_PT_proj_METperp_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiCMI_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiCMI_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"dphiCMI_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);

 Get_Overlay(inFiles,"genmet_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmet_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmet_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmet_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmet_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmet_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_lep_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_lep_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_lep_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_ele_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_ele_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_ele_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_mu_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_mu_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 //Get_Overlay(inFiles,"gendphiMET_mu_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_PT_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_PT_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_PT_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_PT_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_PT_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_PT_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Phi_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Phi_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Phi_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Eta_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Eta_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genele_Eta_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Eta_Hist",WJets_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Eta_Hist",WJets_Old_directories,cuts,colors,"Cuts",trigger);
 Get_Overlay(inFiles,"genmu_Eta_Hist",TTJets_directories,cuts,colors,"Cuts",trigger);
*/

 //Get_Overlay(inFiles,"dphiMET_V_Hist",directories_2016,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_V_Hist",directories_2017,cuts,colors,"Cuts",false);
 //Get_Overlay(inFiles,"dphiMET_V_Hist",directories_2018,cuts,colors,"Cuts",false);

 //Get1D_Ratio("met_Hist","PreSelection","HEM","MET_2018",true);
 //Get1D_Ratio("met_Hist","PreSelection","met_Hist_HEM","MET_2018",false);
 
 Get2D_Plot("HT_v_MET_Hist",directories_2D,inFiles,cuts,trigger);
 Get2D_Plot("HTMedium_v_MET_Hist",directories_2D,inFiles,cuts,trigger);
 Get2D_Plot("HTLoose_v_MET_Hist",directories_2D,inFiles,cuts,trigger);
 Get2D_Plot("HTVeryLoose_v_MET_Hist",directories_2D,inFiles,cuts,trigger);
 
 //Get2D_Plot("dphiCMI_v_PTCM_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_Mperp_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_RISR_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_PTCM_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("RISR_v_PTCM_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_dphiMET_V_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiMET_V_v_RISR_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_dphiMET_V_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiMET_V_v_PTCM_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_RISR_Hist",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_PTCM_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_Mperp_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_RISR_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_PTCM_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("RISR_v_PTCM_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiCMI_v_dphiMET_V_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiMET_V_v_RISR_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_dphiMET_V_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("dphiMET_V_v_PTCM_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 //Get2D_Plot("Mperp_v_RISR_Hist_HEM",directories_2D,inFiles,cuts,trigger);
 
 //Get1D_Plot(inFiles,"ele_PT_Hist",sig_directories,cuts,colors);
 //Get1D_Plot(inFiles,"mu_PT_Hist",sig_directories,cuts,colors);
 //Get1D_Plot(inFiles,"genele_PT_Hist",sig_directories,cuts,colors);
 //Get1D_Plot(inFiles,"genmu_PT_Hist",sig_directories,cuts,colors);
 
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","EventFilterE0","EventFilterE1","MET_2017");
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","PTISRG200-RISRG0.5-EventFilterE0","PTISRG200-RISRG0.5-EventFilterE1","MET_2017");
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","PTISRG200-RISRG0.85-EventFilterE0","PTISRG200-RISRG0.85-EventFilterE1","MET_2017");
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","PTISRG200-RISRG0.9-EventFilterE0","PTISRG200-RISRG0.9-EventFilterE1","MET_2017");
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","PTISRG200-RISRG0.95-EventFilterE0","PTISRG200-RISRG0.95-EventFilterE1","MET_2017");
 
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_Mperp_Hist","dphiCMI_v_Mperp_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_RISR_Hist","dphiCMI_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_PTCM_Hist","Mperp_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("RISR_v_PTCM_Hist","RISR_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_dphiMET_V_Hist","dphiCMI_v_dphiMET_V_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiMET_V_v_RISR_Hist","dphiMET_V_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_dphiMET_V_Hist","Mperp_v_dphiMET_V_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiMET_V_v_PTCM_Hist","dphiMET_V_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_RISR_Hist","Mperp_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",true);

 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_Mperp_Hist","dphiCMI_v_Mperp_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_RISR_Hist","dphiCMI_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_PTCM_Hist","Mperp_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("RISR_v_PTCM_Hist","RISR_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_dphiMET_V_Hist","dphiCMI_v_dphiMET_V_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiMET_V_v_RISR_Hist","dphiMET_V_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_dphiMET_V_Hist","Mperp_v_dphiMET_V_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiMET_V_v_PTCM_Hist","dphiMET_V_v_PTCM_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_RISR_Hist","Mperp_v_RISR_Hist_HEM","PreSelection","PreSelection","MET_2018","MET_2018",false);

 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_Mperp_Hist","dphiCMI_v_Mperp_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_RISR_Hist","dphiCMI_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_PTCM_Hist","Mperp_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("RISR_v_PTCM_Hist","RISR_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_dphiMET_V_Hist","dphiCMI_v_dphiMET_V_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiMET_V_v_RISR_Hist","dphiMET_V_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_dphiMET_V_Hist","Mperp_v_dphiMET_V_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiMET_V_v_PTCM_Hist","dphiMET_V_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);
 //Get2D_Ratio("Mperp_v_RISR_Hist","Mperp_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",true);

 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_Mperp_Hist","dphiCMI_v_Mperp_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_RISR_Hist","dphiCMI_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_PTCM_Hist","Mperp_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("RISR_v_PTCM_Hist","RISR_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiCMI_v_dphiMET_V_Hist","dphiCMI_v_dphiMET_V_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiMET_V_v_RISR_Hist","dphiMET_V_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_dphiMET_V_Hist","Mperp_v_dphiMET_V_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("dphiMET_V_v_PTCM_Hist","dphiMET_V_v_PTCM_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);
 //Get2D_Ratio("Mperp_v_RISR_Hist","Mperp_v_RISR_Hist_HEM","PreSelection","HEM","MET_2018","MET_2018",false);

 //HEM $$$
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_preHEM","dphiCMI_v_PTCM_Hist_postHEM","PreSelection","PreSelection","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_preHEM","dphiCMI_v_PTCM_Hist_postHEM","PreSelection","HEM-EventFlag_JetInHEM_Pt20E0","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_preHEM","dphiCMI_v_PTCM_Hist_postHEM","PreSelection","HEM-EventFlag_JetInHEM_Pt20_JetIDE0","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_preHEM","dphiCMI_v_PTCM_Hist_postHEM","PreSelection","EventFlag_JetInHEM_Pt20E0","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_preHEM","dphiCMI_v_PTCM_Hist_postHEM","PreSelection","EventFlag_JetInHEM_Pt20_JetIDE0","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_postHEM","dphiCMI_v_PTCM_Hist_postHEM","HEM-EventFlag_JetInHEM_Pt20E0","HEM-EventFlag_JetInHEM_Pt20_JetIDE0","MET_2018","MET_2018",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist_postHEM","dphiCMI_v_PTCM_Hist_postHEM","EventFlag_JetInHEM_Pt20E0","HEM-EventFlag_JetInHEM_Pt20E0","MET_2018","MET_2018",true);
 
 //2D Ratio 2017 Cleaning
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist","RISRG0.9","RISRG0.9","Bkg_2017","MET_2017",true);
 //Get2D_Ratio("dphiCMI_v_PTCM_Hist","dphiCMI_v_PTCM_Hist","PreSelection","PreSelection","Bkg_2017","MET_2017",true);
 

 //cout << "Eff of 20 GeV Jets in MET: " << get_hist_2D("Hist_output_Clean-HEM-EventFlag_JetInHEM_Pt20E0.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_Clean.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral() << endl;
 //cout << "Eff of 20 GeV Jets in Bkg: " << get_hist_2D("Hist_output_Clean-HEM-EventFlag_JetInHEM_Pt20E0.root","Bkg_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_Clean.root","Bkg_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;

 //string PreSelection = "weight*(PTISR>200. && RISR>0.5 && EventFilter==1 && METtrigger==1 && TMath::Abs(dphiMET_V)<3.14/2. && MET>175. && RISR<1.)";
 //TH2F* dphiCMI_v_PTCM_MET_2016 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Summer16_102X_Data_MET/MET_2016.root","dphiCMI","PTCM",PreSelection,"MET_2016",64,0.,TMath::Pi(),80,0.,500.,"KUAnalysis");
 //TH2F* dphiCMI_v_PTCM_Bkg_2016 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Summer16_102X/Bkg_2016.root","dphiCMI","PTCM",PreSelection,"Bkg_2016",64,0.,TMath::Pi(),80,0.,500.,"KUAnalysis");
 //Get2D_Ratio(dphiCMI_v_PTCM_Bkg_2016,dphiCMI_v_PTCM_MET_2016,"PreSelection","PreSelection","Bkg_2016","MET_2016",true);
 //TH2F* dphiCMI_v_PTCM_MET_2017 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Fall17_102X_Data_MET/MET_2017.root","dphiCMI","PTCM",PreSelection,"MET_2017",64,0.,3.14,80,0.,500.,"KUAnalysis");
 //TH2F* dphiCMI_v_PTCM_Bkg_2017 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Fall17_102X/Bkg_2017.root","dphiCMI","PTCM",PreSelection,"Bkg_2017",64,0.,3.14,80,0.,500.,"KUAnalysis");
 //Get2D_Ratio(dphiCMI_v_PTCM_Bkg_2017,dphiCMI_v_PTCM_MET_2017,"PreSelection","PreSelection","Bkg_2017","MET_2017",true);
 //TH2F* dphiCMI_v_PTCM_MET_2018 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Autumn18_102X_Data/MET_2018.root","dphiCMI","PTCM",PreSelection,"MET_2018",64,0.,TMath::Pi(),80,0.,500.,"KUAnalysis");
 //TH2F* dphiCMI_v_PTCM_Bkg_2018 = get_hist_TreeDraw_2D("/stash/user/zflowers/NTUPLES/Processing/Autumn18_102X/Bkg_2018.root","dphiCMI","PTCM",PreSelection,"Bkg_2018",64,0.,TMath::Pi(),80,0.,500.,"KUAnalysis");
 //Get2D_Ratio(dphiCMI_v_PTCM_Bkg_2018,dphiCMI_v_PTCM_MET_2018,"PreSelection","PreSelection","Bkg_2018","MET_2018",true);
 //
 
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2016_PreSelection"),get_hist_2D("Save.root","MET_2016_PreSelection"),"PreSelection","PreSelection","Bkg_2016","MET_2016",true);
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2016_RISRG09"),get_hist_2D("Save.root","MET_2016_RISRG09"),"RISRG0.9","RISRG0.9","Bkg_2016","MET_2016",true);
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2017_PreSelection"),get_hist_2D("Save.root","MET_2017_PreSelection"),"PreSelection","PreSelection","Bkg_2017","MET_2017",true);
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2017_RISRG09"),get_hist_2D("Save.root","MET_2017_RISRG09"),"RISRG0.9","RISRG0.9","Bkg_2017","MET_2017",true);
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2018_PreSelection"),get_hist_2D("Save.root","MET_2018_PreSelection"),"PreSelection","PreSelection","Bkg_2018","MET_2018",true);
 //Get2D_Ratio(get_hist_2D("Save.root","Bkg_2018_RISRG09"),get_hist_2D("Save.root","MET_2018_RISRG09"),"RISRG0.9","RISRG0.9","Bkg_2018","MET_2018",true);

 //cout << "Eff of 15 GeV Jets in MET: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEME0.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_PreSelection.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral() << endl;
 //cout << "Eff of 20 GeV Jets in MET: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEM_Pt20E0.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_PreSelection.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral() << endl;
 //cout << "Eff of HEM-nom in MET: " << get_hist_2D("Hist_output_HEM.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_PreSelection.root","MET_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral() << endl;
 //cout << "Eff of 15 GeV Jets in WJets: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEME0.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_PreSelection.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of 20 GeV Jets in WJets: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEM_Pt20E0.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_PreSelection.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of HEM-nom in WJets: " << get_hist_2D("Hist_output_HEM.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_PreSelection.root","WJets_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of 15 GeV Jets in T2tt: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEME0.root","T2tt_500_490_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_PreSelection.root","T2tt_500_490_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of 20 GeV Jets in T2tt: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEM_Pt20E0.root","T2tt_500_490_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_PreSelection.root","T2tt_500_490_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of 15 GeV Jets in T2ChiWZ: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEME0.root","TChiWZ_300_290_2018","dphiCMI_v_PTCM_Hist")->Integral()/get_hist_2D("Hist_output_PreSelection.root","TChiWZ_300_290_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl;
 //cout << "Eff of 20 GeV Jets in TChiWZ: " << get_hist_2D("Hist_output_HEM-EventFlag_JetInHEM_Pt20E0.root","TChiWZ_300_290_2018","dphiCMI_v_PTCM_Hist_HEM")->Integral()/get_hist_2D("Hist_output_PreSelection.root","TChiWZ_300_290_2018","dphiCMI_v_PTCM_Hist")->Integral() << endl; 

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
  if(cut.rfind("#", 0) == 0) continue;
  cuts.push_back(cut);
  files.push_back("Hist_output_"+cut+".root");
 }

 Stacker(files,cuts);
 return 0;
}

