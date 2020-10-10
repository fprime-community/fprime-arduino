# Disable targets not supported on Arduino
set_target_properties(
    Svc_LinuxTime
    Drv_SocketIpDriver
    PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-arduino/ArduinoOs")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-arduino/ArduinoTime")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-arduino/ArduinoDrv/SerialDriver")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/fprime-arduino/ArduinoDrv/HardwareRateDriver")

