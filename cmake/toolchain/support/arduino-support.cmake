####
# arduino-support.cmake:
#
# Support for arduino supported boards using the arduino-cli utility. Note: users must install boards, libraries, and
# cores through the arduino-cli utility in order to use those parts of arduino with this toolchain. Additionally, this
# toolchain provides for the following functions:
#
# - include_arduino_libraries: called to add arduino libraries into the toolchain. The user may use these libraries and
#     the final executable will be linked against these libraries.
# - finalize_arduino_executable: called on a deployment target to attach the arduino specific steps and libraries to it.
#
# @author lestarch
####
cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/arduino-wrapper.cmake")
set(FPRIME_ARDUINO TRUE)
set(ARDUINO_WRAPPER_JSON_OUTPUT "${CMAKE_BINARY_DIR}/arduino-cli-compiler-settings.json")
set(EXTRA_LIBRARY_SOURCE "${CMAKE_CURRENT_LIST_DIR}/sources/extras.cpp")


####
# Function `set_arduino_build_settings`:
#
# Detects compiler settings from `arduino-cli`. Compiles a test sketch in order to detect these settings. Sets necessary
# tool variables for CMake to run.
#
####
function(set_arduino_build_settings)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY PARENT_SCOPE)
    # Check if a file cache was created already: prescan (..), try-compile (../..), or prescan try-compile (../../..)
    set(POSSIBLE_LOCATIONS ".." "../.." "../../..")
    get_filename_component(JSON_NAME "${ARDUINO_WRAPPER_JSON_OUTPUT}" NAME)
    foreach(LOCATION IN LISTS POSSIBLE_LOCATIONS)
        set(FOUND_LOCATION "${CMAKE_BINARY_DIR}/${LOCATION}/${JSON_NAME}")
        if (NOT EXISTS "${FOUND_LOCATION}")
            set(FOUND_LOCATION)
        endif()
    endforeach()

    # If it was not found, generate it
    if (NOT FOUND_LOCATION)
        set(FOUND_LOCATION "${ARDUINO_WRAPPER_JSON_OUTPUT}")
        run_arduino_wrapper("-b" "${ARDUINO_FQBN}" "--properties" ${ARDUINO_BUILD_PROPERTIES} -j "${FOUND_LOCATION}")
    endif()
    file(READ "${FOUND_LOCATION}" WRAPPER_OUTPUT)
    # Compilers detection
    foreach(SOURCE_TYPE IN ITEMS ASM C CXX)
        read_json(CMAKE_${SOURCE_TYPE}_COMPILER "${WRAPPER_OUTPUT}" tools ${SOURCE_TYPE})
        read_json(CMAKE_${SOURCE_TYPE}_FLAGS_INIT "${WRAPPER_OUTPUT}" flags ${SOURCE_TYPE})
    endforeach()
    # Other tools detection
    foreach(TOOL IN ITEMS AR LINKER)
        read_json(CMAKE_${TOOL} "${WRAPPER_OUTPUT}" tools ${TOOL})
    endforeach()
    # Flags for each of the tools
    read_json(ARDUINO_AR_FLAGS "${WRAPPER_OUTPUT}" flags AR)
    read_json(CMAKE_EXE_LINKER_FLAGS_INIT "${WRAPPER_OUTPUT}" flags LINKER_EXE)

    # Convert lists to the INIT " " separated format
    foreach(LIST_VARIABLE IN ITEMS
            CMAKE_ASM_FLAGS_INIT CMAKE_C_FLAGS_INIT CMAKE_CXX_FLAGS_INIT
            ARDUINO_AR_FLAGS CMAKE_EXE_LINKER_FLAGS_INIT)
        string(REPLACE ";" " " "${LIST_VARIABLE}" "${${LIST_VARIABLE}}")
    endforeach()

    read_json(INCLUDES "${WRAPPER_OUTPUT}" includes CXX)
    include_directories(${INCLUDES})
    if (NOT TARGET fprime_arduino_base_libraries)
        add_library(fprime_arduino_base_libraries INTERFACE)
        add_dependencies(fprime_arduino_base_libraries core fprime_arduino_loose_object_library)
        target_link_libraries(fprime_arduino_base_libraries INTERFACE core fprime_arduino_loose_object_library fprime_arduino_patcher)
    endif()
    link_libraries(fprime_arduino_base_libraries)
    # Setup misc commands
    SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> ${ARDUINO_AR_FLAGS} <TARGET> <OBJECTS>")
    SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> ${ARDUINO_AR_FLAGS} <TARGET> <OBJECTS>")
    set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

    # Export data here-in
    foreach(SETTING IN ITEMS CMAKE_ASM_COMPILER CMAKE_ASM_FLAGS_INIT
        CMAKE_C_COMPILER CMAKE_C_FLAGS_INIT
        CMAKE_CXX_COMPILER CMAKE_CXX_FLAGS_INIT
        CMAKE_AR CMAKE_C_ARCHIVE_CREATE CMAKE_CXX_ARCHIVE_CREATE
        CMAKE_LINKER CMAKE_EXE_LINKER_FLAGS_INIT CMAKE_CXX_LINK_EXECUTABLE
    )
        set(${SETTING} "${${SETTING}}" PARENT_SCOPE)
    endforeach()
