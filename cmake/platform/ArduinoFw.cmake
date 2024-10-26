if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/arm") 
else()
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/basic")
endif()
set(CMAKE_EXECUTABLE_SUFFIX "${FPRIME_ARDUINO_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE)
# fprime implementations
choose_fprime_implementation(Os/Mutex Os/Mutex/Stub)
choose_fprime_implementation(Os/Queue Os/Generic/PriorityQueue)

# Baremetal support layer implementations
choose_fprime_implementation(Os/File Os/File/Stub)
choose_fprime_implementation(Os/Task Os/Task/Baremetal)
choose_fprime_implementation(Os/Cpu Os/Cpu/Baremetal)
choose_fprime_implementation(Os/Memory Os/Memory/Baremetal)

# Arduino specific implementations
choose_fprime_implementation(Os/RawTime Os/RawTime/Arduino)
choose_fprime_implementation(Os/Console Os/Console/Arduino)

message(STATUS "[fprime-arduino] Including Types Directory: ${ARDUINO_TYPES_DIR}")
include_directories("${ARDUINO_TYPES_DIR}" "${CMAKE_CURRENT_LIST_DIR}")

