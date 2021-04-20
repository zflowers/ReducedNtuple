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
#include <TLine.h>
#include <TEfficiency.h>
#include <TMinuit.h>
#include <Math/ProbFunc.h>
#include "Fitter_Eff_Nano.C"

using namespace std;

double Get_ScaleFactor(string bkg_tag, string data_tag, string Trigger, vector<int> colors, string outFile, string cut, string option);
TGraphAsymmErrors* get_gr(string fname, string tag, string Trigger, int color, TLegend*& leg, TCanvas*& can);

void ScaleFactors(vector<string> cut){

 vector<string> inFile;
 for(int i = 0; i < cut.size(); i++) { inFile.push_back("Eff_output_"+cut[i]+".root"); }

 //string inFile ="output_quick.root";
 vector<string> data_tags_2016 = {"SingleElectron_2016","SingleMuon_2016"};
 vector<string> data_tags_2017 = {"SingleElectron_2017","SingleMuon_2017"};
 vector<string> data_tags_2018 = {"SingleElectron_2018","SingleMuon_2018"};
 
 //vector<int> colors = {kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};
 vector<int> colors = {kGreen+2, kAzure-2, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};

 for(int i = 0; i < inFile.size(); i++)
 {
  for(int j = 0; j < int(data_tags_2017.size()); j++)
  {
   double scale_Ratio_2016 = Get_ScaleFactor("Bkg_2016", data_tags_2016[j], "METtrigger", colors, inFile[i], cut[i], "Ratio");
   if(scale_Ratio_2016 == -1) cout << "Failed to get SF for: " << data_tags_2016[j] << " " << cut[i] << endl;
   double scale_Ratio_2017 = Get_ScaleFactor("Bkg_2017", data_tags_2017[j], "METtrigger", colors, inFile[i], cut[i], "Ratio");
   if(scale_Ratio_2017 == -1) cout << "Failed to get SF for: " << data_tags_2017[j] << " " << cut[i] << endl;
   double scale_Ratio_2018 = Get_ScaleFactor("Bkg_2018", data_tags_2018[j], "METtrigger", colors, inFile[i], cut[i], "Ratio");
   if(scale_Ratio_2018 == -1) cout << "Failed to get SF for: " << data_tags_2018[j] << " " << cut[i] << endl;
  }
 }
}

void Get_Values(string cut, bool muon = false, bool data = false, bool bkg = false, bool HT_group = true, bool zero_lep = false){
 
 string muon_FS = "SingleMuontrigger-E1--Nmu-E1";
 string electron_FS = "SingleElectrontrigger-E1--Nele-E1";
 string zero_lep_FS = "Nlep-E0";

 if(muon && zero_lep) { cout << "Check booleans (leptons)" << endl; return; }

 if(HT_group)
 {
  double HT;
  if(cut.find("HT-Le600") != std::string::npos) { HT = 550.; }
  else if(cut.find("HT-G600--HT-L750") != std::string::npos) { HT = 650.; }
  else if(cut.find("HT-Ge750") != std::string::npos) { HT = 800.; }
 
  if(muon)
  {
   if(data)
   {
    Output_Parameters(HT,2016,true,false,true,cut,"SingleMuon_2016");
    Output_Parameters(HT,2017,true,false,true,cut,"SingleMuon_2017");
    Output_Parameters(HT,2018,true,false,true,cut,"SingleMuon_2018");
   }
   if(bkg)
   {
    Output_Parameters(HT,2016,true,false,false,cut,"Bkg_2016");
    Output_Parameters(HT,2017,true,false,false,cut,"Bkg_2017");
    Output_Parameters(HT,2018,true,false,false,cut,"Bkg_2018");
   }
  }
  else if(zero_lep)
  {
   if(data) { cout << "Check booleans" << endl; return; }
   if(bkg)
   {
    Output_Parameters(HT,2016,false,false,false,cut,"Bkg_2016");
    Output_Parameters(HT,2017,false,false,false,cut,"Bkg_2017");
    Output_Parameters(HT,2018,false,false,false,cut,"Bkg_2018");
   }
  }
  else
  {
   if(data)
   {
    Output_Parameters(HT,2016,false,true,true,cut,"SingleElectron_2016");
    Output_Parameters(HT,2017,false,true,true,cut,"SingleElectron_2017");
    Output_Parameters(HT,2018,false,true,true,cut,"SingleElectron_2018");
   }
   if(bkg)
   {
    Output_Parameters(HT,2016,false,true,false,cut,"Bkg_2016");
    Output_Parameters(HT,2017,false,true,false,cut,"Bkg_2017");
    Output_Parameters(HT,2018,false,true,false,cut,"Bkg_2018");
   }
  }
 }
}



