####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ArduinoTopologyAppAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"  
  "${CMAKE_CURRENT_LIST_DIR}/Topology.cpp"  
  "${CMAKE_CURRENT_LIST_DIR}/write.c"
)
# Note: supply non-explicit dependencies here
set(MOD_DEPS
  Fw/Logger
  Svc/GroundInterface
  fprime-arduino/ArduinoTime
  fprime-arduino/ArduinoOs
  Os
  Os/Baremetal/TaskRunner
)
# Register the standard elf build as another target
register_fprime_executable("${PROJECT_NAME}_exe")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    add_arduino_dependency("${PROJECT_NAME}_exe")
endif()
add_custom_target("${PROJECT_NAME}" DEPENDS "${PROJECT_NAME}_exe_hex")
