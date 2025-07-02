####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/SpiDriver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/SpiDriver.cpp"
)

list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/SpiDriverArduino.cpp")
target_use_arduino_libraries("SPI")

register_fprime_module()
