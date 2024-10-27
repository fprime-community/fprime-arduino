####
# Teensyduino.cmake:
#
# Toolchain file setup for building F prime for the Teensy hardware platform. This must, by definition, include the
# Arduino framework in order to ensure that basic functions of the Teensy hardware platform are available. This
# toolchain will build the core Teensy Arduino libraries, and include the headers as part of the target include headers.
####
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

# Prevent test program compiling
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(ARDUINO_FQBN "STMicroelectronics:stm32:GenF4:pnum=BLACKPILL_F411CE,usb=CDCgen,upload_method=dfuMethod")
add_compile_options(
    -D_BOARD_BLACKPILL_STM32F411CE
    -DVARIANT_H=\"variant_BLACKPILL_F411CE.h\"
    -DUSE_BASIC_TIMER
)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
