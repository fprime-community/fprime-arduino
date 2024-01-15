####
# esp32.cmake:
#
# ESP32 Dev Module support.
####
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-std=c++20 -std=gnu++20) # Force C++20 standard

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)

# Prevent test program compiling
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(ARDUINO_FQBN "esp32:esp32:esp32")
add_compile_options(-D_BOARD_ESP32 -DNO_ONBOARD_LED -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
