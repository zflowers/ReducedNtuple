#include <TFile.h>
#include <iostream>
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

bool invert_colors = true;

TMultiGraph* get_mg(string fname, vector<string> years, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can);
void Get_Plot(vector<string> years, vector<string> Triggers, vector<int> colors, string outFile, string name);

void Plotter_Eff_Nano(string inFile){

 vector<string> years_2016 = { "2016" };
 vector<string> Triggers_2016{
   "HLT_MET100",
   "HLT_MET150",
   "HLT_MET200",
   "HLT_MET250",
   "HLT_MET300",
 };
 vector<int> colors_2016 = {kPink, kGreen, kCyan, kMagenta, kOrange};
 
 vector<string> years_2017_2018 = { "2017", "2018" };
 vector<string> Triggers_2017_2018{
   "HLT_PFMET200_HBHECleaned",
 };
 vector<int> colors_2017_2018 = {kPink, kGreen}; 

 Get_Plot(years_2016, Triggers_2016,colors_2016,inFile,"HLT_MET_2016");
 Get_Plot(years_2017_2018, Triggers_2017_2018,colors_2017_2018,inFile,"HLT_2017_2018");
}

//get all Eff on one plot
void Get_Plot(vector<string> years, vector<string> Triggers, vector<int> colors, string outFile, string name)
{
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }

 TLegend* leg = new TLegend(0.588,0.546,0.945,0.904);
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 
 TLatex l;
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.13);
 can->SetRightMargin(0.04);
 can->SetBottomMargin(0.15);
 can->SetTopMargin(0.085);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 TMultiGraph* mg = get_mg(outFile,years,Triggers,colors,leg,can);
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
 l.SetTextSize(0.05);
 l.SetTextFont(42);
 l.DrawLatex(0.15,0.943,"#bf{#it{CMS}} Internal 13 TeV Simulation");
  
 TFile* output = new TFile(outFile.c_str(),"UPDATE");
 can->Write();
 output->Close();
 delete leg;
 delete mg;
 delete can;
 delete output;
}

TMultiGraph* get_mg(string fname, vector<string> years, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can)
{
 TMultiGraph* mg = new TMultiGraph();
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return mg;
 }
 for(int i = 0; i < int(years.size()); i++)
 {
  TDirectoryFile* folder = nullptr;
  f->GetObject(years[i].c_str(),folder);
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
   gr->SetMarkerStyle(22);
   gr->SetMarkerColor(colors[i+j]);
   gr->SetLineColor(colors[i+j]);
   leg->AddEntry(gr,(years.at(i)+"_"+Triggers.at(j)).c_str(),"P");
   mg->Add(gr);
  }
 }
 return mg;
}
