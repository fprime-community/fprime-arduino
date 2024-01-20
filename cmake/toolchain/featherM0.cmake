####
# featherM0.cmake:
#
# Toolchain file setup for building F prime for the Feather M0 hardware platform. This must, by definition, include the
# Arduino framework in order to ensure that basic functions of the Feather M0 hardware platform are available. This
# toolchain will build the core Feather M0 Arduino libraries, and include the headers as part of the target include headers.
####
# System setup for Adafruit Feather M0
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "adafruit:samd:adafruit_feather_m0")
add_compile_options(-D_BOARD_FEATHERM0 -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