endfunction(set_arduino_build_settings)

####
# Function `target_use_arduino_libraries`:
#
# Uses `arduino-cli` to detect include paths for libraries supplied to this call. Allows these libraries to be used by
# adding a dependency to the library's name.
#
# Args:
#   *: list of arduino library name without spaces (e.g. Wire or Adafruit_LSM6DS). Must be installed via `arduino-cli`.
#####
function(target_use_arduino_libraries)
    get_property(ARDUINO_LIBRARY_LIST_LOCAL GLOBAL PROPERTY ARDUINO_LIBRARY_LIST)
    list(APPEND ARDUINO_LIBRARY_LIST_LOCAL ${ARGN})
    list(REMOVE_DUPLICATES ARDUINO_LIBRARY_LIST_LOCAL)
    set_property(GLOBAL PROPERTY ARDUINO_LIBRARY_LIST ${ARDUINO_LIBRARY_LIST_LOCAL})
endfunction(target_use_arduino_libraries)

####
# Function `setup_arduino_linking`:
#
# Takes the final list of arduino libraries, builds these libraries, exports these libraries as targets, and provides
# the necessary header and other information for these libraries for the final link of an arduino setup.
####
function(setup_arduino_libraries)
    get_property(ARDUINO_LIBRARY_LIST_LOCAL GLOBAL PROPERTY ARDUINO_LIBRARY_LIST)
    prevent_prescan(${ARDUINO_LIBRARY_LIST_LOCAL} fprime-arduino-patcher core fprime_arduino_loose_object_library)
    run_arduino_wrapper(
        -b "${ARDUINO_FQBN}"
        --properties ${ARDUINO_BUILD_PROPERTIES} -j "${ARDUINO_WRAPPER_JSON_OUTPUT}"
        --generate-code
        --libraries ${ARDUINO_LIBRARY_LIST_LOCAL}
    )
    file(READ "${ARDUINO_WRAPPER_JSON_OUTPUT}" WRAPPER_OUTPUT)
    read_json(INCLUDES "${WRAPPER_OUTPUT}" includes CXX)
    read_json(LIBRARIES "${WRAPPER_OUTPUT}" libraries)
    read_json(OBJECTS "${WRAPPER_OUTPUT}" objects)

    # Setup an extra arduino libraries
    add_library(fprime_arduino_patcher ${EXTRA_LIBRARY_SOURCE})
    add_library(fprime_arduino_loose_object_library OBJECT IMPORTED GLOBAL)
    set_target_properties(fprime_arduino_loose_object_library PROPERTIES IMPORTED_OBJECTS "${OBJECTS}")
    target_include_directories(fprime_arduino_loose_object_library INTERFACE ${INCLUDES})

    # Import all of the libraries including core
    list(APPEND ARDUINO_LIBRARY_LIST_LOCAL core)
    message(STATUS "${LIBRARIES}")
    foreach(NEEDED_LIBRARY IN LISTS ARDUINO_LIBRARY_LIST_LOCAL)
        set(FOUND OFF)
        foreach(BUILT_LIBRARY IN LISTS LIBRARIES)
            ends_with(IS_NEEDLE "${BUILT_LIBRARY}" "${NEEDED_LIBRARY}.a")
            # If a matching library was built, use it
            if (IS_NEEDLE)
                message(STATUS "Adding Arduino Library: ${NEEDED_LIBRARY}")
                add_library(${NEEDED_LIBRARY} STATIC IMPORTED GLOBAL)
                set_target_properties(${NEEDED_LIBRARY} PROPERTIES IMPORTED_LOCATION "${BUILT_LIBRARY}")
                set(FOUND ON)
                break()
            endif()
        endforeach()
        # If the matching library was not found, create an interface to the object library
        if (NOT FOUND)
            message(STATUS "Adding Arduino Interface: ${NEEDED_LIBRARY}")
            add_library(${NEEDED_LIBRARY} INTERFACE)
        endif()
        # Add dependencies and header information
        add_dependencies(${NEEDED_LIBRARY} fprime_arduino_loose_object_library)
        target_link_libraries(${NEEDED_LIBRARY} INTERFACE fprime_arduino_loose_object_library)
    endforeach()
    set(WRAPPER_OUTPUT "${WRAPPER_OUTPUT}" PARENT_SCOPE)
