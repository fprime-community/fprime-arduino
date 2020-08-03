####
# Teensyduino.cmake:
#
# Toolchain file setup for building F prime for the Teensy hardware platform. This must, by definition, include the
# Arduino framework in order to ensure that basic functions of the Teensy hardware platform are available. This
# toolchain will build the core Teensy Arduino libraries, and include the headers as part of the target include headers.
####
# System setup for Teensyduino
set(CMAKE_SYSTEM_NAME Teensyduino)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY" CACHE STRING "Try Static Lib Type" FORCE)

# Check if ARDUINO_SDK_PATH is set, otherwise set it to /opt/arduino-1.8.9/
SET(ARDUINO_SDK_PATH "/opt/arduino-1.8.13" CACHE PATH "Path to Arduino SDK")
SET(TEENSY_VERSION "teensy32" CACHE STRING "Version of TEENSY to use")
string(REGEX MATCH "teensy[0-9]" TEENSY_CORE_DIR "${TEENSY_VERSION}")
include("${CMAKE_CURRENT_LIST_DIR}/ArduinoSupport/${TEENSY_VERSION}.cmake")
set(TEENSY_SRC_DIR "${ARDUINO_SDK_PATH}/hardware/teensy/avr/cores/${TEENSY_CORE_DIR}" CACHE PATH "Teensy SRC")
set(TEENSY_LIB_DIR "${ARDUINO_SDK_PATH}/hardware/teensy/avr/libraries/" CACHE PATH "Teensy Libraries SRC")
set(TEENSY_SUPPORTED_LIBS "SPI" "Wire")

message(STATUS "Arduino SDK path:  ${ARDUINO_SDK_PATH}")
message(STATUS "Teensy Version:    ${TEENSY_VERSION}; ${TEENSY_CORE_DIR}")
message(STATUS "Teensy Source Dir: ${TEENSY_SRC_DIR}")

# Setup the cross compiling tools path
set(ARDUINO_TOOLS_PATH "${ARDUINO_SDK_PATH}/hardware/tools/${CMAKE_SYSTEM_PROCESSOR}/bin")
message(STATUS "Teensy Tools Dir:  ${ARDUINO_TOOLS_PATH}")

# Grab a suffix for tools
if(WIN32)
    set(TOOL_SUFFIX .exe)
else()
    set(TOOL_SUFFIX )
endif()
# Set the tools path
set(CMAKE_C_COMPILER   "${ARDUINO_TOOLS_PATH}/arm-none-eabi-gcc${TOOL_SUFFIX}"         CACHE PATH "gcc"       FORCE)
set(CMAKE_CXX_COMPILER "${ARDUINO_TOOLS_PATH}/arm-none-eabi-g++${TOOL_SUFFIX}"         CACHE PATH "g++"       FORCE)
set(CMAKE_ASM_COMPILER "${ARDUINO_TOOLS_PATH}/arm-none-eabi-g++${TOOL_SUFFIX}"         CACHE PATH "assembler" FORCE)
set(CMAKE_AR           "${ARDUINO_TOOLS_PATH}/arm-none-eabi-gcc-ar${TOOL_SUFFIX}"      CACHE PATH "archive"   FORCE)
set(CMAKE_LINKER       "${ARDUINO_TOOLS_PATH}/arm-none-eabi-ld${TOOL_SUFFIX}"          CACHE PATH "linker"    FORCE)
set(CMAKE_NM           "${ARDUINO_TOOLS_PATH}/arm-none-eabi-nm${TOOL_SUFFIX}"          CACHE PATH "nm"        FORCE)
set(CMAKE_OBJCOPY      "${ARDUINO_TOOLS_PATH}/arm-none-eabi-objcopy${TOOL_SUFFIX}"     CACHE PATH "objcopy"   FORCE)
set(CMAKE_OBJDUMP      "${ARDUINO_TOOLS_PATH}/arm-none-eabi-objdump${TOOL_SUFFIX}"     CACHE PATH "objdump"   FORCE)
set(CMAKE_STRIP        "${ARDUINO_TOOLS_PATH}/arm-none-eabi-strip${TOOL_SUFFIX}"       CACHE PATH "strip"     FORCE)
set(CMAKE_SIZE         "${ARDUINO_TOOLS_PATH}/arm-none-eabi-size${TOOL_SUFFIX}"        CACHE PATH "size"      FORCE)
set(CMAKE_RANLIB       "${ARDUINO_TOOLS_PATH}/arm-none-eabi-gcc-ranlib${TOOL_SUFFIX}"  CACHE PATH "ranlib"    FORCE)

