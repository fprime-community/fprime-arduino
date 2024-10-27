####
# kb2040.cmake:
#
# Adafruit KB2040 support.
####
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -std=gnu++17) # Force C++17 standard

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_WIFI_ENABLED ON)

set(ARDUINO_FQBN "rp2040:rp2040:adafruit_kb2040")
add_compile_options(-D_BOARD_KB2040 -DNO_ONBOARD_LED -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
