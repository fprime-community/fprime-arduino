####
# Uart:
#
# An implementation of the Arduino UART.  
####
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/UartComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/UartLinux.cpp"
    )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/UartComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/UartLinux.cpp"
    )
else() 
    set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/UartComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/UartComponentImpl.cpp"
    )
endif()
register_fprime_module()
