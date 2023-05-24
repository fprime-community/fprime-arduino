####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/GpioDriver.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/GpioDriver.cpp"
)
if(FPRIME_ARDUINO)
	list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/GpioDriverArduino.cpp")
else()
	list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/GpioDriverLinux.cpp")
endif()
register_fprime_module()
