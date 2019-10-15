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

//get a set of Eff
vector<TEfficiency*> list_effs(string fname, vector<string> years, vector<string> Triggers)
{
 vector<TEfficiency*> vect_eff;
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return vect_eff;
 }
 for(int i = 0; i < int(years.size()); i++)
 {
  TDirectoryFile* folder = nullptr;
  f->GetObject(years[i].c_str(),folder);
  folder->cd();
  for(int j = 0; j < int(Triggers.size()); j++)
  {
   TEfficiency* e = nullptr;
   folder->GetObject(Triggers.at(j).c_str(),e);
   vect_eff.push_back(e);
  }
 }
 return vect_eff;
}

//get all Eff on one plot
void Get_Plot(vector<string> years, vector<string> Triggers, vector<int> colors, string outFile, string name)
{
 vector<TEfficiency*> vect_Eff = list_effs(outFile,years,Triggers);
 TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 can->SetLeftMargin(0.13);
 can->SetRightMargin(0.04);
 can->SetBottomMargin(0.15);
 can->SetTopMargin(0.085);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();

 TLegend* leg = new TLegend(0.588,0.546,0.945,0.904);
 leg->SetTextFont(132);
 leg->SetTextSize(0.045);
 leg->SetFillColor(kWhite);
 leg->SetLineColor(kWhite);
 leg->SetShadowColor(kWhite);

 TMultiGraph* mg = new TMultiGraph();
 for(int i = 0; i < int(Triggers.size()); i++)
 {
  vect_Eff[i]->Draw("AP");
  can->Update();
  TGraphAsymmErrors* gr = vect_Eff[i]->GetPaintedGraph();
  gr->SetMarkerStyle(21);
  gr->SetMarkerColor(colors[i]);
  gr->SetLineColor(colors[i]);
  mg->Add(gr);
  leg->AddEntry(gr,Triggers[i].c_str(),"P");
  can->Clear();
 }

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

 gPad->RedrawAxis();
 gPad->RedrawAxis("G");
 leg->Draw("SAME");

 TLatex l;
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

void Eff_Nano_Plotter(string inFile){

 vector<string> years_2016 = { "2016" };
 vector<string> Triggers_2016{
 "HLT_PFMET300",
 "HLT_PFMET400",
 "HLT_PFMET500",
 "HLT_PFMET600",
 };
 vector<int> colors_2016 = {kRed, kGreen, kBlue, kMagenta};
 
 //vector<string> Triggers_2017;
 //vector<string> Triggers_2018;
 
 Get_Plot(years_2016, Triggers_2016,colors_2016,inFile,"HLT_PFMET_2016");

}
