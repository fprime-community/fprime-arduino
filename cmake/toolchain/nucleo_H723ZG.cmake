#### 
# nucleo_H723ZG.cmake: 
# 
# NUCLEO-H723ZG support. 
#### 
cmake_minimum_required(VERSION 3.26) 
set(CMAKE_CXX_STANDARD 17) 
add_compile_options(-std=c++17 -std=gnu++17) # Force C++17 standard 

set(CMAKE_SYSTEM_NAME "Generic") 
set(CMAKE_SYSTEM_PROCESSOR "arm") 
set(CMAKE_CROSSCOMPILING 1) 

if(NOT DEFINED FPRIME_PLATFORM)
    set(FPRIME_PLATFORM "ArduinoFw") 
endif()

if(NOT DEFINED FPRIME_USE_BAREMETAL_SCHEDULER)
    set(FPRIME_USE_BAREMETAL_SCHEDULER ON) 
endif()

set(ARDUINO_BUILD_PROPERTIES) 

# Prevent test program compiling 
set(CMAKE_C_COMPILER_WORKS 1) 
set(CMAKE_CXX_COMPILER_WORKS 1) 

set(ARDUINO_FQBN "STMicroelectronics:stm32:Nucleo_144:pnum=NUCLEO_H723ZG,upload_method=swdMethod") 
 
add_compile_options( 
-D_BOARD_NUCLEO_H723ZG 
-DVARIANT_H=\"variant_NUCLEO_H723ZG.h\" 
-DUSE_BASIC_TIMER 
) 
message("--------------------------------------------------------------------")
message("----------------------- CONFIGURATION VALUES -----------------------")
message("--------------------------------------------------------------------")
message("FPRIME_USE_BAREMETAL_SCHEDULER: ${FPRIME_USE_BAREMETAL_SCHEDULER} ")
message("FPRIME_PLATFORM: ${FPRIME_PLATFORM} ")
message("---------------------------------------------------------------------")


# Run the base arduino setup which should detect settings! 
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake") 