//get all SF plot
double Get_ScaleFactor(string bkg_tag, string data_tag, string Trigger, vector<int> colors, string outFile, string cut, string option)
{
 double scale = 0;
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }

 TLegend* leg = new TLegend(0.6,0.3,0.85,0.6); 
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 
 string name = "METtrigger_"+cut+"_"+data_tag;
 TLatex l;
 TCanvas* can = new TCanvas((name).c_str(),"",864.,468.);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 if(invert_colors) can->SetFillColor(kBlack);
 can->Modified();
 can->Update();
 TMultiGraph* mg = new TMultiGraph();
 TGraphAsymmErrors* gr_bkg = get_gr(outFile,bkg_tag,Trigger,colors[0],leg,can);
 Format_Graph(gr_bkg);
 mg->Add(gr_bkg);
 TGraphAsymmErrors* gr_data = get_gr(outFile,data_tag,Trigger,colors[1],leg,can);
 Format_Graph(gr_data);
 mg->Add(gr_data);
 can->Clear();
 can->cd();

 mg->Draw("A"); 
 Format_Graph(mg);
 //pad_gr->Update();
 //pad_gr->Modified();
 can->Update();
 
 double x_min = mg->GetXaxis()->GetXmin();
 double x_max = mg->GetXaxis()->GetXmax();

 if(invert_colors)
 {
  //pad_gr->SetFillColor(kBlack);
  leg->SetTextColor(kWhite);
  leg->SetFillColor(kBlack);
  leg->SetLineColor(kBlack);
  leg->SetShadowColor(kBlack); 
  l.SetTextColor(kWhite);
 }

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

