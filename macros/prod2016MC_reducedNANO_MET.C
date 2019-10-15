#define prod2016MC_reducedNANO_MET_cxx
#include "prod2016MC_reducedNANO_MET.h"
#include "Eff_Nano.h"

void prod2016MC_reducedNANO_MET::Loop()
{
   vector<string> vect_string_Trigger{
   "HLT_PFHT300_PFMET100",
   "HLT_PFHT300_PFMET110",
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
   };
   string x = "MET_pt";
   string year = "2016";
   Analyze(vect_string_Trigger,x,year,fChain,m_outFile);
}
