#!/bin/bash
wget --no-check-certificate http://stash.osgconnect.net/+zflowers/sandbox-CMSSW_10_2_20_UL-9184d4c.tar.bz2

tar -xzf config_eff.tgz

export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh

source ./config_eff/cmssw_setup.sh

cmssw_setup sandbox-CMSSW_10_2_20_UL-9184d4c.tar.bz2 

./config_eff/Eff_Nano_Hist.x "$@"
