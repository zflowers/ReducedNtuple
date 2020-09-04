#!/bin/sh
python Setup/setup.py

python hadd.py

sendmail z374f439@ku.edu < notify.txt
