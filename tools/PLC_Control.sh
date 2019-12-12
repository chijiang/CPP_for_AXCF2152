#!/bin/bash

VERSION="V1.0.1"

#// Set the IP address, user name and password of PLC
PLC_IP="192.168.1.10"
PLC_USRNAME="admin"
PLC_PASS="15644c8d"

#// Collect input data
while getopts s: option
do
    case "${option}"
    in
        s) PLC_OPERATION=${OPTARG};;
    esac
done 

#// Print the parameters information of the script
echo "Script Version:$VERSION"
echo "IP address:\"$PLC_IP\""
echo "UserName:\"$PLC_USRNAME\" || PassWord : \"$PLC_PASS\""

case "$PLC_OPERATION" in
    #// Log in via SSH
    "login")
        echo "Login to controller"
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP
        ;;
    #// observe the system log
    "syslog")
        echo "Open system log......"
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "tail -f ~/logs/Output.log"
        ;;
    #// Start the PLC
    "start")
        echo "PLCnext is going to START"
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS | sudo -S  /etc/init.d/plcnext start"
        ;;
    #// Stop the PLC
    "stop")
        echo "PLCnext is going to STOP"
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS | sudo -S  /etc/init.d/plcnext stop"
        ;;
    #// Restart the PLC
    "restart")
        echo "PLCnext is going to RESTART"
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS | sudo -S  /etc/init.d/plcnext restart"
        ;;
    #// Reset the PLC (Clean all user programs)
    "recover")
        echo "PLCnext is going to RECOVER"
        echo "You have 5 seconds to CANCEL by pressing \"CTRL + C \""
        sleep 5s
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS | sudo -S  recover-plcnext 1"
        ;;
    #// Factory reset the PLC
    #重置PLC（恢复出厂状态）
    "FactoryReset")
        echo "PLCnext is going to reset to Factory state!"
        echo "You have 10 seconds to CANCEL by pressing \"CTRL + C \""
        sleep 10s
        sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS | sudo -S  recover-plcnext 2"
        ;;
esac