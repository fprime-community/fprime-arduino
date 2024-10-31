####
# featherRP2350.cmake:
#
# Adafruit Feather RP2350 HSTX support.
####
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -std=gnu++17) # Force C++17 standard

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_WIFI_ENABLED ON)

set(ARDUINO_FQBN "rp2040:rp2040:adafruit_feather_rp2350_hstx")
add_compile_options(-D_BOARD_FEATHER_RP2350 -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
