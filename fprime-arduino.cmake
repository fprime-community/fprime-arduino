restrict_platforms(ArduinoFw)

# Add ASSERT_RELATIVE_PATH definition for FW_ASSERT_LEVEL = FW_RELATIVE_PATH_ASSERT
add_definitions(-DASSERT_RELATIVE_PATH="${FPRIME_FRAMEWORK_PATH}/../")

# Add Arduino OSAL Implementations
choose_fprime_implementation(Os/Task Os_Task_Arduino)
choose_fprime_implementation(Os/Queue Os_Generic_PriorityQueue)
choose_fprime_implementation(Os/Mutex Os_Mutex_Arduino)
choose_fprime_implementation(Os/File Os_File_Stub)
choose_fprime_implementation(Os/Console Os_Console_Arduino)
choose_fprime_implementation(Os/Cpu Os_Cpu_Stub)
choose_fprime_implementation(Os/Memory Os_Memory_Stub)
choose_fprime_implementation(Os/RawTime Os_RawTime_Arduino)

# Include subdirectories
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Os")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/ArduinoTime")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/GpioDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/StreamDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/I2cDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/SpiDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/PwmDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/TcpClient")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/HardwareRateDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Arduino/Drv/AnalogDriver")
