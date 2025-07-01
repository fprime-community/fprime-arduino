####
# FPrime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/user-manual/build-system/cmake-api/
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/TcpServer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/TcpServer.cpp"
)

if (ARDUINO_WIFI_ENABLED)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/TcpServerWiFi.cpp")
    target_use_arduino_libraries("WiFi")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/TcpServerBasic.cpp")
endif()

register_fprime_module()
