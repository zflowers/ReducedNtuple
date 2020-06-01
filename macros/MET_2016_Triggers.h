#ifndef MET_2016_TRIGGERS_H
#define MET_2016_TRIGGERS_H

#include <vector>

using namespace std;
vector<string> Get_2016_Triggers()
{
   vector<string> vect_string_Trigger{
   /*
   "HLT_DoubleMu33NoFiltersNoVtx",
   "HLT_DoubleMu38NoFiltersNoVtx",
   "HLT_DoubleMu23NoFiltersNoVtxDisplaced",
   "HLT_DoubleMu28NoFiltersNoVtxDisplaced",
   "HLT_DoubleMu0",
   "HLT_Ele17_Ele8_Gsf",
   "HLT_Ele22_eta2p1_WPLoose_Gsf",
   "HLT_Ele23_WPLoose_Gsf",
   "HLT_Ele24_eta2p1_WPLoose_Gsf",
   "HLT_Ele25_WPTight_Gsf",
   "HLT_Ele25_eta2p1_WPLoose_Gsf",
   "HLT_Ele25_eta2p1_WPTight_Gsf",
   "HLT_Ele27_WPLoose_Gsf",
   "HLT_Ele27_WPTight_Gsf",
   "HLT_Ele27_eta2p1_WPLoose_Gsf",
   "HLT_Ele27_eta2p1_WPTight_Gsf",
   "HLT_Ele30_WPTight_Gsf",
   "HLT_Ele30_eta2p1_WPLoose_Gsf",
   "HLT_Ele30_eta2p1_WPTight_Gsf",
   "HLT_Ele32_WPTight_Gsf",
   "HLT_Ele32_eta2p1_WPLoose_Gsf",
   "HLT_Ele32_eta2p1_WPTight_Gsf",
   "HLT_Ele35_WPLoose_Gsf",
   "HLT_Ele45_WPLoose_Gsf",
   "HLT_HT200",
   "HLT_HT275",
   "HLT_HT325",
   "HLT_HT425",
   "HLT_HT575",
   "HLT_HT410to430",
   "HLT_HT430to450",
   "HLT_HT450to470",
   "HLT_HT470to500",
   "HLT_HT500to550",
   "HLT_HT550to650",
   "HLT_HT650",
   "HLT_Mu16_eta2p1_MET30",
   "HLT_IsoMu16_eta2p1_MET30",
   "HLT_IsoMu17_eta2p1",
   "HLT_DoubleIsoMu17_eta2p1",
   "HLT_DoubleIsoMu17_eta2p1_noDzCut",
   "HLT_IsoMu18",
   "HLT_IsoMu20",
   "HLT_IsoMu22",
   "HLT_IsoMu24",
   "HLT_IsoMu27",
   "HLT_L1SingleMu18",
   "HLT_Mu17_Mu8",
   "HLT_Mu17_Mu8_DZ",
   "HLT_Mu17_Mu8_SameSign",
   "HLT_Mu17_Mu8_SameSign_DZ",
   "HLT_Mu20_Mu10",
   "HLT_Mu20_Mu10_DZ",
   "HLT_Mu20_Mu10_SameSign",
   "HLT_Mu20_Mu10_SameSign_DZ",
   "HLT_Mu17_TkMu8_DZ",
   "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL",
   "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ",
   "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL",
   "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ",
   "HLT_PFHT300_PFMET100",
   "HLT_PFHT300_PFMET110",
   "HLT_MET60_IsoTrk35_Loose",
   "HLT_MET75_IsoTrk50",
   "HLT_MET90_IsoTrk50",
   "HLT_PFMET170_NotCleaned",
   "HLT_PFMET170_NoiseCleaned",
   "HLT_PFMET170_HBHECleaned",
   "HLT_PFMET170_JetIdCleaned",
   "HLT_PFMET170_BeamHaloCleaned",
   "HLT_PFMET170_HBHE_BeamHaloCleaned",
   "HLT_PFMETTypeOne190_HBHE_BeamHaloCleaned",
   "HLT_PFMET90_PFMHT90_IDTight",
   "HLT_PFMET100_PFMHT100_IDTight",
   "HLT_PFMET100_PFMHT100_IDTight_BeamHaloCleaned",
   "HLT_PFMET110_PFMHT110_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight",
   "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight_BTagCSV_p067",
   "HLT_CaloMHTNoPU90_PFMET90_PFMHT90_IDTight",
   "HLT_Mu8_TrkIsoVVL",
   "HLT_Mu17_TrkIsoVVL",
   "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded",
   "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL",
   "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",
   "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
   "HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL",
   "HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL",
   "HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL",
   "HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL",
   "HLT_Mu8_DiEle12_CaloIdL_TrackIdL",
   "HLT_DiMu9_Ele9_CaloIdL_TrackIdL",
   "HLT_TripleMu_5_3_3",
   "HLT_TripleMu_12_10_5",
   "HLT_Mu6_PFHT200_PFMET80_BTagCSV_p067",
   "HLT_Mu6_PFHT200_PFMET100",
   "HLT_Mu14er_PFMET100",
   "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL",
   "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL",
   "HLT_Ele12_CaloIdL_TrackIdL_IsoVL",
   "HLT_Ele17_CaloIdL_GsfTrkIdVL",
   "HLT_Ele17_CaloIdL_TrackIdL_IsoVL",
   "HLT_Ele23_CaloIdL_TrackIdL_IsoVL",
   "HLT_PFMET90_PFMHT90_IDTight",
   "HLT_PFMET100_PFMHT100_IDTight",
   "HLT_PFMET110_PFMHT110_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight",
   "HLT_PFMETNoMu90_PFMHTNoMu90_IDTight",
   "HLT_PFMETNoMu100_PFMHTNoMu100_IDTight",
   "HLT_PFMETNoMu110_PFMHTNoMu110_IDTight",
   "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
   "HLT_PFMET120_Mu5",
   "HLT_Mu3er_PFHT140_PFMET125",
   "HLT_DoubleMu3_PFMET50",
   "HLT_Ele15_IsoVVVL_PFHT350_PFMET50",
   "HLT_Ele15_IsoVVVL_PFHT400_PFMET50",
   "HLT_Mu15_IsoVVVL_PFHT350_PFMET50",
   "HLT_Mu15_IsoVVVL_PFHT400_PFMET50",
   "HLT_Mu8",
   "HLT_Mu17",
   "HLT_Mu55",
   "HLT_MET100",
   "HLT_MET150",
   "HLT_MET200",
   "HLT_MET250",
   "HLT_MET300",
   "HLT_MET600",
   "HLT_MET700",
   "HLT_PFMET300",
   "HLT_PFMET400",
   "HLT_PFMET500",
   "HLT_PFMET600",
   */
   "METtrigger",
   //"METHTtrigger",
   "METORtrigger",
   };
   return vect_string_Trigger;
};

#endif
