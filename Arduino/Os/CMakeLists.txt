####
# ArduinoOs:
#
# The Arudino Os support layer uses the F prime baremetal virtualization technology and a custom
# rebuild of the Arduino framework in order to ensure that all the code can compile into a sensible
# binary. This file sets up the Os layer to support all of that.
####
set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Console.cpp")
set(HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/Console.hpp")
set(MOD_DEPS)
register_fprime_module(Os_Console_Arduino)
register_fprime_implementation(Os/Console Os_Console_Arduino "${CMAKE_CURRENT_LIST_DIR}/DefaultConsole.cpp")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/RawTime.cpp")
set(HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/RawTime.hpp")
set(MOD_DEPS)
register_fprime_module(Os_RawTime_Arduino)
register_fprime_implementation(Os/RawTime Os_RawTime_Arduino "${CMAKE_CURRENT_LIST_DIR}/DefaultRawTime.cpp")