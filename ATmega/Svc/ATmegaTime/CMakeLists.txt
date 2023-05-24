####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaTimeComponent.cpp"
  )
else()
  set(SOURCE_FILES "${SOURCE_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/../../../fprime/Svc/LinuxTime/LinuxTimeImpl.cpp"
  )
endif()

set(MOD_DEPS
  Svc/Time
)

register_fprime_module()
# Add Teensyduino dependency
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()

