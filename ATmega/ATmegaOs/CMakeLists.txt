####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
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
# Determine the platform specific source files to append:

string(TOLOWER "${CMAKE_SYSTEM_NAME}" CMAKE_SYSTEM_NAME_LOWER)

# Arduino additions
if (${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
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
        "${CMAKE_CURRENT_LIST_DIR}/Arduino/IntervalTimer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Arduino/StreamLog.cpp"
    )
# AVR platform additions
elseif(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "avr")
    set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AVR/IntervalTimer.cpp")
endif()

register_fprime_module()


####
# Dependency Melding:
#
# In short, this Os layer depends on the framework's Os layer and vise-versa. Effectively it is one
# library built in two halves, the framework base, and this add on. Here we make the link pointers
# depend on one another forming a (weak) circular dependency. This is allowed in CMake 3.13 and
# newer.
####
if (${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    add_dependencies(Os ATmega_ATmegaOs)
    target_link_libraries(Os ATmega_ATmegaOs)
    target_link_libraries(ATmega_ATmegaOs Os)
endif()

# Add Arduino dependency
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()

# Add AVR dependency
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "avr")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_avr_dependency("${MODULE_NAME}")
endif()