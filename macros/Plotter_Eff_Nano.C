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
void Get_Plot_WithSF(vector<string> tags, string data_tag, string bkg_tag, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cuts, string SF_FinalState, string name, string option, bool HT_group = true);
TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option, string SF_Cut = "default", bool HT_group = true);
TMultiGraph* get_mg_ratio(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, string nominal, string name);
TGraphAsymmErrors* get_gr(string cut, string tag, string trigger, TCanvas*& can);

void Plotter_Eff_Nano(vector<string> cut, bool muon = false, bool data = false, bool bkg = false, bool HT_group = true, bool zero_lep = false){
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

 string muon_FS = "SingleMuontrigger-E1--Nmu-E1";
 string electron_FS = "SingleElectrontrigger-E1--Nele-E1";
 string zero_lep_FS = "Nlep-E0";

 if(muon && zero_lep) { cout << "Check booleans" << endl; return;}

 if(muon)
 {
  if(data)
  {
   Get_Plot_WithSF(tags_SingleMuon_2016,"SingleMuon_2016","Bkg_2016",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2016","FinalState",HT_group);
   Get_Plot_WithSF(tags_SingleMuon_2017,"SingleMuon_2017","Bkg_2017",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2017","FinalState",HT_group);
   Get_Plot_WithSF(tags_SingleMuon_2018,"SingleMuon_2018","Bkg_2018",METtrigger,colors,inFile,cut,muon_FS,"SingleMuon_2018","FinalState",HT_group);
  }
  if(bkg)
  {
   Get_Plot_WithSF(tags_bkg_2016,"SingleMuon_2016","Bkg_2016",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2016","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2017,"SingleMuon_2017","Bkg_2017",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2017","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2018,"SingleMuon_2018","Bkg_2018",METtrigger,colors,inFile,cut,muon_FS,"Bkg_2018","FinalState",HT_group);
  }
 }
 else if(zero_lep)
 {
  if(data) { cout << "Check booleans" << endl; return; }
  if(bkg)
  {
   Get_Plot_WithSF(tags_bkg_2016,"Bkg_2016","Bkg_2016",METtrigger,colors,inFile,cut,zero_lep_FS,"Bkg_2016","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2017,"Bkg_2017","Bkg_2017",METtrigger,colors,inFile,cut,zero_lep_FS,"Bkg_2017","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2018,"Bkg_2018","Bkg_2018",METtrigger,colors,inFile,cut,zero_lep_FS,"Bkg_2018","FinalState",HT_group);
  }
 }
 else
 {
  if(data)
  {
   Get_Plot_WithSF(tags_SingleElectron_2016,"SingleElectron_2016","Bkg_2016",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2016","FinalState",HT_group);
   Get_Plot_WithSF(tags_SingleElectron_2017,"SingleElectron_2017","Bkg_2017",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2017","FinalState",HT_group);
   Get_Plot_WithSF(tags_SingleElectron_2018,"SingleElectron_2018","Bkg_2018",METtrigger,colors,inFile,cut,electron_FS,"SingleElectron_2018","FinalState",HT_group);
  }
  if(bkg)
  {
   Get_Plot_WithSF(tags_bkg_2016,"SingleElectron_2016","Bkg_2016",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2016","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2017,"SingleElectron_2017","Bkg_2017",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2017","FinalState",HT_group);
   Get_Plot_WithSF(tags_bkg_2018,"SingleElectron_2018","Bkg_2018",METtrigger,colors,inFile,cut,electron_FS,"Bkg_2018","FinalState",HT_group);
  }
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

void Get_Plot_WithSF(vector<string> tags, string data_tag, string bkg_tag, vector<string> Triggers, vector<int> colors, vector<string> inFile, vector<string> cuts, string SF_FinalState, string name, string option, bool HT_group)
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
 //known_cuts.push_back("Nlep");
 if(HT_group) { known_cuts.push_back("Njet_S"); }
 else { known_cuts.push_back("HT"); }
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
   if(HT_group) { if(cuts[i].find("Njet_S") != std::string::npos) { extra_name = "Jets"; continue; } }
   else { if(cuts[i].find("HT") != std::string::npos) { extra_name = "HT"; continue; } }
   if(cuts[i].find("Bronze") != std::string::npos) { extra_name = "Quality"; continue; }
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
 double x_max = mg->GetXaxis()->GetXmax();
 //double x_max = 500.;

 double a1, a2, b1, b2, c1, c2, HT;

 if(SF_Cut.find("HT-Le600") != std::string::npos) { HT = 550.; }
 else if(SF_Cut.find("HT-G600--HT-L750") != std::string::npos) { HT = 650.; }
 else if(SF_Cut.find("HT-Ge750") != std::string::npos) { HT = 800.; }

 int year = std::stoi(data_tag.substr(data_tag.find("_")+1));
 bool muon = false;
 bool electron = false;
 if(data_tag.find("Muon") != std::string::npos) { muon = true; }
 else if(data_tag.find("Electron") != std::string::npos) { electron = true; }

 string CSV_name = SF_Cut+"_"+data_tag;
 if(muon) { CSV_name+="_Muon"; }
 else if(electron) { CSV_name+="_Electron"; }
 else { CSV_name+="_ZeroLepton"; }
 Get_Band_Params_CSV(CSV_name,a1,a2,b1,b2,c1,c2);

 /*
 Get_Bands_Ratio_Params(a1,a2,b1,b2,c1,c2,HT,year,muon,electron);
 TF1* Bkg_Nominal = Get_Func_Nominal(HT,year,muon,electron,false,x_min,x_max);
 TF1* Data_Nominal = Get_Func_Nominal(HT,year,muon,electron,true,x_min,x_max);
 gr_bkg->Fit(Bkg_Nominal,"QEMS+0");
 gr_data->Fit(Data_Nominal,"QEMS+0");
 */
 
 double bkg_norm, bkg_mean, bkg_sigma, bkg_scale, bkg_weight, data_norm, data_mean, data_sigma, data_scale, data_weight;
 Get_Fit_Params_CSV(CSV_name,data_norm,data_mean,data_sigma,data_scale,data_weight);
 CSV_name = SF_Cut+"_"+bkg_tag;
 if(muon) { CSV_name+="_Muon"; }
 else if(electron) { CSV_name+="_Electron"; }
 else { CSV_name+="_ZeroLepton"; }
 Get_Fit_Params_CSV(CSV_name,bkg_norm,bkg_mean,bkg_sigma,bkg_scale,bkg_weight);

 TF1* Bkg_Nominal;
 TF1* Data_Nominal;
 if(bkg_scale == 0 && bkg_weight == 0)
 {
  Bkg_Nominal = new TF1("Bkg_Nominal","[0]*ROOT::Math::normal_cdf(x,[2],[1])",x_min,x_max);
  Bkg_Nominal->SetParameters(bkg_norm,bkg_mean,bkg_sigma);
 }
 else
 {
  Bkg_Nominal = new TF1("Bkg_Nominal","[0]*((TMath::Cos([4])*TMath::Cos([4]))*ROOT::Math::normal_cdf(x,[2],[1])+(TMath::Sin([4])*TMath::Sin([4]))*ROOT::Math::normal_cdf(x,[2]*[3],[1]))",x_min,x_max);
  Bkg_Nominal->SetParameters(bkg_norm,bkg_mean,bkg_sigma,bkg_scale,bkg_weight);
 }
 if(data_scale == 0 && data_weight == 0)
 {
  Data_Nominal = new TF1("Data_Nominal","[0]*ROOT::Math::normal_cdf(x,[2],[1])",x_min,x_max);
  Data_Nominal->SetParameters(data_norm,data_mean,data_sigma);
 }
 else
 {
  Data_Nominal = new TF1("Data_Nominal","[0]*((TMath::Cos([4])*TMath::Cos([4]))*ROOT::Math::normal_cdf(x,[2],[1])+(TMath::Sin([4])*TMath::Sin([4]))*ROOT::Math::normal_cdf(x,[2]*[3],[1]))",x_min,x_max);
  Data_Nominal->SetParameters(data_norm,data_mean,data_sigma,data_scale,data_weight);
 }

 can->Clear();
 can->Update();
 TGraphErrors* gr_bands_ratio = NULL;
 TGraphErrors* gr_bands = NULL;
 TGraphAsymmErrors* res_ratio;
 res_ratio = TGAE_Ratio(gr_bkg,gr_data);

 if(name.find("Bkg") != std::string::npos)
 {
  gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,Data_Nominal,Bkg_Nominal,a1,a2,b1,b2,c1,c2);
  gr_bands = Get_Bands(x_min,x_max,Bkg_Nominal,int(gr_bkg->GetN()),a1,a2,b1,b2,c1,c2); 
 }
 else 
 { 
  gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,Bkg_Nominal,Data_Nominal,a1,a2,b1,b2,c1,c2);
  gr_bands = Get_Bands(x_min,x_max,Data_Nominal,int(gr_bkg->GetN()),a1,a2,b1,b2,c1,c2); 
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

 TMultiGraph* mg_new = get_mg(cuts,tags,Triggers,inFile,colors,leg_new,can,option,SF_Cut,HT_group);
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
 TGraphErrors* gr_bands_ratio_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio_ratio,Bkg_Nominal,Bkg_Nominal,a1,a2,b1,b2,c1,c2);
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
 
 name += "";
 string current_cut = cuts[0]+"--";
 known_cuts.clear();
 if(HT_group) { known_cuts.push_back("HT"); }
 else { known_cuts.push_back("Njet_S"); }
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

TMultiGraph* get_mg(vector<string> cut, vector<string> tags, vector<string> Triggers, vector<string> fname, vector<int> colors, TLegend*& leg, TCanvas*& can, string option, string SF_Cut, bool HT_group)
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
    string new_cut = RewriteCut(cut.at(k),HT_group);
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
    if(gr_ratio == NULL) { cout << "Couldn't get ratio for: " << cut[k] << "/" << nominal << endl; continue; }
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
  //cuts_2.push_back("HT-Le600--DoubleElectrontrigger-E1--Nele-E2");
  //cuts_2.push_back("HT-Le600--Nlep-E0");
  Plotter_Eff_Nano(cuts_2, false, true, true, true);
  //Plot
  vector<string> cuts_3;
  cuts_3.push_back("HT-Le600--SingleMuontrigger-E1--Nmu-E1");
  cuts_3.push_back("HT-Le600--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_3.push_back("HT-Le600--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_3.push_back("HT-Le600--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_3, true, true, true, true);
  //Plot
  vector<string> cuts_4;
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--Nmu-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_4.push_back("HT-Le600--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_4.push_back("HT-Le600--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_4.push_back("HT-Le600--DoubleMuontrigger-E1--Nmu-E2");
  //cuts_4.push_back("HT-Le600--Nlep-E0");
  Plotter_Eff_Nano(cuts_4, true, true, true, true);
  //Plot
  vector<string> cuts_5;
  cuts_5.push_back("HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1");
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
  //cuts_6.push_back("HT-G600--HT-L750--DoubleElectrontrigger-E1--Nele-E2");
  //cuts_6.push_back("HT-G600--HT-L750--Nlep-E0");
  Plotter_Eff_Nano(cuts_6, false, true, true, true);
  //Plot
  vector<string> cuts_7;
  cuts_7.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_7.push_back("HT-G600--HT-L750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_7, true, true, true, true);
  //Plot
  vector<string> cuts_8;
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_8.push_back("HT-G600--HT-L750--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_8.push_back("HT-G600--HT-L750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_8.push_back("HT-G600--HT-L750--DoubleMuontrigger-E1--Nmu-E2");
  //cuts_8.push_back("HT-G600--HT-L750--Nlep-E0");
  Plotter_Eff_Nano(cuts_8, true, true, true, true);
  //Plot
  vector<string> cuts_9;
  cuts_9.push_back("HT-Ge750--SingleElectrontrigger-E1--Nele-E1");
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
  //cuts_10.push_back("HT-Ge750--DoubleElectrontrigger-E1--Nele-E2");
  //cuts_10.push_back("HT-Ge750--Nlep-E0");
  Plotter_Eff_Nano(cuts_10, false, true, true, true);
  //Plot
  vector<string> cuts_11;
  cuts_11.push_back("HT-Ge750--SingleMuontrigger-E1--Nmu-E1");
  cuts_11.push_back("HT-Ge750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_11.push_back("HT-Ge750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_11.push_back("HT-Ge750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_11, true, true, true, true);
  //Plot
  vector<string> cuts_12;
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--Nmu-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_12.push_back("HT-Ge750--SingleMuontrigger-E1--NmuGold-E1");
  //cuts_12.push_back("HT-Ge750--EMutrigger-E1--Nmu-E1--Nele-E1");
  //cuts_12.push_back("HT-Ge750--DoubleMuontrigger-E1--Nmu-E2");
  //cuts_12.push_back("HT-Ge750--Nlep-E0");
  Plotter_Eff_Nano(cuts_12, true, true, true, true);
  /* 
  //Plot
  vector<string> cuts_13;
  cuts_13.push_back("Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_13.push_back("HT-Le600--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_13.push_back("HT-G600--HT-L750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_13.push_back("HT-Ge750--Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_13, false, true, true, false);
  //Plot
  vector<string> cuts_14;
  cuts_14.push_back("Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  cuts_14.push_back("Njet_S-E0--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_14.push_back("Njet_S-E0--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_14.push_back("Njet_S-E0--SingleElectrontrigger-E1--NeleGold-E1");
  Plotter_Eff_Nano(cuts_14, false, true, true, false);
  //Plot
  vector<string> cuts_15;
  cuts_15.push_back("Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_15.push_back("HT-Le600--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_15.push_back("HT-G600--HT-L750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_15.push_back("HT-Ge750--Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_15, true, true, true, false);
  //Plot
  vector<string> cuts_16;
  cuts_16.push_back("Njet_S-E0--SingleMuontrigger-E1--Nmu-E1");
  cuts_16.push_back("Njet_S-E0--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_16.push_back("Njet_S-E0--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_16.push_back("Njet_S-E0--SingleMuontrigger-E1--NmuGold-E1");
  Plotter_Eff_Nano(cuts_16, true, true, true, false);
  //Plot
  vector<string> cuts_17;
  cuts_17.push_back("Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_17.push_back("HT-Le600--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_17.push_back("HT-G600--HT-L750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_17.push_back("HT-Ge750--Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_17, false, true, true, false);
  //Plot
  vector<string> cuts_18;
  cuts_18.push_back("Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  cuts_18.push_back("Njet_S-E1--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_18.push_back("Njet_S-E1--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_18.push_back("Njet_S-E1--SingleElectrontrigger-E1--NeleGold-E1");
  Plotter_Eff_Nano(cuts_18, false, true, true, false);
  //Plot
  vector<string> cuts_19;
  cuts_19.push_back("Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_19.push_back("HT-Le600--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_19.push_back("HT-G600--HT-L750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_19.push_back("HT-Ge750--Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_19, true, true, true, false);
  //Plot
  vector<string> cuts_20;
  cuts_20.push_back("Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  cuts_20.push_back("Njet_S-E1--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_20.push_back("Njet_S-E1--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_20.push_back("Njet_S-E1--SingleMuontrigger-E1--NmuGold-E1");
  Plotter_Eff_Nano(cuts_20, true, true, true, false);
  //Plot
  vector<string> cuts_21;
  cuts_21.push_back("Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  cuts_21.push_back("HT-Le600--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  cuts_21.push_back("HT-G600--HT-L750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  cuts_21.push_back("HT-Ge750--Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  Plotter_Eff_Nano(cuts_21, false, true, true, false);
  //Plot
  vector<string> cuts_22;
  cuts_22.push_back("Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  cuts_22.push_back("Njet_S-Ge2--SingleElectrontrigger-E1--NeleBronze-E1");
  cuts_22.push_back("Njet_S-Ge2--SingleElectrontrigger-E1--NeleSilver-E1");
  cuts_22.push_back("Njet_S-Ge2--SingleElectrontrigger-E1--NeleGold-E1");
  Plotter_Eff_Nano(cuts_22, false, true, true, false);
  //Plot
  vector<string> cuts_23;
  cuts_23.push_back("Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  cuts_23.push_back("HT-Le600--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  cuts_23.push_back("HT-G600--HT-L750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  cuts_23.push_back("HT-Ge750--Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  Plotter_Eff_Nano(cuts_23, true, true, true, false);
  //Plot
  vector<string> cuts_24;
  cuts_24.push_back("Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  cuts_24.push_back("Njet_S-Ge2--SingleMuontrigger-E1--NmuBronze-E1");
  cuts_24.push_back("Njet_S-Ge2--SingleMuontrigger-E1--NmuSilver-E1");
  cuts_24.push_back("Njet_S-Ge2--SingleMuontrigger-E1--NmuGold-E1");
  Plotter_Eff_Nano(cuts_24, true, true, true, false);
  */
  //Plot
  vector<string> cuts_25;
  cuts_25.push_back("HT-Le600--Nlep-E0");
  //cuts_25.push_back("HT-Le600--Njet_S-E0--Nlep-E0");
  cuts_25.push_back("HT-Le600--Njet_S-E1--Nlep-E0");
  cuts_25.push_back("HT-Le600--Njet_S-Ge2--Nlep-E0");
  Plotter_Eff_Nano(cuts_25, false, false, true, true, true);
  //Plot
  vector<string> cuts_26;
  cuts_26.push_back("HT-G600--HT-L750--Nlep-E0");
  //cuts_26.push_back("HT-G600--HT-L750--Njet_S-E0--Nlep-E0");
  cuts_26.push_back("HT-G600--HT-L750--Njet_S-E1--Nlep-E0");
  cuts_26.push_back("HT-G600--HT-L750--Njet_S-Ge2--Nlep-E0");
  Plotter_Eff_Nano(cuts_26, false, false, true, true, true);
  //Plot
  vector<string> cuts_27;
  cuts_27.push_back("HT-Ge750--Nlep-E0");
  //cuts_27.push_back("HT-Ge750--Njet_S-E0--Nlep-E0");
  cuts_27.push_back("HT-Ge750--Njet_S-E1--Nlep-E0");
  cuts_27.push_back("HT-Ge750--Njet_S-Ge2--Nlep-E0");
  Plotter_Eff_Nano(cuts_27, false, false, true, true, true);
  //Plot
  //vector<string> cuts_28;
  //cuts_28.push_back("Njet_S-E0--Nlep-E0");
  //cuts_28.push_back("HT-Le600--Njet_S-E0--Nlep-E0");
  //cuts_28.push_back("HT-G600--HT-L750--Njet_S-E0--Nlep-E0");
  //cuts_28.push_back("HT-Ge750--Njet_S-E0--Nlep-E0");
  //Plotter_Eff_Nano(cuts_28, false, false, true, false, true);
  //Plot
  vector<string> cuts_29;
  cuts_29.push_back("Njet_S-E1--Nlep-E0");
  cuts_29.push_back("HT-Le600--Njet_S-E1--Nlep-E0");
  cuts_29.push_back("HT-G600--HT-L750--Njet_S-E1--Nlep-E0");
  cuts_29.push_back("HT-Ge750--Njet_S-E1--Nlep-E0");
  Plotter_Eff_Nano(cuts_29, false, false, true, false, true);
  //Plot
  vector<string> cuts_30;
  cuts_30.push_back("Njet_S-Ge2--Nlep-E0");
  cuts_30.push_back("HT-Le600--Njet_S-Ge2--Nlep-E0");
  cuts_30.push_back("HT-G600--HT-L750--Njet_S-Ge2--Nlep-E0");
  cuts_30.push_back("HT-Ge750--Njet_S-Ge2--Nlep-E0");
  Plotter_Eff_Nano(cuts_30, false, false, true, false, true);
 }

 return 0;
}
