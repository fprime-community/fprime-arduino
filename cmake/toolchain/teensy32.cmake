####
# teensy32.cmake:
#
# Toolchain file setup for building F prime for the Teensy hardware platform. This must, by definition, include the
# Arduino framework in order to ensure that basic functions of the Teensy hardware platform are available. This
# toolchain will build the core Teensy Arduino libraries, and include the headers as part of the target include headers.
####
# System setup for Teensyduino
set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

# Teensy 31 is used to compile for the teensy 3.2 board
set(ARDUINO_FQBN "teensy:avr:teensy31")
add_compile_options(-D_BOARD_TEENSY32 -DFPRIME_ARUDINO_SYNTHETIC_WRITE -DFPRIME_ARUDINO_SYNTHETIC_NEW_NOTHROW)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
