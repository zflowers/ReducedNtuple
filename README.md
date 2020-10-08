Grid Setup

voms-proxy-init --voms cms -valid 192:00 

eval `scramv1 runtime -sh`

To make Ntuples

Single File:

./scripts/runMET.sh

CONDOR:

python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Some.list -selector prod201*MC_reducedNANO_MET

HADD Example:

python scripts/DO_hadd.py -idir output/Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/ -odir root/Autumn18_102X/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Autumn18_102X/

HADD Script:

./scripts/DO_hadd_MET.sh


To Process Ntuples (Jan 23, 2020)

./scripts/runMET_CONDOR.sh

After jobs finish

Run this in a screen:

./scripts/DO_hadd_MET.sh

Go to macros/ to make plots

