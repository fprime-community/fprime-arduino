####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverComponentAi.xml"
  "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriver.cpp"
)

# Arduino additions
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverArduino.cpp")
# Check the Linux build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/HardwareRateDriverLinux.cpp")
endif()
register_fprime_module()

# Add Arduino dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
