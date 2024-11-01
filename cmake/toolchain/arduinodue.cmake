####
# arduinodue.cmake:
#
# Arduino DUE support.
####
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm32")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "arduino:sam:arduino_due_x_dbg")
add_compile_options(-D_BOARD_ARDUINO_DUE -DFPRIME_ARUDINO_SYNTHETIC_NEW_NOTHROW -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
include("${CMAKE_CURRENT_LIST_DIR}/support/arduino-support.cmake")
