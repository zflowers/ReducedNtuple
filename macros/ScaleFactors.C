#include <TFile.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <TTree.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
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

using namespace std;

bool invert_colors = false;

double Get_ScaleFactor(string bkg_tag, vector<string> data_tags, string Trigger, vector<int> colors, string outFile, string name, string option);
TGraphErrors* Get_Bands_Ratio(double x_min, double x_max, TGraphAsymmErrors* gr, vector<double>& y_upper, vector<double>& y_lower, TF1* Bkg_Nominal, TF1* Data_Nominal);
TGraphErrors* Get_Bands(double x_min, double x_max, TF1* Data_Nominal, vector<double>& y_upper, vector<double>& y_lower);
TGraph* Get_Fit_Ratio(double x_min, double x_max, TF1* Bkg_Nominal, TF1* Data_Nominal);
TGraphAsymmErrors* get_gr(string fname, string tag, string Trigger, int color, TLegend*& leg, TCanvas*& can);
TGraphAsymmErrors* TGAE_Ratio(TGraphAsymmErrors* gr_bkg, TGraphAsymmErrors* gr_data);

Double_t Gaussian_CDF_Func(Double_t *x, Double_t *par)
{
 return par[0]*ROOT::Math::normal_cdf(x[0],par[2],par[1]);
}

