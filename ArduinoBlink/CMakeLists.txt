####
# 'ArduinoBlink' Deployment:
#
# This sets up the build for the 'ArduinoBlink' Application, including the custom
# components. In addition, it imports FPrime.cmake, which includes the core F 
# Prime components.
#
# Author: lestarch
####

##
# Section 1: Basic Project Setup
#
# This contains the basic project information. Specifically, a cmake version and
# project definition.
##
project(ArduinoBlink C CXX)
cmake_minimum_required(VERSION 3.13)
# Must set baremetal scheduler
set(BAREMETAL_SCHEDULER "ON")

# Include the two parts of the build system. Not needing to register separate targets
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino.cmake")

##
# Section 3: Components and Topology
#
# This section includes deployment specific directories. This allows use of non-
# core components in the topology, which is also added here.
##
# Add component subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/LedBlinker")

# Add Topology subdirectory
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top")

