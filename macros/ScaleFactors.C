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

using namespace std;

bool invert_colors = true;

double Get_ScaleFactor(string bkg_tag, vector<string> data_tags, string Trigger, vector<int> colors, string outFile, string name, string option);
TGraphAsymmErrors* get_gr(string fname, string tag, string Trigger, int color, TLegend*& leg, TCanvas*& can);
TGraphAsymmErrors* TGAE_Ratio(TGraphAsymmErrors* gr_bkg, TGraphAsymmErrors* gr_data);

void ScaleFactors(vector<string> inFile, vector<string> cut){
 //string inFile ="output_quick.root";
 vector<string> data_tags_2016 = {"SingleElectron_2016","SingleMuon_2016"};
 vector<string> data_tags_2017 = {"SingleElectron_2017","SingleMuon_2017","DoubleEG_2017","DoubleMuon_2017"};
 vector<string> data_tags_2018 = {"SingleElectron_2018","SingleMuon_2018"};
 
 vector<int> colors = {kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kPink, kGreen, kGray};

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
 gr->GetXaxis()->SetLabelSize(0.05);
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

void Format_Graph_res(TMultiGraph*& gr)
{
  gr->GetXaxis()->CenterTitle(true);
  gr->GetXaxis()->SetTitleFont(132);
  gr->GetXaxis()->SetTitleSize(0.12);
  gr->GetXaxis()->SetTitleOffset(.7);
  gr->GetXaxis()->SetLabelFont(132);
  gr->GetXaxis()->SetLabelSize(0.1);
  gr->GetYaxis()->CenterTitle(true);
  gr->GetYaxis()->SetTitleFont(132);
  gr->GetYaxis()->SetTitleSize(0.12);
  gr->GetYaxis()->SetTitleOffset(.35);
  gr->GetYaxis()->SetLabelFont(132);
  gr->GetYaxis()->SetLabelSize(0.1);

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
 gr->GetXaxis()->SetTitleSize(0.12);
 gr->GetXaxis()->SetTitleOffset(.7);
 gr->GetXaxis()->SetLabelFont(132);
 gr->GetXaxis()->SetLabelSize(0.0);
 gr->GetYaxis()->CenterTitle(true);
 gr->GetYaxis()->SetTitleFont(132);
 gr->GetYaxis()->SetTitleSize(0.1);
 gr->GetYaxis()->SetTitleOffset(.3);
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

 TLegend* leg = new TLegend(0.55,0.3,0.85,0.6); 
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

 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,.3,1.,1.);
 pad_gr->SetGridx();
 pad_gr->SetGridy();
 pad_gr->Draw();
 pad_gr->cd();
 can->Update();

 mg->Draw("AP"); 
 Format_Graph(mg);
 pad_gr->Update();
 pad_gr->Modified();
 can->Update();
 mg->GetYaxis()->SetTitle("Efficiency");

 if(invert_colors)
 {
  pad_gr->SetFillColor(kBlack);
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
 pad_gr->Update();
 can->Update();
 can->cd();

//This is where we evaluate scale factors (Ratio or Fit)
 TPad *pad_res = new TPad("pad_res","pad_res",0,0.03,1,0.3);
 pad_res->SetGridx(); 
 pad_res->SetGridy();
 pad_res->SetTopMargin(1.3);
 pad_res->SetBottomMargin(0.2);
 pad_res->Draw();
 pad_res->cd();
 pad_res->Update();
 can->Update();
 if(invert_colors) pad_res->SetFillColor(kBlack);
 bool empty_mg = true;
 TMultiGraph* mg_res = new TMultiGraph();
 for(int i = 0; i < data_tags.size(); i++)
 {
  TGraphAsymmErrors* res_ratio = TGAE_Ratio(gr_bkg,vect_gr_data[i]);
  if(res_ratio == NULL) continue;
  res_ratio->SetMarkerColor(colors[i+1]);
  res_ratio->SetLineColor(colors[i+1]);
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
 mg_res->Draw("AP");
 Format_Graph_res(mg_res);
 mg_res->GetXaxis()->SetLimits(mg->GetXaxis()->GetXmin(),mg->GetXaxis()->GetXmax());
 mg_res->GetYaxis()->SetTitle("Data/Bkg");
 mg_res->GetXaxis()->SetTitle("MET");
 pad_res->Modified();
 pad_res->Update();
 TLine* line = new TLine(mg_res->GetXaxis()->GetXmin(),0.0,mg_res->GetXaxis()->GetXmax(),0.0);
 line->SetLineColor(kWhite);
 line->SetLineStyle(1);
 line->Draw("SAMES");
 pad_res->Modified();
 pad_res->Update();
 can->Modified();
 can->Update();

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
 leg->AddEntry(gr,tag.c_str(),"PL");
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