void ScaleFactors(vector<string> inFile, vector<string> cut){

 //string inFile ="output_quick.root";
 vector<string> data_tags_2016 = {"SingleElectron_2016","SingleMuon_2016"};
 //vector<string> data_tags_2017 = {"SingleElectron_2017","SingleMuon_2017","DoubleEG_2017","DoubleMuon_2017"};
 vector<string> data_tags_2017 = {"SingleMuon_2017"};
 vector<string> data_tags_2018 = {"SingleElectron_2018","SingleMuon_2018"};
 
 //vector<int> colors = {kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};
 vector<int> colors = {kGreen+2, kAzure-2, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};

 for(int i = 0; i < inFile.size(); i++)
 {
  //double scale_Ratio_2016 = Get_ScaleFactor("Bkg_2016", data_tags_2016, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2016", "Ratio");
  //double scale_Fit_2016 = Get_ScaleFactor("Bkg_2016", data_tags_2016, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2016", "Fit");
  double scale_Ratio_2017 = Get_ScaleFactor("Bkg_2017", data_tags_2017, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2017", "Ratio");
  //double scale_Fit_2017 = Get_ScaleFactor("Bkg_2017", data_tags_2017, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2017", "Fit");
  //double scale_Ratio_2018 = Get_ScaleFactor("Bkg_2018", data_tags_2018, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2018", "Ratio");
  //double scale_Fit_2018 = Get_ScaleFactor("Bkg_2018", data_tags_2018, "METtrigger", colors, inFile[i], "METtrigger"+cut[i]+"_2018", "Fit");
 }
}

void Format_Graph(TMultiGraph*& gr)
{
 gr->GetXaxis()->CenterTitle(true);
 gr->GetXaxis()->SetTitleFont(132);
 gr->GetXaxis()->SetTitleSize(0.06);
 gr->GetXaxis()->SetTitleOffset(1.06);
 gr->GetXaxis()->SetLabelFont(132);
 gr->GetXaxis()->SetLabelSize(0.0);
 gr->GetYaxis()->CenterTitle(true);
 gr->GetYaxis()->SetTitleFont(132);
 gr->GetYaxis()->SetTitleSize(0.06);
 gr->GetYaxis()->SetTitleOffset(.6);
 gr->GetYaxis()->SetLabelFont(132);
 gr->GetYaxis()->SetLabelSize(0.05);

 if(invert_colors)
 {
  gr->GetXaxis()->SetAxisColor(kWhite);
  gr->GetYaxis()->SetAxisColor(kWhite);
  gr->GetXaxis()->SetTitleColor(kWhite);
  gr->GetYaxis()->SetTitleColor(kWhite);
  gr->GetXaxis()->SetLabelColor(kWhite);
  gr->GetYaxis()->SetLabelColor(kWhite);
 }
}

void Format_Graph_res(TMultiGraph*& gr)
{
  gr->GetXaxis()->CenterTitle(true);
  gr->GetXaxis()->SetTitleFont(132);
  gr->GetXaxis()->SetTitleSize(0.13);
  gr->GetXaxis()->SetTitleOffset(.71);
  gr->GetXaxis()->SetLabelFont(132);
  gr->GetXaxis()->SetLabelSize(0.11);
  gr->GetYaxis()->CenterTitle(true);
  gr->GetYaxis()->SetTitleFont(132);
  gr->GetYaxis()->SetTitleSize(0.13);
  gr->GetYaxis()->SetTitleOffset(.29);
  gr->GetYaxis()->SetLabelFont(132);
  gr->GetYaxis()->SetLabelSize(0.11);

  if(invert_colors)
  {
   gr->GetXaxis()->SetAxisColor(kWhite);
   gr->GetYaxis()->SetAxisColor(kWhite);
   gr->GetXaxis()->SetTitleColor(kWhite);
   gr->GetYaxis()->SetTitleColor(kWhite);
   gr->GetXaxis()->SetLabelColor(kWhite);
   gr->GetYaxis()->SetLabelColor(kWhite);
  }
}

void Format_Graph(TGraphAsymmErrors*& gr)
{
 gr->GetXaxis()->CenterTitle(true);
 gr->GetXaxis()->SetTitleFont(132);
 gr->GetXaxis()->SetTitleSize(0.06);
 gr->GetXaxis()->SetTitleOffset(1.06);
 gr->GetXaxis()->SetLabelFont(132);
 gr->GetXaxis()->SetLabelSize(0.0);
 //gr->GetXaxis()->SetLabelSize(0.00000001);
 gr->GetYaxis()->CenterTitle(true);
 gr->GetYaxis()->SetTitleFont(132);
 gr->GetYaxis()->SetTitleSize(0.06);
 gr->GetYaxis()->SetTitleOffset(.6);
 gr->GetYaxis()->SetLabelFont(132);
 gr->GetYaxis()->SetLabelSize(0.05);

 if(invert_colors)
 {
  gr->GetXaxis()->SetAxisColor(kWhite);
  gr->GetYaxis()->SetAxisColor(kWhite);
  gr->GetXaxis()->SetTitleColor(kWhite);
  gr->GetYaxis()->SetTitleColor(kWhite);
  gr->GetXaxis()->SetLabelColor(kWhite);
  gr->GetYaxis()->SetLabelColor(kWhite);
 }
}

void Format_Graph(TGraphErrors*& gr)
{
 gr->GetXaxis()->CenterTitle(true);
 gr->GetXaxis()->SetTitleFont(132);
 gr->GetXaxis()->SetTitleSize(0.06);
 gr->GetXaxis()->SetTitleOffset(1.06);
 gr->GetXaxis()->SetLabelFont(132);
 gr->GetXaxis()->SetLabelSize(0.0);
 //gr->GetXaxis()->SetLabelSize(0.00000001);
 gr->GetYaxis()->CenterTitle(true);
 gr->GetYaxis()->SetTitleFont(132);
 gr->GetYaxis()->SetTitleSize(0.06);
 gr->GetYaxis()->SetTitleOffset(.6);
 gr->GetYaxis()->SetLabelFont(132);
 gr->GetYaxis()->SetLabelSize(0.05);

 if(invert_colors)
 {
  gr->GetXaxis()->SetAxisColor(kWhite);
  gr->GetYaxis()->SetAxisColor(kWhite);
  gr->GetXaxis()->SetTitleColor(kWhite);
  gr->GetYaxis()->SetTitleColor(kWhite);
  gr->GetXaxis()->SetLabelColor(kWhite);
  gr->GetYaxis()->SetLabelColor(kWhite);
 }
}

//get all Eff on one plot
double Get_ScaleFactor(string bkg_tag, vector<string> data_tags, string Trigger, vector<int> colors, string outFile, string name, string option)
{
 double scale = 0;
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }

 TLegend* leg = new TLegend(0.65,0.3,0.85,0.6); 
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 
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
 vector<TGraphAsymmErrors*> vect_gr_data;
 for(int i = 0; i < data_tags.size(); i++)
 {
  TGraphAsymmErrors* gr_data = get_gr(outFile,data_tags[i],Trigger,colors[i+1],leg,can);
  Format_Graph(gr_data);
  vect_gr_data.push_back(gr_data);
  mg->Add(gr_data);
 }
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
 gr_bkg->Fit(Bkg_Nominal,"EMS+0");

 TF1* Data_Nominal = new TF1("Data_Nominal",Gaussian_CDF_Func,150.,500.,3);
 Data_Nominal->SetLineColor(kAzure+10);
 Data_Nominal->SetParameter(0,0.99);
 Data_Nominal->SetParameter(1,125.);
 Data_Nominal->SetParameter(2,40.);
 Data_Nominal->SetParName(0,"Norm_Gauss_CDF");
 Data_Nominal->SetParName(1,"Mean_Gauss_CDF");
 Data_Nominal->SetParName(2,"Sigma_Gauss_CDF");
 vect_gr_data[0]->Fit(Data_Nominal,"EMS+0");

 can->Clear();


//This is where we evaluate scale factors (Ratio or Fit)
 TPad *pad_res = new TPad("pad_res","pad_res",0,0.03,1,0.3);
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
 for(int i = 0; i < data_tags.size(); i++)
 {
  res_ratio = TGAE_Ratio(gr_bkg,vect_gr_data[i]);
  if(res_ratio == NULL) continue;
  res_ratio->SetMarkerColor(colors[i+1]);
  res_ratio->SetLineColor(colors[i+1]);
  res_ratio->SetMarkerStyle(20);
  mg_res->Add(res_ratio);
  empty_mg = false;
 }
 if(empty_mg)
 {
  delete leg;
  delete mg;
  delete can;
  return -1.;
 }
 vector<double> y_upper, y_lower;
 gr_bands_ratio = Get_Bands_Ratio(x_min,x_max,res_ratio,y_upper,y_lower,Bkg_Nominal,Data_Nominal);
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
 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,.3,1.,1.);
 pad_gr->SetGridx();
 pad_gr->SetGridy();
 pad_gr->Draw();
 pad_gr->cd();
 can->Update();

 TGraphErrors* gr_bands = Get_Bands(x_min,x_max,Data_Nominal,y_upper,y_lower);
 gr_bands->SetFillColor(kCyan+2);
 gr_bands->SetFillStyle(3003);
 gr_bands->SetMarkerSize(0);
 //TMultiGraph* mg_new = new TMultiGraph();
 //mg_new->Add(gr_bkg);
 //mg_new->Add(vect_gr_data[0]);
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
 vect_gr_data[0]->Draw("P");
 pad_gr->Modified();
 pad_gr->Update();
 can->Modified();
 can->Update();

 leg->AddEntry(gr_bands,"Systematic Uncertainty","F");
 leg->AddEntry(Data_Nominal,"SingleMuon Fit","L");
 leg->AddEntry(Bkg_Nominal,"MC Bkg Fit","L");
 leg->Draw("SAME");
 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.06);
 l.SetTextFont(42);
 //l.DrawLatex(0.65,0.93,name.c_str());
 l.DrawLatex(0.1,0.93,"#bf{#it{CMS}} Preliminary");
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
 TFile* output = TFile::Open(outFile.c_str(),"UPDATE");
 can->Write();
 output->Close();
 delete leg;
 delete mg;
 delete can;
 delete output;


