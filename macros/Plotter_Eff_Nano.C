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
void Get_Plot_WithSF(vector<string> tags, string data_tag, string bkg_tag, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cuts, string SF_FinalState, string name, string option);
TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option, string SF_Cut = "default");
TMultiGraph* get_mg_ratio(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, string nominal, string name);
TGraphAsymmErrors* get_gr(string cut, string tag, string trigger, TCanvas*& can);
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

void Plotter_Eff_Nano(vector<string> cut, bool muon = false, bool electron = false, bool data = false, bool bkg = false){
 vector<string> inFile;
 for(int i = 0; i < cut.size(); i++) { inFile.push_back("Eff_output_"+cut[i]+".root"); }
 vector<int> colors = {kBlue+1, kRed+1, kGreen+1, kBlack, kOrange-1, kViolet+1, kMagenta, kAzure+1};
 //string inFile ="output_quick.root";

 vector<string> METtrigger{ "METtrigger" };
 
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

 string muon_FS = "SingleMuontrigger-E1--Nmu-E1";
 string electron_FS = "SingleElectrontrigger-E1--Nele-E1";

 if(muon)
 {
  if(data)
  {
   Get_Plot_WithSF(tags_SingleMuon_2016,"SingleMuon_2016","Bkg_2016",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2016","FinalState");
   Get_Plot_WithSF(tags_SingleMuon_2017,"SingleMuon_2017","Bkg_2017",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2017","FinalState");
   Get_Plot_WithSF(tags_SingleMuon_2018,"SingleMuon_2018","Bkg_2018",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2018","FinalState");
  }
  if(bkg)
  {
   Get_Plot_WithSF(tags_bkg_2016,"SingleMuon_2016","Bkg_2016",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2016","FinalState");
   Get_Plot_WithSF(tags_bkg_2017,"SingleMuon_2017","Bkg_2017",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2017","FinalState");
   Get_Plot_WithSF(tags_bkg_2018,"SingleMuon_2018","Bkg_2018",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2018","FinalState");
  }
 }
 if(electron)
 {
  if(data)
  {
   Get_Plot_WithSF(tags_SingleElectron_2016,"SingleElectron_2016","Bkg_2016",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2016","FinalState");
   Get_Plot_WithSF(tags_SingleElectron_2017,"SingleElectron_2017","Bkg_2017",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2017","FinalState");
   Get_Plot_WithSF(tags_SingleElectron_2018,"SingleElectron_2018","Bkg_2018",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2018","FinalState");
  }
  if(bkg)
  {
   Get_Plot_WithSF(tags_bkg_2016,"SingleElectron_2016","Bkg_2016",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2016","FinalState");
   Get_Plot_WithSF(tags_bkg_2017,"SingleElectron_2017","Bkg_2017",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2017","FinalState");
   Get_Plot_WithSF(tags_bkg_2018,"SingleElectron_2018","Bkg_2018",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2018","FinalState");
  }
 }

// for(int i = 0; i < inFile.size(); i++)
// {
 // Get_Plot(tags_bkg_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
 // Get_Plot(tags_SingleElectron_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
 // Get_Plot(tags_SingleMuon_years,METtrigger,colors,inFile[i],cut[i],"Trigger");
// }
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

void Get_Plot_WithSF(vector<string> tags, string data_tag, string bkg_tag, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cuts, string SF_FinalState, string name, string option)
{
 TLegend* leg = new TLegend(0.3,0.2,0.95,0.5); 
 leg->SetTextFont(132);
 leg->SetTextSize(0.033);
 
 TLatex l;
 TCanvas* can = new TCanvas((name).c_str(),"",1278,775);
 can->SetLeftMargin(0.13);
 can->SetRightMargin(0.04);
 can->SetBottomMargin(0.15);
 can->SetTopMargin(0.085);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 TMultiGraph* mg = get_mg(cuts,tags,Triggers,inFile,colors,leg,can,option);
 can->Clear();

 string extra_name = "";
 vector<string> known_cuts;
 known_cuts.push_back("PTISR");
 known_cuts.push_back("PTCM");
 known_cuts.push_back("RISR");
 known_cuts.push_back("dphiCMI");
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
 known_cuts.push_back("DoubleElectrontrigger");
 known_cuts.push_back("DoubleMuontrigger");
 known_cuts.push_back("EMutrigger");
 //known_cuts.push_back("EventFilter");
 //known_cuts.push_back("EventFlag_FailJetID");
 //known_cuts.push_back("EventFlag_JetInHEM");
 //known_cuts.push_back("EventFlag_JetInHEM_Pt20");
 //known_cuts.push_back("EventFlag_JetInHEM_Pt20_JetID");
 //known_cuts.push_back("HEM_Veto");

 //Add SF stuff to plot
 int color_SF = kBlack;
 string SF_Cut = "";
 for(int i = 0; i < int(cuts.size()); i++)
 { 
  for(int j = 0; j < int(known_cuts.size()); j++)
  {
   if(cuts[i].find("Njet_S") != std::string::npos) { extra_name = " Jets"; continue; }
   if(cuts[i].find("Bronze") != std::string::npos) { extra_name = " Quality"; continue; }
   if(cuts[i].find(known_cuts[j]) != std::string::npos) { continue; }
   if(cuts[i].find(SF_FinalState) != std::string::npos) { SF_Cut = cuts[i]; color_SF = colors[i]; }
  }
 }

 TGraphAsymmErrors* gr_bkg = get_gr(SF_Cut,bkg_tag,"METtrigger",can);
 TGraphAsymmErrors* gr_data = get_gr(SF_Cut,data_tag,"METtrigger",can);
 can->Clear();

 mg->Draw("A"); 
 can->Update();
 
 double x_min = mg->GetXaxis()->GetXmin();
 //double x_max = mg->GetXaxis()->GetXmax();
 double x_max = 500.;

 TF1* Bkg_Nominal = new TF1("Bkg_Nominal",Gaussian_CDF_Func,150.,500.,3);
 Bkg_Nominal->SetLineColor(kGreen);
 Bkg_Nominal->SetParameter(0,0.99);
 Bkg_Nominal->SetParameter(1,125.);
 Bkg_Nominal->SetParameter(2,40.);
 Bkg_Nominal->SetParName(0,"Norm_Gauss_CDF");
 Bkg_Nominal->SetParName(1,"Mean_Gauss_CDF");
 Bkg_Nominal->SetParName(2,"Sigma_Gauss_CDF");
 gr_bkg->Fit(Bkg_Nominal,"QEMS+0");

 TF1* Data_Nominal = new TF1("Data_Nominal",Gaussian_CDF_Func,150.,500.,3);
 Data_Nominal->SetLineColor(kAzure+10);
 Data_Nominal->SetParameter(0,0.99);
 Data_Nominal->SetParameter(1,125.);
 Data_Nominal->SetParameter(2,40.);
 Data_Nominal->SetParName(0,"Norm_Gauss_CDF");
 Data_Nominal->SetParName(1,"Mean_Gauss_CDF");
 Data_Nominal->SetParName(2,"Sigma_Gauss_CDF");
 gr_data->Fit(Data_Nominal,"QEMS+0");

 can->Clear();
 can->Update();
 TGraphErrors* gr_bands_ratio = NULL;
 TGraphErrors* gr_bands = NULL;
 TGraphAsymmErrors* res_ratio;
 res_ratio = TGAE_Ratio(gr_bkg,gr_data);

 vector<double> y_upper, y_lower;
 double a1, a2, b1, b2, c1, c2, HT;

 if(SF_Cut.find("HT-Le600") != std::string::npos) { HT = 550.; }
 else if(SF_Cut.find("HT-G600--HT-L750") != std::string::npos) { HT = 650.; }
 else if(SF_Cut.find("HT-Ge750") != std::string::npos) { HT = 800.; }

 int year = std::stoi(data_tag.substr(data_tag.find("_")+1));
 bool muon = false;
 if(data_tag.find("Muon") != std::string::npos) { muon = true; }

 Get_Bands_Ratio_Params(a1,a2,b1,b2,c1,c2,HT,year,muon);

 if(name.find("Bkg") != std::string::npos)
 {
  gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,y_upper,y_lower,Data_Nominal,Bkg_Nominal,a1,a2,b1,b2,c1,c2);
  gr_bands = Get_Bands(x_min,x_max,Bkg_Nominal,y_upper,y_lower); 
 }
 else 
 { 
  gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,y_upper,y_lower,Bkg_Nominal,Data_Nominal,a1,a2,b1,b2,c1,c2);
  gr_bands = Get_Bands(x_min,x_max,Data_Nominal,y_upper,y_lower); 
 }
 gr_bands_ratio->SetFillColor(color_SF+1);
 gr_bands_ratio->SetLineColor(color_SF+1);
 gr_bands_ratio->SetMarkerColor(color_SF+1);
 gr_bands_ratio->SetFillStyle(3003);
 gr_bands_ratio->SetMarkerSize(0);
 gr_bands->SetFillColor(color_SF+1);
 gr_bands->SetLineColor(color_SF+1);
 gr_bands->SetMarkerColor(color_SF+1);
 gr_bands->SetFillStyle(3003);
 gr_bands->SetMarkerSize(0);
 delete leg;
 delete mg;
 can->Clear();

 TLegend* leg_new = new TLegend(0.4,0.05,0.85,0.4); 
 leg_new->SetTextFont(132);
 leg_new->SetTextSize(0.033);
 leg_new->AddEntry(gr_bands,"Systematic Uncertainty From SF","F");

 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,0.32,1.,1.);
 pad_gr->SetGridx();
 pad_gr->SetGridy();
 pad_gr->SetBottomMargin(0.02);
 pad_gr->Draw();
 pad_gr->cd();
 pad_gr->Update();
 can->Update();

 TMultiGraph* mg_new = get_mg(cuts,tags,Triggers,inFile,colors,leg_new,can,option,SF_Cut);
 //mg_new->Draw("A"); 
 gr_bands->Draw("A3");
 can->Update();
 Format_Graph(gr_bands);
 gr_bands->GetXaxis()->SetTitle("MET [GeV]");
 gr_bands->GetYaxis()->SetTitle("Efficiency");
 gr_bands->SetTitle("");
 gr_bands->GetXaxis()->SetLimits(x_min,x_max);
 pad_gr->Modified();
 pad_gr->Update();
 can->Modified();
 can->Update();
 mg_new->Draw("P");
 can->Update();

 //leg->AddEntry(Data_Nominal,(data_tag+" Fit").c_str(),"L");
 //leg->AddEntry(Bkg_Nominal,(bkg_tag+" Fit").c_str(),"L");
 leg_new->Draw("SAME");
 can->Update();

 can->cd();
 TPad *pad_res = new TPad("pad_res","pad_res",0.,0.03,1.,0.31);
 pad_res->SetGridx(); 
 pad_res->SetGridy();
 pad_res->SetTopMargin(0.05);
 pad_res->SetBottomMargin(0.2);
 pad_res->Draw();
 pad_res->cd();
 pad_res->Update();
 can->Update();

 TMultiGraph* mg_ratio = get_mg_ratio(cuts,tags,Triggers,inFile,colors,SF_Cut,extra_name); 
 TGraphAsymmErrors* res_ratio_ratio = TGAE_Ratio(gr_bkg,gr_bkg);
 vector<double> y_upper_ratio, y_lower_ratio;
 TGraphErrors* gr_bands_ratio_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio_ratio,y_upper_ratio,y_lower_ratio,Bkg_Nominal,Bkg_Nominal,a1,a2,b1,b2,c1,c2);
 gr_bands_ratio_ratio->SetFillColor(color_SF+1);
 gr_bands_ratio_ratio->SetLineColor(color_SF+1);
 gr_bands_ratio_ratio->SetMarkerColor(color_SF+1);
 gr_bands_ratio_ratio->SetFillStyle(3003);
 gr_bands_ratio_ratio->SetMarkerSize(0);
 pad_res->cd();
 string mg_ratio_name = mg_ratio->GetName();
 mg_ratio->Draw("AP");
 mg_ratio->GetXaxis()->SetLimits(x_min,x_max);
 pad_res->Update();
 gr_bands_ratio_ratio->Draw("30");
 Format_Graph_res(mg_ratio);
 //Format_Graph_res(gr_bands_ratio);
 mg_ratio->SetTitle("");
 mg_ratio->GetXaxis()->SetTitle("MET [GeV]");
 mg_ratio->GetYaxis()->SetTitle("#frac{Final State}{Nominal}");
 pad_res->Modified();
 pad_res->Update();
 can->Modified();
 can->Update();
 can->Update();

 pad_gr->cd();
 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.06);
 l.SetTextFont(42);
 //eraseSubStr(name,states);
 
 name += "";
 string current_cut = cuts[0]+"--";
 known_cuts.clear();
 known_cuts.push_back("HT");
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
 UInt_t w, h;
 TText t;
 t.SetNDC();
 t.GetTextExtent(w,h,name.c_str());
 double x_latex = 1.0-w*0.001-0.05;
 l.DrawLatex(x_latex,0.93,name.c_str());
 l.DrawLatex(0.1,0.93,"#bf{#it{CMS}}  work-in-progress");
 pad_gr->Modified();
 pad_gr->Update();
 can->Modified();
 can->Update();
 string can_name = name+extra_name;
 std::replace(can_name.begin(), can_name.end(), ' ', '_');
 std::replace(can_name.begin(), can_name.end(), '>', 'G');
 std::replace(can_name.begin(), can_name.end(), '<', 'L');
 can_name.erase(std::remove(can_name.begin(), can_name.end(), '='), can_name.end());
 can_name.erase(std::remove(can_name.begin(), can_name.end(), '&'), can_name.end());
 if(name.find("Bkg") != std::string::npos)
 {
  if(data_tag.find("Electron") != std::string::npos) { can_name += "_Electron"; }
  if(data_tag.find("Muon") != std::string::npos) { can_name += "_Muon"; }
 }
 can->SetName((can_name).c_str());

 can->SaveAs((can_name+".pdf").c_str());
 TFile* output = TFile::Open("output_Plots.root","UPDATE");
 can->Write();
 output->Close();
 delete leg_new;
 delete mg_new;
 delete can;
 delete output;
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
 TCanvas* can = new TCanvas((name).c_str(),"",1278,775);
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

 string extra_name = "";
 vector<string> known_cuts;
 known_cuts.push_back("PTISR");
 known_cuts.push_back("PTCM");
 known_cuts.push_back("RISR");
 known_cuts.push_back("dphiCMI");
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
 known_cuts.push_back("DoubleElectrontrigger");
 known_cuts.push_back("DoubleMuontrigger");
 known_cuts.push_back("EMutrigger");
 //known_cuts.push_back("EventFilter");
 //known_cuts.push_back("EventFlag_FailJetID");
 //known_cuts.push_back("EventFlag_JetInHEM");
 //known_cuts.push_back("EventFlag_JetInHEM_Pt20");
 //known_cuts.push_back("EventFlag_JetInHEM_Pt20_JetID");
 //known_cuts.push_back("HEM_Veto");


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
 //eraseSubStr(name,states);
 
 name += "";
 string current_cut = cut[0]+"--";
 known_cuts.clear();
 known_cuts.push_back("HT");
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
 UInt_t w, h;
 TText t;
 t.SetNDC();
 t.GetTextExtent(w,h,name.c_str());
 double x_latex = 1.0-w*0.001+0.2;
 l.DrawLatex(x_latex,0.93,name.c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}}  work-in-progress");
 can->Modified();
 can->Update();
 string can_name = name+extra_name;
 std::replace(can_name.begin(), can_name.end(), ' ', '_');
 std::replace(can_name.begin(), can_name.end(), '>', 'G');
 std::replace(can_name.begin(), can_name.end(), '<', 'L');
 can_name.erase(std::remove(can_name.begin(), can_name.end(), '='), can_name.end());
 can_name.erase(std::remove(can_name.begin(), can_name.end(), '&'), can_name.end());
 can->SetName((can_name).c_str());

 can->SaveAs((can_name+".pdf").c_str());
 TFile* output = TFile::Open("output_Plots.root","UPDATE");
 can->Write();
 output->Close();
 //delete leg;
 //delete mg;
 delete can;
 delete output;
}

TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option, string SF_Cut)
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
     mg->SetTitle((title+gr->GetXaxis()->GetTitle()+" [GeV];"+gr->GetYaxis()->GetTitle()).c_str());
    }
    string new_cut = RewriteCut(cut.at(k));
    if(cut.at(k) == SF_Cut) { new_cut += "(Nominal)"; }
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

TMultiGraph* get_mg_ratio(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, string nominal, string name)
{
 TMultiGraph* mg = new TMultiGraph();
 TCanvas* can = new TCanvas(("dummy_can"+cut[0]+tags[0]+Triggers[0]+nominal+name).c_str(),"dummy_can",750,500);
 TGraphAsymmErrors* Nominal = get_gr(nominal,tags[0],Triggers[0],can);
 
 for(int k = 0; k < int(fname.size()); k++)
 {
  if(cut[k] == nominal) continue;
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
    TGraphAsymmErrors* gr_ratio = TGAE_Ratio(Nominal,gr);
    if((i+j) == 0)
    {
     string title = " ;";
     mg->SetTitle((title+gr->GetXaxis()->GetTitle()+" [GeV];"+gr->GetYaxis()->GetTitle()).c_str());
    }
    /*
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
    */
    gr_ratio->SetMarkerStyle(20);
    gr_ratio->SetMarkerColor(colors[i+j+k]);
    gr_ratio->SetLineColor(colors[i+j+k]);
    mg->Add(gr_ratio);
   }
  }
  f->Close();
  delete f;
 }
 return mg;
}

TGraphAsymmErrors* get_gr(string cut, string tag, string trigger, TCanvas*& can)
{
 TFile *f = TFile::Open(("Eff_output_"+cut+".root").c_str(), "READ");
 TDirectoryFile* folder = nullptr;
 f->GetObject(tag.c_str(),folder);
 TEfficiency* eff = nullptr;
 folder->GetObject(trigger.c_str(),eff);
 eff->Draw("AP");
 can->Update();
 TGraphAsymmErrors* gr = eff->GetPaintedGraph();
 return gr;
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
 if(found_cut.find("EMutrigger-E1") != std::string::npos)
 {
  cut =  " Passed Electron+Muon Trigger &";
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
 known_cuts.push_back("EMutrigger");

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
 string cutsFile = "";

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
 
 if(cutsFile != "")
 {
  vector<string> cuts;
  string cut = "";
  std::ifstream fs(cutsFile);
  while(std::getline(fs,cut))
  {
   if(cut.rfind("#", 0) == 0) continue;
   cuts.push_back(cut);
  }
  Plotter_Eff_Nano(cuts);
 }
 else
 {
  //Plot
  vector<string> cuts_1;
  cuts_1.push_back("HT-Le600--SingleElectrontrigger-E1--Nele-E1");
  //cuts_1.push_back("HT-Le600--Njet_S-E0");
  //cuts_1.push_back("HT-Le600--Njet_S-E1");
  //cuts_1.push_back("HT-Le600--Njet_S-Ge2");
  cuts_1.push_back("HT-Le600--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_1.push_back("HT-Le600--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_1.push_back("HT-Le600--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_1, false, true, true, true);
  //Plot
  vector<string> cuts_2;
  cuts_2.push_back("HT-Le600--SingleElectrontrigger-E1--Nele-E1");
  cuts_2.push_back("HT-Le600--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_2.push_back("HT-Le600--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_2.push_back("HT-Le600--SingleElectrontrigger-E1--NeleGold-E1");
  //cuts_2.push_back("HT-Le600--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_2.push_back("HT-Le600--DoubleElectrontrigger-E1--NeleE2");
  //cuts_2.push_back("HT-Le600--Nlep-E0");
  Plotter_Eff_Nano(cuts_2, false, true, true, true);
  //Plot
  vector<string> cuts_3;
  cuts_3.push_back("HT-Le600--SingleMuontrigger-E1--Nmu-E1");
  //cuts_3.push_back("HT-Le600--Njet_S-E0");
  //cuts_3.push_back("HT-Le600--Njet_S-E1");
  //cuts_3.push_back("HT-Le600--Njet_S-Ge2");
  cuts_3.push_back("HT-Le600--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_3.push_back("HT-Le600--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_3.push_back("HT-Le600--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_3, true, false, true, true);
  //Plot
  vector<string> cuts_4;
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--Nmu-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_4.push_back("HT-Le600--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_4.push_back("HT-Le600--DoubleMuontrigger-E1--NmuE2");
  //cuts_4.push_back("HT-Le600--Nlep-E0");
  Plotter_Eff_Nano(cuts_4, true, false, true, true);
  //Plot
  vector<string> cuts_5;
  cuts_5.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1");
  //cuts_5.push_back("HT-G600--HT-L750--Njet_S-E0");
  //cuts_5.push_back("HT-G600--HT-L750--Njet_S-E1");
  //cuts_5.push_back("HT-G600--HT-L750--Njet_S-Ge2");
  cuts_5.push_back("HT-G600--HT-L750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_5.push_back("HT-G600--HT-L750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_5.push_back("HT-G600--HT-L750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_5, false, true, true, true);
  //Plot
  vector<string> cuts_6;
  cuts_6.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1");
  cuts_6.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_6.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_6.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--NeleGold-E1");
  //cuts_6.push_back("HT-G600--HT-L750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_6.push_back("HT-G600--HT-L750--DoubleElectrontrigger-E1--NeleE2");
  //cuts_6.push_back("HT-G600--HT-L750--Nlep-E0");
  Plotter_Eff_Nano(cuts_6, false, true, true, true);
  //Plot
  vector<string> cuts_7;
  cuts_7.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1");
  //cuts_7.push_back("HT-G600--HT-L750--Njet_S-E0");
  //cuts_7.push_back("HT-G600--HT-L750--Njet_S-E1");
  //cuts_7.push_back("HT-G600--HT-L750--Njet_S-Ge2");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_7, true, false, true, true);
  //Plot
  vector<string> cuts_8;
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_8.push_back("HT-G600--HT-L750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_8.push_back("HT-G600--HT-L750--DoubleMuontrigger-E1--NmuE2");
  //cuts_8.push_back("HT-G600--HT-L750--Nlep-E0");
  Plotter_Eff_Nano(cuts_8, true, false, true, true);
  //Plot
  vector<string> cuts_9;
  cuts_9.push_back("HT-Ge750--SingleElectrontrigger-E1--Nele-E1");
  //cuts_9.push_back("HT-Ge750--Njet_S-E0");
  //cuts_9.push_back("HT-Ge750--Njet_S-E1");
  //cuts_9.push_back("HT-Ge750--Njet_S-Ge2");
  cuts_9.push_back("HT-Ge750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_9.push_back("HT-Ge750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_9.push_back("HT-Ge750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_9, false, true, true, true);
  //Plot
  vector<string> cuts_10;
  cuts_10.push_back("HT-Ge750--SingleElectrontrigger-E1--Nele-E1");
  cuts_10.push_back("HT-Ge750--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_10.push_back("HT-Ge750--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_10.push_back("HT-Ge750--SingleElectrontrigger-E1--NeleGold-E1");
  //cuts_10.push_back("HT-Ge750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_10.push_back("HT-Ge750--DoubleElectrontrigger-E1--NeleE2");
  //cuts_10.push_back("HT-Ge750--Nlep-E0");
  Plotter_Eff_Nano(cuts_10, false, true, true, true);
  //Plot
  vector<string> cuts_11;
  cuts_11.push_back("HT-Ge750--SingleMuontrigger-E1--Nmu-E1");
  //cuts_11.push_back("HT-Ge750--Njet_S-E0");
  //cuts_11.push_back("HT-Ge750--Njet_S-E1");
  //cuts_11.push_back("HT-Ge750--Njet_S-Ge2");
  cuts_11.push_back("HT-Ge750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_11.push_back("HT-Ge750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_11.push_back("HT-Ge750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_11, true, false, true, true);
  //Plot
  vector<string> cuts_12;
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--Nmu-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_12.push_back("HT-Ge750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_12.push_back("HT-Ge750--DoubleMuontrigger-E1--NmuE2");
  //cuts_12.push_back("HT-Ge750--Nlep-E0");
  Plotter_Eff_Nano(cuts_12, true, false, true, true);
 }

//muon electron data bkg
 return 0;
}
