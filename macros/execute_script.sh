tar -xzf config.tgz

export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh

source ./config/cmssw_setup.sh

./config/Eff_Nano_Hist.x "$@"
