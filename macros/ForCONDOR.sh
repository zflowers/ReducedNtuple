#!/bin/sh

python Setup_Hist/setup.py

python watch.py

python hadd.py

cp HIST/*.root ./

sendmail z374f439@ku.edu < notify.txt
