#include "XsecTool.hh"
#include <math.h>

XsecTool::XsecTool(){

}

XsecTool::~XsecTool(){

}

double XsecTool::GetXsec_BKG(const std::string& dataset) const {
  if(m_Label2Xsec_BKG.count(dataset) == 0)
    return 0.;

  return m_Label2Xsec_BKG[dataset]*1000.;
}

double XsecTool::GetXsec_SMS(const std::string& dataset, double MP) const {
  std::string label = "";
  double BR = 1.;
  if(m_N_SMS.count(dataset) > 0)
    label = dataset;
  else {
    if((dataset.find("C1N1")!=std::string::npos)){
      label = "CN_hino";
    }
    if((dataset.find("C1C1")!=std::string::npos)){
      label = "C1C1_hino";
    }
    if((dataset.find("TChiZZ")!=std::string::npos)){
      label = "N1N2_hino";
      if(dataset.find("ZToLL")!= std::string::npos)
	BR = 0.1; // fixme
      if(dataset.find("ZToLL_ZToLL")!= std::string::npos)
	BR = 0.01; // fixme
    }
    if((dataset.find("TChiWZ")!=std::string::npos) ||
       (dataset.find("TChiWG")!=std::string::npos)){
      label = "C1N2_wino";
      if(dataset.find("ZToLL")!= std::string::npos)
	BR = 0.1; // fixme
    }
    if((dataset.find("TChiWH")!=std::string::npos) ||
       (dataset.find("N2C1")!=std::string::npos)){
      label = "C1N2_hino";
      if(dataset.find("HToGG")!= std::string::npos)
	BR = 0.002; // fixme
      if(dataset.find("HToBB")!= std::string::npos)
	BR = 0.6; // fixme
      if(dataset.find("WToLNu")!= std::string::npos)
	BR = 0.3; // fixme
    }
    if((dataset.find("T2tt")!=std::string::npos) ||
       (dataset.find("T2cc")!=std::string::npos) ||
       (dataset.find("T2bW")!=std::string::npos) ||
       (dataset.find("T2-4bd")!=std::string::npos)){
      label = "StopStop";
    }
  }

  if(m_N_SMS.count(label) == 0)
    return 0.;

  int N = m_N_SMS[label];
  
  if(MP < m_Label2Mass_SMS[label][0] ||
     MP > m_Label2Mass_SMS[label][N-1])
    return 0.;

  for(int i = 0; i < N-1; i++){
    if(MP <= m_Label2Mass_SMS[label][i+1]){
      double x1 = m_Label2Mass_SMS[label][i];
      double x2 = m_Label2Mass_SMS[label][i+1];
      double y1 = m_Label2Xsec_SMS[label][i];
      double y2 = m_Label2Xsec_SMS[label][i+1];
      double beta = log(y1/y2)/(x2-x1);
      return BR*y1*exp(beta*(x1-MP));
    }
  }
  
  return 0.;
}

