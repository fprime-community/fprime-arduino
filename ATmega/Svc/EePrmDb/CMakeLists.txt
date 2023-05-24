####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/EePrmDbComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/EePrmDbComponentImpl.cpp"
)

# Determine the platform specific source files to append:
string(TOLOWER "${CMAKE_SYSTEM_NAME}" CMAKE_SYSTEM_NAME_LOWER)

# Arduino/AVR additions
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino" OR ${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "avr")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/EePrmDbComponentAVRImpl.cpp")
# Otherwise, assume Linux-compatible build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/EePrmDbComponentLinuxImpl.cpp")
endif()

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#   Fw/Logger
# )

register_fprime_module()

# Add Arduino dependency
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()

# Add AVR dependency
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "avr")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_avr_dependency("${MODULE_NAME}")
endif()
