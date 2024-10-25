set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/arm") 
else()
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/basic")
endif()

# fprime implementations
choose_fprime_implementation(Os/Mutex Os/Mutex/Stub)
choose_fprime_implementation(Os/Queue Os/Generic/PriorityQueue)

# Baremetal support layer implementations
choose_fprime_implementation(Os/File Os/File/Stub)
choose_fprime_implementation(Os/Task Os/Task/Stub)
choose_fprime_implementation(Os/Cpu Os/Cpu/Stub)
choose_fprime_implementation(Os/Memory Os/Memory/Stub)

# Arduino specific implementations
choose_fprime_implementation(Os/RawTime Os/RawTime/Stub)
choose_fprime_implementation(Os/Console Os/Console/Stub)

message(STATUS "[fprime-arduino] Including Types Directory: ${ARDUINO_TYPES_DIR}")
include_directories("${ARDUINO_TYPES_DIR}" "${CMAKE_CURRENT_LIST_DIR}")

