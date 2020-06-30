//Code for Fitting Efficiency Curves
//function: Error function or CDF for gaussian or Fermi function or Soft Heaviside

#include <TMinuit.h>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <TMatrixDSym.h>
#include <TPaveStats.h>
#include <TLine.h>
#include <TFitResult.h>
#include <Math/ProbFunc.h>

void Get_Fit(TGraphAsymmErrors*& gr, vector<TF1*> funcs, vector<int> colors, string outFile, string name);
void Fit_Graph_With_Funcs(TCanvas*& canv, TGraphAsymmErrors*& gr, vector<TF1*> funcs, const vector<int>& colors, string name);

Double_t Error_Func(Double_t *x, Double_t *par)
{
 return par[0]*TMath::Erf(x[0]-par[1]);
}

Double_t Gaussian_CDF_Func(Double_t *x, Double_t *par)
{
 return par[0]*ROOT::Math::normal_cdf(x[0],par[2],par[1]);
}

Double_t Double_Gaussian_CDF_Func_Add(Double_t *x, Double_t *par)
{
 return par[0]*((TMath::Cos(par[4])*TMath::Cos(par[4]))*ROOT::Math::normal_cdf(x[0],par[2],par[1])+(TMath::Sin(par[4])*TMath::Sin(par[4]))*ROOT::Math::normal_cdf(x[0],par[2]+par[3],par[1]));
}

Double_t Double_Gaussian_CDF_Func_Multi(Double_t *x, Double_t *par)
{
 return par[0]*((TMath::Cos(par[4])*TMath::Cos(par[4]))*ROOT::Math::normal_cdf(x[0],par[2],par[1])+(TMath::Sin(par[4])*TMath::Sin(par[4]))*ROOT::Math::normal_cdf(x[0],par[2]*par[3],par[1]));
}

bool invert_colors = true;

bool fileExists(const std::string& filename)
{
 struct stat buf;
 if (stat(filename.c_str(), &buf) != -1)
 {
     return true;
 }
 return false;
}

