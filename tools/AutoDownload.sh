#!/bin/bash

VERSION="V1.1"

#*******************************************************************
#// The IP address, user name and password of the PLCnext.
PLC_IP="192.168.1.10"
PLC_USRNAME="admin"
PLC_PASS="15644c8d"

#// ACF project path.
ACF_DIR_PATH="~/projects/AcfTest"
#// Name of the binary file executed.
ACF_BINARY_NAME="AcfTest"
#// Local path of the execution files.
ACF_BUILD_FILE_PATH="../deploy/AXCF2152_20.0.0.24752/Release/bin"
#// Local configure and settings file path.
ACF_SETTINGS_FILE_PATH="../ACFxml"
ACF_CONFIGURE_FILE_PATH="../ACFxml"
#*******************************************************************

# print the information of the script
echo "Script Version:$VERSION"
echo "IP address:\"$PLC_IP\""
echo "UserName:\"$PLC_USRNAME\" || PassWord : \"$PLC_PASS\""

echo "Step01 : Stop PLCnext Platform  (  wait about 10 s  )"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS  | sudo -S  /etc/init.d/plcnext stop"

echo "Step02 : Killing application's all threads"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP  "echo $PLC_PASS  | sudo -S   killall  ${ACF_BINARY_NAME} "

echo "Waiting... "
sleep 2s

echo "Step03 : Creating directory for ACF project"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "mkdir ${ACF_DIR_PATH}"

echo "Step04 : Creating directory for logs"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "mkdir ${ACF_DIR_PATH}/logs"

echo "Step06 : Pushing *.acf.settings file"
sshpass -p "$PLC_PASS"  scp  ${ACF_SETTINGS_FILE_PATH}/${ACF_BINARY_NAME}.acf.settings $PLC_USRNAME@$PLC_IP:${ACF_DIR_PATH}

echo "Step07 : Pushing *.acf.config file"
sshpass -p "$PLC_PASS"  scp  ${ACF_CONFIGURE_FILE_PATH}/${ACF_BINARY_NAME}.acf.config $PLC_USRNAME@$PLC_IP:~/projects/Default

echo "Step08 : Giving write-in permission to logs"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS  | sudo -S  chmod 777  ${ACF_DIR_PATH}/logs"

echo "Step09 : Downloading"
sshpass -p "$PLC_PASS"  scp  ${ACF_BUILD_FILE_PATH}/${ACF_BINARY_NAME} $PLC_USRNAME@$PLC_IP:${ACF_DIR_PATH}/

echo "Step10 : Enabling multi-RTthread"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP  " echo $PLC_PASS  | sudo -S  setcap cap_net_bind_service,cap_net_admin,cap_net_raw,cap_sys_boot,cap_sys_nice,cap_sys_time+ep  ${ACF_DIR_PATH}/${ACF_BINARY_NAME}"

echo "Step11 : Starting PLCnext Platform"
sshpass -p "$PLC_PASS" ssh $PLC_USRNAME@$PLC_IP "echo $PLC_PASS  | sudo -S  /etc/init.d/plcnext start"
echo "**********  Done  **********"