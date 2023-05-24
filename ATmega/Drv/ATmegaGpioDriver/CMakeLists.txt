####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####

set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentImplCommon.cpp"
)

# Arduino additions
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentImplAVR.cpp")
# Check the Linux build
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ATmegaGpioDriverComponentImplLinux.cpp")
endif()

register_fprime_module()
