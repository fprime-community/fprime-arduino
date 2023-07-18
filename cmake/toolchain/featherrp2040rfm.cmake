####
# thingplusrp2040.cmake:
#
# RP2040 support.
####
# System setup for Teensyduino
set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)


set(ARDUINO_FQBN "rp2040:rp2040:adafruit_feather_rfm")
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
