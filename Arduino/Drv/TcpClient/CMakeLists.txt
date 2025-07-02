####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/TcpClient.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/TcpClient.cpp"
)

if (ARDUINO_WIFI_ENABLED)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/TcpClientWiFi.cpp")
    target_use_arduino_libraries("WiFi")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/TcpClientBasic.cpp")
endif()

register_fprime_module()
