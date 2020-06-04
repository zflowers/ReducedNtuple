//Code for Fitting Efficiency Curves
//function: Error function or CDF for gaussian or Fermi function or Soft Heaviside

#include <TMinuit.h>

void Get_Fit(TGraphAsymmErrors*& gr, vector<TF1*> funcs, vector<int> colors, string outFile, string name);
void Fit_Graph_With_Funcs(TCanvas*& canv, TGraphAsymmErrors*& gr, vector<TF1*> funcs, const vector<int>& colors);

Double_t Error_Func(Double_t *x, Double_t *par)
{
 return par[0]*TMath::Erf(x[0]-par[1]);
}

Double_t Gaussian_CDF_Func(Double_t *x, Double_t *par)
{
 return par[0]*ROOT::Math::normal_cdf(x[0],par[2],par[1]);
}

Double_t Double_Gaussian_CDF_Func(Double_t *x, Double_t *par)
{
 return par[0]*(par[3]*ROOT::Math::normal_cdf(x[0],par[2],par[1])+(1.-par[3])*ROOT::Math::normal_cdf(x[0],par[4],par[1]));
}

bool invert_colors = true;

void Fitter_Eff_Nano(TGraphAsymmErrors* gr_given, vector<int> colors, string name)
{
 //TGraphAsymmErrors* gr = (TGraphAsymmErrors*)(gr_given->Clone());
 for(int j = 0; j < int(gr_given->GetN()); j++)
 {
  gr_given->SetPointEXlow(j,0.);
  gr_given->SetPointEXhigh(j,0.);
 }
 double x_min = gr_given->GetXaxis()->GetXmin();
 double x_max = gr_given->GetXaxis()->GetXmax();
 
 vector<TF1*> funcs;

 //Err Function
 double Norm_Erf=1.;
 double Mean_Erf=100.;

 TF1* func_Erf = new TF1("func_Erf",Error_Func,x_min,x_max,2);
 func_Erf->SetParameter(0,Norm_Erf);
 func_Erf->SetParameter(1,Mean_Erf);
 func_Erf->SetParName(0,"Norm_Erf");
 func_Erf->SetParName(1,"Mean_Erf");
 
 //funcs.push_back(func_Erf);

 //Gaussian CDF Function
 double Norm_Gauss_CDF=1.;
 double Mean_Gauss_CDF=100.;
 double Sigma_Gauss_CDF=10.;

 TF1* func_Gaussian_CDF0 = new TF1("func_Gaussian_CDF0",Gaussian_CDF_Func,x_min,x_max,3);
 func_Gaussian_CDF0->SetParameter(0,Norm_Gauss_CDF);
 func_Gaussian_CDF0->SetParameter(1,Mean_Gauss_CDF);
 func_Gaussian_CDF0->SetParameter(2,Sigma_Gauss_CDF);
 func_Gaussian_CDF0->SetParName(0,"Norm_Gauss_CDF");
 func_Gaussian_CDF0->SetParName(1,"Mean_Gauss_CDF");
 func_Gaussian_CDF0->SetParName(2,"Sigma_Gauss_CDF");
 
 funcs.push_back(func_Gaussian_CDF0);

 TF1* func_Gaussian_CDF1 = new TF1("func_Gaussian_CDF1",Gaussian_CDF_Func,160.,x_max,3);
 func_Gaussian_CDF1->SetParameter(0,Norm_Gauss_CDF);
 func_Gaussian_CDF1->SetParameter(1,Mean_Gauss_CDF);
 func_Gaussian_CDF1->SetParameter(2,Sigma_Gauss_CDF);
 func_Gaussian_CDF1->SetParName(0,"Norm_Gauss_CDF");
 func_Gaussian_CDF1->SetParName(1,"Mean_Gauss_CDF");
 func_Gaussian_CDF1->SetParName(2,"Sigma_Gauss_CDF");
 
 funcs.push_back(func_Gaussian_CDF1);


 //Call Get_Fit and send it whatever functions we need
 Get_Fit(gr_given,funcs,colors,"output_Fits.root",name);

}

void Format_Graph(TGraphAsymmErrors*& gr)
{
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
  }
}

TGraphAsymmErrors* TGAE_TF1(TGraphAsymmErrors *gr, TF1 *fit_func)
{
 int N = gr->GetN();
 double xnew[N];
 double ynew[N];
 double xnew_err[N];
 double ynew_err[N];
 for(int i=0; i < N; i++)
 {
  double x,y,ex,ey;
  gr->GetPoint(i, x, y);
  xnew[i] = x;
  ynew[i] = fit_func->Eval(x)-y;
 }
 TGraphAsymmErrors* res_gr = new TGraphAsymmErrors(N,xnew,ynew);
 for(int i=0; i < N; i++)
 {
  res_gr->SetPointError(i,gr->GetErrorXlow(i),gr->GetErrorXhigh(i),gr->GetErrorYlow(i),gr->GetErrorYhigh(i));
 }
 res_gr->SetTitle("");
 return res_gr;
}

