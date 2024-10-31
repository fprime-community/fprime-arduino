####
# rpipico2.cmake:
#
# Raspberry Pi Pico 2 RP2350 support.
####
cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -std=gnu++17) # Force C++17 standard

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_WIFI_ENABLED ON)

set(ARDUINO_FQBN "rp2040:rp2040:rpipico2")
add_compile_options(-D_BOARD_RPIPICO2 -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
