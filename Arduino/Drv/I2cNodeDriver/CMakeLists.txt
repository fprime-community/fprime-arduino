####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
restrict_platforms(ArduinoFw)
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/I2cNodeDriver.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/I2cNodeDriver.cpp"
)
target_use_arduino_libraries("Wire")
register_fprime_module()
