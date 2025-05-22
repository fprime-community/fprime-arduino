####
# arm/Platform/CMakeLists.txt:
#
# This file defines a configuration module for arm platforms.
####
register_fprime_config(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/PlatformTypes.fpp"
    HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/PlatformTypes.h"
        "${CMAKE_CURRENT_LIST_DIR}/cassert"
        "${CMAKE_CURRENT_LIST_DIR}/cinttypes"
        "${CMAKE_CURRENT_LIST_DIR}/cmath"
        "${CMAKE_CURRENT_LIST_DIR}/cstdarg"
        "${CMAKE_CURRENT_LIST_DIR}/cstdint"
        "${CMAKE_CURRENT_LIST_DIR}/cstdio"
        "${CMAKE_CURRENT_LIST_DIR}/cstdlib"
        "${CMAKE_CURRENT_LIST_DIR}/cstring"
        "${CMAKE_CURRENT_LIST_DIR}/ctime"
        "${CMAKE_CURRENT_LIST_DIR}/limits"
        "${CMAKE_CURRENT_LIST_DIR}/new"
    INTERFACE # No buildable files generated
)