//This is where we evaluate scale factors (Ratio or Fit)
 TPad *pad_res = new TPad("pad_res","pad_res",0,0.03,1,0.31);
 pad_res->SetGridx(); 
 pad_res->SetGridy();
 pad_res->SetTopMargin(0.);
 pad_res->SetBottomMargin(0.2);
 pad_res->Draw();
 pad_res->cd();
 pad_res->Update();
 can->Update();
 if(invert_colors) pad_res->SetFillColor(kBlack);
 bool empty_mg = true;
 TMultiGraph* mg_res = new TMultiGraph();
 TGraphErrors* gr_bands_ratio = NULL;
 TGraphAsymmErrors* res_ratio;
 res_ratio = TGAE_Ratio(gr_bkg,gr_data);
 if(res_ratio == NULL) return -1;
 res_ratio->SetMarkerColor(colors[1]);
 res_ratio->SetLineColor(colors[1]);
 res_ratio->SetMarkerStyle(20);
 mg_res->Add(res_ratio);

 double a1, a2, b1, b2, c1, c2, HT;
 if(cut.find("HT-Le600") != std::string::npos) { HT = 550.; }
 else if(cut.find("HT-G600--HT-L750") != std::string::npos) { HT = 650.; }
 else if(cut.find("HT-Ge750") != std::string::npos) { HT = 800.; }

 int year = std::stoi(data_tag.substr(data_tag.find("_")+1));
 bool muon = false;
 bool electron = false;
 bool data = false;
 if(data_tag.find("Muon") != std::string::npos) { muon = true; data = true; }
 else if(data_tag.find("Electron") != std::string::npos) { electron = true; data = true; }

 Get_Bands_Ratio_Params(a1,a2,b1,b2,c1,c2,HT,year,muon,electron,data);

 gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,Bkg_Nominal,Data_Nominal,a1,a2,b1,b2,c1,c2);
 gr_bands_ratio->SetFillColor(kCyan+2);
 gr_bands_ratio->SetFillStyle(3003);
 gr_bands_ratio->SetMarkerSize(0);
 res_ratio->SetName("gr_res_ratio");
 res_ratio->SetMarkerSize(1.1);
 TGraph* Fit_Ratio = Get_Fit_Ratio(x_min,x_max,Bkg_Nominal, Data_Nominal);
 Fit_Ratio->SetLineColor(kAzure+10);
 mg_res->Add(Fit_Ratio);
 mg_res->Draw("AP");
 Format_Graph_res(mg_res);
 mg_res->GetXaxis()->SetLimits(x_min,x_max);
 mg_res->GetYaxis()->SetTitle("Data/MC Bkg");
 mg_res->GetXaxis()->SetTitle("MET [GeV]");
 pad_res->Modified();
 pad_res->Update();
 TLine* line = new TLine(mg_res->GetXaxis()->GetXmin(),0.0,mg_res->GetXaxis()->GetXmax(),0.0);
 line->SetLineColor(kWhite);
 line->SetLineStyle(1);
 //line->Draw("SAMES");
 gr_bands_ratio->Draw("30");
 Fit_Ratio->Draw("C");
 res_ratio->Draw("P");
 pad_res->Modified();
 pad_res->Update();
 can->Modified();
 can->Update();

 can->cd();
 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,0.35,1.,1.);
 pad_gr->SetGridx();
 pad_gr->SetGridy();
 pad_gr->SetBottomMargin(0.02);
 pad_gr->Draw();
 pad_gr->cd();
 can->Update();

 TGraphErrors* gr_bands = Get_Bands(x_min,x_max,Data_Nominal,gr_bands_ratio->GetN(),a1,a2,b1,b2,c1,c2);
 gr_bands->SetFillColor(kCyan+2);
 gr_bands->SetFillStyle(3003);
 gr_bands->SetMarkerSize(0);
 //TMultiGraph* mg_new = new TMultiGraph();
 //mg_new->Add(gr_bkg);
 //mg_new->Add(gr_data);
 //mg_new->Add(gr_bands);

 pad_gr->cd();
 pad_gr->Clear();
 //mg_new->Draw("A"); 
 //Format_Graph(mg_new);
 //mg_new->GetXaxis()->SetLimits(x_min,x_max);
 pad_gr->Update();
 pad_gr->Modified();
 can->Update();
 //mg_new->GetYaxis()->SetTitle("Efficiency");
 gr_bands->Draw("A3");
 Data_Nominal->Draw("SAME");
 Bkg_Nominal->Draw("SAME");
 Format_Graph(gr_bands);
 gr_bands->SetTitle("");
 gr_bands->GetXaxis()->SetLimits(x_min,x_max);
 gr_bands->GetYaxis()->SetTitle("Efficiency");
 gr_bkg->Draw("P");
 gr_data->Draw("P");
 pad_gr->Modified();
 pad_gr->Update();
 can->Modified();
 can->Update();

 leg->AddEntry(gr_bands,"Systematic Uncertainty","F");
 leg->AddEntry(Data_Nominal,(data_tag+" Fit").c_str(),"L");
 leg->AddEntry(Bkg_Nominal,(bkg_tag+" Fit").c_str(),"L");
 leg->Draw("SAME");
 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.06);
 l.SetTextFont(42);
 double eps = 0.0015;
 double hhi = 0.1;
 UInt_t w, h;
 TText t;
 t.SetNDC();
 t.GetTextExtent(w,h,cut.c_str());
 double x_latex = 1.-.1-w*eps;
 l.DrawLatex(x_latex,0.93,cut.c_str());
 l.DrawLatex(.1,0.93,"#bf{#it{CMS}} Preliminary");
 pad_gr->Update();
 can->Update();
 can->cd();


/*
 if(option.compare("Ratio") == 0)
 {
  
 }
 else if(option.compare("Fit") == 0)
 {

 }
*/




