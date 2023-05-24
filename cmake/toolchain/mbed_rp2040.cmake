####
# mbed_rp2040.cmake:
#
# RP2040 support.
####
# System setup for Teensyduino
set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)
set(ARDUINO_EXTRA_FILES "linker_script.ld" ".map")

# Teensy 40 is used to compile for the teensy 4.1 board
set(ARDUINO_FQBN "arduino:mbed_rp2040:pico")
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
