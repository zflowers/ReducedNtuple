#!/bin/sh
python Setup_Eff/setup.py

python hadd_Eff.py

sendmail z374f439@ku.edu < notify_eff.txt