//Save stuff
 //TFile* output = TFile::Open(outFile.c_str(),"UPDATE");
 TFile* output = TFile::Open("output_Scale.root","UPDATE");
 can->Write();
 output->Close();
 delete leg;
 delete mg;
 delete can;
 delete output;


//Return scale factor
return scale;




}

TGraphAsymmErrors* get_gr(string fname, string tag, string Trigger, int color, TLegend*& leg, TCanvas*& can)
{
 TGraphAsymmErrors* gr;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return gr;
 }
 TDirectoryFile* folder = nullptr;
 f->GetObject(tag.c_str(),folder);
 folder->cd();
 TEfficiency* eff = nullptr;
 folder->GetObject(Trigger.c_str(),eff);
 eff->Draw("AP");
 can->Update();
 gr = eff->GetPaintedGraph();
 string title = " ;";
 gr->SetTitle((title+gr->GetXaxis()->GetTitle()+";"+gr->GetYaxis()->GetTitle()).c_str());
 if(tag.find("Bkg") != std::string::npos) { leg->AddEntry(gr,"MC Bkg","PL"); }
 else if(tag.find("SingleMuon") != std::string::npos) { leg->AddEntry(gr,"SingleMuon","PL"); }
 else { leg->AddEntry(gr,tag.c_str(),"PL"); }
 gr->SetMarkerStyle(20);
 gr->SetMarkerColor(color);
 gr->SetLineColor(color);
 f->Close();
 delete f;
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
  ScaleFactors(cuts);
 }
 else
 {
  if(fileExists("Parameters.csv")) { remove("Parameters.csv"); }
  Get_Values("HT-Le600--SingleElectrontrigger-E1--Nele-E1",false,true,false,true,false);
  Get_Values("HT-Le600--SingleElectrontrigger-E1--Nele-E1",false,false,true,true,false);
  Get_Values("HT-Le600--SingleMuontrigger-E1--Nmu-E1",true,true,false,true,false);
  Get_Values("HT-Le600--SingleMuontrigger-E1--Nmu-E1",true,false,true,true,false);
  Get_Values("HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",false,true,false,true,false);
  Get_Values("HT-G600--HT-L750--SingleElectrontrigger-E1--Nele-E1",false,false,true,true,false);
  Get_Values("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",true,true,false,true,false);
  Get_Values("HT-G600--HT-L750--SingleMuontrigger-E1--Nmu-E1",true,false,true,true,false);
  Get_Values("HT-Ge750--SingleElectrontrigger-E1--Nele-E1",false,true,false,true,false);
  Get_Values("HT-Ge750--SingleElectrontrigger-E1--Nele-E1",false,false,true,true,false);
  Get_Values("HT-Ge750--SingleMuontrigger-E1--Nmu-E1",true,true,false,true,false);
  Get_Values("HT-Ge750--SingleMuontrigger-E1--Nmu-E1",true,false,true,true,false);
  Get_Values("Njet_S-E0--SingleElectrontrigger-E1--Nele-E1");
  Get_Values("HT-Le600--Nlep-E0",false,false,true,true,true);
  Get_Values("HT-G600--HT-L750--Nlep-E0",false,false,true,true,true);
  Get_Values("HT-Ge750--Nlep-E0",false,false,true,true,true);
  //Get_Values("Njet_S-E0--SingleMuontrigger-E1--Nmu-E1",true,true,false,false,false);
  //Get_Values("Njet_S-E1--SingleElectrontrigger-E1--Nele-E1");
  //Get_Values("Njet_S-E1--SingleMuontrigger-E1--Nmu-E1");
  //Get_Values("Njet_S-Ge2--SingleElectrontrigger-E1--Nele-E1");
  //Get_Values("Njet_S-Ge2--SingleMuontrigger-E1--Nmu-E1");
  //Get_Values("Njet_S-E0--Nlep-E0");
  //Get_Values("Njet_S-E1--Nlep-E0");
  //Get_Values("Njet_S-Ge2--Nlep-E0");
 }

 return 0;
}
