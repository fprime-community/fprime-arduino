####
# featherSTM32F405.cmake:
#
# Adafruit Feather STM32F405 Express support.
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

set(ARDUINO_FQBN "STMicroelectronics:stm32:GenF4:pnum=FEATHER_F405,usb=CDCgen,upload_method=dfuMethod")
add_compile_options(
    -D_BOARD_FEATHER_STM32F405
    -DVARIANT_H=\"variant_FEATHER_F405.h\"
    -DNUM_DIGITAL_PINS=20
    -DNO_ONBOARD_LED
    -DUSE_BASIC_TIMER
)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
