####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/I2cDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/I2cDriver.cpp"
)
if(FPRIME_ARDUINO)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/I2cDriverArduino.cpp")
    target_use_arduino_libraries("Wire")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/I2cDriverLinux.cpp")
endif()
register_fprime_module()
