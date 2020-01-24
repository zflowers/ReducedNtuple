cd /home/t3-ku/z374f439/Eff_NANO/ReducedNtuple/

#python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Autumn18_102X.list -selector prod2018MC_reducedNANO_MET -tree Events -split=15,50

#python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Autumn18_102X_SMS.list -selector prod2018MC_reducedNANO_MET -tree Events -split=15,50

python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Fall17_102X.list -selector prod2017MC_reducedNANO_MET -tree Events -split=15,50

python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Fall17_102X_SMS.list -selector prod2017MC_reducedNANO_MET -tree Events -split=15,50

#python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Summer16_102X.list -selector prod2016MC_reducedNANO_MET -tree Events -split=15,50

#python scripts/CONDOR_unlt3_NANO_submit.py -list samples/NANO/Lists/Summer16_102X_SMS.list -selector prod2016MC_reducedNANO_MET -tree Events -split=15,50
