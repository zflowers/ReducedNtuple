#!/bin/sh
while getopts s: flag
do
    case "{flag}" in
        s) sms=${OPTARG};;
    esac
done

python Setup_Hist/setup.py --$sms

python hadd.py

sendmail z374f439@ku.edu < notify.txt
