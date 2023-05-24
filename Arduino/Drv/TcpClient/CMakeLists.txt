####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
if (NOT ARDUINO_WIFI_ENABLED)
    return()
endif()
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/TcpClient.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/TcpClient.cpp"
)

target_use_arduino_libraries("WiFi")

register_fprime_module()
