####
# ArduinoOs:
#
# The Arudino Os support layer uses the F prime baremetal virtualization technology and a custom
# rebuild of the Arduino framework in order to ensure that all the code can compile into a sensible
# binary. This file sets up the Os layer to support all of that.
####
cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0079 NEW)

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
if (FPRIME_ARDUINO)
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
        "${CMAKE_CURRENT_LIST_DIR}/IntervalTimer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/StreamLog.cpp"
    )
    target_use_arduino_libraries("TimeLib")
    register_fprime_module()
endif()

# Check for default logger and add it to the source list if needed
#if (NOT FPRIME_DISABLE_DEFAULT_LOGGER)
#    list(APPEND SOURCE_FILES "${FPRIME_FRAMEWORK_PATH}/Os/LogDefault.cpp")
#endif()

####
# Dependency Melding:
#
# In short, this Os layer depends on the framework's Os layer and vise-versa. Effectively it is one
# library built in two halves, the framework base, and this add on. Here we make the link pointers
# depend on one another forming a (weak) circular dependency. This is allowed in CMake 3.13 and
# newer.
####
if (FPRIME_ARDUINO)
    add_dependencies(Os Arduino_Os)
    target_link_libraries(Os PRIVATE Arduino_Os)
    target_link_libraries(Arduino_Os PUBLIC Os)
endif()
