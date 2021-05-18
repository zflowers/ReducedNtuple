ls

tar -xzf config.tgz

ls config/

echo "Arguments: "

echo $@

export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh

source ./config/cmssw_setup.sh

cmssw_setup config/sandbox-CMSSW_10_2_20_UL-9d39de6.tar.bz2

./config/Eff_Nano_Hist.x "$@"
