####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
if(FPRIME_ARDUINO)
  set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ArduinoTimeImpl.cpp")
else()
  set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/LinuxTimeImpl.cpp")
endif()

set(MOD_DEPS
  Svc/Time
)

register_fprime_module()

