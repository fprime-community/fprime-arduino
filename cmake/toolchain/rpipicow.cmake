####
# rpipicow.cmake:
#
# Raspberry Pi Pico W RP2040 support.
####

set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_WIFI_ENABLED ON)
set(ARDUINO_FQBN "rp2040:rp2040:rpipicow")
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
