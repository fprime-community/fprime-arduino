####
# esp32.cmake:
#
# ESP32 Dev Module support.
####
set(CMAKE_SYSTEM_NAME "ArduinoFw")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)

# Prevent test program compiling
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(ARDUINO_FQBN "esp32:esp32:esp32")
add_compile_options(-DFREERTOS)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
