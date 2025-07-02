####
# nucleo_F401RE.cmake:
#
# NUCLEO-F401RE support.
####
cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -std=gnu++17) # Force C++17 standard

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

# Prevent test program compiling
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Fully Qualified Board Name for NUCLEO-F401RE
set(ARDUINO_FQBN "STMicroelectronics:stm32:Nucleo_64:pnum=NUCLEO_F401RE,upload_method=swdMethod")

add_compile_options(
    -D_BOARD_NUCLEO_F401RE
    -DVARIANT_H=\"variant_NUCLEO_F401RE.h\"
    -DUSE_BASIC_TIMER
)

# Run the base Arduino setup
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
