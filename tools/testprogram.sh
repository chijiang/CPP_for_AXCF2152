#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact China

VERSION="V1.0"

#// Set the file name
FileName="testprog"



#// Set up ip address, user name and password of the PLC
PLC_IP="192.168.1.10"
PLC_USRNAME="admin"
PLC_PASS="15644c8d"


#// Show all information about the PLC
echo "Script Version:$VERSION"
echo "IP address:\"$PLC_IP\""
echo "UserName:\"$PLC_USRNAME\" || PassWord : \"$PLC_PASS\""



#// Download the program to PLC.
echo "Downloading... "
sshpass -p "$PLC_PASS"  scp  ../deploy/AXCF2152_20.0.0.24752/Release/bin/${FileName} $PLC_USRNAME@$PLC_IP:/tmp

#// Run program.
echo "Run Program..."
sshpass -p "$PLC_PASS"  ssh $PLC_USRNAME@$PLC_IP "/tmp/${FileName}"