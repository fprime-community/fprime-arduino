####
# circuitplaybluefruit.cmake:
#
# Adafruit Circuit Playground Bluefruit support.
####
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "adafruit:nrf52:cplaynrf52840")
add_compile_options(-D_BOARD_CIRCUIT_PLAYGROUND_BLUEFRUIT -DFPRIME_ARUDINO_SYNTHETIC_NEW_NOTHROW -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
