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
    CHOOSES_IMPLEMENTATIONS
        Os_File_Stub
        Os_Generic_PriorityQueue
        Os_Mutex_Stub
        Fw_StringFormat_snprintf
        Os_Cpu_Baremetal
        Os_Memory_Baremetal
        Os_Task_Baremetal
        Os_Console_Arduino
        Os_RawTime_Arduino
    INTERFACE # No buildable files generated
)