//Return scale factor
return scale;




}

TGraphErrors* Get_Bands_Ratio(double x_min, double x_max, TGraphAsymmErrors* gr, vector<double>& y_upper, vector<double>& y_lower, TF1* Bkg_Nominal, TF1* Data_Nominal)
{
 int N = 1000;
 TGraphErrors* gr_bands_ratio = new TGraphErrors(N);
 double x = 0.;
 double y_upper_i = 0.;
 double y_lower_i = 0.;
 double y = 0.;
 double x_err = ((x_max-x_min)/(N));
 double y_err = 0.;
 double b = 300.;

 for(int i = 0; i < N; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  //y_upper_i = ((.1e-5*(x-b)*(x-b)+1.01)*(Ratio_Nominal->GetParameter(0))*ROOT::Math::normal_cdf(x,Ratio_Nominal->GetParameter(2),Ratio_Nominal->GetParameter(1)));
  //y_lower_i = ((-1.e-5*(x-b)*(x-b)+.98)*(Ratio_Nominal->GetParameter(0))*ROOT::Math::normal_cdf(x,Ratio_Nominal->GetParameter(2),Ratio_Nominal->GetParameter(1)));
  //y_upper_i = (.1e-5*(x-b)*(x-b)+1.01)*Ratio_Nominal->Eval(x);
  //y_lower_i = (-0.25e-5*(x-b)*(x-b)+.98)*Ratio_Nominal->Eval(x);
  y_upper_i = (.2e-5*(x-b)*(x-b)+1.01);
  y_lower_i = (-.2e-5*(x-b)*(x-b)+.99);
  if(x > b)
  {
   y_upper_i = 1.01;
  }
  if(x > b)
  {
   y_lower_i = 0.99;
  }
  y_upper.push_back(y_upper_i);
  y_lower.push_back(y_lower_i);
  y_upper_i *= (Data_Nominal->Eval(x)/Bkg_Nominal->Eval(x));
  y_lower_i *= (Data_Nominal->Eval(x)/Bkg_Nominal->Eval(x));
/*
  if(x > b)
  {
   y_upper_i = 1.015;
  }
  if(x > b)
  {
   y_lower_i = 0.99;
  }
*/ 
 //if(y_upper_i < 1.) {y_upper_i=1.;}
  //if(y_lower_i > .98) {y_lower_i=.98;}
  y = (y_upper_i+y_lower_i)/2.;
  y_err = (y_upper_i-y_lower_i)/2.;
  gr_bands_ratio->SetPoint(i,x,y);
  gr_bands_ratio->SetPointError(i,x_err,y_err);
 }
 return gr_bands_ratio; 
}