std::map<std::string,double> XsecTool::InitMap_Xsec_BKG(){
  std::map<std::string,double> Label2Xsec;
  
  Label2Xsec["DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_120to170_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_15to30_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_170to300_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_300to470_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_30to50_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_470to600_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_50to80_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_600to800_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_800to1000_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_80to120_TuneCP5_13TeV_pythia8"] = 1;
  Label2Xsec["QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8"] = 1;
  Label2Xsec["ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"] = 1;
  Label2Xsec["ST_t-channel_antitop_5f_TuneCP5_PSweights_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1"] = 1;
  Label2Xsec["ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"] = 1;
  Label2Xsec["ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"] = 1;
  Label2Xsec["ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8"] = 1;
  Label2Xsec["TTJets_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8"] = 1;
  Label2Xsec["TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["TTToHadronic_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["TTWH_TuneCP5_13TeV-madgraph-pythia8"] = 1;
  Label2Xsec["TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8"] = 1;
  Label2Xsec["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] = 1;
  Label2Xsec["TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8"] = 1;
  Label2Xsec["TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] = 1;
  Label2Xsec["TTWW_TuneCP5_13TeV-madgraph-pythia8"] = 1;
  Label2Xsec["TTWZ_TuneCP5_13TeV-madgraph-pythia8"] = 1;
  Label2Xsec["TTZH_TuneCP5_13TeV-madgraph-pythia8"] = 1;
  Label2Xsec["TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["TTZZ_TuneCP5_13TeV-madgraph-pythia8"] = 1;
  Label2Xsec["WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["WWG_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WWG_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WWTo2L2Nu_13TeV-powheg"] = 1;
  Label2Xsec["WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["WWTo4Q_13TeV-powheg"] = 1;
  Label2Xsec["WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["WWToLNuQQ_13TeV-powheg"] = 1;
  Label2Xsec["WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["WW_TuneCP5_13TeV-pythia8"] = 1;
  Label2Xsec["WZ_TuneCP5_13TeV-pythia8"] = 1;
  Label2Xsec["WZ_TuneCUETP8M1_13TeV-pythia8"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-100To200_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-1200To2500_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-200To400_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-400To600_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-600To800_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToNuNu_HT-800To1200_13TeV-madgraph"] = 1;
  Label2Xsec["ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["ZJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["ZJetsToQQ_HT600to800_3j_TuneCP5_13TeV-madgraphMLM-pythia8"] = 1;
  Label2Xsec["ZZTo2L2Nu_13TeV_powheg_pythia8"] = 1;
  Label2Xsec["ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8"] = 1;
  Label2Xsec["ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8"] = 1;
  Label2Xsec["ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8"] = 1;
  Label2Xsec["ZZTo4L_13TeV_powheg_pythia8"] = 1;
  Label2Xsec["ZZTo4Q_13TeV_amcatnloFXFX_madspin_pythia8"] = 1;
  Label2Xsec["ZZZ_TuneCP5_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 1;
  Label2Xsec["ZZ_TuneCP5_13TeV-pythia8"] = 1;
  Label2Xsec["ttH_M125_TuneCP5_13TeV-powheg-pythia8"] = 1;
  Label2Xsec["ttWJets_TuneCP5_13TeV_madgraphMLM_pythia8"] = 1;
  Label2Xsec["ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8"] = 1;

  return Label2Xsec;
}

std::map<std::string,int> XsecTool::InitMap_N_SMS(){
  std::map<std::string,int> N_SMS;

  N_SMS["C1C1_hino"] = 57;
  N_SMS["C1C1_wino"] = 57;
  N_SMS["C1N2_hino"] = 57;
  N_SMS["C1N2_wino"] = 57;
  N_SMS["C1mN2_wino"] = 57;
  N_SMS["C1pN2_wino"] = 57;
  N_SMS["CN_hino"] = 28;
  N_SMS["N1N2_hino"] = 28;
  N_SMS["SlepSlep_left"] = 10;
  N_SMS["SlepSlep_right"] = 10;
  N_SMS["StopStop"] = 381;
  
  return N_SMS;
}

std::map<std::string,std::vector<double> > XsecTool::InitMap_Mass_SMS(){
  std::map<std::string,std::vector<double> > Label2Mass; 

  Label2Mass["C1C1_hino"] = std::vector<double>();
  Label2Mass["C1C1_hino"].push_back(100);
  Label2Mass["C1C1_hino"].push_back(125);
  Label2Mass["C1C1_hino"].push_back(150);
  Label2Mass["C1C1_hino"].push_back(175);
  Label2Mass["C1C1_hino"].push_back(200);
  Label2Mass["C1C1_hino"].push_back(225);
  Label2Mass["C1C1_hino"].push_back(250);
  Label2Mass["C1C1_hino"].push_back(275);
  Label2Mass["C1C1_hino"].push_back(300);
  Label2Mass["C1C1_hino"].push_back(325);
  Label2Mass["C1C1_hino"].push_back(350);
  Label2Mass["C1C1_hino"].push_back(375);
  Label2Mass["C1C1_hino"].push_back(400);
  Label2Mass["C1C1_hino"].push_back(425);
  Label2Mass["C1C1_hino"].push_back(450);
  Label2Mass["C1C1_hino"].push_back(475);
  Label2Mass["C1C1_hino"].push_back(500);
  Label2Mass["C1C1_hino"].push_back(525);
  Label2Mass["C1C1_hino"].push_back(550);
  Label2Mass["C1C1_hino"].push_back(575);
  Label2Mass["C1C1_hino"].push_back(600);
  Label2Mass["C1C1_hino"].push_back(625);
  Label2Mass["C1C1_hino"].push_back(650);
  Label2Mass["C1C1_hino"].push_back(675);
  Label2Mass["C1C1_hino"].push_back(700);
  Label2Mass["C1C1_hino"].push_back(725);
  Label2Mass["C1C1_hino"].push_back(750);
  Label2Mass["C1C1_hino"].push_back(775);
  Label2Mass["C1C1_hino"].push_back(800);
  Label2Mass["C1C1_hino"].push_back(825);
  Label2Mass["C1C1_hino"].push_back(850);
  Label2Mass["C1C1_hino"].push_back(875);
  Label2Mass["C1C1_hino"].push_back(900);
  Label2Mass["C1C1_hino"].push_back(925);
  Label2Mass["C1C1_hino"].push_back(950);
  Label2Mass["C1C1_hino"].push_back(975);
  Label2Mass["C1C1_hino"].push_back(1000);
  Label2Mass["C1C1_hino"].push_back(1025);
  Label2Mass["C1C1_hino"].push_back(1050);
  Label2Mass["C1C1_hino"].push_back(1075);
  Label2Mass["C1C1_hino"].push_back(1100);
  Label2Mass["C1C1_hino"].push_back(1125);
  Label2Mass["C1C1_hino"].push_back(1150);
  Label2Mass["C1C1_hino"].push_back(1175);
  Label2Mass["C1C1_hino"].push_back(1200);
  Label2Mass["C1C1_hino"].push_back(1225);
  Label2Mass["C1C1_hino"].push_back(1250);
  Label2Mass["C1C1_hino"].push_back(1275);
  Label2Mass["C1C1_hino"].push_back(1300);
  Label2Mass["C1C1_hino"].push_back(1325);
  Label2Mass["C1C1_hino"].push_back(1350);
  Label2Mass["C1C1_hino"].push_back(1375);
  Label2Mass["C1C1_hino"].push_back(1400);
  Label2Mass["C1C1_hino"].push_back(1425);
  Label2Mass["C1C1_hino"].push_back(1450);
  Label2Mass["C1C1_hino"].push_back(1475);
  Label2Mass["C1C1_hino"].push_back(1500);

  Label2Mass["C1C1_wino"] = std::vector<double>();
  Label2Mass["C1C1_wino"].push_back(100);
  Label2Mass["C1C1_wino"].push_back(125);
  Label2Mass["C1C1_wino"].push_back(150);
  Label2Mass["C1C1_wino"].push_back(175);
  Label2Mass["C1C1_wino"].push_back(200);
  Label2Mass["C1C1_wino"].push_back(225);
  Label2Mass["C1C1_wino"].push_back(250);
  Label2Mass["C1C1_wino"].push_back(275);
  Label2Mass["C1C1_wino"].push_back(300);
  Label2Mass["C1C1_wino"].push_back(325);
  Label2Mass["C1C1_wino"].push_back(350);
  Label2Mass["C1C1_wino"].push_back(375);
  Label2Mass["C1C1_wino"].push_back(400);
  Label2Mass["C1C1_wino"].push_back(425);
  Label2Mass["C1C1_wino"].push_back(450);
  Label2Mass["C1C1_wino"].push_back(475);
  Label2Mass["C1C1_wino"].push_back(500);
  Label2Mass["C1C1_wino"].push_back(525);
  Label2Mass["C1C1_wino"].push_back(550);
  Label2Mass["C1C1_wino"].push_back(575);
  Label2Mass["C1C1_wino"].push_back(600);
  Label2Mass["C1C1_wino"].push_back(625);
  Label2Mass["C1C1_wino"].push_back(650);
  Label2Mass["C1C1_wino"].push_back(675);
  Label2Mass["C1C1_wino"].push_back(700);
  Label2Mass["C1C1_wino"].push_back(725);
  Label2Mass["C1C1_wino"].push_back(750);
  Label2Mass["C1C1_wino"].push_back(775);
  Label2Mass["C1C1_wino"].push_back(800);
  Label2Mass["C1C1_wino"].push_back(825);
  Label2Mass["C1C1_wino"].push_back(850);
  Label2Mass["C1C1_wino"].push_back(875);
  Label2Mass["C1C1_wino"].push_back(900);
  Label2Mass["C1C1_wino"].push_back(925);
  Label2Mass["C1C1_wino"].push_back(950);
  Label2Mass["C1C1_wino"].push_back(975);
  Label2Mass["C1C1_wino"].push_back(1000);
  Label2Mass["C1C1_wino"].push_back(1025);
  Label2Mass["C1C1_wino"].push_back(1050);
  Label2Mass["C1C1_wino"].push_back(1075);
  Label2Mass["C1C1_wino"].push_back(1100);
  Label2Mass["C1C1_wino"].push_back(1125);
  Label2Mass["C1C1_wino"].push_back(1150);
  Label2Mass["C1C1_wino"].push_back(1175);
  Label2Mass["C1C1_wino"].push_back(1200);
  Label2Mass["C1C1_wino"].push_back(1225);
  Label2Mass["C1C1_wino"].push_back(1250);
  Label2Mass["C1C1_wino"].push_back(1275);
  Label2Mass["C1C1_wino"].push_back(1300);
  Label2Mass["C1C1_wino"].push_back(1325);
  Label2Mass["C1C1_wino"].push_back(1350);
  Label2Mass["C1C1_wino"].push_back(1375);
  Label2Mass["C1C1_wino"].push_back(1400);
  Label2Mass["C1C1_wino"].push_back(1425);
  Label2Mass["C1C1_wino"].push_back(1450);
  Label2Mass["C1C1_wino"].push_back(1475);
  Label2Mass["C1C1_wino"].push_back(1500);

  Label2Mass["C1N2_hino"] = std::vector<double>();
  Label2Mass["C1N2_hino"].push_back(100);
  Label2Mass["C1N2_hino"].push_back(125);
  Label2Mass["C1N2_hino"].push_back(150);
  Label2Mass["C1N2_hino"].push_back(175);
  Label2Mass["C1N2_hino"].push_back(200);
  Label2Mass["C1N2_hino"].push_back(225);
  Label2Mass["C1N2_hino"].push_back(250);
  Label2Mass["C1N2_hino"].push_back(275);
  Label2Mass["C1N2_hino"].push_back(300);
  Label2Mass["C1N2_hino"].push_back(325);
  Label2Mass["C1N2_hino"].push_back(350);
  Label2Mass["C1N2_hino"].push_back(375);
  Label2Mass["C1N2_hino"].push_back(400);
  Label2Mass["C1N2_hino"].push_back(425);
  Label2Mass["C1N2_hino"].push_back(450);
  Label2Mass["C1N2_hino"].push_back(475);
  Label2Mass["C1N2_hino"].push_back(500);
  Label2Mass["C1N2_hino"].push_back(525);
  Label2Mass["C1N2_hino"].push_back(550);
  Label2Mass["C1N2_hino"].push_back(575);
  Label2Mass["C1N2_hino"].push_back(600);
  Label2Mass["C1N2_hino"].push_back(625);
  Label2Mass["C1N2_hino"].push_back(650);
  Label2Mass["C1N2_hino"].push_back(675);
  Label2Mass["C1N2_hino"].push_back(700);
  Label2Mass["C1N2_hino"].push_back(725);
  Label2Mass["C1N2_hino"].push_back(750);
  Label2Mass["C1N2_hino"].push_back(775);
  Label2Mass["C1N2_hino"].push_back(800);
  Label2Mass["C1N2_hino"].push_back(825);
  Label2Mass["C1N2_hino"].push_back(850);
  Label2Mass["C1N2_hino"].push_back(875);
  Label2Mass["C1N2_hino"].push_back(900);
  Label2Mass["C1N2_hino"].push_back(925);
  Label2Mass["C1N2_hino"].push_back(950);
  Label2Mass["C1N2_hino"].push_back(975);
  Label2Mass["C1N2_hino"].push_back(1000);
  Label2Mass["C1N2_hino"].push_back(1025);
  Label2Mass["C1N2_hino"].push_back(1050);
  Label2Mass["C1N2_hino"].push_back(1075);
  Label2Mass["C1N2_hino"].push_back(1100);
  Label2Mass["C1N2_hino"].push_back(1125);
  Label2Mass["C1N2_hino"].push_back(1150);
  Label2Mass["C1N2_hino"].push_back(1175);
  Label2Mass["C1N2_hino"].push_back(1200);
  Label2Mass["C1N2_hino"].push_back(1225);
  Label2Mass["C1N2_hino"].push_back(1250);
  Label2Mass["C1N2_hino"].push_back(1275);
  Label2Mass["C1N2_hino"].push_back(1300);
  Label2Mass["C1N2_hino"].push_back(1325);
  Label2Mass["C1N2_hino"].push_back(1350);
  Label2Mass["C1N2_hino"].push_back(1375);
  Label2Mass["C1N2_hino"].push_back(1400);
  Label2Mass["C1N2_hino"].push_back(1425);
  Label2Mass["C1N2_hino"].push_back(1450);
  Label2Mass["C1N2_hino"].push_back(1475);
  Label2Mass["C1N2_hino"].push_back(1500);

  Label2Mass["C1N2_wino"] = std::vector<double>();
  Label2Mass["C1N2_wino"].push_back(100);
  Label2Mass["C1N2_wino"].push_back(125);
  Label2Mass["C1N2_wino"].push_back(150);
  Label2Mass["C1N2_wino"].push_back(175);
  Label2Mass["C1N2_wino"].push_back(200);
  Label2Mass["C1N2_wino"].push_back(225);
  Label2Mass["C1N2_wino"].push_back(250);
  Label2Mass["C1N2_wino"].push_back(275);
  Label2Mass["C1N2_wino"].push_back(300);
  Label2Mass["C1N2_wino"].push_back(325);
  Label2Mass["C1N2_wino"].push_back(350);
  Label2Mass["C1N2_wino"].push_back(375);
  Label2Mass["C1N2_wino"].push_back(400);
  Label2Mass["C1N2_wino"].push_back(425);
  Label2Mass["C1N2_wino"].push_back(450);
  Label2Mass["C1N2_wino"].push_back(475);
  Label2Mass["C1N2_wino"].push_back(500);
  Label2Mass["C1N2_wino"].push_back(525);
  Label2Mass["C1N2_wino"].push_back(550);
  Label2Mass["C1N2_wino"].push_back(575);
  Label2Mass["C1N2_wino"].push_back(600);
  Label2Mass["C1N2_wino"].push_back(625);
  Label2Mass["C1N2_wino"].push_back(650);
  Label2Mass["C1N2_wino"].push_back(675);
  Label2Mass["C1N2_wino"].push_back(700);
  Label2Mass["C1N2_wino"].push_back(725);
  Label2Mass["C1N2_wino"].push_back(750);
  Label2Mass["C1N2_wino"].push_back(775);
  Label2Mass["C1N2_wino"].push_back(800);
  Label2Mass["C1N2_wino"].push_back(825);
  Label2Mass["C1N2_wino"].push_back(850);
  Label2Mass["C1N2_wino"].push_back(875);
  Label2Mass["C1N2_wino"].push_back(900);
  Label2Mass["C1N2_wino"].push_back(925);
  Label2Mass["C1N2_wino"].push_back(950);
  Label2Mass["C1N2_wino"].push_back(975);
  Label2Mass["C1N2_wino"].push_back(1000);
  Label2Mass["C1N2_wino"].push_back(1025);
  Label2Mass["C1N2_wino"].push_back(1050);
  Label2Mass["C1N2_wino"].push_back(1075);
  Label2Mass["C1N2_wino"].push_back(1100);
  Label2Mass["C1N2_wino"].push_back(1125);
  Label2Mass["C1N2_wino"].push_back(1150);
  Label2Mass["C1N2_wino"].push_back(1175);
  Label2Mass["C1N2_wino"].push_back(1200);
  Label2Mass["C1N2_wino"].push_back(1225);
  Label2Mass["C1N2_wino"].push_back(1250);
  Label2Mass["C1N2_wino"].push_back(1275);
  Label2Mass["C1N2_wino"].push_back(1300);
  Label2Mass["C1N2_wino"].push_back(1325);
  Label2Mass["C1N2_wino"].push_back(1350);
  Label2Mass["C1N2_wino"].push_back(1375);
  Label2Mass["C1N2_wino"].push_back(1400);
  Label2Mass["C1N2_wino"].push_back(1425);
  Label2Mass["C1N2_wino"].push_back(1450);
  Label2Mass["C1N2_wino"].push_back(1475);
  Label2Mass["C1N2_wino"].push_back(1500);

  Label2Mass["C1mN2_wino"] = std::vector<double>();
  Label2Mass["C1mN2_wino"].push_back(100);
  Label2Mass["C1mN2_wino"].push_back(125);
  Label2Mass["C1mN2_wino"].push_back(150);
  Label2Mass["C1mN2_wino"].push_back(175);
  Label2Mass["C1mN2_wino"].push_back(200);
  Label2Mass["C1mN2_wino"].push_back(225);
  Label2Mass["C1mN2_wino"].push_back(250);
  Label2Mass["C1mN2_wino"].push_back(275);
  Label2Mass["C1mN2_wino"].push_back(300);
  Label2Mass["C1mN2_wino"].push_back(325);
  Label2Mass["C1mN2_wino"].push_back(350);
  Label2Mass["C1mN2_wino"].push_back(375);
  Label2Mass["C1mN2_wino"].push_back(400);
  Label2Mass["C1mN2_wino"].push_back(425);
  Label2Mass["C1mN2_wino"].push_back(450);
  Label2Mass["C1mN2_wino"].push_back(475);
  Label2Mass["C1mN2_wino"].push_back(500);
  Label2Mass["C1mN2_wino"].push_back(525);
  Label2Mass["C1mN2_wino"].push_back(550);
  Label2Mass["C1mN2_wino"].push_back(575);
  Label2Mass["C1mN2_wino"].push_back(600);
  Label2Mass["C1mN2_wino"].push_back(625);
  Label2Mass["C1mN2_wino"].push_back(650);
  Label2Mass["C1mN2_wino"].push_back(675);
  Label2Mass["C1mN2_wino"].push_back(700);
  Label2Mass["C1mN2_wino"].push_back(725);
  Label2Mass["C1mN2_wino"].push_back(750);
  Label2Mass["C1mN2_wino"].push_back(775);
  Label2Mass["C1mN2_wino"].push_back(800);
  Label2Mass["C1mN2_wino"].push_back(825);
  Label2Mass["C1mN2_wino"].push_back(850);
  Label2Mass["C1mN2_wino"].push_back(875);
  Label2Mass["C1mN2_wino"].push_back(900);
  Label2Mass["C1mN2_wino"].push_back(925);
  Label2Mass["C1mN2_wino"].push_back(950);
  Label2Mass["C1mN2_wino"].push_back(975);
  Label2Mass["C1mN2_wino"].push_back(1000);
  Label2Mass["C1mN2_wino"].push_back(1025);
  Label2Mass["C1mN2_wino"].push_back(1050);
  Label2Mass["C1mN2_wino"].push_back(1075);
  Label2Mass["C1mN2_wino"].push_back(1100);
  Label2Mass["C1mN2_wino"].push_back(1125);
  Label2Mass["C1mN2_wino"].push_back(1150);
  Label2Mass["C1mN2_wino"].push_back(1175);
  Label2Mass["C1mN2_wino"].push_back(1200);
  Label2Mass["C1mN2_wino"].push_back(1225);
  Label2Mass["C1mN2_wino"].push_back(1250);
  Label2Mass["C1mN2_wino"].push_back(1275);
  Label2Mass["C1mN2_wino"].push_back(1300);
  Label2Mass["C1mN2_wino"].push_back(1325);
  Label2Mass["C1mN2_wino"].push_back(1350);
  Label2Mass["C1mN2_wino"].push_back(1375);
  Label2Mass["C1mN2_wino"].push_back(1400);
  Label2Mass["C1mN2_wino"].push_back(1425);
  Label2Mass["C1mN2_wino"].push_back(1450);
  Label2Mass["C1mN2_wino"].push_back(1475);
  Label2Mass["C1mN2_wino"].push_back(1500);

  Label2Mass["C1pN2_wino"] = std::vector<double>();
  Label2Mass["C1pN2_wino"].push_back(100);
  Label2Mass["C1pN2_wino"].push_back(125);
  Label2Mass["C1pN2_wino"].push_back(150);
  Label2Mass["C1pN2_wino"].push_back(175);
  Label2Mass["C1pN2_wino"].push_back(200);
  Label2Mass["C1pN2_wino"].push_back(225);
  Label2Mass["C1pN2_wino"].push_back(250);
  Label2Mass["C1pN2_wino"].push_back(275);
  Label2Mass["C1pN2_wino"].push_back(300);
  Label2Mass["C1pN2_wino"].push_back(325);
  Label2Mass["C1pN2_wino"].push_back(350);
  Label2Mass["C1pN2_wino"].push_back(375);
  Label2Mass["C1pN2_wino"].push_back(400);
  Label2Mass["C1pN2_wino"].push_back(425);
  Label2Mass["C1pN2_wino"].push_back(450);
  Label2Mass["C1pN2_wino"].push_back(475);
  Label2Mass["C1pN2_wino"].push_back(500);
  Label2Mass["C1pN2_wino"].push_back(525);
  Label2Mass["C1pN2_wino"].push_back(550);
  Label2Mass["C1pN2_wino"].push_back(575);
  Label2Mass["C1pN2_wino"].push_back(600);
  Label2Mass["C1pN2_wino"].push_back(625);
  Label2Mass["C1pN2_wino"].push_back(650);
  Label2Mass["C1pN2_wino"].push_back(675);
  Label2Mass["C1pN2_wino"].push_back(700);
  Label2Mass["C1pN2_wino"].push_back(725);
  Label2Mass["C1pN2_wino"].push_back(750);
  Label2Mass["C1pN2_wino"].push_back(775);
  Label2Mass["C1pN2_wino"].push_back(800);
  Label2Mass["C1pN2_wino"].push_back(825);
  Label2Mass["C1pN2_wino"].push_back(850);
  Label2Mass["C1pN2_wino"].push_back(875);
  Label2Mass["C1pN2_wino"].push_back(900);
  Label2Mass["C1pN2_wino"].push_back(925);
  Label2Mass["C1pN2_wino"].push_back(950);
  Label2Mass["C1pN2_wino"].push_back(975);
  Label2Mass["C1pN2_wino"].push_back(1000);
  Label2Mass["C1pN2_wino"].push_back(1025);
  Label2Mass["C1pN2_wino"].push_back(1050);
  Label2Mass["C1pN2_wino"].push_back(1075);
  Label2Mass["C1pN2_wino"].push_back(1100);
  Label2Mass["C1pN2_wino"].push_back(1125);
  Label2Mass["C1pN2_wino"].push_back(1150);
  Label2Mass["C1pN2_wino"].push_back(1175);
  Label2Mass["C1pN2_wino"].push_back(1200);
  Label2Mass["C1pN2_wino"].push_back(1225);
  Label2Mass["C1pN2_wino"].push_back(1250);
  Label2Mass["C1pN2_wino"].push_back(1275);
  Label2Mass["C1pN2_wino"].push_back(1300);
  Label2Mass["C1pN2_wino"].push_back(1325);
  Label2Mass["C1pN2_wino"].push_back(1350);
  Label2Mass["C1pN2_wino"].push_back(1375);
  Label2Mass["C1pN2_wino"].push_back(1400);
  Label2Mass["C1pN2_wino"].push_back(1425);
  Label2Mass["C1pN2_wino"].push_back(1450);
  Label2Mass["C1pN2_wino"].push_back(1475);
  Label2Mass["C1pN2_wino"].push_back(1500);

  Label2Mass["CN_hino"] = std::vector<double>();
  Label2Mass["CN_hino"].push_back(100);
  Label2Mass["CN_hino"].push_back(150);
  Label2Mass["CN_hino"].push_back(200);
  Label2Mass["CN_hino"].push_back(250);
  Label2Mass["CN_hino"].push_back(300);
  Label2Mass["CN_hino"].push_back(350);
  Label2Mass["CN_hino"].push_back(400);
  Label2Mass["CN_hino"].push_back(450);
  Label2Mass["CN_hino"].push_back(500);
  Label2Mass["CN_hino"].push_back(550);
  Label2Mass["CN_hino"].push_back(600);
  Label2Mass["CN_hino"].push_back(650);
  Label2Mass["CN_hino"].push_back(700);
  Label2Mass["CN_hino"].push_back(750);
  Label2Mass["CN_hino"].push_back(800);
  Label2Mass["CN_hino"].push_back(850);
  Label2Mass["CN_hino"].push_back(900);
  Label2Mass["CN_hino"].push_back(950);
  Label2Mass["CN_hino"].push_back(1000);
  Label2Mass["CN_hino"].push_back(1050);
  Label2Mass["CN_hino"].push_back(1100);
  Label2Mass["CN_hino"].push_back(1150);
  Label2Mass["CN_hino"].push_back(1200);
  Label2Mass["CN_hino"].push_back(1250);
  Label2Mass["CN_hino"].push_back(1300);
  Label2Mass["CN_hino"].push_back(1350);
  Label2Mass["CN_hino"].push_back(1400);
  Label2Mass["CN_hino"].push_back(1450);

  Label2Mass["N1N2_hino"] = std::vector<double>();
  Label2Mass["N1N2_hino"].push_back(100);
  Label2Mass["N1N2_hino"].push_back(150);
  Label2Mass["N1N2_hino"].push_back(200);
  Label2Mass["N1N2_hino"].push_back(250);
  Label2Mass["N1N2_hino"].push_back(300);
  Label2Mass["N1N2_hino"].push_back(350);
  Label2Mass["N1N2_hino"].push_back(400);
  Label2Mass["N1N2_hino"].push_back(450);
  Label2Mass["N1N2_hino"].push_back(500);
  Label2Mass["N1N2_hino"].push_back(550);
  Label2Mass["N1N2_hino"].push_back(600);
  Label2Mass["N1N2_hino"].push_back(650);
  Label2Mass["N1N2_hino"].push_back(700);
  Label2Mass["N1N2_hino"].push_back(750);
  Label2Mass["N1N2_hino"].push_back(800);
  Label2Mass["N1N2_hino"].push_back(850);
  Label2Mass["N1N2_hino"].push_back(900);
  Label2Mass["N1N2_hino"].push_back(950);
  Label2Mass["N1N2_hino"].push_back(1000);
  Label2Mass["N1N2_hino"].push_back(1050);
  Label2Mass["N1N2_hino"].push_back(1100);
  Label2Mass["N1N2_hino"].push_back(1150);
  Label2Mass["N1N2_hino"].push_back(1200);
  Label2Mass["N1N2_hino"].push_back(1250);
  Label2Mass["N1N2_hino"].push_back(1300);
  Label2Mass["N1N2_hino"].push_back(1350);
  Label2Mass["N1N2_hino"].push_back(1400);
  Label2Mass["N1N2_hino"].push_back(1450);

  Label2Mass["SlepSlep_left"] = std::vector<double>();
  Label2Mass["SlepSlep_left"].push_back(50);
  Label2Mass["SlepSlep_left"].push_back(100);
  Label2Mass["SlepSlep_left"].push_back(150);
  Label2Mass["SlepSlep_left"].push_back(200);
  Label2Mass["SlepSlep_left"].push_back(250);
  Label2Mass["SlepSlep_left"].push_back(300);
  Label2Mass["SlepSlep_left"].push_back(350);
  Label2Mass["SlepSlep_left"].push_back(400);
  Label2Mass["SlepSlep_left"].push_back(450);
  Label2Mass["SlepSlep_left"].push_back(500);

  Label2Mass["SlepSlep_right"] = std::vector<double>();
  Label2Mass["SlepSlep_right"].push_back(50);
  Label2Mass["SlepSlep_right"].push_back(100);
  Label2Mass["SlepSlep_right"].push_back(150);
  Label2Mass["SlepSlep_right"].push_back(200);
  Label2Mass["SlepSlep_right"].push_back(250);
  Label2Mass["SlepSlep_right"].push_back(300);
  Label2Mass["SlepSlep_right"].push_back(350);
  Label2Mass["SlepSlep_right"].push_back(400);
  Label2Mass["SlepSlep_right"].push_back(450);
  Label2Mass["SlepSlep_right"].push_back(500);

  Label2Mass["StopStop"].push_back(100.);
  Label2Mass["StopStop"].push_back(105.);
  Label2Mass["StopStop"].push_back(110.); 
  Label2Mass["StopStop"].push_back(115.); 
  Label2Mass["StopStop"].push_back(120.); 
  Label2Mass["StopStop"].push_back(125.); 
  Label2Mass["StopStop"].push_back(130.);
  Label2Mass["StopStop"].push_back(135.); 
  Label2Mass["StopStop"].push_back(140.); 
  Label2Mass["StopStop"].push_back(145.); 
  Label2Mass["StopStop"].push_back(150.); 
  Label2Mass["StopStop"].push_back(155.); 
  Label2Mass["StopStop"].push_back(160.); 
  Label2Mass["StopStop"].push_back(165.); 
  Label2Mass["StopStop"].push_back(170.); 
  Label2Mass["StopStop"].push_back(175.);
  Label2Mass["StopStop"].push_back(180.);
  Label2Mass["StopStop"].push_back(185.); 
  Label2Mass["StopStop"].push_back(190.);
  Label2Mass["StopStop"].push_back(195.);
  Label2Mass["StopStop"].push_back(200.); 
  Label2Mass["StopStop"].push_back(205.); 
  Label2Mass["StopStop"].push_back(210.); 
  Label2Mass["StopStop"].push_back(215.); 
  Label2Mass["StopStop"].push_back(220.); 
  Label2Mass["StopStop"].push_back(225.); 
  Label2Mass["StopStop"].push_back(230.); 
  Label2Mass["StopStop"].push_back(235.); 
  Label2Mass["StopStop"].push_back(240.);
  Label2Mass["StopStop"].push_back(245.);
  Label2Mass["StopStop"].push_back(250.); 
  Label2Mass["StopStop"].push_back(255.); 
  Label2Mass["StopStop"].push_back(260.); 
  Label2Mass["StopStop"].push_back(265.); 
  Label2Mass["StopStop"].push_back(270.); 
  Label2Mass["StopStop"].push_back(275.); 
  Label2Mass["StopStop"].push_back(280.);
  Label2Mass["StopStop"].push_back(285.); 
  Label2Mass["StopStop"].push_back(290.); 
  Label2Mass["StopStop"].push_back(295.); 
  Label2Mass["StopStop"].push_back(300.); 
  Label2Mass["StopStop"].push_back(305.); 
  Label2Mass["StopStop"].push_back(310.); 
  Label2Mass["StopStop"].push_back(315.); 
  Label2Mass["StopStop"].push_back(320.); 
  Label2Mass["StopStop"].push_back(325.); 
  Label2Mass["StopStop"].push_back(330.); 
  Label2Mass["StopStop"].push_back(335.);
  Label2Mass["StopStop"].push_back(340.);
  Label2Mass["StopStop"].push_back(345.); 
  Label2Mass["StopStop"].push_back(350.); 
  Label2Mass["StopStop"].push_back(355.); 
  Label2Mass["StopStop"].push_back(360.); 
  Label2Mass["StopStop"].push_back(365.); 
  Label2Mass["StopStop"].push_back(370.);
  Label2Mass["StopStop"].push_back(375.);
  Label2Mass["StopStop"].push_back(380.); 
  Label2Mass["StopStop"].push_back(385.);
  Label2Mass["StopStop"].push_back(390.);
  Label2Mass["StopStop"].push_back(395.); 
  Label2Mass["StopStop"].push_back(400.);
  Label2Mass["StopStop"].push_back(405.); 
  Label2Mass["StopStop"].push_back(410.); 
  Label2Mass["StopStop"].push_back(415.); 
  Label2Mass["StopStop"].push_back(420.);
  Label2Mass["StopStop"].push_back(425.);
  Label2Mass["StopStop"].push_back(430.); 
  Label2Mass["StopStop"].push_back(435.); 
  Label2Mass["StopStop"].push_back(440.);
  Label2Mass["StopStop"].push_back(445.); 
  Label2Mass["StopStop"].push_back(450.); 
  Label2Mass["StopStop"].push_back(455.); 
  Label2Mass["StopStop"].push_back(460.); 
  Label2Mass["StopStop"].push_back(465.);
  Label2Mass["StopStop"].push_back(470.); 
  Label2Mass["StopStop"].push_back(475.);
  Label2Mass["StopStop"].push_back(480.);
  Label2Mass["StopStop"].push_back(485.);
  Label2Mass["StopStop"].push_back(490.);
  Label2Mass["StopStop"].push_back(495.);
  Label2Mass["StopStop"].push_back(500.); 
  Label2Mass["StopStop"].push_back(505.);
  Label2Mass["StopStop"].push_back(510.);
  Label2Mass["StopStop"].push_back(515.);
  Label2Mass["StopStop"].push_back(520.); 
  Label2Mass["StopStop"].push_back(525.);
  Label2Mass["StopStop"].push_back(530.); 
  Label2Mass["StopStop"].push_back(535.); 
  Label2Mass["StopStop"].push_back(540.);
  Label2Mass["StopStop"].push_back(545.);
  Label2Mass["StopStop"].push_back(550.); 
  Label2Mass["StopStop"].push_back(555.);
  Label2Mass["StopStop"].push_back(560.); 
  Label2Mass["StopStop"].push_back(565.); 
  Label2Mass["StopStop"].push_back(570.);
  Label2Mass["StopStop"].push_back(575.); 
  Label2Mass["StopStop"].push_back(580.); 
  Label2Mass["StopStop"].push_back(585.);
  Label2Mass["StopStop"].push_back(590.); 
  Label2Mass["StopStop"].push_back(595.); 
  Label2Mass["StopStop"].push_back(600.);
  Label2Mass["StopStop"].push_back(605.); 
  Label2Mass["StopStop"].push_back(610.); 
  Label2Mass["StopStop"].push_back(615.); 
  Label2Mass["StopStop"].push_back(620.); 
  Label2Mass["StopStop"].push_back(625.); 
  Label2Mass["StopStop"].push_back(630.);
  Label2Mass["StopStop"].push_back(635.);
  Label2Mass["StopStop"].push_back(640.);
  Label2Mass["StopStop"].push_back(645.); 
  Label2Mass["StopStop"].push_back(650.); 
  Label2Mass["StopStop"].push_back(655.);
  Label2Mass["StopStop"].push_back(660.); 
  Label2Mass["StopStop"].push_back(665.); 
  Label2Mass["StopStop"].push_back(670.);
  Label2Mass["StopStop"].push_back(675.); 
  Label2Mass["StopStop"].push_back(680.); 
  Label2Mass["StopStop"].push_back(685.);
  Label2Mass["StopStop"].push_back(690.); 
  Label2Mass["StopStop"].push_back(695.); 
  Label2Mass["StopStop"].push_back(700.); 
  Label2Mass["StopStop"].push_back(705.);
  Label2Mass["StopStop"].push_back(710.);
  Label2Mass["StopStop"].push_back(715.); 
  Label2Mass["StopStop"].push_back(720.); 
  Label2Mass["StopStop"].push_back(725.);
  Label2Mass["StopStop"].push_back(730.); 
  Label2Mass["StopStop"].push_back(735.); 
  Label2Mass["StopStop"].push_back(740.); 
  Label2Mass["StopStop"].push_back(745.); 
  Label2Mass["StopStop"].push_back(750.); 
  Label2Mass["StopStop"].push_back(755.); 
  Label2Mass["StopStop"].push_back(760.); 
  Label2Mass["StopStop"].push_back(765.); 
  Label2Mass["StopStop"].push_back(770.);
  Label2Mass["StopStop"].push_back(775.);
  Label2Mass["StopStop"].push_back(780.); 
  Label2Mass["StopStop"].push_back(785.); 
  Label2Mass["StopStop"].push_back(790.); 
  Label2Mass["StopStop"].push_back(795.); 
  Label2Mass["StopStop"].push_back(800.); 
  Label2Mass["StopStop"].push_back(805.);
  Label2Mass["StopStop"].push_back(810.); 
  Label2Mass["StopStop"].push_back(815.);
  Label2Mass["StopStop"].push_back(820.);
  Label2Mass["StopStop"].push_back(825.);
  Label2Mass["StopStop"].push_back(830.); 
  Label2Mass["StopStop"].push_back(835.); 
  Label2Mass["StopStop"].push_back(840.);
  Label2Mass["StopStop"].push_back(845.); 
  Label2Mass["StopStop"].push_back(850.);
  Label2Mass["StopStop"].push_back(855.); 
  Label2Mass["StopStop"].push_back(860.);
  Label2Mass["StopStop"].push_back(865.); 
  Label2Mass["StopStop"].push_back(870.); 
  Label2Mass["StopStop"].push_back(875.); 
  Label2Mass["StopStop"].push_back(880.);
  Label2Mass["StopStop"].push_back(885.);
  Label2Mass["StopStop"].push_back(890.);
  Label2Mass["StopStop"].push_back(895.); 
  Label2Mass["StopStop"].push_back(900.); 
  Label2Mass["StopStop"].push_back(905.); 
  Label2Mass["StopStop"].push_back(910.);
  Label2Mass["StopStop"].push_back(915.);
  Label2Mass["StopStop"].push_back(920.);
  Label2Mass["StopStop"].push_back(925.);
  Label2Mass["StopStop"].push_back(930.);
  Label2Mass["StopStop"].push_back(935.);
  Label2Mass["StopStop"].push_back(940.);
  Label2Mass["StopStop"].push_back(945.);
  Label2Mass["StopStop"].push_back(950.);
  Label2Mass["StopStop"].push_back(955.);
  Label2Mass["StopStop"].push_back(960.);
  Label2Mass["StopStop"].push_back(965.);
  Label2Mass["StopStop"].push_back(970.);
  Label2Mass["StopStop"].push_back(975.);
  Label2Mass["StopStop"].push_back(980.);
  Label2Mass["StopStop"].push_back(985.);
  Label2Mass["StopStop"].push_back(990.);
  Label2Mass["StopStop"].push_back(995.);
  Label2Mass["StopStop"].push_back(1000.);
  Label2Mass["StopStop"].push_back(1005.);
  Label2Mass["StopStop"].push_back(1010.);
  Label2Mass["StopStop"].push_back(1015.);
  Label2Mass["StopStop"].push_back(1020.);
  Label2Mass["StopStop"].push_back(1025.);
  Label2Mass["StopStop"].push_back(1030.);
  Label2Mass["StopStop"].push_back(1035.);
  Label2Mass["StopStop"].push_back(1040.);
  Label2Mass["StopStop"].push_back(1045.);
  Label2Mass["StopStop"].push_back(1050.);
  Label2Mass["StopStop"].push_back(1055.);
  Label2Mass["StopStop"].push_back(1060.);
  Label2Mass["StopStop"].push_back(1065.);
  Label2Mass["StopStop"].push_back(1070.);
  Label2Mass["StopStop"].push_back(1075.);
  Label2Mass["StopStop"].push_back(1080.);
  Label2Mass["StopStop"].push_back(1085.);
  Label2Mass["StopStop"].push_back(1090.);
  Label2Mass["StopStop"].push_back(1095.);
  Label2Mass["StopStop"].push_back(1100.);
  Label2Mass["StopStop"].push_back(1105.);
  Label2Mass["StopStop"].push_back(1110.);
  Label2Mass["StopStop"].push_back(1115.);
  Label2Mass["StopStop"].push_back(1120.);
  Label2Mass["StopStop"].push_back(1125.);
  Label2Mass["StopStop"].push_back(1130.);
  Label2Mass["StopStop"].push_back(1135.);
  Label2Mass["StopStop"].push_back(1140.);
  Label2Mass["StopStop"].push_back(1145.);
  Label2Mass["StopStop"].push_back(1150.);
  Label2Mass["StopStop"].push_back(1155.);
  Label2Mass["StopStop"].push_back(1160.);
  Label2Mass["StopStop"].push_back(1165.);
  Label2Mass["StopStop"].push_back(1170.);
  Label2Mass["StopStop"].push_back(1175.);
  Label2Mass["StopStop"].push_back(1180.);
  Label2Mass["StopStop"].push_back(1185.);
  Label2Mass["StopStop"].push_back(1190.);
  Label2Mass["StopStop"].push_back(1195.);
  Label2Mass["StopStop"].push_back(1200.);
  Label2Mass["StopStop"].push_back(1205.);
  Label2Mass["StopStop"].push_back(1210.);
  Label2Mass["StopStop"].push_back(1215.);
  Label2Mass["StopStop"].push_back(1220.);
  Label2Mass["StopStop"].push_back(1225.);
  Label2Mass["StopStop"].push_back(1230.);
  Label2Mass["StopStop"].push_back(1235.);
  Label2Mass["StopStop"].push_back(1240.);
  Label2Mass["StopStop"].push_back(1245.);
  Label2Mass["StopStop"].push_back(1250.);
  Label2Mass["StopStop"].push_back(1255.);
  Label2Mass["StopStop"].push_back(1260.);
  Label2Mass["StopStop"].push_back(1265.);
  Label2Mass["StopStop"].push_back(1270.);
  Label2Mass["StopStop"].push_back(1275.);
  Label2Mass["StopStop"].push_back(1280.);
  Label2Mass["StopStop"].push_back(1285.);
  Label2Mass["StopStop"].push_back(1290.);
  Label2Mass["StopStop"].push_back(1295.);
  Label2Mass["StopStop"].push_back(1300.);
  Label2Mass["StopStop"].push_back(1305.);
  Label2Mass["StopStop"].push_back(1310.);
  Label2Mass["StopStop"].push_back(1315.);
  Label2Mass["StopStop"].push_back(1320.);
  Label2Mass["StopStop"].push_back(1325.);
  Label2Mass["StopStop"].push_back(1330.);
  Label2Mass["StopStop"].push_back(1335.);
  Label2Mass["StopStop"].push_back(1340.);
  Label2Mass["StopStop"].push_back(1345.);
  Label2Mass["StopStop"].push_back(1350.);
  Label2Mass["StopStop"].push_back(1355.);
  Label2Mass["StopStop"].push_back(1360.);
  Label2Mass["StopStop"].push_back(1365.);
  Label2Mass["StopStop"].push_back(1370.);
  Label2Mass["StopStop"].push_back(1375.);
  Label2Mass["StopStop"].push_back(1380.);
  Label2Mass["StopStop"].push_back(1385.);
  Label2Mass["StopStop"].push_back(1390.);
  Label2Mass["StopStop"].push_back(1395.);
  Label2Mass["StopStop"].push_back(1400.);
  Label2Mass["StopStop"].push_back(1405.);
  Label2Mass["StopStop"].push_back(1410.);
  Label2Mass["StopStop"].push_back(1415.);
  Label2Mass["StopStop"].push_back(1420.);
  Label2Mass["StopStop"].push_back(1425.);
  Label2Mass["StopStop"].push_back(1430.);
  Label2Mass["StopStop"].push_back(1435.);
  Label2Mass["StopStop"].push_back(1440.);
  Label2Mass["StopStop"].push_back(1445.);
  Label2Mass["StopStop"].push_back(1450.);
  Label2Mass["StopStop"].push_back(1455.);
  Label2Mass["StopStop"].push_back(1460.);
  Label2Mass["StopStop"].push_back(1465.);
  Label2Mass["StopStop"].push_back(1470.);
  Label2Mass["StopStop"].push_back(1475.);
  Label2Mass["StopStop"].push_back(1480.);
  Label2Mass["StopStop"].push_back(1485.);
  Label2Mass["StopStop"].push_back(1490.);
  Label2Mass["StopStop"].push_back(1495.);
  Label2Mass["StopStop"].push_back(1500.);
  Label2Mass["StopStop"].push_back(1505.);
  Label2Mass["StopStop"].push_back(1510.);
  Label2Mass["StopStop"].push_back(1515.);
  Label2Mass["StopStop"].push_back(1520.);
  Label2Mass["StopStop"].push_back(1525.);
  Label2Mass["StopStop"].push_back(1530.);
  Label2Mass["StopStop"].push_back(1535.);
  Label2Mass["StopStop"].push_back(1540.);
  Label2Mass["StopStop"].push_back(1545.);
  Label2Mass["StopStop"].push_back(1550.);
  Label2Mass["StopStop"].push_back(1555.);
  Label2Mass["StopStop"].push_back(1560.);
  Label2Mass["StopStop"].push_back(1565.);
  Label2Mass["StopStop"].push_back(1570.);
  Label2Mass["StopStop"].push_back(1575.);
  Label2Mass["StopStop"].push_back(1580.);
  Label2Mass["StopStop"].push_back(1585.);
  Label2Mass["StopStop"].push_back(1590.);
  Label2Mass["StopStop"].push_back(1595.);
  Label2Mass["StopStop"].push_back(1600.);
  Label2Mass["StopStop"].push_back(1605.);
  Label2Mass["StopStop"].push_back(1610.);
  Label2Mass["StopStop"].push_back(1615.);
  Label2Mass["StopStop"].push_back(1620.);
  Label2Mass["StopStop"].push_back(1625.);
  Label2Mass["StopStop"].push_back(1630.);
  Label2Mass["StopStop"].push_back(1635.);
  Label2Mass["StopStop"].push_back(1640.);
  Label2Mass["StopStop"].push_back(1645.);
  Label2Mass["StopStop"].push_back(1650.);
  Label2Mass["StopStop"].push_back(1655.);
  Label2Mass["StopStop"].push_back(1660.);
  Label2Mass["StopStop"].push_back(1665.);
  Label2Mass["StopStop"].push_back(1670.);
  Label2Mass["StopStop"].push_back(1675.);
  Label2Mass["StopStop"].push_back(1680.);
  Label2Mass["StopStop"].push_back(1685.);
  Label2Mass["StopStop"].push_back(1690.);
  Label2Mass["StopStop"].push_back(1695.);
  Label2Mass["StopStop"].push_back(1700.);
  Label2Mass["StopStop"].push_back(1705.);
  Label2Mass["StopStop"].push_back(1710.);
  Label2Mass["StopStop"].push_back(1715.);
  Label2Mass["StopStop"].push_back(1720.);
  Label2Mass["StopStop"].push_back(1725.);
  Label2Mass["StopStop"].push_back(1730.);
  Label2Mass["StopStop"].push_back(1735.);
  Label2Mass["StopStop"].push_back(1740.);
  Label2Mass["StopStop"].push_back(1745.);
  Label2Mass["StopStop"].push_back(1750.);
  Label2Mass["StopStop"].push_back(1755.);
  Label2Mass["StopStop"].push_back(1760.);
  Label2Mass["StopStop"].push_back(1765.);
  Label2Mass["StopStop"].push_back(1770.);
  Label2Mass["StopStop"].push_back(1775.);
  Label2Mass["StopStop"].push_back(1780.);
  Label2Mass["StopStop"].push_back(1785.);
  Label2Mass["StopStop"].push_back(1790.);
  Label2Mass["StopStop"].push_back(1795.);
  Label2Mass["StopStop"].push_back(1800.);
  Label2Mass["StopStop"].push_back(1805.);
  Label2Mass["StopStop"].push_back(1810.);
  Label2Mass["StopStop"].push_back(1815.);
  Label2Mass["StopStop"].push_back(1820.);
  Label2Mass["StopStop"].push_back(1825.);
  Label2Mass["StopStop"].push_back(1830.);
  Label2Mass["StopStop"].push_back(1835.);
  Label2Mass["StopStop"].push_back(1840.);
  Label2Mass["StopStop"].push_back(1845.);
  Label2Mass["StopStop"].push_back(1850.);
  Label2Mass["StopStop"].push_back(1855.);
  Label2Mass["StopStop"].push_back(1860.);
  Label2Mass["StopStop"].push_back(1865.);
  Label2Mass["StopStop"].push_back(1870.);
  Label2Mass["StopStop"].push_back(1875.);
  Label2Mass["StopStop"].push_back(1880.);
  Label2Mass["StopStop"].push_back(1885.);
  Label2Mass["StopStop"].push_back(1890.);
  Label2Mass["StopStop"].push_back(1895.);
  Label2Mass["StopStop"].push_back(1900.);
  Label2Mass["StopStop"].push_back(1905.);
  Label2Mass["StopStop"].push_back(1910.);
  Label2Mass["StopStop"].push_back(1915.);
  Label2Mass["StopStop"].push_back(1920.);
  Label2Mass["StopStop"].push_back(1925.);
  Label2Mass["StopStop"].push_back(1930.);
  Label2Mass["StopStop"].push_back(1935.);
  Label2Mass["StopStop"].push_back(1940.);
  Label2Mass["StopStop"].push_back(1945.);
  Label2Mass["StopStop"].push_back(1950.);
  Label2Mass["StopStop"].push_back(1955.);
  Label2Mass["StopStop"].push_back(1960.);
  Label2Mass["StopStop"].push_back(1965.);
  Label2Mass["StopStop"].push_back(1970.);
  Label2Mass["StopStop"].push_back(1975.);
  Label2Mass["StopStop"].push_back(1980.);
  Label2Mass["StopStop"].push_back(1985.);
  Label2Mass["StopStop"].push_back(1990.);
  Label2Mass["StopStop"].push_back(1995.);
  Label2Mass["StopStop"].push_back(2000.);
  
  
  return Label2Mass;
}

std::map<std::string,std::vector<double> > XsecTool::InitMap_Xsec_SMS(){
  std::map<std::string,std::vector<double> > Label2Xsec;

  Label2Xsec["C1C1_hino"] = std::vector<double>();
  Label2Xsec["C1C1_hino"].push_back(2883.67);
  Label2Xsec["C1C1_hino"].push_back(1315.04);
  Label2Xsec["C1C1_hino"].push_back(689.592);
  Label2Xsec["C1C1_hino"].push_back(397.021);
  Label2Xsec["C1C1_hino"].push_back(244.321);
  Label2Xsec["C1C1_hino"].push_back(158.09);
  Label2Xsec["C1C1_hino"].push_back(106.302);
  Label2Xsec["C1C1_hino"].push_back(73.7884);
  Label2Xsec["C1C1_hino"].push_back(52.569);
  Label2Xsec["C1C1_hino"].push_back(38.2794);
  Label2Xsec["C1C1_hino"].push_back(28.3799);
  Label2Xsec["C1C1_hino"].push_back(21.3859);
  Label2Xsec["C1C1_hino"].push_back(16.3405);
  Label2Xsec["C1C1_hino"].push_back(12.6435);
  Label2Xsec["C1C1_hino"].push_back(9.88317);
  Label2Xsec["C1C1_hino"].push_back(7.80868);
  Label2Xsec["C1C1_hino"].push_back(6.21625);
  Label2Xsec["C1C1_hino"].push_back(4.98488);
  Label2Xsec["C1C1_hino"].push_back(4.02662);
  Label2Xsec["C1C1_hino"].push_back(3.27691);
  Label2Xsec["C1C1_hino"].push_back(2.68388);
  Label2Xsec["C1C1_hino"].push_back(2.20317);
  Label2Xsec["C1C1_hino"].push_back(1.82122);
  Label2Xsec["C1C1_hino"].push_back(1.51667);
  Label2Xsec["C1C1_hino"].push_back(1.25981);
  Label2Xsec["C1C1_hino"].push_back(1.05324);
  Label2Xsec["C1C1_hino"].push_back(0.890126);
  Label2Xsec["C1C1_hino"].push_back(0.744491);
  Label2Xsec["C1C1_hino"].push_back(0.630966);
  Label2Xsec["C1C1_hino"].push_back(0.535245);
  Label2Xsec["C1C1_hino"].push_back(0.45283);
  Label2Xsec["C1C1_hino"].push_back(0.386926);
  Label2Xsec["C1C1_hino"].push_back(0.328529);
  Label2Xsec["C1C1_hino"].push_back(0.283075);
  Label2Xsec["C1C1_hino"].push_back(0.24241);
  Label2Xsec["C1C1_hino"].push_back(0.206987);
  Label2Xsec["C1C1_hino"].push_back(0.182305);
  Label2Xsec["C1C1_hino"].push_back(0.15685);
  Label2Xsec["C1C1_hino"].push_back(0.136754);
  Label2Xsec["C1C1_hino"].push_back(0.116612);
  Label2Xsec["C1C1_hino"].push_back(0.0964837);
  Label2Xsec["C1C1_hino"].push_back(0.0865278);
  Label2Xsec["C1C1_hino"].push_back(0.0765253);
  Label2Xsec["C1C1_hino"].push_back(0.0661394);
  Label2Xsec["C1C1_hino"].push_back(0.05633);
  Label2Xsec["C1C1_hino"].push_back(0.0507347);
  Label2Xsec["C1C1_hino"].push_back(0.0406719);
  Label2Xsec["C1C1_hino"].push_back(0.0408149);
  Label2Xsec["C1C1_hino"].push_back(0.0304569);
  Label2Xsec["C1C1_hino"].push_back(0.0305873);
  Label2Xsec["C1C1_hino"].push_back(0.0261173);
  Label2Xsec["C1C1_hino"].push_back(0.0204332);
  Label2Xsec["C1C1_hino"].push_back(0.0203259);
  Label2Xsec["C1C1_hino"].push_back(0.0203678);
  Label2Xsec["C1C1_hino"].push_back(0.0160618);
  Label2Xsec["C1C1_hino"].push_back(0.0102831);
  Label2Xsec["C1C1_hino"].push_back(0.0103036);

  Label2Xsec["C1C1_wino"] = std::vector<double>();
  Label2Xsec["C1C1_wino"].push_back(11611.9);
  Label2Xsec["C1C1_wino"].push_back(5090.52);
  Label2Xsec["C1C1_wino"].push_back(2612.31);
  Label2Xsec["C1C1_wino"].push_back(1482.42);
  Label2Xsec["C1C1_wino"].push_back(902.569);
  Label2Xsec["C1C1_wino"].push_back(579.564);
  Label2Xsec["C1C1_wino"].push_back(387.534);
  Label2Xsec["C1C1_wino"].push_back(267.786);
  Label2Xsec["C1C1_wino"].push_back(190.159);
  Label2Xsec["C1C1_wino"].push_back(138.086);
  Label2Xsec["C1C1_wino"].push_back(102.199);
  Label2Xsec["C1C1_wino"].push_back(76.8342);
  Label2Xsec["C1C1_wino"].push_back(58.6311);
  Label2Xsec["C1C1_wino"].push_back(45.2189);
  Label2Xsec["C1C1_wino"].push_back(35.3143);
  Label2Xsec["C1C1_wino"].push_back(27.8342);
  Label2Xsec["C1C1_wino"].push_back(22.1265);
  Label2Xsec["C1C1_wino"].push_back(17.7394);
  Label2Xsec["C1C1_wino"].push_back(14.3134);
  Label2Xsec["C1C1_wino"].push_back(11.6266);
  Label2Xsec["C1C1_wino"].push_back(9.49913);
  Label2Xsec["C1C1_wino"].push_back(7.80081);
  Label2Xsec["C1C1_wino"].push_back(6.43244);
  Label2Xsec["C1C1_wino"].push_back(5.33642);
  Label2Xsec["C1C1_wino"].push_back(4.4387);
  Label2Xsec["C1C1_wino"].push_back(3.70675);
  Label2Xsec["C1C1_wino"].push_back(3.10861);
  Label2Xsec["C1C1_wino"].push_back(2.61656);
  Label2Xsec["C1C1_wino"].push_back(2.21197);
  Label2Xsec["C1C1_wino"].push_back(1.86142);
  Label2Xsec["C1C1_wino"].push_back(1.58356);
  Label2Xsec["C1C1_wino"].push_back(1.34699);
  Label2Xsec["C1C1_wino"].push_back(1.15301);
  Label2Xsec["C1C1_wino"].push_back(0.981406);
  Label2Xsec["C1C1_wino"].push_back(0.842779);
  Label2Xsec["C1C1_wino"].push_back(0.713432);
  Label2Xsec["C1C1_wino"].push_back(0.621866);
  Label2Xsec["C1C1_wino"].push_back(0.535563);
  Label2Xsec["C1C1_wino"].push_back(0.458716);
  Label2Xsec["C1C1_wino"].push_back(0.398794);
  Label2Xsec["C1C1_wino"].push_back(0.342626);
  Label2Xsec["C1C1_wino"].push_back(0.301119);
  Label2Xsec["C1C1_wino"].push_back(0.262408);
  Label2Xsec["C1C1_wino"].push_back(0.224723);
  Label2Xsec["C1C1_wino"].push_back(0.196044);
  Label2Xsec["C1C1_wino"].push_back(0.168114);
  Label2Xsec["C1C1_wino"].push_back(0.148219);
  Label2Xsec["C1C1_wino"].push_back(0.128682);
  Label2Xsec["C1C1_wino"].push_back(0.115645);
  Label2Xsec["C1C1_wino"].push_back(0.0987141);
  Label2Xsec["C1C1_wino"].push_back(0.0881654);
  Label2Xsec["C1C1_wino"].push_back(0.0778987);
  Label2Xsec["C1C1_wino"].push_back(0.0686671);
  Label2Xsec["C1C1_wino"].push_back(0.0591995);
  Label2Xsec["C1C1_wino"].push_back(0.0505255);
  Label2Xsec["C1C1_wino"].push_back(0.0478698);
  Label2Xsec["C1C1_wino"].push_back(0.0401287);

  Label2Xsec["C1N2_hino"] = std::vector<double>();
  Label2Xsec["C1N2_hino"].push_back(5325.95);
  Label2Xsec["C1N2_hino"].push_back(2355.59);
  Label2Xsec["C1N2_hino"].push_back(1215.47);
  Label2Xsec["C1N2_hino"].push_back(693.104);
  Label2Xsec["C1N2_hino"].push_back(424.166);
  Label2Xsec["C1N2_hino"].push_back(273.466);
  Label2Xsec["C1N2_hino"].push_back(183.689);
  Label2Xsec["C1N2_hino"].push_back(127.471);
  Label2Xsec["C1N2_hino"].push_back(90.8167);
  Label2Xsec["C1N2_hino"].push_back(66.1949);
  Label2Xsec["C1N2_hino"].push_back(49.1579);
  Label2Xsec["C1N2_hino"].push_back(37.1052);
  Label2Xsec["C1N2_hino"].push_back(28.423);
  Label2Xsec["C1N2_hino"].push_back(22.0262);
  Label2Xsec["C1N2_hino"].push_back(17.2696);
  Label2Xsec["C1N2_hino"].push_back(13.6457);
  Label2Xsec["C1N2_hino"].push_back(10.8865);
  Label2Xsec["C1N2_hino"].push_back(8.761);
  Label2Xsec["C1N2_hino"].push_back(7.08913);
  Label2Xsec["C1N2_hino"].push_back(5.76587);
  Label2Xsec["C1N2_hino"].push_back(4.73741);
  Label2Xsec["C1N2_hino"].push_back(3.89352);
  Label2Xsec["C1N2_hino"].push_back(3.22106);
  Label2Xsec["C1N2_hino"].push_back(2.68671);
  Label2Xsec["C1N2_hino"].push_back(2.23385);
  Label2Xsec["C1N2_hino"].push_back(1.87634);
  Label2Xsec["C1N2_hino"].push_back(1.58082);
  Label2Xsec["C1N2_hino"].push_back(1.3232);
  Label2Xsec["C1N2_hino"].push_back(1.12392);
  Label2Xsec["C1N2_hino"].push_back(0.94237);
  Label2Xsec["C1N2_hino"].push_back(0.810952);
  Label2Xsec["C1N2_hino"].push_back(0.684339);
  Label2Xsec["C1N2_hino"].push_back(0.58695);
  Label2Xsec["C1N2_hino"].push_back(0.501398);
  Label2Xsec["C1N2_hino"].push_back(0.431228);
  Label2Xsec["C1N2_hino"].push_back(0.371456);
  Label2Xsec["C1N2_hino"].push_back(0.311324);
  Label2Xsec["C1N2_hino"].push_back(0.266049);
  Label2Xsec["C1N2_hino"].push_back(0.236496);
  Label2Xsec["C1N2_hino"].push_back(0.20709);
  Label2Xsec["C1N2_hino"].push_back(0.17535);
  Label2Xsec["C1N2_hino"].push_back(0.155963);
  Label2Xsec["C1N2_hino"].push_back(0.130143);
  Label2Xsec["C1N2_hino"].push_back(0.116732);
  Label2Xsec["C1N2_hino"].push_back(0.0957498);
  Label2Xsec["C1N2_hino"].push_back(0.0859254);
  Label2Xsec["C1N2_hino"].push_back(0.0803461);
  Label2Xsec["C1N2_hino"].push_back(0.0703178);
  Label2Xsec["C1N2_hino"].push_back(0.0502516);
  Label2Xsec["C1N2_hino"].push_back(0.050112);
  Label2Xsec["C1N2_hino"].push_back(0.0311342);
  Label2Xsec["C1N2_hino"].push_back(0.0299707);
  Label2Xsec["C1N2_hino"].push_back(0.020026);
  Label2Xsec["C1N2_hino"].push_back(0.02);
  Label2Xsec["C1N2_hino"].push_back(0.0200264);
  Label2Xsec["C1N2_hino"].push_back(0.0200743);
  Label2Xsec["C1N2_hino"].push_back(0.0100552);

  Label2Xsec["C1N2_wino"] = std::vector<double>();
  Label2Xsec["C1N2_wino"].push_back(22670.1);
  Label2Xsec["C1N2_wino"].push_back(10034.8);
  Label2Xsec["C1N2_wino"].push_back(5180.86);
  Label2Xsec["C1N2_wino"].push_back(2953.28);
  Label2Xsec["C1N2_wino"].push_back(1807.39);
  Label2Xsec["C1N2_wino"].push_back(1165.09);
  Label2Xsec["C1N2_wino"].push_back(782.487);
  Label2Xsec["C1N2_wino"].push_back(543.03);
  Label2Xsec["C1N2_wino"].push_back(386.936);
  Label2Xsec["C1N2_wino"].push_back(281.911);
  Label2Xsec["C1N2_wino"].push_back(209.439);
  Label2Xsec["C1N2_wino"].push_back(158.06);
  Label2Xsec["C1N2_wino"].push_back(121.013);
  Label2Xsec["C1N2_wino"].push_back(93.771);
  Label2Xsec["C1N2_wino"].push_back(73.4361);
  Label2Xsec["C1N2_wino"].push_back(58.0811);
  Label2Xsec["C1N2_wino"].push_back(46.3533);
  Label2Xsec["C1N2_wino"].push_back(37.2636);
  Label2Xsec["C1N2_wino"].push_back(30.1656);
  Label2Xsec["C1N2_wino"].push_back(24.5798);
  Label2Xsec["C1N2_wino"].push_back(20.1372);
  Label2Xsec["C1N2_wino"].push_back(16.5706);
  Label2Xsec["C1N2_wino"].push_back(13.7303);
  Label2Xsec["C1N2_wino"].push_back(11.3975);
  Label2Xsec["C1N2_wino"].push_back(9.51032);
  Label2Xsec["C1N2_wino"].push_back(7.9595);
  Label2Xsec["C1N2_wino"].push_back(6.69356);
  Label2Xsec["C1N2_wino"].push_back(5.63562);
  Label2Xsec["C1N2_wino"].push_back(4.75843);
  Label2Xsec["C1N2_wino"].push_back(4.02646);
  Label2Xsec["C1N2_wino"].push_back(3.42026);
  Label2Xsec["C1N2_wino"].push_back(2.90547);
  Label2Xsec["C1N2_wino"].push_back(2.49667);
  Label2Xsec["C1N2_wino"].push_back(2.12907);
  Label2Xsec["C1N2_wino"].push_back(1.8164);
  Label2Xsec["C1N2_wino"].push_back(1.56893);
  Label2Xsec["C1N2_wino"].push_back(1.34352);
  Label2Xsec["C1N2_wino"].push_back(1.15949);
  Label2Xsec["C1N2_wino"].push_back(0.997903);
  Label2Xsec["C1N2_wino"].push_back(0.86504);
  Label2Xsec["C1N2_wino"].push_back(0.740372);
  Label2Xsec["C1N2_wino"].push_back(0.647288);
  Label2Xsec["C1N2_wino"].push_back(0.555594);
  Label2Xsec["C1N2_wino"].push_back(0.486863);
  Label2Xsec["C1N2_wino"].push_back(0.415851);
  Label2Xsec["C1N2_wino"].push_back(0.362455);
  Label2Xsec["C1N2_wino"].push_back(0.316975);
  Label2Xsec["C1N2_wino"].push_back(0.276522);
  Label2Xsec["C1N2_wino"].push_back(0.240739);
  Label2Xsec["C1N2_wino"].push_back(0.20999);
  Label2Xsec["C1N2_wino"].push_back(0.185601);
  Label2Xsec["C1N2_wino"].push_back(0.161343);
  Label2Xsec["C1N2_wino"].push_back(0.131074);
  Label2Xsec["C1N2_wino"].push_back(0.121045);
  Label2Xsec["C1N2_wino"].push_back(0.110889);
  Label2Xsec["C1N2_wino"].push_back(0.0906868);
  Label2Xsec["C1N2_wino"].push_back(0.0813221);

  Label2Xsec["C1mN2_wino"] = std::vector<double>();
  Label2Xsec["C1mN2_wino"].push_back(8766.08);
  Label2Xsec["C1mN2_wino"].push_back(3782.8);
  Label2Xsec["C1mN2_wino"].push_back(1907.04);
  Label2Xsec["C1mN2_wino"].push_back(1063.01);
  Label2Xsec["C1mN2_wino"].push_back(637.14);
  Label2Xsec["C1mN2_wino"].push_back(402.717);
  Label2Xsec["C1mN2_wino"].push_back(265.255);
  Label2Xsec["C1mN2_wino"].push_back(180.802);
  Label2Xsec["C1mN2_wino"].push_back(126.627);
  Label2Xsec["C1mN2_wino"].push_back(90.6096);
  Label2Xsec["C1mN2_wino"].push_back(66.3319);
  Label2Xsec["C1mN2_wino"].push_back(49.2359);
  Label2Xsec["C1mN2_wino"].push_back(37.12);
  Label2Xsec["C1mN2_wino"].push_back(28.3325);
  Label2Xsec["C1mN2_wino"].push_back(21.8561);
  Label2Xsec["C1mN2_wino"].push_back(17.0676);
  Label2Xsec["C1mN2_wino"].push_back(13.4441);
  Label2Xsec["C1mN2_wino"].push_back(10.6671);
  Label2Xsec["C1mN2_wino"].push_back(8.52674);
  Label2Xsec["C1mN2_wino"].push_back(6.86761);
  Label2Xsec["C1mN2_wino"].push_back(5.56289);
  Label2Xsec["C1mN2_wino"].push_back(4.52654);
  Label2Xsec["C1mN2_wino"].push_back(3.71232);
  Label2Xsec["C1mN2_wino"].push_back(3.05164);
  Label2Xsec["C1mN2_wino"].push_back(2.5208);
  Label2Xsec["C1mN2_wino"].push_back(2.09484);
  Label2Xsec["C1mN2_wino"].push_back(1.73984);
  Label2Xsec["C1mN2_wino"].push_back(1.45562);
  Label2Xsec["C1mN2_wino"].push_back(1.2175);
  Label2Xsec["C1mN2_wino"].push_back(1.02139);
  Label2Xsec["C1mN2_wino"].push_back(0.862477);
  Label2Xsec["C1mN2_wino"].push_back(0.727098);
  Label2Xsec["C1mN2_wino"].push_back(0.623379);
  Label2Xsec["C1mN2_wino"].push_back(0.529463);
  Label2Xsec["C1mN2_wino"].push_back(0.450722);
  Label2Xsec["C1mN2_wino"].push_back(0.385788);
  Label2Xsec["C1mN2_wino"].push_back(0.329002);
  Label2Xsec["C1mN2_wino"].push_back(0.280284);
  Label2Xsec["C1mN2_wino"].push_back(0.240707);
  Label2Xsec["C1mN2_wino"].push_back(0.213287);
  Label2Xsec["C1mN2_wino"].push_back(0.180922);
  Label2Xsec["C1mN2_wino"].push_back(0.155356);
  Label2Xsec["C1mN2_wino"].push_back(0.135615);
  Label2Xsec["C1mN2_wino"].push_back(0.115356);
  Label2Xsec["C1mN2_wino"].push_back(0.100687);
  Label2Xsec["C1mN2_wino"].push_back(0.0862252);
  Label2Xsec["C1mN2_wino"].push_back(0.0762914);
  Label2Xsec["C1mN2_wino"].push_back(0.0662261);
  Label2Xsec["C1mN2_wino"].push_back(0.0605883);
  Label2Xsec["C1mN2_wino"].push_back(0.0504674);
  Label2Xsec["C1mN2_wino"].push_back(0.0464939);
  Label2Xsec["C1mN2_wino"].push_back(0.0406594);
  Label2Xsec["C1mN2_wino"].push_back(0.0303342);
  Label2Xsec["C1mN2_wino"].push_back(0.030426);
  Label2Xsec["C1mN2_wino"].push_back(0.0303359);
  Label2Xsec["C1mN2_wino"].push_back(0.0202839);
  Label2Xsec["C1mN2_wino"].push_back(0.0204383);

  Label2Xsec["C1pN2_wino"] = std::vector<double>();
  Label2Xsec["C1pN2_wino"].push_back(13895.1);
  Label2Xsec["C1pN2_wino"].push_back(6252.21);
  Label2Xsec["C1pN2_wino"].push_back(3273.84);
  Label2Xsec["C1pN2_wino"].push_back(1890.26);
  Label2Xsec["C1pN2_wino"].push_back(1170.26);
  Label2Xsec["C1pN2_wino"].push_back(762.405);
  Label2Xsec["C1pN2_wino"].push_back(517.259);
  Label2Xsec["C1pN2_wino"].push_back(362.248);
  Label2Xsec["C1pN2_wino"].push_back(260.319);
  Label2Xsec["C1pN2_wino"].push_back(191.314);
  Label2Xsec["C1pN2_wino"].push_back(143.126);
  Label2Xsec["C1pN2_wino"].push_back(108.84);
  Label2Xsec["C1pN2_wino"].push_back(83.9069);
  Label2Xsec["C1pN2_wino"].push_back(65.4553);
  Label2Xsec["C1pN2_wino"].push_back(51.5901);
  Label2Xsec["C1pN2_wino"].push_back(41.0233);
  Label2Xsec["C1pN2_wino"].push_back(32.9135);
  Label2Xsec["C1pN2_wino"].push_back(26.6028);
  Label2Xsec["C1pN2_wino"].push_back(21.644);
  Label2Xsec["C1pN2_wino"].push_back(17.7159);
  Label2Xsec["C1pN2_wino"].push_back(14.5767);
  Label2Xsec["C1pN2_wino"].push_back(12.0454);
  Label2Xsec["C1pN2_wino"].push_back(10.0188);
  Label2Xsec["C1pN2_wino"].push_back(8.34633);
  Label2Xsec["C1pN2_wino"].push_back(6.99008);
  Label2Xsec["C1pN2_wino"].push_back(5.86536);
  Label2Xsec["C1pN2_wino"].push_back(4.95438);
  Label2Xsec["C1pN2_wino"].push_back(4.18041);
  Label2Xsec["C1pN2_wino"].push_back(3.54111);
  Label2Xsec["C1pN2_wino"].push_back(3.0052);
  Label2Xsec["C1pN2_wino"].push_back(2.55793);
  Label2Xsec["C1pN2_wino"].push_back(2.17847);
  Label2Xsec["C1pN2_wino"].push_back(1.87338);
  Label2Xsec["C1pN2_wino"].push_back(1.59963);
  Label2Xsec["C1pN2_wino"].push_back(1.36565);
  Label2Xsec["C1pN2_wino"].push_back(1.18309);
  Label2Xsec["C1pN2_wino"].push_back(1.01451);
  Label2Xsec["C1pN2_wino"].push_back(0.879192);
  Label2Xsec["C1pN2_wino"].push_back(0.757183);
  Label2Xsec["C1pN2_wino"].push_back(0.651686);
  Label2Xsec["C1pN2_wino"].push_back(0.55945);
  Label2Xsec["C1pN2_wino"].push_back(0.491938);
  Label2Xsec["C1pN2_wino"].push_back(0.419984);
  Label2Xsec["C1pN2_wino"].push_back(0.371485);
  Label2Xsec["C1pN2_wino"].push_back(0.31567);
  Label2Xsec["C1pN2_wino"].push_back(0.27623);
  Label2Xsec["C1pN2_wino"].push_back(0.240685);
  Label2Xsec["C1pN2_wino"].push_back(0.210298);
  Label2Xsec["C1pN2_wino"].push_back(0.18015);
  Label2Xsec["C1pN2_wino"].push_back(0.159393);
  Label2Xsec["C1pN2_wino"].push_back(0.139246);
  Label2Xsec["C1pN2_wino"].push_back(0.120872);
  Label2Xsec["C1pN2_wino"].push_back(0.10087);
  Label2Xsec["C1pN2_wino"].push_back(0.0906208);
  Label2Xsec["C1pN2_wino"].push_back(0.0807007);
  Label2Xsec["C1pN2_wino"].push_back(0.0704072);
  Label2Xsec["C1pN2_wino"].push_back(0.0609286);

  Label2Xsec["CN_hino"] = std::vector<double>();
  Label2Xsec["CN_hino"].push_back(16797.2);
  Label2Xsec["CN_hino"].push_back(3832.31);
  Label2Xsec["CN_hino"].push_back(1335.62);
  Label2Xsec["CN_hino"].push_back(577.314);
  Label2Xsec["CN_hino"].push_back(284.855);
  Label2Xsec["CN_hino"].push_back(153.841);
  Label2Xsec["CN_hino"].push_back(88.7325);
  Label2Xsec["CN_hino"].push_back(53.7702);
  Label2Xsec["CN_hino"].push_back(33.8387);
  Label2Xsec["CN_hino"].push_back(21.9868);
  Label2Xsec["CN_hino"].push_back(14.6677);
  Label2Xsec["CN_hino"].push_back(9.96406);
  Label2Xsec["CN_hino"].push_back(6.89981);
  Label2Xsec["CN_hino"].push_back(4.8731);
  Label2Xsec["CN_hino"].push_back(3.46143);
  Label2Xsec["CN_hino"].push_back(2.4923);
  Label2Xsec["CN_hino"].push_back(1.80616);
  Label2Xsec["CN_hino"].push_back(1.32692);
  Label2Xsec["CN_hino"].push_back(0.968853);
  Label2Xsec["CN_hino"].push_back(0.731306);
  Label2Xsec["CN_hino"].push_back(0.538005);
  Label2Xsec["CN_hino"].push_back(0.405108);
  Label2Xsec["CN_hino"].push_back(0.299347);
  Label2Xsec["CN_hino"].push_back(0.240471);
  Label2Xsec["CN_hino"].push_back(0.160765);
  Label2Xsec["CN_hino"].push_back(0.111174);
  Label2Xsec["CN_hino"].push_back(0.0780263);
  Label2Xsec["CN_hino"].push_back(0.0696962);

  Label2Xsec["N1N2_hino"] = std::vector<double>();
  Label2Xsec["N1N2_hino"].push_back(3277.01);
  Label2Xsec["N1N2_hino"].push_back(715.14);
  Label2Xsec["N1N2_hino"].push_back(244.213);
  Label2Xsec["N1N2_hino"].push_back(104.252);
  Label2Xsec["N1N2_hino"].push_back(50.9994);
  Label2Xsec["N1N2_hino"].push_back(27.3286);
  Label2Xsec["N1N2_hino"].push_back(15.6691);
  Label2Xsec["N1N2_hino"].push_back(9.44017);
  Label2Xsec["N1N2_hino"].push_back(5.90757);
  Label2Xsec["N1N2_hino"].push_back(3.8167);
  Label2Xsec["N1N2_hino"].push_back(2.53015);
  Label2Xsec["N1N2_hino"].push_back(1.71418);
  Label2Xsec["N1N2_hino"].push_back(1.18113);
  Label2Xsec["N1N2_hino"].push_back(0.826366);
  Label2Xsec["N1N2_hino"].push_back(0.586211);
  Label2Xsec["N1N2_hino"].push_back(0.420556);
  Label2Xsec["N1N2_hino"].push_back(0.305935);
  Label2Xsec["N1N2_hino"].push_back(0.22285);
  Label2Xsec["N1N2_hino"].push_back(0.16428);
  Label2Xsec["N1N2_hino"].push_back(0.121865);
  Label2Xsec["N1N2_hino"].push_back(0.0912469);
  Label2Xsec["N1N2_hino"].push_back(0.0684561);
  Label2Xsec["N1N2_hino"].push_back(0.0516263);
  Label2Xsec["N1N2_hino"].push_back(0.0391587);
  Label2Xsec["N1N2_hino"].push_back(0.0299353);
  Label2Xsec["N1N2_hino"].push_back(0.0228072);
  Label2Xsec["N1N2_hino"].push_back(0.0175031);
  Label2Xsec["N1N2_hino"].push_back(0.0134572);

  Label2Xsec["SlepSlep_left"] = std::vector<double>();
  Label2Xsec["SlepSlep_left"].push_back(4104.9);
  Label2Xsec["SlepSlep_left"].push_back(270.79);
  Label2Xsec["SlepSlep_left"].push_back(63.34);
  Label2Xsec["SlepSlep_left"].push_back(21.81);
  Label2Xsec["SlepSlep_left"].push_back(9.21);
  Label2Xsec["SlepSlep_left"].push_back(4.43);
  Label2Xsec["SlepSlep_left"].push_back(2.33);
  Label2Xsec["SlepSlep_left"].push_back(1.31);
  Label2Xsec["SlepSlep_left"].push_back(0.77);
  Label2Xsec["SlepSlep_left"].push_back(0.47);

  Label2Xsec["SlepSlep_right"] = std::vector<double>();
  Label2Xsec["SlepSlep_right"].push_back(1377.6);
  Label2Xsec["SlepSlep_right"].push_back(96.51);
  Label2Xsec["SlepSlep_right"].push_back(23.32);
  Label2Xsec["SlepSlep_right"].push_back(8.15);
  Label2Xsec["SlepSlep_right"].push_back(3.47);
  Label2Xsec["SlepSlep_right"].push_back(1.68);
  Label2Xsec["SlepSlep_right"].push_back(0.89);
  Label2Xsec["SlepSlep_right"].push_back(0.5);
  Label2Xsec["SlepSlep_right"].push_back(0.3);
  Label2Xsec["SlepSlep_right"].push_back(0.18);

  /*
  100 GeV	1521.11);
    105 GeV	1233.18);
    110 GeV	1013.76);
    115 GeV	832.656);
    120 GeV	689.799);
    125 GeV	574.981);
    130 GeV	481.397);
    135 GeV	405.159);
    140 GeV	342.865);
    145 GeV	291.752);
    150 GeV	249.409);
    155 GeV	214.221);
    160 GeV	184.623);
    165 GeV	159.614);
    170 GeV	139.252);
    175 GeV	121.416);
    180 GeV	106.194);
    185 GeV	93.3347);
    190 GeV	82.2541);
    195 GeV	72.7397);
    200 GeV	64.5085);
    205 GeV	57.2279);
    210 GeV	50.9226);
    215 GeV	45.3761);
    220 GeV	40.5941);
    225 GeV	36.3818);
    230 GeV	32.6679);
    235 GeV	29.3155);
    240 GeV	26.4761);
    245 GeV	23.8853);
    250 GeV	21.5949);
    255 GeV	19.5614);
    260 GeV	17.6836);
    265 GeV	16.112);
    270 GeV	14.6459);
    275 GeV	13.3231);
    280 GeV	12.1575);
    285 GeV	11.0925);
    290 GeV	10.1363);
    295 GeV	9.29002);
    300 GeV	8.51615);
    305 GeV	7.81428);
    310 GeV	7.17876);
    315 GeV	6.60266);
    320 GeV	6.08444);
    325 GeV	5.60471);
    330 GeV	5.17188);
    335 GeV	4.77871);
    340 GeV	4.41629);
    345 GeV	4.08881);
    350 GeV	3.78661);
    355 GeV	3.50911);
    360 GeV	3.25619);
    365 GeV	3.02472);
    370 GeV	2.8077);
    375 GeV	2.61162);
    380 GeV	2.43031);
    385 GeV	2.26365);
    390 GeV	2.10786);
    395 GeV	1.9665);
    400 GeV	1.83537);
    405 GeV	1.70927);
    410 GeV	1.60378);
    415 GeV	1.49798);
    420 GeV	1.39688);
    425 GeV	1.31169);
    430 GeV	1.22589);
    435 GeV	1.14553);
    440 GeV	1.07484);
    445 GeV	1.01019);
    450 GeV	0.948333);
    455 GeV	0.890847);
    460 GeV	0.836762);
    465 GeV	0.787221);
    470 GeV	0.740549);
    475 GeV	0.697075);
    480 GeV	0.655954);
    485 GeV	0.618562);
    490 GeV	0.582467);
    495 GeV	0.549524);
    500 GeV	0.51848);
    505 GeV	0.489324);
    510 GeV	0.462439);
    515 GeV	0.436832);
    520 GeV	0.412828);
    525 GeV	0.390303);
    530 GeV	0.368755);
    535 GeV	0.348705);
    540 GeV	0.330157);
    545 GeV	0.312672);
    550 GeV	0.296128);
    555 GeV	0.280734);
    560 GeV	0.266138);
    565 GeV	0.251557);
    570 GeV	0.238537);
    575 GeV	0.226118);
    580 GeV	0.214557);
    585 GeV	0.203566);
    590 GeV	0.193079);
    595 GeV	0.183604);
    600 GeV	0.174599);
    605 GeV	0.166131);
    610 GeV	0.158242);
    615 GeV	0.150275);
    620 GeV	0.142787);
    625 GeV	0.136372);
    630 GeV	0.129886);
    635 GeV	0.123402);
    640 GeV	0.11795);
    645 GeV	0.112008);
    650 GeV	0.107045);
    655 GeV	0.102081);
    660 GeV	0.09725);
    665 GeV	0.0927515);
    670 GeV	0.0885084);
    675 GeV	0.0844877);
    680 GeV	0.0806192);
    685 GeV	0.0769099);
    690 GeV	0.0734901);
    695 GeV	0.0701805);
    700 GeV	0.0670476);
    705 GeV	0.0641426);
    710 GeV	0.0612942);
    715 GeV	0.0585678);
    720 GeV	0.0560753);
    725 GeV	0.0536438);
    730 GeV	0.0513219);
    735 GeV	0.0491001);
    740 GeV	0.0470801);
    745 GeV	0.045061);
    750 GeV	0.0431418);
    755 GeV	0.0413447);
    760 GeV	0.0396264);
    765 GeV	0.0379036);
    770 GeV	0.0363856);
    775 GeV	0.0348796);
    780 GeV	0.0334669);
    785 GeV	0.0320548);
    790 GeV	0.0307373);
    795 GeV	0.0295348);
    800 GeV	0.0283338);
    805 GeV	0.0272206);
    810 GeV	0.0261233);
    815 GeV	0.0251107);
    820 GeV	0.0241099);
    825 GeV	0.0230866);
    830 GeV	0.0221834);
    835 GeV	0.0213766);
    840 GeV	0.0204715);
    845 GeV	0.0197653);
    850 GeV	0.0189612);
    855 GeV	0.0182516);
    860 GeV	0.0175509);
    865 GeV	0.0168336);
    870 GeV	0.0162314);
    875 GeV	0.015625);
    880 GeV	0.0150143);
    885 GeV	0.0144112);
    890 GeV	0.0138979);
    895 GeV	0.0133962);
    900 GeV	0.0128895);
    905 GeV	0.0123843);
    910 GeV	0.0119837);
    915 GeV	0.0114713);
    920 GeV	0.0110688);
    925 GeV	0.0106631);
    930 GeV	0.0102629);
    935 GeV	0.0098874);
    940 GeV	0.00952142);
    945 GeV	0.00916636);
    950 GeV	0.00883465);
    955 GeV	0.00851073);
    960 GeV	0.00820884);
    965 GeV	0.00791403);
    970 GeV	0.00763112);
    975 GeV	0.00735655);
    980 GeV	0.00710317);
    985 GeV	0.00684867);
    990 GeV	0.00660695);
    995 GeV	0.00637546);
    1000 GeV	0.00615134);
    1005 GeV	0.00593765 ± 16.3716%
    1010 GeV	0.00572452 ± 16.3857%
    1015 GeV	0.00553094 ± 16.4628%
    1020 GeV	0.00533968 ± 16.4963%
    1025 GeV	0.00514619 ± 16.5762%
    1030 GeV	0.00497235 ± 16.5838%
    1035 GeV	0.00479906 ± 16.6646%
    1040 GeV	0.00463806 ± 16.6947%
    1045 GeV	0.00447537 ± 16.7071%
    1050 GeV	0.00432261 ± 16.7859%
    1055 GeV	0.00417983 ± 16.8637%
    1060 GeV	0.00403886 ± 16.8981%
    1065 GeV	0.0038962 ± 16.9794%
    1070 GeV	0.00376343 ± 16.9764%
    1075 GeV	0.00364174 ± 17.0634%
    1080 GeV	0.00352093 ± 17.0908%
    1085 GeV	0.00339813 ± 17.1929%
    1090 GeV	0.00328695 ± 17.2274%
    1095 GeV	0.00317628 ± 17.2617%
    1100 GeV	0.00307413 ± 17.3377%
    1105 GeV	0.00297377 ± 17.3822%
    1110 GeV	0.00287148 ± 17.4725%
    1115 GeV	0.00278078 ± 17.5091%
    1120 GeV	0.00268873 ± 17.5883%
    1125 GeV	0.00260821 ± 17.6126%
    1130 GeV	0.00251529 ± 17.6836%
    1135 GeV	0.00243484 ± 17.7128%
    1140 GeV	0.00236295 ± 17.7977%
    1145 GeV	0.00228192 ± 17.8507%
    1150 GeV	0.00221047 ± 17.9259%
    1155 GeV	0.00213907 ± 18.0255%
    1160 GeV	0.00206845 ± 18.0518%
    1165 GeV	0.0020063 ± 18.0954%
    1170 GeV	0.00194569 ± 18.1194%
    1175 GeV	0.0018741 ± 18.2145%
    1180 GeV	0.00182266 ± 18.3074%
    1185 GeV	0.00176211 ± 18.3375%
    1190 GeV	0.00170006 ± 18.4075%
    1195 GeV	0.00164968 ± 18.4438%
    1200 GeV	0.00159844 ± 18.5209%
    1205 GeV	0.0015472 ± 18.5977%
    1210 GeV	0.00149657 ± 18.6485%
    1215 GeV	0.00145544 ± 18.7347%
    1220 GeV	0.00140288 ± 18.8774%
    1225 GeV	0.00136155 ± 18.989%
    1230 GeV	0.00131271 ± 18.8763%
    1235 GeV	0.0012717 ± 18.9588%
    1240 GeV	0.00123066 ± 19.049%
    1245 GeV	0.00119994 ± 19.1442%
    1250 GeV	0.0011583 ± 19.3006%
    1255 GeV	0.00112694 ± 19.4441%
    1260 GeV	0.00108716 ± 19.4141%
    1265 GeV	0.00105517 ± 19.6361%
    1270 GeV	0.00102241 ± 19.6297%
    1275 GeV	0.000991293 ± 19.762%
    1280 GeV	0.000961012 ± 19.7926%
    1285 GeV	0.000932394 ± 19.8682%
    1290 GeV	0.000903404 ± 19.9924%
    1295 GeV	0.000876957 ± 20.0777%
    1300 GeV	0.000850345 ± 20.1604%
    1305 GeV	0.00082443 ± 20.2883%
    1310 GeV	0.00079983 ± 20.373%
    1315 GeV	0.000775222 ± 20.4622%
    1320 GeV	0.000751372 ± 20.5919%
    1325 GeV	0.000728912 ± 20.6884%
    1330 GeV	0.000706867 ± 20.7763%
    1335 GeV	0.000685372 ± 20.8587%
    1340 GeV	0.000664649 ± 20.9879%
    1345 GeV	0.000644804 ± 21.1487%
    1350 GeV	0.000625155 ± 21.2761%
    1355 GeV	0.000606802 ± 21.3529%
    1360 GeV	0.000588512 ± 21.4428%
    1365 GeV	0.000570506 ± 21.6584%
    1370 GeV	0.000553379 ± 21.6036%
    1375 GeV	0.000536646 ± 21.775%
    1380 GeV	0.000521404 ± 21.8383%
    1385 GeV	0.000505008 ± 21.9675%
    1390 GeV	0.000490353 ± 22.1444%
    1395 GeV	0.000476164 ± 22.2016%
    1400 GeV	0.000461944 ± 22.2704%
    1405 GeV	0.000448172 ± 22.4911%
    1410 GeV	0.000435082 ± 22.5606%
    1415 GeV	0.000422967 ± 22.6095%
    1420 GeV	0.000410381 ± 22.797%
    1425 GeV	0.000398106 ± 22.8949%
    1430 GeV	0.000386792 ± 23.1319%
    1435 GeV	0.000375724 ± 23.1724%
    1440 GeV	0.000364616 ± 23.2234%
    1445 GeV	0.000353965 ± 23.4637%
    1450 GeV	0.000343923 ± 23.4948%
    1455 GeV	0.000333885 ± 23.5468%
    1460 GeV	0.000324344 ± 23.771%
    1465 GeV	0.0003153 ± 23.8004%
    1470 GeV	0.00030583 ± 24.0064%
    1475 GeV	0.000296811 ± 24.0314%
    1480 GeV	0.000288149 ± 23.9248%
    1485 GeV	0.000279711 ± 24.1257%
    1490 GeV	0.000271724 ± 24.1274%
    1495 GeV	0.000264275 ± 24.3545%
    1500 GeV	0.000256248 ± 24.372%
    1505 GeV	0.000248853 ± 24.5827%
    1510 GeV	0.000241844 ± 24.6187%
    1515 GeV	0.000234438 ± 24.8442%
    1520 GeV	0.000227374 ± 24.8909%
    1525 GeV	0.000221045 ± 25.0895%
    1530 GeV	0.000214431 ± 24.8728%
    1535 GeV	0.000208092 ± 25.1043%
    1540 GeV	0.000201748 ± 25.3207%
    1545 GeV	0.000196399 ± 25.5641%
    1550 GeV	0.000190474 ± 25.5213%
    1555 GeV	0.000185188 ± 25.7329%
    1560 GeV	0.000179263 ± 25.6931%
    1565 GeV	0.000174021 ± 25.9111%
    1570 GeV	0.000169176 ± 25.8106%
    1575 GeV	0.000163861 ± 26.0597%
    1580 GeV	0.000159583 ± 26.2958%
    1585 GeV	0.000154719 ± 26.195%
    1590 GeV	0.000150506 ± 26.4111%
    1595 GeV	0.000145626 ± 26.3077%
    1600 GeV	0.000141382 ± 26.5291%
    1605 GeV	0.000137131 ± 26.7424%
    1610 GeV	0.000132187 ± 26.668%
    1615 GeV	0.000127929 ± 26.9117%
    1620 GeV	0.000124086 ± 26.7738%
    1625 GeV	0.00011982 ± 27.0483%
    1630 GeV	0.000116042 ± 26.8071%
    1635 GeV	0.000112767 ± 27.127%
    1640 GeV	0.000108936 ± 26.9351%
    1645 GeV	0.000105746 ± 27.1783%
    1650 GeV	0.000102693 ± 27.292%
    1655 GeV	0.000100112 ± 27.4445%
    1660 GeV	9.75763e-05 ± 27.5431%
    1665 GeV	9.52062e-05 ± 27.6946%
    1670 GeV	9.29857e-05 ± 27.7869%
    1675 GeV	9.08285e-05 ± 27.9347%
    1680 GeV	8.87433e-05 ± 28.1539%
    1685 GeV	8.66618e-05 ± 28.3509%
    1690 GeV	8.46535e-05 ± 28.4432%
    1695 GeV	8.27102e-05 ± 28.591%
    1700 GeV	8.07774e-05 ± 28.7497%
    1705 GeV	7.8666e-05 ± 28.8194%
    1710 GeV	7.6572e-05 ± 29.0265%
    1715 GeV	7.45994e-05 ± 29.1193%
    1720 GeV	7.25199e-05 ± 29.3013%
    1725 GeV	7.05189e-05 ± 29.3697%
    1730 GeV	6.85712e-05 ± 29.4972%
    1735 GeV	6.67296e-05 ± 29.6167%
    1740 GeV	6.49184e-05 ± 29.7686%
    1745 GeV	6.30949e-05 ± 29.8524%
    1750 GeV	6.13637e-05 ± 29.9789%
    1755 GeV	5.97301e-05 ± 30.0928%
    1760 GeV	5.80751e-05 ± 30.2585%
    1765 GeV	5.65479e-05 ± 30.366%
    1770 GeV	5.49998e-05 ± 30.5241%
    1775 GeV	5.35686e-05 ± 30.6718%
    1780 GeV	5.20828e-05 ± 30.6799%
    1785 GeV	5.07079e-05 ± 30.9201%
    1790 GeV	4.93948e-05 ± 31.0043%
    1795 GeV	4.80635e-05 ± 31.138%
    1800 GeV	4.67492e-05 ± 31.2291%
    1805 GeV	4.55055e-05 ± 31.4321%
    1810 GeV	4.42835e-05 ± 31.5499%
    1815 GeV	4.30744e-05 ± 31.6302%
    1820 GeV	4.19954e-05 ± 31.7151%
    1825 GeV	4.08527e-05 ± 31.9048%
    1830 GeV	3.97561e-05 ± 31.9718%
    1835 GeV	3.87041e-05 ± 32.2028%
    1840 GeV	3.76008e-05 ± 32.268%
    1845 GeV	3.66914e-05 ± 32.4529%
    1850 GeV	3.56995e-05 ± 32.5039%
    1855 GeV	3.47689e-05 ± 32.6767%
    1860 GeV	3.38528e-05 ± 32.8878%
    1865 GeV	3.29644e-05 ± 32.8975%
    1870 GeV	3.20679e-05 ± 32.9608%
    1875 GeV	3.12583e-05 ± 33.1541%
    1880 GeV	3.04342e-05 ± 33.3117%
    1885 GeV	2.96516e-05 ± 33.2866%
    1890 GeV	2.88952e-05 ± 33.6279%
    1895 GeV	2.81145e-05 ± 33.6845%
    1900 GeV	2.73974e-05 ± 33.8247%
    1905 GeV	2.66796e-05 ± 33.9708%
    1910 GeV	2.59941e-05 ± 33.9526%
    1915 GeV	2.52784e-05 ± 34.1137%
    1920 GeV	2.46598e-05 ± 34.2714%
    1925 GeV	2.39932e-05 ± 34.2328%
    1930 GeV	2.33737e-05 ± 34.394%
    1935 GeV	2.27623e-05 ± 34.5138%
    1940 GeV	2.21454e-05 ± 34.6933%
    1945 GeV	2.15924e-05 ± 35.0815%
    1950 GeV	2.10232e-05 ± 34.9444%
    1955 GeV	2.05211e-05 ± 35.0155%
    1960 GeV	1.98996e-05 ± 35.2135%
    1965 GeV	1.9408e-05 ± 35.3328%
    1970 GeV	1.88974e-05 ± 35.4643%
    1975 GeV	1.84612e-05 ± 35.7904%
    1980 GeV	1.79562e-05 ± 35.8898%
    1985 GeV	1.75673e-05 ± 35.989%
    1990 GeV	1.70612e-05 ± 36.0953%
    1995 GeV	1.66228e-05 ± 36.4709%
    2000 GeV	1.62355e-05 ± 36.5277%
  */
  
  return Label2Xsec;
}

std::map<std::string,std::vector<double> > XsecTool::InitMap_XsecUnc_SMS(){
  std::map<std::string,std::vector<double> > Label2XsecUnc; 

  Label2XsecUnc["C1C1_hino"] = std::vector<double>();
  Label2XsecUnc["C1C1_hino"].push_back(126.968);
  Label2XsecUnc["C1C1_hino"].push_back(62.0114);
  Label2XsecUnc["C1C1_hino"].push_back(34.6605);
  Label2XsecUnc["C1C1_hino"].push_back(21.3472);
  Label2XsecUnc["C1C1_hino"].push_back(13.8982);
  Label2XsecUnc["C1C1_hino"].push_back(9.56897);
  Label2XsecUnc["C1C1_hino"].push_back(6.63225);
  Label2XsecUnc["C1C1_hino"].push_back(4.79301);
  Label2XsecUnc["C1C1_hino"].push_back(3.5507);
  Label2XsecUnc["C1C1_hino"].push_back(2.70668);
  Label2XsecUnc["C1C1_hino"].push_back(2.0796);
  Label2XsecUnc["C1C1_hino"].push_back(1.61303);
  Label2XsecUnc["C1C1_hino"].push_back(1.26734);
  Label2XsecUnc["C1C1_hino"].push_back(1.01146);
  Label2XsecUnc["C1C1_hino"].push_back(0.813575);
  Label2XsecUnc["C1C1_hino"].push_back(0.659301);
  Label2XsecUnc["C1C1_hino"].push_back(0.543279);
  Label2XsecUnc["C1C1_hino"].push_back(0.445471);
  Label2XsecUnc["C1C1_hino"].push_back(0.362855);
  Label2XsecUnc["C1C1_hino"].push_back(0.303924);
  Label2XsecUnc["C1C1_hino"].push_back(0.255607);
  Label2XsecUnc["C1C1_hino"].push_back(0.213665);
  Label2XsecUnc["C1C1_hino"].push_back(0.186275);
  Label2XsecUnc["C1C1_hino"].push_back(0.152791);
  Label2XsecUnc["C1C1_hino"].push_back(0.13226);
  Label2XsecUnc["C1C1_hino"].push_back(0.107062);
  Label2XsecUnc["C1C1_hino"].push_back(0.0958385);
  Label2XsecUnc["C1C1_hino"].push_back(0.0808315);
  Label2XsecUnc["C1C1_hino"].push_back(0.0708789);
  Label2XsecUnc["C1C1_hino"].push_back(0.0590975);
  Label2XsecUnc["C1C1_hino"].push_back(0.0517395);
  Label2XsecUnc["C1C1_hino"].push_back(0.0428921);
  Label2XsecUnc["C1C1_hino"].push_back(0.0403214);
  Label2XsecUnc["C1C1_hino"].push_back(0.0322892);
  Label2XsecUnc["C1C1_hino"].push_back(0.0294562);
  Label2XsecUnc["C1C1_hino"].push_back(0.0216365);
  Label2XsecUnc["C1C1_hino"].push_back(0.0254472);
  Label2XsecUnc["C1C1_hino"].push_back(0.0185931);
  Label2XsecUnc["C1C1_hino"].push_back(0.0173155);
  Label2XsecUnc["C1C1_hino"].push_back(0.0156864);
  Label2XsecUnc["C1C1_hino"].push_back(0.0141733);
  Label2XsecUnc["C1C1_hino"].push_back(0.013431);
  Label2XsecUnc["C1C1_hino"].push_back(0.0125656);
  Label2XsecUnc["C1C1_hino"].push_back(0.0117384);
  Label2XsecUnc["C1C1_hino"].push_back(0.0107865);
  Label2XsecUnc["C1C1_hino"].push_back(0.005345);
  Label2XsecUnc["C1C1_hino"].push_back(0.00443465);
  Label2XsecUnc["C1C1_hino"].push_back(0.00445492);
  Label2XsecUnc["C1C1_hino"].push_back(0.00345704);
  Label2XsecUnc["C1C1_hino"].push_back(0.00352806);
  Label2XsecUnc["C1C1_hino"].push_back(0.0081195);
  Label2XsecUnc["C1C1_hino"].push_back(0.00248229);
  Label2XsecUnc["C1C1_hino"].push_back(0.00256577);
  Label2XsecUnc["C1C1_hino"].push_back(0.00266911);
  Label2XsecUnc["C1C1_hino"].push_back(0.00715417);
  Label2XsecUnc["C1C1_hino"].push_back(0.0013767);
  Label2XsecUnc["C1C1_hino"].push_back(0.00141695);

  Label2XsecUnc["C1C1_wino"] = std::vector<double>();
  Label2XsecUnc["C1C1_wino"].push_back(518.613);
  Label2XsecUnc["C1C1_wino"].push_back(249.469);
  Label2XsecUnc["C1C1_wino"].push_back(138.156);
  Label2XsecUnc["C1C1_wino"].push_back(83.2672);
  Label2XsecUnc["C1C1_wino"].push_back(53.7411);
  Label2XsecUnc["C1C1_wino"].push_back(36.0699);
  Label2XsecUnc["C1C1_wino"].push_back(25.3131);
  Label2XsecUnc["C1C1_wino"].push_back(18.2886);
  Label2XsecUnc["C1C1_wino"].push_back(13.4438);
  Label2XsecUnc["C1C1_wino"].push_back(10.1835);
  Label2XsecUnc["C1C1_wino"].push_back(7.75261);
  Label2XsecUnc["C1C1_wino"].push_back(6.02606);
  Label2XsecUnc["C1C1_wino"].push_back(4.7276);
  Label2XsecUnc["C1C1_wino"].push_back(3.71547);
  Label2XsecUnc["C1C1_wino"].push_back(2.97283);
  Label2XsecUnc["C1C1_wino"].push_back(2.41224);
  Label2XsecUnc["C1C1_wino"].push_back(1.94904);
  Label2XsecUnc["C1C1_wino"].push_back(1.5992);
  Label2XsecUnc["C1C1_wino"].push_back(1.32368);
  Label2XsecUnc["C1C1_wino"].push_back(1.09669);
  Label2XsecUnc["C1C1_wino"].push_back(0.912324);
  Label2XsecUnc["C1C1_wino"].push_back(0.768988);
  Label2XsecUnc["C1C1_wino"].push_back(0.638889);
  Label2XsecUnc["C1C1_wino"].push_back(0.541519);
  Label2XsecUnc["C1C1_wino"].push_back(0.457123);
  Label2XsecUnc["C1C1_wino"].push_back(0.385799);
  Label2XsecUnc["C1C1_wino"].push_back(0.330353);
  Label2XsecUnc["C1C1_wino"].push_back(0.283139);
  Label2XsecUnc["C1C1_wino"].push_back(0.245196);
  Label2XsecUnc["C1C1_wino"].push_back(0.201762);
  Label2XsecUnc["C1C1_wino"].push_back(0.177806);
  Label2XsecUnc["C1C1_wino"].push_back(0.150075);
  Label2XsecUnc["C1C1_wino"].push_back(0.135822);
  Label2XsecUnc["C1C1_wino"].push_back(0.114539);
  Label2XsecUnc["C1C1_wino"].push_back(0.102086);
  Label2XsecUnc["C1C1_wino"].push_back(0.0779702);
  Label2XsecUnc["C1C1_wino"].push_back(0.0771005);
  Label2XsecUnc["C1C1_wino"].push_back(0.0667594);
  Label2XsecUnc["C1C1_wino"].push_back(0.0569349);
  Label2XsecUnc["C1C1_wino"].push_back(0.0506191);
  Label2XsecUnc["C1C1_wino"].push_back(0.0427672);
  Label2XsecUnc["C1C1_wino"].push_back(0.0414674);
  Label2XsecUnc["C1C1_wino"].push_back(0.0373521);
  Label2XsecUnc["C1C1_wino"].push_back(0.0301438);
  Label2XsecUnc["C1C1_wino"].push_back(0.0264135);
  Label2XsecUnc["C1C1_wino"].push_back(0.021483);
  Label2XsecUnc["C1C1_wino"].push_back(0.0198313);
  Label2XsecUnc["C1C1_wino"].push_back(0.0173508);
  Label2XsecUnc["C1C1_wino"].push_back(0.018756);
  Label2XsecUnc["C1C1_wino"].push_back(0.014292);
  Label2XsecUnc["C1C1_wino"].push_back(0.0135402);
  Label2XsecUnc["C1C1_wino"].push_back(0.0131703);
  Label2XsecUnc["C1C1_wino"].push_back(0.0114478);
  Label2XsecUnc["C1C1_wino"].push_back(0.00946571);
  Label2XsecUnc["C1C1_wino"].push_back(0.00707791);
  Label2XsecUnc["C1C1_wino"].push_back(0.00982729);
  Label2XsecUnc["C1C1_wino"].push_back(0.00619242);

  Label2XsecUnc["C1N2_hino"] = std::vector<double>();
  Label2XsecUnc["C1N2_hino"].push_back(191.047);
  Label2XsecUnc["C1N2_hino"].push_back(88.5068);
  Label2XsecUnc["C1N2_hino"].push_back(49.5956);
  Label2XsecUnc["C1N2_hino"].push_back(30.2898);
  Label2XsecUnc["C1N2_hino"].push_back(20.1252);
  Label2XsecUnc["C1N2_hino"].push_back(13.7917);
  Label2XsecUnc["C1N2_hino"].push_back(9.91401);
  Label2XsecUnc["C1N2_hino"].push_back(7.29273);
  Label2XsecUnc["C1N2_hino"].push_back(5.48175);
  Label2XsecUnc["C1N2_hino"].push_back(4.21492);
  Label2XsecUnc["C1N2_hino"].push_back(3.27086);
  Label2XsecUnc["C1N2_hino"].push_back(2.59994);
  Label2XsecUnc["C1N2_hino"].push_back(2.08121);
  Label2XsecUnc["C1N2_hino"].push_back(1.67896);
  Label2XsecUnc["C1N2_hino"].push_back(1.36074);
  Label2XsecUnc["C1N2_hino"].push_back(1.11821);
  Label2XsecUnc["C1N2_hino"].push_back(0.923598);
  Label2XsecUnc["C1N2_hino"].push_back(0.768185);
  Label2XsecUnc["C1N2_hino"].push_back(0.641762);
  Label2XsecUnc["C1N2_hino"].push_back(0.535553);
  Label2XsecUnc["C1N2_hino"].push_back(0.454855);
  Label2XsecUnc["C1N2_hino"].push_back(0.384183);
  Label2XsecUnc["C1N2_hino"].push_back(0.320722);
  Label2XsecUnc["C1N2_hino"].push_back(0.275617);
  Label2XsecUnc["C1N2_hino"].push_back(0.233891);
  Label2XsecUnc["C1N2_hino"].push_back(0.199351);
  Label2XsecUnc["C1N2_hino"].push_back(0.170376);
  Label2XsecUnc["C1N2_hino"].push_back(0.145489);
  Label2XsecUnc["C1N2_hino"].push_back(0.130506);
  Label2XsecUnc["C1N2_hino"].push_back(0.106692);
  Label2XsecUnc["C1N2_hino"].push_back(0.0964175);
  Label2XsecUnc["C1N2_hino"].push_back(0.082671);
  Label2XsecUnc["C1N2_hino"].push_back(0.0707011);
  Label2XsecUnc["C1N2_hino"].push_back(0.0589374);
  Label2XsecUnc["C1N2_hino"].push_back(0.0544187);
  Label2XsecUnc["C1N2_hino"].push_back(0.0516039);
  Label2XsecUnc["C1N2_hino"].push_back(0.041882);
  Label2XsecUnc["C1N2_hino"].push_back(0.0330277);
  Label2XsecUnc["C1N2_hino"].push_back(0.0298371);
  Label2XsecUnc["C1N2_hino"].push_back(0.0290054);
  Label2XsecUnc["C1N2_hino"].push_back(0.0253133);
  Label2XsecUnc["C1N2_hino"].push_back(0.0236533);
  Label2XsecUnc["C1N2_hino"].push_back(0.0152935);
  Label2XsecUnc["C1N2_hino"].push_back(0.0184681);
  Label2XsecUnc["C1N2_hino"].push_back(0.0168516);
  Label2XsecUnc["C1N2_hino"].push_back(0.0158738);
  Label2XsecUnc["C1N2_hino"].push_back(0.0105191);
  Label2XsecUnc["C1N2_hino"].push_back(0.00972415);
  Label2XsecUnc["C1N2_hino"].push_back(0.00687453);
  Label2XsecUnc["C1N2_hino"].push_back(0.00682866);
  Label2XsecUnc["C1N2_hino"].push_back(0.00500265);
  Label2XsecUnc["C1N2_hino"].push_back(0.00393035);
  Label2XsecUnc["C1N2_hino"].push_back(0.00277541);
  Label2XsecUnc["C1N2_hino"].push_back(0.00291342);
  Label2XsecUnc["C1N2_hino"].push_back(0.00295792);
  Label2XsecUnc["C1N2_hino"].push_back(0.00319031);
  Label2XsecUnc["C1N2_hino"].push_back(0.00183217);

  Label2XsecUnc["C1N2_wino"] = std::vector<double>();
  Label2XsecUnc["C1N2_wino"].push_back(973.967);
  Label2XsecUnc["C1N2_wino"].push_back(457.604);
  Label2XsecUnc["C1N2_wino"].push_back(253.223);
  Label2XsecUnc["C1N2_wino"].push_back(154.386);
  Label2XsecUnc["C1N2_wino"].push_back(101.316);
  Label2XsecUnc["C1N2_wino"].push_back(68.8042);
  Label2XsecUnc["C1N2_wino"].push_back(48.7463);
  Label2XsecUnc["C1N2_wino"].push_back(35.4083);
  Label2XsecUnc["C1N2_wino"].push_back(26.3602);
  Label2XsecUnc["C1N2_wino"].push_back(20.0201);
  Label2XsecUnc["C1N2_wino"].push_back(15.4539);
  Label2XsecUnc["C1N2_wino"].push_back(12.0956);
  Label2XsecUnc["C1N2_wino"].push_back(9.61659);
  Label2XsecUnc["C1N2_wino"].push_back(7.73547);
  Label2XsecUnc["C1N2_wino"].push_back(6.2389);
  Label2XsecUnc["C1N2_wino"].push_back(5.05005);
  Label2XsecUnc["C1N2_wino"].push_back(4.16461);
  Label2XsecUnc["C1N2_wino"].push_back(3.46763);
  Label2XsecUnc["C1N2_wino"].push_back(2.88065);
  Label2XsecUnc["C1N2_wino"].push_back(2.40183);
  Label2XsecUnc["C1N2_wino"].push_back(2.04438);
  Label2XsecUnc["C1N2_wino"].push_back(1.70195);
  Label2XsecUnc["C1N2_wino"].push_back(1.43519);
  Label2XsecUnc["C1N2_wino"].push_back(1.21937);
  Label2XsecUnc["C1N2_wino"].push_back(1.04092);
  Label2XsecUnc["C1N2_wino"].push_back(0.885243);
  Label2XsecUnc["C1N2_wino"].push_back(0.769988);
  Label2XsecUnc["C1N2_wino"].push_back(0.654544);
  Label2XsecUnc["C1N2_wino"].push_back(0.564061);
  Label2XsecUnc["C1N2_wino"].push_back(0.478362);
  Label2XsecUnc["C1N2_wino"].push_back(0.412315);
  Label2XsecUnc["C1N2_wino"].push_back(0.366257);
  Label2XsecUnc["C1N2_wino"].push_back(0.314019);
  Label2XsecUnc["C1N2_wino"].push_back(0.26801);
  Label2XsecUnc["C1N2_wino"].push_back(0.242682);
  Label2XsecUnc["C1N2_wino"].push_back(0.217618);
  Label2XsecUnc["C1N2_wino"].push_back(0.175604);
  Label2XsecUnc["C1N2_wino"].push_back(0.155683);
  Label2XsecUnc["C1N2_wino"].push_back(0.133077);
  Label2XsecUnc["C1N2_wino"].push_back(0.117638);
  Label2XsecUnc["C1N2_wino"].push_back(0.107178);
  Label2XsecUnc["C1N2_wino"].push_back(0.0917503);
  Label2XsecUnc["C1N2_wino"].push_back(0.0828113);
  Label2XsecUnc["C1N2_wino"].push_back(0.0644736);
  Label2XsecUnc["C1N2_wino"].push_back(0.0579252);
  Label2XsecUnc["C1N2_wino"].push_back(0.0561888);
  Label2XsecUnc["C1N2_wino"].push_back(0.046491);
  Label2XsecUnc["C1N2_wino"].push_back(0.0430197);
  Label2XsecUnc["C1N2_wino"].push_back(0.0339561);
  Label2XsecUnc["C1N2_wino"].push_back(0.0288259);
  Label2XsecUnc["C1N2_wino"].push_back(0.0309793);
  Label2XsecUnc["C1N2_wino"].push_back(0.0231066);
  Label2XsecUnc["C1N2_wino"].push_back(0.0188826);
  Label2XsecUnc["C1N2_wino"].push_back(0.0184156);
  Label2XsecUnc["C1N2_wino"].push_back(0.0173553);
  Label2XsecUnc["C1N2_wino"].push_back(0.0153453);
  Label2XsecUnc["C1N2_wino"].push_back(0.0140102);

  Label2XsecUnc["C1mN2_wino"] = std::vector<double>();
  Label2XsecUnc["C1mN2_wino"].push_back(517.621);
  Label2XsecUnc["C1mN2_wino"].push_back(235.43);
  Label2XsecUnc["C1mN2_wino"].push_back(126.192);
  Label2XsecUnc["C1mN2_wino"].push_back(73.7751);
  Label2XsecUnc["C1mN2_wino"].push_back(46.5066);
  Label2XsecUnc["C1mN2_wino"].push_back(30.8673);
  Label2XsecUnc["C1mN2_wino"].push_back(21.1263);
  Label2XsecUnc["C1mN2_wino"].push_back(14.9232);
  Label2XsecUnc["C1mN2_wino"].push_back(10.8212);
  Label2XsecUnc["C1mN2_wino"].push_back(7.9809);
  Label2XsecUnc["C1mN2_wino"].push_back(6.07824);
  Label2XsecUnc["C1mN2_wino"].push_back(4.60991);
  Label2XsecUnc["C1mN2_wino"].push_back(3.57812);
  Label2XsecUnc["C1mN2_wino"].push_back(2.80898);
  Label2XsecUnc["C1mN2_wino"].push_back(2.20924);
  Label2XsecUnc["C1mN2_wino"].push_back(1.77199);
  Label2XsecUnc["C1mN2_wino"].push_back(1.43549);
  Label2XsecUnc["C1mN2_wino"].push_back(1.1752);
  Label2XsecUnc["C1mN2_wino"].push_back(0.962412);
  Label2XsecUnc["C1mN2_wino"].push_back(0.797123);
  Label2XsecUnc["C1mN2_wino"].push_back(0.665467);
  Label2XsecUnc["C1mN2_wino"].push_back(0.544023);
  Label2XsecUnc["C1mN2_wino"].push_back(0.458682);
  Label2XsecUnc["C1mN2_wino"].push_back(0.387201);
  Label2XsecUnc["C1mN2_wino"].push_back(0.327628);
  Label2XsecUnc["C1mN2_wino"].push_back(0.283497);
  Label2XsecUnc["C1mN2_wino"].push_back(0.238501);
  Label2XsecUnc["C1mN2_wino"].push_back(0.202704);
  Label2XsecUnc["C1mN2_wino"].push_back(0.175172);
  Label2XsecUnc["C1mN2_wino"].push_back(0.142823);
  Label2XsecUnc["C1mN2_wino"].push_back(0.128463);
  Label2XsecUnc["C1mN2_wino"].push_back(0.111186);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0974831);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0826968);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0738302);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0622388);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0521727);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0474706);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0430882);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0377717);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0360823);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0280178);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0262367);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0232758);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0168488);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0190064);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0178031);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0165332);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0110105);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00934855);
  Label2XsecUnc["C1mN2_wino"].push_back(0.0137161);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00783768);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00620691);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00632462);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00644575);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00440125);
  Label2XsecUnc["C1mN2_wino"].push_back(0.00444647);

  Label2XsecUnc["C1pN2_wino"] = std::vector<double>();
  Label2XsecUnc["C1pN2_wino"].push_back(485.572);
  Label2XsecUnc["C1pN2_wino"].push_back(222.508);
  Label2XsecUnc["C1pN2_wino"].push_back(127.175);
  Label2XsecUnc["C1pN2_wino"].push_back(80.6306);
  Label2XsecUnc["C1pN2_wino"].push_back(54.8302);
  Label2XsecUnc["C1pN2_wino"].push_back(37.9761);
  Label2XsecUnc["C1pN2_wino"].push_back(27.6553);
  Label2XsecUnc["C1pN2_wino"].push_back(20.51);
  Label2XsecUnc["C1pN2_wino"].push_back(15.5522);
  Label2XsecUnc["C1pN2_wino"].push_back(12.0565);
  Label2XsecUnc["C1pN2_wino"].push_back(9.39716);
  Label2XsecUnc["C1pN2_wino"].push_back(7.50279);
  Label2XsecUnc["C1pN2_wino"].push_back(6.05361);
  Label2XsecUnc["C1pN2_wino"].push_back(4.94466);
  Label2XsecUnc["C1pN2_wino"].push_back(4.04097);
  Label2XsecUnc["C1pN2_wino"].push_back(3.28837);
  Label2XsecUnc["C1pN2_wino"].push_back(2.73443);
  Label2XsecUnc["C1pN2_wino"].push_back(2.29957);
  Label2XsecUnc["C1pN2_wino"].push_back(1.92376);
  Label2XsecUnc["C1pN2_wino"].push_back(1.60859);
  Label2XsecUnc["C1pN2_wino"].push_back(1.38165);
  Label2XsecUnc["C1pN2_wino"].push_back(1.15947);
  Label2XsecUnc["C1pN2_wino"].push_back(0.977468);
  Label2XsecUnc["C1pN2_wino"].push_back(0.832887);
  Label2XsecUnc["C1pN2_wino"].push_back(0.714013);
  Label2XsecUnc["C1pN2_wino"].push_back(0.602628);
  Label2XsecUnc["C1pN2_wino"].push_back(0.532335);
  Label2XsecUnc["C1pN2_wino"].push_back(0.452388);
  Label2XsecUnc["C1pN2_wino"].push_back(0.389213);
  Label2XsecUnc["C1pN2_wino"].push_back(0.335727);
  Label2XsecUnc["C1pN2_wino"].push_back(0.284029);
  Label2XsecUnc["C1pN2_wino"].push_back(0.255221);
  Label2XsecUnc["C1pN2_wino"].push_back(0.216666);
  Label2XsecUnc["C1pN2_wino"].push_back(0.185445);
  Label2XsecUnc["C1pN2_wino"].push_back(0.168945);
  Label2XsecUnc["C1pN2_wino"].push_back(0.15545);
  Label2XsecUnc["C1pN2_wino"].push_back(0.123448);
  Label2XsecUnc["C1pN2_wino"].push_back(0.108224);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0900054);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0799626);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0711016);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0637444);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0565834);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0412257);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0415881);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0371856);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0286937);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0264908);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0229469);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0196224);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0174043);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0154592);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0128138);
  Label2XsecUnc["C1pN2_wino"].push_back(0.012095);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0110593);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0109494);
  Label2XsecUnc["C1pN2_wino"].push_back(0.0096102);

  Label2XsecUnc["CN_hino"] = std::vector<double>();
  Label2XsecUnc["CN_hino"].push_back(603.411);
  Label2XsecUnc["CN_hino"].push_back(158.509);
  Label2XsecUnc["CN_hino"].push_back(63.3568);
  Label2XsecUnc["CN_hino"].push_back(30.7553);
  Label2XsecUnc["CN_hino"].push_back(16.7172);
  Label2XsecUnc["CN_hino"].push_back(9.85502);
  Label2XsecUnc["CN_hino"].push_back(6.18924);
  Label2XsecUnc["CN_hino"].push_back(4.02376);
  Label2XsecUnc["CN_hino"].push_back(2.7158);
  Label2XsecUnc["CN_hino"].push_back(1.86729);
  Label2XsecUnc["CN_hino"].push_back(1.32111);
  Label2XsecUnc["CN_hino"].push_back(0.937269);
  Label2XsecUnc["CN_hino"].push_back(0.678178);
  Label2XsecUnc["CN_hino"].push_back(0.493209);
  Label2XsecUnc["CN_hino"].push_back(0.372511);
  Label2XsecUnc["CN_hino"].push_back(0.274194);
  Label2XsecUnc["CN_hino"].push_back(0.204818);
  Label2XsecUnc["CN_hino"].push_back(0.155285);
  Label2XsecUnc["CN_hino"].push_back(0.122278);
  Label2XsecUnc["CN_hino"].push_back(0.0866612);
  Label2XsecUnc["CN_hino"].push_back(0.0721461);
  Label2XsecUnc["CN_hino"].push_back(0.0488588);
  Label2XsecUnc["CN_hino"].push_back(0.0486751);
  Label2XsecUnc["CN_hino"].push_back(0.0286811);
  Label2XsecUnc["CN_hino"].push_back(0.0196493);
  Label2XsecUnc["CN_hino"].push_back(0.0197535);
  Label2XsecUnc["CN_hino"].push_back(0.00926313);
  Label2XsecUnc["CN_hino"].push_back(0.0138617);

  Label2XsecUnc["N1N2_hino"] = std::vector<double>();
  Label2XsecUnc["N1N2_hino"].push_back(120.646);
  Label2XsecUnc["N1N2_hino"].push_back(30.1429);
  Label2XsecUnc["N1N2_hino"].push_back(11.7039);
  Label2XsecUnc["N1N2_hino"].push_back(5.48542);
  Label2XsecUnc["N1N2_hino"].push_back(2.92105);
  Label2XsecUnc["N1N2_hino"].push_back(1.66094);
  Label2XsecUnc["N1N2_hino"].push_back(1.00609);
  Label2XsecUnc["N1N2_hino"].push_back(0.636781);
  Label2XsecUnc["N1N2_hino"].push_back(0.413476);
  Label2XsecUnc["N1N2_hino"].push_back(0.275884);
  Label2XsecUnc["N1N2_hino"].push_back(0.190847);
  Label2XsecUnc["N1N2_hino"].push_back(0.132968);
  Label2XsecUnc["N1N2_hino"].push_back(0.0940638);
  Label2XsecUnc["N1N2_hino"].push_back(0.067662);
  Label2XsecUnc["N1N2_hino"].push_back(0.0505623);
  Label2XsecUnc["N1N2_hino"].push_back(0.0360593);
  Label2XsecUnc["N1N2_hino"].push_back(0.0279147);
  Label2XsecUnc["N1N2_hino"].push_back(0.0204919);
  Label2XsecUnc["N1N2_hino"].push_back(0.015677);
  Label2XsecUnc["N1N2_hino"].push_back(0.0117916);
  Label2XsecUnc["N1N2_hino"].push_back(0.0087975);
  Label2XsecUnc["N1N2_hino"].push_back(0.00709167);
  Label2XsecUnc["N1N2_hino"].push_back(0.00529162);
  Label2XsecUnc["N1N2_hino"].push_back(0.00410133);
  Label2XsecUnc["N1N2_hino"].push_back(0.00322793);
  Label2XsecUnc["N1N2_hino"].push_back(0.00249572);
  Label2XsecUnc["N1N2_hino"].push_back(0.00195389);
  Label2XsecUnc["N1N2_hino"].push_back(0.0014916);

  Label2XsecUnc["SlepSlep_left"] = std::vector<double>();
  Label2XsecUnc["SlepSlep_left"].push_back(161.713);
  Label2XsecUnc["SlepSlep_left"].push_back(9.27022);
  Label2XsecUnc["SlepSlep_left"].push_back(2.47754);
  Label2XsecUnc["SlepSlep_left"].push_back(0.963588);
  Label2XsecUnc["SlepSlep_left"].push_back(0.461974);
  Label2XsecUnc["SlepSlep_left"].push_back(0.239588);
  Label2XsecUnc["SlepSlep_left"].push_back(0.137647);
  Label2XsecUnc["SlepSlep_left"].push_back(0.0852404);
  Label2XsecUnc["SlepSlep_left"].push_back(0.0524108);
  Label2XsecUnc["SlepSlep_left"].push_back(0.0334231);

  Label2XsecUnc["SlepSlep_right"] = std::vector<double>();
  Label2XsecUnc["SlepSlep_right"].push_back(55.5328);
  Label2XsecUnc["SlepSlep_right"].push_back(3.87124);
  Label2XsecUnc["SlepSlep_right"].push_back(1.05173);
  Label2XsecUnc["SlepSlep_right"].push_back(0.400678);
  Label2XsecUnc["SlepSlep_right"].push_back(0.184433);
  Label2XsecUnc["SlepSlep_right"].push_back(0.0958926);
  Label2XsecUnc["SlepSlep_right"].push_back(0.0543556);
  Label2XsecUnc["SlepSlep_right"].push_back(0.0335597);
  Label2XsecUnc["SlepSlep_right"].push_back(0.0210193);
  Label2XsecUnc["SlepSlep_right"].push_back(0.0133309);
  
  return Label2XsecUnc;
}

std::map<std::string,double> XsecTool::m_Label2Xsec_BKG = XsecTool::InitMap_Xsec_BKG();
std::map<std::string,int> XsecTool::m_N_SMS = XsecTool::InitMap_N_SMS();
std::map<std::string,std::vector<double> > XsecTool::m_Label2Mass_SMS = XsecTool::InitMap_Mass_SMS();
std::map<std::string,std::vector<double> > XsecTool::m_Label2Xsec_SMS = XsecTool::InitMap_Xsec_SMS();
std::map<std::string,std::vector<double> > XsecTool::m_Label2XsecUnc_SMS = XsecTool::InitMap_XsecUnc_SMS();

// C1C1 2016   1000022 1000024
// C1N1 2016   1000022 1000024
// N2C1 2016   1000022 1000023 1000024half
// T2-4bd      1000022 1000006
// T2bW        1000022 1000006 1000024half
// T2cc         1000022 1000006
// T2tt         1000022 1000006
// TChiWG       1000022 1000023=1000024
// TChiWH       1000022 1000023=1000024
// TChiWH_2016  1000022 1000023=1000024
// TChiWZ       1000022 1000023=1000024
// TChiWZ_2016  1000022 1000023=1000024
