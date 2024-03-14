####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ArduinoTime.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ArduinoTime.cpp"
)

target_use_arduino_libraries("TimeLib")

register_fprime_module()