endfunction(setup_arduino_libraries)

####
# Function `finalize_arduino_executable`:
#
# Attach the arduino libraries to a given target (e.g. executable/deployment). Additionally sets up finalization steps
# for the executable (e.g. building hex files, calculating size, etc).
#
# Args:
#    TARGET_NAME: target name to setup and build a hex file
####
function(finalize_arduino_executable TARGET_NAME)
    setup_arduino_libraries()
    prevent_prescan()

    # Add link dependency on
    target_link_libraries(
        "${TARGET_NAME}"
        PUBLIC $<TARGET_OBJECTS:fprime_arduino_loose_object_library> fprime_arduino_patcher
    )
    read_json(POST_COMMANDS "${WRAPPER_OUTPUT}" post)
    set(COMMAND_SET_ARGUMENTS)
    foreach(COMMAND IN LISTS POST_COMMANDS)
        string(REPLACE "<TARGET_PATH>" "$<TARGET_FILE:${TARGET_NAME}>" COMMAND_WITH_INPUT "${COMMAND}")
        string(REPLACE "<TARGET_NAME>" "$<TARGET_FILE_NAME:${TARGET_NAME}>" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        string(REPLACE "<TARGET_DIRECTORY>" "$<TARGET_FILE_DIR:${TARGET_NAME}>" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        string(REPLACE " " ";" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        list(APPEND COMMAND_SET_ARGUMENTS COMMAND ${COMMAND_WITH_INPUT})
    endforeach()
    message(STATUS ">>>>>${COMMAND_SET_ARGUMENTS}")
    list(APPEND COMMAND_SET_ARGUMENTS COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "$<TARGET_FILE:${TARGET_NAME}>*" "${CMAKE_INSTALL_PREFIX}/${TOOLCHAIN_NAME}/bin")
    add_custom_command(
        TARGET "${TARGET_NAME}" POST_BUILD ${COMMAND_SET_ARGUMENTS}
    )
endfunction(finalize_arduino_executable)

# Setup the arduino build settings, and output when debugging
set_arduino_build_settings()
if (CMAKE_DEBUG_OUTPUT)
    message(STATUS "[arduino-support] Detected ASM  settings: ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C    settings: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected C++  settings: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS_INIT}")
    message(STATUS "[arduino-support] Detected AR   settings: ${CMAKE_AR} ${ARDUINO_AR_FLAGS}")
    message(STATUS "[arduino-support] Detected link settings: ${CMAKE_LINKER} ${CMAKE_EXE_LINKER_FLAGS_INIT}")
endif()