void Get_Fit(TGraphAsymmErrors*& gr, vector<TF1*> funcs, vector<int> colors, string outFile, string name)
{
 if(invert_colors)
 {
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameLineColor(kWhite);
 }
 
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
 if(invert_colors)
 {
  can->SetFillColor(kBlack);
  l.SetTextColor(kWhite);
 }

 can->Modified();
 can->Update();
 //TGraph* gr = get_gr(tags,Triggers,inFile,colors,can);
 Fit_Graph_With_Funcs(can,gr,funcs,colors);
 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.55,0.93,name.c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Internal 13 TeV Simulation");


 TFile* output = TFile::Open(outFile.c_str(),"UPDATE");
 can->Write();
 output->Close();
 delete can;
 delete output;
}

void Fit_Graph_With_Funcs(TCanvas*& canv, TGraphAsymmErrors*& gr_given, vector<TF1*> funcs, const vector<int>& colors)
{
 gStyle->SetOptFit(1111);
 canv->cd();
 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,.3,1.,1.);
 pad_gr->SetBottomMargin(0.95);
 pad_gr->Draw();
 pad_gr->cd();
 canv->Update();
 TLegend leg(0.55,0.2,0.98,0.8,"");
 leg.SetTextFont(132);
 leg.SetTextSize(0.04);
 if(invert_colors)
 {
  leg.SetFillColor(kBlack);
  leg.SetLineColor(kBlack);
  leg.SetShadowColor(kBlack); 
 }
 //TMultiGraph* mg = new TMultiGraph();
 vector<TGraphAsymmErrors*> vect_gr;
 for(int i = 0; i < int(funcs.size()); i++)
 {
  TGraphAsymmErrors* gr = (TGraphAsymmErrors*)(gr_given->Clone());
  Format_Graph(gr);
  vect_gr.push_back(gr);
 }
 vector<TPaveStats*> vect_stats;

 for(int i = 0; i < int(funcs.size()); i++)
 {
  vect_gr[i]->SetMarkerColor(kWhite);
  vect_gr[i]->SetLineColor(kWhite);

  if(invert_colors)
  {
   canv->SetFillColor(kBlack);
   pad_gr->SetFillColor(kBlack);
  }
  funcs[i]->SetNpx(1000000);
  funcs[i]->SetLineColor(colors[i]);
  vect_gr[i]->Fit(funcs[i],"EMR0");
  //mg->Add(vect_gr[i]);
  TString status_func = gMinuit->fCstatu;
  TString status_func_leg = "Status = ";
  status_func_leg+=status_func;
  leg.AddEntry((TObject*)0, status_func_leg, "");
  leg.SetTextColor(colors[i]);
  pad_gr->Update();
  
  vect_gr[i]->Draw("AP SAMES");
  pad_gr->Update();
  canv->Update();
  TPaveStats *stats = (TPaveStats*)vect_gr[i]->GetListOfFunctions()->FindObject("stats");
  string stats_name = funcs[i]->GetName();
  stats->SetName(("stats_"+stats_name).c_str());
  stats->SetTextColor(colors[i]);
  stats->SetLineColor(colors[i]);
  stats->SetY1NDC(0.8-i*.2);
  stats->SetY2NDC(0.6-i*.2);
  vect_stats.push_back(stats);
  pad_gr->Update();
  
  //TLegend leg(0.55,0.4-i*.1,0.98,0.5-i*.1,"");
  if(invert_colors)
  {
   stats->SetFillColor(kBlack);
  }
 
  pad_gr->Update();
  canv->Update();

 }
 for(int i = 0; i < int(funcs.size()); i++)
 {
  vect_stats[i]->Draw("SAMES");
  funcs[i]->Draw("SAMES");
 }
 //mg->Draw("AP SAMES");
 leg.Draw("SAMES");
 pad_gr->Update();
 pad_gr->Modified();
 canv->Update();

 TPad *pad_res = new TPad("pad_res", "pad_res", 0, 0.05, 1, 0.3);
 pad_res->Draw();
 pad_res->SetTopMargin(0.05);
 pad_res->Update();
 pad_res->cd();
 canv->Update();

 TMultiGraph* mg_res = new TMultiGraph();
 for(int i = 0; i < int(funcs.size()); i++)
 {
  TGraphAsymmErrors* res=TGAE_TF1(vect_gr[i],funcs[i]);
  Format_Graph(res);
  res->SetMarkerColor(colors[i]);
  res->SetLineColor(colors[i]);
  mg_res->Add(res);
 }

 mg_res->Draw("AP");
 mg_res->GetXaxis()->SetLabelSize(0.12);
 mg_res->GetYaxis()->SetLabelSize(0.12);
 
 //TLine* line = new TLine(res->GetXaxis()->GetXmin(),0.0,res->GetXaxis()->GetXmax(),0.0);
 //line->SetLineColor(kBlack);
 //line->SetLineStyle(2);
 //line->Draw();
 pad_res->Update();
 canv->Update();

}

TGraphAsymmErrors* get_gr(vector<string> tags, vector<string> Triggers, string fname, vector<int> colors, TCanvas*& can)
{
 TKey *key;
 TFile *f = TFile::Open(fname.c_str(), "READ");
 TGraphAsymmErrors* gr = NULL;
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return gr;
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
