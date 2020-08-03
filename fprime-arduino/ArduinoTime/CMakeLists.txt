####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
  set(SOURCE_FILES
      "${CMAKE_CURRENT_LIST_DIR}/ArduinoTimeImpl.cpp")
else()
  set(SOURCE_FILES
      "${CMAKE_CURRENT_LIST_DIR}/LinuxTimeImpl.cpp")
endif()
set(MOD_DEPS
  Svc/Time
)
register_fprime_module()
# Add Teensyduino dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "Teensyduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
### UTs ###
set(UT_SOURCE_FILES
  "${FPRIME_FRAMEWORK_PATH}/Svc/Time/TimeComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Main.cpp"
)
register_fprime_ut()
