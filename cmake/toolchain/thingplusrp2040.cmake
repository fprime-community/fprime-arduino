####
# thingplusrp2040.cmake:
#
# RP2040 support.
####
# System setup for Teensyduino
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)

set(ARDUINO_FQBN "rp2040:rp2040:sparkfun_thingplusrp2040")
add_compile_options(-DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
