#!/bin/bash
#//
#// Copyright (c) 2019 Phoenix Contact  & Co. KG. All rights reserved.

while getopts t:a:n: option
do
    case "${option}"
    in
        t) TOOLCHAIN=${OPTARG};;
        a) ARPVERSION=${OPTARG};;
        n) TARGETNAME=${OPTARG};;
    esac
done

VERSION=$(echo $ARPVERSION | grep -oP [0-9]+[.][0-9]+[.][0-9]+[.][0-9]+)
echo "Version:${VERSION}"

# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo ">>>>>> The directory: $DIR <<<<<<<<<<"
echo "-DARP_TOOLCHAIN_ROOT=${TOOLCHAIN}"
echo "-DARP_DEVICE=${TARGETNAME}"
echo "-DARP_DEVICE_VERSION=${ARPVERSION}"
echo "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN}/toolchain.cmake"
echo "-S \"${DIR}/../.\""
echo "-B \"${DIR}/../build/${TARGETNAME}_${VERSION}\""
echo "<<<<<<<<<<>>>>>>>>>>><<<<<<<<<<<>>>>>>>>>>>"

echo CMAKE Configure
cmake --configure -G "Ninja" \
-DBUILD_TESTING=OFF \
-DUSE_ARP_DEVICE=ON \
-DCMAKE_STAGING_PREFIX="${DIR}/../deploy/" \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DCMAKE_PREFIX_PATH="${DIR}/../deploy/${TARGETNAME}_${VERSION}" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
"-DARP_TOOLCHAIN_ROOT=${TOOLCHAIN}" \
"-DARP_DEVICE=${TARGETNAME}" \
"-DARP_DEVICE_VERSION=${ARPVERSION}" \
"-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN}/toolchain.cmake" \
-S "${DIR}/../." \
-B "${DIR}/../build/${TARGETNAME}_${VERSION}"

cmake --build "${DIR}/../build/${TARGETNAME}_${VERSION}" \
--config Debug \
--target all -- -j 4

cmake --build "${DIR}/../build/${TARGETNAME}_${VERSION}" \
--config Debug --target install -- -j 4