# Teensy common defines
set(TEENSY_DEF "-DF_CPU=${TEENSY_FREQ} -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE -D__${TEENSY_MCU}__")
set(TEENSY_DEF "${TEENSY_DEF} -DARDUINO=${TEENSY_ARDUINO_NUM} -DTEENSYDUINO=${TEENSY_TEENSYDUINO_NUM}")
# Teensy flags for each language
set(TEENSY_COM "-Wall -g -Os -MMD -ffunction-sections -fdata-sections")
set(TEENSY_CPU "-mthumb -mcpu=${TEENSY_CPU_ARCH} ${TEENSY_CPU_FLAGS}")
set(TEENSY_CPP "-std=gnu++14 -fno-exceptions -fpermissive -fno-rtti -felide-constructors -Wno-error=narrowing")
set(TEENSY_ASM "-x assembler-with-cpp")
set(TEENSY_LD  "-T${TEENSY_SRC_DIR}/${MCU_LD} -Wl,--gc-sections,--defsym=__rtc_localtime=0") #TODO: fix this time

# Set the tool and language flags
set(CMAKE_C_FLAGS   "${TEENSY_CPU} ${TEENSY_COM} ${TEENSY_DEF}"               CACHE STRING "C_FLAGS")
set(CMAKE_CXX_FLAGS "${TEENSY_CPU} ${TEENSY_COM} ${TEENSY_DEF} ${TEENSY_CPP}" CACHE STRING "CXX_FLAGS")
set(CMAKE_ASM_FLAGS "${TEENSY_CPU} ${TEENSY_COM} ${TEENSY_DEF} ${TEENSY_ASM}" CACHE STRING "ASM_FLAGS")
set(CMAKE_EXE_LINKER_FLAGS "${TEENSY_CPU} ${TEENSY_LD}"                       CACHE STRING "LD_FLAGS")

# Calls into the compiler
set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILER} -c <SOURCE> -o <OBJECT> <FLAGS> <DEFINES> <INCLUDES>" CACHE STRING "C++ to o")
set(CMAKE_ASM_COMPILE_OBJECT "${CMAKE_ASM_COMPILER} -c <SOURCE> -o <OBJECT> <FLAGS> <DEFINES> <INCLUDES>" CACHE STRING "ASM to o")
set(CMAKE_C_COMPILE_OBJECT   "${CMAKE_C_COMPILER}   -c <SOURCE> -o <OBJECT> <FLAGS> <DEFINES> <INCLUDES>" CACHE STRING "C to o")

# Glob up all the files for the Arduino lib build
file(GLOB ARDUINO_SRC "${TEENSY_SRC_DIR}/*.cpp" "${TEENSY_SRC_DIR}/*.c" "${TEENSY_SRC_DIR}/*.S")
foreach (TSLIB ${TEENSY_SUPPORTED_LIBS})
    file(GLOB ARDUINO_LIB "${TEENSY_LIB_DIR}/${TSLIB}/*.cpp" "${TEENSY_SRC_DIR}/${TSLIB}/*.c" "${TEENSY_SRC_DIR}/${TSLIB}/*.S")
    LIST(APPEND ARDUINO_SRC ${ARDUINO_LIB})
endforeach()
if (NOT ARDUINO_SRC STREQUAL "")
    set(TEENSY_ARDUINO_SRC ${ARDUINO_SRC} CACHE STRING "Teensy's Arduino Sources")
endif()
####
# add_arduino_dependency:
#
# Adds a dependency on the built version of the Arduino core for the teensy. It also registers a custom command to build
# the hex version of the output file for upload to the teensy itself. This will allow the user to burn to the Teensy
# using the Teensy bootloader utility.
# @param target: target project used to identify the output executable
####
function(add_arduino_dependency target)
    # Build the Arduino core library for Teensy
    if (NOT TARGET "teensycore")
        add_library("teensycore" ${ARDUINO_SRC} ${TEENSY_SHIM_SOURCES})
        target_link_libraries("teensycore" "m" "stdc++" ${TEENSY_LIBS})
        target_include_directories("teensycore" PUBLIC ${TEENSY_SRC_DIR})
        # Loop through the libraries
        foreach (TSLIB ${TEENSY_SUPPORTED_LIBS})
            target_include_directories("teensycore" PUBLIC "${TEENSY_LIB_DIR}/${TSLIB}")
        endforeach()
    endif()


    # Add a dependency on the teensycore (Arduino framework build) to the target
    add_dependencies(${target} "teensycore")
    target_link_libraries(${target} "teensycore" "m" "stdc++")
    target_include_directories(${target} PUBLIC ${TEENSY_SRC_DIR})
    # Loop through the libraries
    foreach (TSLIB ${TEENSY_SUPPORTED_LIBS})
         target_include_directories(${target} PUBLIC "${TEENSY_LIB_DIR}/${TSLIB}")
    endforeach()

    # Check if executable
    get_target_property(target_type ${target} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        # Add a command to generate the hex, and adding the custom target to link it in
        add_custom_command(OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex"
                           COMMAND "${CMAKE_OBJCOPY}"
                           ARGS "-O" "ihex" "-R" ".eeprom" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex"
                           DEPENDS "${target}")
        add_custom_target("${target}_hex" ALL DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex")
	add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_SIZE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}")
	add_custom_command(TARGET ${target}_hex POST_BUILD COMMAND ${CMAKE_SIZE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target}.hex")
    endif()
endfunction()
