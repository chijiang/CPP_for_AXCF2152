############################## Set the project name ##################################
set(Project_Name "AcfTest")

############################## Requirement setup #####################################
cmake_minimum_required(VERSION 3.13)
project(${Project_Name})
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

############################## Create the generation object ###########################
set (WILDCARD_SOURCE *.cpp)
set (WILDCARD_HEADER *.h *.hpp *.hxx)

file(GLOB_RECURSE Headers src/${WILDCARD_HEADER} inc/${WILDCARD_HEADER})
file(GLOB_RECURSE Sources src/${WILDCARD_SOURCE})
add_executable(${Project_Name} ${Headers} ${Sources})

############################## Add the include directory ##############################

target_include_directories(${Project_Name}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/inc>)

############################## Cmake modules search directory #########################

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")

############################## Dependencies setting ###################################
# WARNING: Without --no-undefined the linker will not check, whether all necessary    #
#          libraries are linked. When a library which is necessary is not linked,     #
#          the firmware will crash and there will be NO indication why it crashed.    #
#######################################################################################

target_link_options(${Project_Name} PRIVATE LINKER:--no-undefined)

############################## Adding dependencies ####################################

find_package(ArpDevice REQUIRED)
find_package(ArpProgramming REQUIRED)

target_link_libraries(${Project_Name} PRIVATE ArpDevice ArpProgramming
                      Arp.System.ModuleLib Arp.System.Module
                      Arp.Plc.AnsiC Arp.System.Lm.Services)

############################## Deploy #################################################

string(REGEX REPLACE "^.*\\(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+).*$" "\\1" _ARP_SHORT_DEVICE_VERSION ${ARP_DEVICE_VERSION})
install(TARGETS ${Project_Name}
    LIBRARY DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    ARCHIVE DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/lib
    RUNTIME DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/$<CONFIG>/bin)
unset(_ARP_SHORT_DEVICE_VERSION)

############################## EOC ####################################################