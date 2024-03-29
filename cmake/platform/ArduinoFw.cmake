set(FPRIME_USE_BAREMETAL_SCHEDULER ON)
if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/arm") 
else()
    set(ARDUINO_TYPES_DIR "${CMAKE_CURRENT_LIST_DIR}/types/basic") 
endif()
message(STATUS "[fprime-arduino] Including Types Directory: ${ARDUINO_TYPES_DIR}")
include_directories("${ARDUINO_TYPES_DIR}" "${CMAKE_CURRENT_LIST_DIR}")

