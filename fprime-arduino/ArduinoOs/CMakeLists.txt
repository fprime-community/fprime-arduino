####
# ArduinoOs:
#
# The Arudino Os support layer uses the F prime baremetal virtualization technology and a custom
# rebuild of the Arduino framework in order to ensure that all the code can compile into a sensible
# binary. This file sets up the Os layer to support all of that.
####

# Basic module dependencies
set(MOD_DEPS
  Fw/Cfg
  Fw/Types
  Fw/Logger
  Utils/Hash
)
####
# Source Files:
#
# These source files activate the baremetal virtualization technology that allows for the Arduino
# layer to take advantage of all functions of F prime (threaded components included) while still
# not using an OS. It is experimental technology, but it should work.
####
set(SOURCE_FILES
    # Common implementations
    "${FPRIME_FRAMEWORK_PATH}/Os/TaskCommon.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/TaskString.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/QueueCommon.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/QueueString.cpp"
    # Baremetal virtualization implementations
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/Queue.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/Task.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/File.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/FileSystem.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/IntervalTimer.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Baremetal/Mutex.cpp"
    # Non-OS based queue implementations
    "${FPRIME_FRAMEWORK_PATH}/Os/Pthreads/BufferQueueCommon.cpp"
    "${FPRIME_FRAMEWORK_PATH}/Os/Pthreads/FIFOBufferQueue.cpp"
    # From this package: an interval timer and a stream-log timer
    "${CMAKE_CURRENT_LIST_DIR}/ArduinoOs/IntervalTimer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ArduinoOs/StreamLog.cpp"
)

# Check for default logger and add it to the source list if needed
if (NOT FPRIME_DISABLE_DEFAULT_LOGGER)
    list(APPEND SOURCE_FILES "${FPRIME_FRAMEWORK_PATH}/LogDefault.cpp")
endif()

register_fprime_module()
####
# Teensyduino:
#
# This sets up a dependency on the Arduino framework compiled with the Teensyduino.cmake toolchain.
# By doing thi when the Teensyduino os is used, it will also build the Arduino dependency, creating
# a nice fresh version of Arduino ready to go.
####
if (${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
