//Code for Fitting TGraphs
//function: Error function or CDF for gaussian or Fermi function or Soft Heaviside
//run after running plotter?

vector<TCanvas*> Fitter_Eff_Nano(vector<TGraphAsymmErrors*> vect_gr, vector<int> colors)
{
 vector<string> tags_2017 = {"WWTo2L2Nu_2017", "WJets_2017", "TTJets_2017", "T2_4bd_500_420_2017", "T2_4bd_500_490_2017"};
 vector<int> colors = {kPink, kGreen, kCyan, kMagenta, kYellow, kViolet+2, kAzure+7, kGray};

 vector<string> METtrigger{ "METtrigger" };
 vector<string> METORtrigger{ "METORtrigger" };
 vector<string> SuperOR { "SuperOR" };

 vector<TF1*> funcs;

 //Err Function
 double Norm=1.;
 double Mean=100.;

 TF1 *func_Erf = new TF1("func_Erf","[0]*TMath::Erf(x-[1])",vect_gr[0]->GetXaxis()->GetXmin(),vect_gr[0]->GetXaxis()->GetXmax(),2);
 func_Erf->SetParameter(0,Norm);
 func_Erf->SetParameter(1,Mean);
 func_Erf->SetParName(0,"Norm");
 func_Erf->SetParName(1,"Mean");
 
 funcs.push_back(func_Erf);
 //Call Get_Fit and send it whatever functions we need
 Get_Fit(tags_2017,METtrigger,colors,"output_MET_NoCuts.root","Test","")



/*
 for(int i = 0; i < int(vect_gr.size()); i++)
 {
  canvases.push_back(Fit_Graph_With_Funcs(vect_gr[i],funcs,colors));
 }
 return canvases
*/

}

void Fit_Graph_With_Funcs(TCanvas*& canv, TGraphAsymmErrors*& gr, vector<TF1*> funcs, const vector<int>& colors)
{
 gr->Draw("AP");
 TLegend leg(0.55,0.2,0.98,0.8,"");
 for(int i = 0; i < int(funcs.size()); i++)
 {
  //TGraphAsymmErrors* gr_clone = (TGraphAsymmErrors*)(gr->Clone());
  funcs[i]->SetLineColor(colors[i]);
  gr->Fit(funcs[i],"EMR");
  TString status_func = gMinuit->fCstatu;
  funcs[i]->Draw("SAMES");
  canvas->Update();
  
  TPaveStats *stats = (TPaveStats*)gr->GetListOfFunctions()->FindObject("stats");
  stats->SetTextColor(colors[i]);
  stats->SetLineColor(colors[i]);
  stats->SetY1NDC(0.9-i*.2);
  stats->SetY2NDC(0.7-i*.2);
  stats->Draw("SAMES");
  canvas->Update();
  
  TString status_func = gMinuit->fCstatu;
  TString status_func_leg = "Status = ";
  status_func_leg+=status_func;
  
  //TLegend leg(0.55,0.4-i*.1,0.98,0.5-i*.1,"");
  leg.SetTextFont(132);
  leg.SetTextSize(0.04);
  leg.SetFillColor(kWhite);
  leg.AddEntry((TObject*)0, status_func_leg, "");
  leg.SetTextColor(colors[i]);
  if(invert_colors)
  {
   leg.SetTextColor(kWhite);
   leg.SetFillColor(kBlack);
   leg.SetLineColor(kBlack);
   leg.SetShadowColor(kBlack); 
  }
 
  canvas->Update();
  leg.Draw("SAMES");
  canvas->Update();

 }
}

TGraphAsymmErrors* get_gr(vector<string> tags, vector<string> Triggers, string fname, vector<int> colors, TCanvas*& can)
{
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
   gr->SetMarkerStyle(20);
   gr->SetMarkerColor(colors[i+j]);
   gr->SetLineColor(colors[i+j]);
  }
 }
 f->Close();
 delete f;
 
 return gr;
}

void Get_Fit(vector<string> tags, vector<string> Triggers, vector<int> colors, string inFile, string name)
{
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }
 
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
 TMultiGraph* gr = get_gr(tags,Triggers,inFile,colors,can);
 Fit_Graph_With_Funcs(can,
 can->Clear();

 gr->GetXaxis()->CenterTitle(true);
 gr->GetXaxis()->SetTitleFont(132);
 gr->GetXaxis()->SetTitleSize(0.06);
 gr->GetXaxis()->SetTitleOffset(1.06);
 gr->GetXaxis()->SetLabelFont(132);
 gr->GetXaxis()->SetLabelSize(0.05);
 gr->GetYaxis()->CenterTitle(true);
 gr->GetYaxis()->SetTitleFont(132);
 gr->GetYaxis()->SetTitleSize(0.06);
 gr->GetYaxis()->SetTitleOffset(1.);
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
  can->SetFillColor(kBlack);
  l.SetTextColor(kWhite);
 }

 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.62,0.93,name.c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Internal 13 TeV Simulation");
 can->Modified();
 can->Update();

 TFile* output = TFile::Open(inFile.c_str(),"UPDATE");
 can->Write();
 output->Close();
 delete mg;
 delete can;
 delete output;
}
