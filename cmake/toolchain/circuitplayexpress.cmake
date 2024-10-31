####
# circuitplayexpress.cmake:
#
# Adafruit Circuit Playground Express support.
####
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "adafruit:samd:adafruit_circuitplayground_m0")
add_compile_options(-D_BOARD_CIRCUIT_PLAYGROUND_EXPRESS -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
