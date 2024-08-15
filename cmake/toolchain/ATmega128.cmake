####
# ATmega128.cmake:
#
# Arduino MegaCore ATmega128 support file. This file ensures that the
# ATmega128 can be used as a target for the CMake system's output. This
# sets the Arduino target to be the MegaCore ATmega128.
####


# System setup for MegaCore
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "avr")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
# set(ARDUINO_LIBRARIES "SPI.h" "Wire.h" "TimerOne.h")
set(ARDUINO_BUILD_PROPERTIES "build.extra_flags=-flto -mrelax -mcall-prologues")
set(ARDUINO_BOARD_OPTIONS "clock=7_3728MHz_external")
set(ARDUINO_LINKER_FLAGS "-Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff")

set(ARDUINO_FQBN "MegaCore:avr:128")
add_compile_options(-DATMEGA)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
# Use the ranlib wrapper which adds the appropriate --plugin option for the compiler
SET(CMAKE_RANLIB "${CMAKE_CXX_COMPILER_RANLIB}")

# include_directories("${CMAKE_CURRENT_LIST_DIR}/../../ATmega/vendor/libraries/TimerOne")
