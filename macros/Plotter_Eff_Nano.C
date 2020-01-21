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

TMultiGraph* get_mg(string fname, vector<string> tags, vector<string> Triggers, vector<int> colors, TLegend*& leg, TCanvas*& can, string option);
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, string outFile, string name, string option);

void Plotter_Eff_Nano(){
 string inFile ="output_test.root";
 vector<string> tags_2016 = {"WJets_2016", "TTJets_2016", "DY_2016"};//, "TChiWZ_2016", "Stop_2016"};
 vector<int> colors = {kPink, kGreen, kCyan};

 vector<string> Triggers_90{
   "HLT_PFMET90_PFMHT90_IDTight",
 };
 vector<string> Triggers_100{
   "HLT_PFMET100_PFMHT100_IDTight",
 };
 vector<string> Triggers_110{
   "HLT_PFMET110_PFMHT110_IDTight",
 };
 vector<string> Triggers_120{
   "HLT_PFMET120_PFMHT120_IDTight",
 };
 vector<string> Triggers_130{ //Not in 2016
   "HLT_PFMET130_PFMHT130_IDTight",
 };
 vector<string> Triggers_140{ //Not in 2016
   "HLT_PFMET140_PFMHT140_IDTight",
 };

 Get_Plot(tags_2016,Triggers_90,colors,inFile,"2016_HLT_PFMET90_PFMHT90_IDTight","Trigger");
 Get_Plot(tags_2016,Triggers_100,colors,inFile,"2016_HLT_PFMET100_PFMHT100_IDTight","Trigger");
 Get_Plot(tags_2016,Triggers_110,colors,inFile,"2016_HLT_PFMET110_PFMHT110_IDTight","Trigger");
 Get_Plot(tags_2016,Triggers_120,colors,inFile,"2016_HLT_PFMET120_PFMHT120_IDTight","Trigger");

 /*
 Get_Plot(tags_2017,Triggers_90,colors,inFile,"2017_HLT_PFMET90_PFMHT90_IDTight","Trigger");
 Get_Plot(tags_2017,Triggers_100,colors,inFile,"2017_HLT_PFMET100_PFMHT100_IDTight","Trigger");
 Get_Plot(tags_2017,Triggers_110,colors,inFile,"2017_HLT_PFMET110_PFMHT110_IDTight","Trigger");
 Get_Plot(tags_2017,Triggers_120,colors,inFile,"2017_HLT_PFMET120_PFMHT120_IDTight","Trigger");
 Get_Plot(tags_2017,Triggers_130,colors,inFile,"2017_HLT_PFMET130_PFMHT130_IDTight","Trigger");
 Get_Plot(tags_2017,Triggers_140,colors,inFile,"2017_HLT_PFMET140_PFMHT140_IDTight","Trigger");

 Get_Plot(tags_2018,Triggers_90,colors,inFile,"2018_HLT_PFMET90_PFMHT90_IDTight","Trigger");
 Get_Plot(tags_2018,Triggers_100,colors,inFile,"2018_HLT_PFMET100_PFMHT100_IDTight","Trigger");
 Get_Plot(tags_2018,Triggers_110,colors,inFile,"2018_HLT_PFMET110_PFMHT110_IDTight","Trigger");
 Get_Plot(tags_2018,Triggers_120,colors,inFile,"2018_HLT_PFMET120_PFMHT120_IDTight","Trigger");
 Get_Plot(tags_2018,Triggers_130,colors,inFile,"2018_HLT_PFMET130_PFMHT130_IDTight","Trigger");
 Get_Plot(tags_2018,Triggers_140,colors,inFile,"2018_HLT_PFMET140_PFMHT140_IDTight","Trigger");
 */
}

//get all Eff on one plot
void Get_Plot(vector<string> tags, vector<string> Triggers, vector<int> colors, string outFile, string name, string option)
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
 if(option.compare("Tag") == 0)
 {
  l.DrawLatex(0.61,0.93,tags.at(0).c_str());
 }
 else if(option.compare("Trigger") == 0)
 {
  l.DrawLatex(0.61,0.93,Triggers.at(0).c_str());
 }
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Internal 13 TeV Simulation");

 TFile* output = new TFile(outFile.c_str(),"UPDATE");
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
 return mg;
}