void Fitter_Eff_Nano(TGraphAsymmErrors* gr_given, vector<int> colors, string name)
{
 if(name.find("triggerE") != std::string::npos) return;
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
 
 //funcs.push_back(func_Gaussian_CDF0);

 //Double Gaussian CDF Function
 double Norm_Double_Gauss_CDF=1.;
 double Mean_Double_Gauss_CDF=100.;
 double Sigma_Double_Gauss_CDF=10.;
 double SigmaScale_Double_Gauss_CDF=10.;
 double Weight_Double_Gauss_CDF=.5;

 TF1* func_Double_Gaussian_CDF_Add0 = new TF1("func_Double_Gaussian_CDF_Add0",Double_Gaussian_CDF_Func_Add,x_min,x_max,5);
 func_Double_Gaussian_CDF_Add0->SetParameter(0,Norm_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Add0->SetParameter(1,Mean_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Add0->SetParameter(2,Sigma_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Add0->SetParameter(3,SigmaScale_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Add0->SetParameter(4,Weight_Double_Gauss_CDF);
 //func_Double_Gaussian_CDF_Add0->SetParLimits(3,1.,100.);
 //func_Double_Gaussian_CDF_Add0->SetParLimits(4,-TMath::Pi()/2.,TMath::Pi()/2.);
 func_Double_Gaussian_CDF_Add0->SetParName(0,"Norm_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Add0->SetParName(1,"Mean_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Add0->SetParName(2,"Sigma_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Add0->SetParName(3,"Scale_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Add0->SetParName(4,"Weight_Double_Gauss_CDF0");
 
 funcs.push_back(func_Double_Gaussian_CDF_Add0);

 TF1* func_Double_Gaussian_CDF_Multi0 = new TF1("func_Double_Gaussian_CDF_Multi0",Double_Gaussian_CDF_Func_Multi,x_min,x_max,5);
 func_Double_Gaussian_CDF_Multi0->SetParameter(0,Norm_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Multi0->SetParameter(1,Mean_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Multi0->SetParameter(2,Sigma_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Multi0->SetParameter(3,SigmaScale_Double_Gauss_CDF);
 func_Double_Gaussian_CDF_Multi0->SetParameter(4,Weight_Double_Gauss_CDF);
 //func_Double_Gaussian_CDF_Multi0->SetParLimits(3,1.,100.);
 //func_Double_Gaussian_CDF_Multi0->SetParLimits(4,-TMath::Pi()/2.,TMath::Pi()/2.);
 func_Double_Gaussian_CDF_Multi0->SetParName(0,"Norm_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Multi0->SetParName(1,"Mean_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Multi0->SetParName(2,"Sigma_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Multi0->SetParName(3,"Scale_Double_Gauss_CDF0");
 func_Double_Gaussian_CDF_Multi0->SetParName(4,"Weight_Double_Gauss_CDF0");
 
 //funcs.push_back(func_Double_Gaussian_CDF_Multi0);

 if(!fileExists("Fit_Parameters_Output.csv"))
 {
  ofstream output;
  output.open("Fit_Parameters_Output.csv",fstream::app);
  output << "Efficiency";
 
  for(int i = 0; i < int(funcs.size()); i++)
  {
   output << " " << ",";
   for(int j = 0; j < funcs[i]->GetNpar(); j++)
   {
    output << funcs[i]->GetParName(j) << ",";
   }
   output << "ChiSquared" << "," << "NDF" << "," << "Status" << endl;
  }
  output.close();
 }



 //Call Get_Fit and send it whatever functions we need
 Get_Fit(gr_given,funcs,colors,"output_Fits.root",name);


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

void Format_Graph(TGraphAsymmErrors*& gr)
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
  ynew[i] = y-fit_func->Eval(x);
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
 
 //TCanvas* can = new TCanvas(name.c_str(),"",600.,500);
 TCanvas* can = new TCanvas(name.c_str(),"",864.,468.);
 can->SetGridx();
 can->SetGridy();
 can->Draw();
 can->cd();
 if(invert_colors)
 {
  can->SetFillColor(kBlack);
 }

 can->Modified();
 can->Update();
 //TGraph* gr = get_gr(tags,Triggers,inFile,colors,can);
 Fit_Graph_With_Funcs(can,gr,funcs,colors,name);

 TFile* output = TFile::Open(outFile.c_str(),"UPDATE");
 can->Write();
 can->SaveAs(("Plots/"+name+".pdf").c_str());
 output->Close();
 delete can;
 delete output;
}

//Code for rounding numbers
double toPrecision(double num, int n) 
{
 if(num == 0) {
   return 0.0;
 }

 double d = std::ceil(std::log10(num < 0 ? -num : num));
 int power = n - (int)d;
 double magnitude = std::pow(10., power);
 long shifted = std::round(num*magnitude);

 std::ostringstream oss;
 oss << shifted/magnitude;
 string num_str = oss.str();
 return atof(num_str.c_str());
}

int getPrecision(double num)
{
 string num_str = std::to_string(num);
 num_str.erase ( num_str.find_last_not_of('0') + 1, std::string::npos );
 int pre = 0;
 bool point = false;
 int num_str_length = num_str.length();
 for(int i=0; i<num_str_length; i++)
 {
  if(point)
  {
   pre++;
  }
  if(num_str.at(i) == '.')
  {
   point = true;
  }
 }
 return pre;
}

double Round(const double& num)
{
 //int precision = getPrecision(num);
 //return (toPrecision(num,precision));
 return (toPrecision(num,3));
}

void Output_Fit(TF1* func, string name, string status, TFitResultPtr result)
{
 ofstream output;
 output.open("Fit_Parameters_Output.csv",fstream::app);
 output << name << ",";
 for(int j = 0; j < func->GetNpar(); j++)
 {
  string ParName = func->GetParName(j);
  if(ParName.find("Weight") != std::string::npos)
  {
   output << Round(TMath::Cos(func->GetParameter(j))*TMath::Cos(func->GetParameter(j))) << " +/- " << Round(fabs(-TMath::Sin(2.*func->GetParameter(j))*func->GetParError(j)-TMath::Cos(2.*func->GetParameter(j))*func->GetParError(j)*func->GetParError(j))) << ",";
  }
  else if(ParName.find("Scale") != std::string::npos)
  {
   double scale = func->GetParameter(j);
   double sigma = func->GetParameter(j-1);
   double scale_err = func->GetParError(j);
   double sigma_err = func->GetParError(j-1);
   TMatrixDSym cov = result->GetCovarianceMatrix();
   double cov_sigmascale = cov(j,j-1);
   string func_name = func->GetName();
   if(func_name.find("Multi") != std::string::npos)
   {
    //for multiplying
    output << Round(scale*sigma) << " +/- " << Round(sqrt(sigma*scale_err*sigma*scale_err+sigma_err*scale*sigma_err*scale+2.*sigma*scale*cov_sigmascale*cov_sigmascale)) << ",";
   }
   else if(func_name.find("Add") != std::string::npos)
   {
    //for adding
    output << Round(scale+sigma) << " +/- " << Round(sqrt(scale_err*scale_err+sigma_err*sigma_err)) << ",";
   }
  }
  else
  {
   output << Round(func->GetParameter(j)) << " +/- " << Round(func->GetParError(j)) << ",";
  }
 }
 output << Round(func->GetChisquare()) << "," << func->GetNDF() << "," << status << endl;

 output.close();


}

void Fit_Graph_With_Funcs(TCanvas*& canv, TGraphAsymmErrors*& gr_given, vector<TF1*> funcs, const vector<int>& colors, string name)
{
 gStyle->SetOptFit(1111);
 canv->cd();
 TPad* pad_gr = new TPad("pad_gr","pad_gr",0,.3,1.,1.);
 pad_gr->SetGridx();
 pad_gr->SetGridy();
 pad_gr->Draw();
 pad_gr->cd();
 canv->Update();

 vector<TGraphAsymmErrors*> vect_gr;
 for(int i = 0; i < int(funcs.size()); i++)
 {
  TGraphAsymmErrors* gr = (TGraphAsymmErrors*)(gr_given->Clone());
  Format_Graph(gr);
  vect_gr.push_back(gr);
 }
 vector<TPaveStats*> vect_stats;
 vector<TLegend> vect_leg;

 string XTitle = vect_gr[0]->GetXaxis()->GetTitle();
 double y1 = 0.8;
 double y2 = 0.8-.06*(funcs[0]->GetNpar());

 TMultiGraph* mg = new TMultiGraph();

 for(int i = 0; i < int(funcs.size()); i++)
 {
  vect_gr[i]->SetMarkerColor(kWhite);
  vect_gr[i]->SetLineColor(kWhite);
  vect_gr[i]->GetXaxis()->SetTitle("");

  if(invert_colors)
  {
   canv->SetFillColor(kBlack);
   pad_gr->SetFillColor(kBlack);
  }
  funcs[i]->SetNpx(10000);
  funcs[i]->SetLineColor(colors[i]);
  cout << endl << "Fitting " << name << " with " << funcs[i]->GetName() << endl;
  TFitResultPtr result = vect_gr[i]->Fit(funcs[i],"EMS+");
  mg->Add(vect_gr[i]); //

  TLegend leg(0.4,y1,0.6,y2,"");
  leg.SetTextFont(42);
  leg.SetTextSize(0.04);
  leg.SetFillColor(kWhite);
  leg.SetTextColor(colors[i]);
  leg.SetLineColor(colors[i]);
  TString func_name = funcs[i]->GetName();
  leg.AddEntry((TObject*)0, func_name, "");
  TString status_func = gMinuit->fCstatu;
  TString status_func_leg = "Status = ";
  status_func_leg+=status_func;
  leg.AddEntry((TObject*)0, status_func_leg, "");
  if(invert_colors)
  {
   leg.SetFillColor(kBlack);
   leg.SetShadowColor(kBlack); 
  }
  vect_leg.push_back(leg);

  pad_gr->Update();
  
  vect_gr[i]->Draw("AP SAMES"); //
  pad_gr->Update();
  canv->Update();
  TPaveStats *stats = (TPaveStats*)vect_gr[i]->GetListOfFunctions()->FindObject("stats");
  string stats_name = funcs[i]->GetName();
  stats->SetName(("stats_"+stats_name).c_str());
  stats->SetTextColor(colors[i]);
  stats->SetLineColor(colors[i]);
  stats->SetY1NDC(y1);
  stats->SetY2NDC(y2);
  y1 = y2;
  y2 = y2-.06*(funcs[i]->GetNpar());
  stats->SetX1NDC(0.6);
  stats->SetX2NDC(0.9);
  vect_stats.push_back(stats);
  pad_gr->Update();
  
  if(invert_colors)
  {
   stats->SetFillColor(kBlack);
  }
  pad_gr->Clear();
  pad_gr->Update();
  canv->Update();

  Output_Fit(funcs[i],name,string(status_func),result);

 }
 mg->Draw("AP SAMES");
 Format_Graph(mg);
 mg->GetYaxis()->SetTitle("Efficiency");
 for(int i = 0; i < int(funcs.size()); i++)
 {
  vect_leg[i].Draw("");
  vect_stats[i]->Draw("SAMES");
  //funcs[i]->Draw("SAMES");
 }
 pad_gr->Update();
 pad_gr->Modified();
 canv->Update();
 TLatex l;
 if(invert_colors)
 {
  l.SetTextColor(kWhite);
 }
 
 l.SetTextFont(42);
 l.SetNDC();
 l.SetTextSize(0.04);
 l.SetTextFont(42);
 l.DrawLatex(0.55,0.93,name.c_str());
 l.DrawLatex(0.13,0.93,"#bf{#it{CMS}} Internal 13 TeV Simulation");

 pad_gr->Update();
 canv->Update();

 canv->cd();
 TPad *pad_res = new TPad("pad_res", "pad_res", 0, 0.03, 1, 0.3);
 pad_res->SetGridx();
 pad_res->SetGridy();
 pad_res->SetTopMargin(1.3);
 pad_res->SetBottomMargin(0.2);
 pad_res->Draw();
 pad_res->cd();
 pad_res->Update();
 canv->Update();

 TMultiGraph* mg_res = new TMultiGraph();
 TGraphAsymmErrors* res = NULL;
 for(int i = 0; i < int(funcs.size()); i++)
 {
  res=TGAE_TF1(vect_gr[i],funcs[i]);
  Format_Graph(res);
  res->SetMarkerColor(colors[i]);
  res->SetLineColor(colors[i]);

  if(invert_colors)
  {
   pad_res->SetFillColor(kBlack);
  }
  mg_res->Add(res);
 }

 mg_res->Draw("AP");
 mg_res->GetXaxis()->SetLimits(mg->GetXaxis()->GetXmin(),mg->GetXaxis()->GetXmax());
 mg_res->GetXaxis()->SetTitle(XTitle.c_str());
 mg_res->GetYaxis()->SetTitle("Eff - Fit");
 Format_Graph_res(mg_res);
 pad_res->Modified();
 pad_res->Update();

 TLine* line = new TLine(mg_res->GetXaxis()->GetXmin(),0.0,mg_res->GetXaxis()->GetXmax(),0.0);
 line->SetLineColor(kWhite);
 line->SetLineStyle(1);
 line->Draw("SAMES");
 pad_res->Update();
 pad_res->Modified();
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
