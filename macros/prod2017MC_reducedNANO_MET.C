#define prod2017MC_reducedNANO_MET_cxx
#include "prod2017MC_reducedNANO_MET.h"
#include "Eff_Nano.h"

void prod2017MC_reducedNANO_MET::Loop()
{
   vector<string> vect_string_Trigger{
   "HLT_PFHT500_PFMET100_PFMHT100_IDTight",
   "HLT_PFHT500_PFMET110_PFMHT110_IDTight",
   "HLT_PFHT700_PFMET85_PFMHT85_IDTight",
   "HLT_PFHT700_PFMET95_PFMHT95_IDTight",
   "HLT_PFHT800_PFMET75_PFMHT75_IDTight",
   "HLT_PFHT800_PFMET85_PFMHT85_IDTight",
   "HLT_PFMET110_PFMHT110_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight",
   "HLT_PFMET130_PFMHT130_IDTight",
   "HLT_PFMET140_PFMHT140_IDTight",
   "HLT_PFMET120_PFMHT120_IDTight_PFHT60",
   "HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60",
   "HLT_PFMETTypeOne110_PFMHT110_IDTight",
   "HLT_PFMETTypeOne120_PFMHT120_IDTight",
   "HLT_PFMETTypeOne130_PFMHT130_IDTight",
   "HLT_PFMETTypeOne140_PFMHT140_IDTight",
   "HLT_PFMET200_NotCleaned",
   "HLT_PFMET200_HBHECleaned",
   "HLT_PFMET250_HBHECleaned",
   "HLT_PFMET300_HBHECleaned",
   "HLT_PFMET200_HBHE_BeamHaloCleaned",
   "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
   "HLT_PFMET100_PFMHT100_IDTight_PFHT60",
   "HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60",
   };
   string x = "METFixEE2017_pt";
   string year = "2017";
   Analyze(vect_string_Trigger,x,year,fChain,m_outFile);
}