TGraphErrors* Get_Bands(double x_min, double x_max, TF1* Data_Nominal, vector<double>& y_upper, vector<double>& y_lower)
{
 int N = y_upper.size();
 TGraphErrors* gr_bands = new TGraphErrors(N);
 double x = 0.;
 double y = 0.;
 double x_err = ((x_max-x_min)/(N));
 double y_err_i = 0.;
 double y_upper_err_i = 0.;
 double y_lower_err_i = 0.;

 for(int i = 0; i < N; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  y_upper_err_i = std::min(1.,Data_Nominal->Eval(x)*y_upper[i]);
  y_lower_err_i = Data_Nominal->Eval(x)*y_lower[i];
  y = (y_upper_err_i+y_lower_err_i)/2.;
  y_err_i = (y_upper_err_i-y_lower_err_i)/2.;
  if(y > 1.) {y = 1.;}
  if(y_err_i > 1.) {y_err_i = 1.;}
  gr_bands->SetPoint(i,x,y);
  //gr_bands->SetPointError(i,x_err,x_err,y_lower_err_i,y_upper_err_i);
  gr_bands->SetPointError(i,x_err,y_err_i);
 }
 return gr_bands; 
}

TGraph* Get_Fit_Ratio(double x_min, double x_max, TF1* Bkg_Nominal, TF1* Data_Nominal)
{
 int N = 1000;
 TGraph* gr = new TGraph(1000);
 double x = 0.;
 for(int i = 0; i < 1000; i++)
 {
  x = x_min+(((x_max-x_min)/(N))*i);
  gr->SetPoint(i,x,Data_Nominal->Eval(x)/Bkg_Nominal->Eval(x));
 }
 return gr;
}

TGraphAsymmErrors* TGAE_Ratio(TGraphAsymmErrors* gr_bkg, TGraphAsymmErrors* gr_data)
{
 TGraphAsymmErrors* mg = NULL;
 int N = gr_bkg->GetN();
 if(N != gr_data->GetN()) return mg;
 double xnew[N];
 double ynew[N];
 for(int i=0; i<N; i++)
 {
  double x_bkg,y_bkg,x_data,y_data;
  gr_bkg->GetPoint(i,x_bkg,y_bkg);
  gr_data->GetPoint(i,x_data,y_data);
  if(x_bkg != x_data) return mg;
  xnew[i]=x_bkg;
  ynew[i]=y_data/y_bkg;
 }
 mg = new TGraphAsymmErrors(N,xnew,ynew);
 for(int i=0; i<N; i++)
 {
  double bkg_ey_h = gr_bkg->GetErrorYhigh(i);
  double bkg_ey_l = gr_bkg->GetErrorYlow(i);
  double data_ey_h = gr_data->GetErrorYhigh(i);
  double data_ey_l = gr_data->GetErrorYlow(i);
  double x_bkg,y_bkg,x_data,y_data;
  gr_bkg->GetPoint(i,x_bkg,y_bkg);
  gr_data->GetPoint(i,x_data,y_data);
  mg->SetPointError(i,gr_bkg->GetErrorXlow(i),gr_data->GetErrorXhigh(i),sqrt((data_ey_l*data_ey_l)*((y_data/y_bkg)*(y_data/y_bkg))/(y_data*y_data)+(bkg_ey_l*bkg_ey_l)*((y_data/y_bkg)*(y_data/y_bkg))/(y_bkg*y_bkg)),sqrt((data_ey_h*data_ey_h)*((y_data/y_bkg)*(y_data/y_bkg))/(y_data*y_data)+(bkg_ey_h*bkg_ey_h)*((y_data/y_bkg)*(y_data/y_bkg))/(y_bkg*y_bkg)));
 }
 return mg;
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
 string cutsFile = "cuts.txt";
 vector<string> cuts;
 vector<string> files;

 if(argc < 1)
 {
  cout << "ERROR: Need to specify cuts file" << endl;
  cout << "Example: ./Scale.x -cuts=cuts.txt" << endl;
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
  files.push_back("Eff_output_"+cut+".root");
  //files.push_back("NoLowHTScale_MET_PreSelection.root");
 }

 ScaleFactors(files,cuts);
 return 0;
}
