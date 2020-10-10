####
# 'fprime-arduino' Deployment:
#
# This sets up the build for the 'fprime-arduino' library package, including the custom
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
project(fprime-arduino C CXX)
cmake_minimum_required(VERSION 3.13)
# Must set baremetal scheduler
set(BAREMETAL_SCHEDULER "ON")

# Include the two parts of the build system. Not needing to register separate targets
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/fprime-arduino.cmake")
