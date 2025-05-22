if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/arm/Platform")
else()
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/basic/Platform")
endif()

set(CMAKE_EXECUTABLE_SUFFIX "${FPRIME_ARDUINO_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE)

# Add FPrime OSAL Implementations
choose_fprime_implementation(Os/File Os_File_Stub)
choose_fprime_implementation(Os/Queue Os_Generic_PriorityQueue)
choose_fprime_implementation(Os/Mutex Os_Mutex_Stub)

# Add Baremetal OSAL Implementations
choose_fprime_implementation(Os/Cpu Os_Cpu_Baremetal)
choose_fprime_implementation(Os/Memory Os_Memory_Baremetal)
choose_fprime_implementation(Os/Task Os_Task_Baremetal)

# Add Arduino OSAL Implementations
choose_fprime_implementation(Os/Console Os_Console_Arduino)
choose_fprime_implementation(Os/RawTime Os_RawTime_Arduino)

message(STATUS "[fprime-arduino] Including Types Directory: ${ARDUINO_TYPES_DIR}")
include_directories("${CMAKE_CURRENT_LIST_DIR}")
add_fprime_subdirectory("${ARDUINO_TYPES_DIR}")

