#!/bin/bash
VERSION="V1.0"

#// IP address, user name, password of the PLCnext.
PLC_IP="192.168.1.10"
PLC_USRNAME="admin"
PLC_PASS="15644c8d"

#// Print script information
echo "Script Version:$VERSION"
echo "IP address:\"$PLC_IP\""
echo "UserName:\"$PLC_USRNAME\" || PassWord : \"$PLC_PASS\""

sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "tail -f ~/projects/AcfTest/logs/AcfTest.log"