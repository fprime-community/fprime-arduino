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
        run_arduino_wrapper("-b" "${ARDUINO_FQBN}" "--properties" ${ARDUINO_BUILD_PROPERTIES} "--board-options" ${ARDUINO_BOARD_OPTIONS} -j "${FOUND_LOCATION}")
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
    string(REPLACE "<TARGET_PATH>.map" "link.map" CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT}")

    # Convert lists to the INIT " " separated format
    foreach(LIST_VARIABLE IN ITEMS
            CMAKE_ASM_FLAGS_INIT CMAKE_C_FLAGS_INIT CMAKE_CXX_FLAGS_INIT
            ARDUINO_AR_FLAGS CMAKE_EXE_LINKER_FLAGS_INIT)
        string(REPLACE ";" " " "${LIST_VARIABLE}" "${${LIST_VARIABLE}}")
    endforeach()

    # Add additional linker flags if provided
    if (ARDUINO_LINKER_FLAGS)
        string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${ARDUINO_LINKER_FLAGS}")
    endif()

    read_json(INCLUDES "${WRAPPER_OUTPUT}" includes CXX)
    include_directories(${INCLUDES})
    if (NOT TARGET fprime_arduino_libraries)
        add_library(fprime_arduino_libraries INTERFACE)
    endif()
    link_libraries(fprime_arduino_libraries)
    link_libraries(fprime_arduino_patcher)
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
    list(APPEND MOD_DEPS fprime_arduino_libraries)
    set(MOD_DEPS "${MOD_DEPS}" PARENT_SCOPE)
endfunction(target_use_arduino_libraries)

####
# Function `setup_arduino_linking`:
#
# Takes the final list of arduino libraries, builds these libraries, exports these libraries as targets, and provides
# the necessary header and other information for these libraries for the final link of an arduino setup.
####
function(setup_arduino_libraries)
    get_property(ARDUINO_LIBRARY_LIST_LOCAL GLOBAL PROPERTY ARDUINO_LIBRARY_LIST)
    skip_on_sub_build(${ARDUINO_LIBRARY_LIST_LOCAL} fprime_arduino_patcher fprime_arduino_loose_object_library)
    run_arduino_wrapper(
        -b "${ARDUINO_FQBN}"
        --properties ${ARDUINO_BUILD_PROPERTIES}
        --board-options ${ARDUINO_BOARD_OPTIONS}
        -j "${ARDUINO_WRAPPER_JSON_OUTPUT}"
        --generate-code
        --libraries ${ARDUINO_LIBRARY_LIST_LOCAL}
    )
    file(READ "${ARDUINO_WRAPPER_JSON_OUTPUT}" WRAPPER_OUTPUT)
    read_json(INCLUDES "${WRAPPER_OUTPUT}" includes CXX)
    read_json(LIBRARIES "${WRAPPER_OUTPUT}" libraries)
    read_json(OBJECTS "${WRAPPER_OUTPUT}" objects)

    # Setup arduino missing C/C++ function patch library
    if (NOT TARGET fprime_arduino_patcher)
        add_library(fprime_arduino_patcher ${EXTRA_LIBRARY_SOURCE})
        add_dependencies(fprime_arduino_patcher config)
        get_target_property(TARGET_LIBRARIES fprime_arduino_patcher LINK_LIBRARIES)
        LIST(REMOVE_ITEM TARGET_LIBRARIES fprime_arduino_libraries)
        LIST(REMOVE_ITEM TARGET_LIBRARIES fprime_arduino_patcher)
        set_property(TARGET fprime_arduino_patcher PROPERTY LINK_LIBRARIES ${TARGET_LIBRARIES})
    endif()

    # Setup library to capture loose object files from arduino-cli compile
    if (NOT TARGET fprime_arduino_loose_object_library)
        add_library(fprime_arduino_loose_object_library OBJECT IMPORTED GLOBAL)
        set_target_properties(fprime_arduino_loose_object_library PROPERTIES IMPORTED_OBJECTS "${OBJECTS}")
        target_include_directories(fprime_arduino_libraries INTERFACE ${INCLUDES})
        target_link_libraries(fprime_arduino_libraries INTERFACE fprime_arduino_loose_object_library)
    endif()

    # Import all of the libraries including core
    foreach(BUILT_LIBRARY IN LISTS LIBRARIES)
        string(SUBSTRING "${BUILT_LIBRARY}" 0 1 MAYBE_DASH)
        if (MAYBE_DASH STREQUAL "-")
            message(STATUS "Adding Arduino Library Flag: ${BUILT_LIBRARY}")
            target_link_libraries(fprime_arduino_libraries INTERFACE ${BUILT_LIBRARY})
        else()
            get_filename_component(LIBRARY_BASE "${BUILT_LIBRARY}" NAME_WE)

            # Add new imported library
            if (NOT TARGET ${LIBRARY_BASE})
                message(STATUS "Adding Arduino Library: ${LIBRARY_BASE}")
                add_library(${LIBRARY_BASE} STATIC IMPORTED GLOBAL)
                set_target_properties(${LIBRARY_BASE} PROPERTIES IMPORTED_LOCATION "${BUILT_LIBRARY}")
                add_dependencies(${LIBRARY_BASE} fprime_arduino_loose_object_library)
                target_link_libraries(${LIBRARY_BASE} INTERFACE fprime_arduino_loose_object_library)

                # Setup detected dependencies to the interface library
                add_dependencies(fprime_arduino_libraries ${LIBRARY_BASE})
                target_link_libraries(fprime_arduino_libraries INTERFACE ${LIBRARY_BASE})
            endif()
        endif()
    endforeach()
    set(WRAPPER_OUTPUT "${WRAPPER_OUTPUT}" PARENT_SCOPE)
endfunction(setup_arduino_libraries)

####
# Function `finalize_arduino_executable`:
#
# Attach the arduino libraries to a given target (e.g. executable/deployment). Additionally sets up finalization steps
# for the executable (e.g. building hex files, calculating size, etc).
####
function(finalize_arduino_executable)
    setup_arduino_libraries()
    include(API)
    skip_on_sub_build()
    # Add link dependency on
    target_link_libraries(
        "${FPRIME_CURRENT_MODULE}"
        PUBLIC fprime_arduino_libraries $<TARGET_OBJECTS:fprime_arduino_loose_object_library>
    )
    read_json(POST_COMMANDS "${WRAPPER_OUTPUT}" post)
    set(COMMAND_SET_ARGUMENTS)
    foreach(COMMAND IN LISTS POST_COMMANDS)
        string(REPLACE "<TARGET_PATH>" "$<TARGET_FILE:${FPRIME_CURRENT_MODULE}>" COMMAND_WITH_INPUT "${COMMAND}")
        string(REPLACE "<TARGET_NAME>" "$<TARGET_FILE_NAME:${FPRIME_CURRENT_MODULE}>" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        string(REPLACE "<TARGET_DIRECTORY>" "$<TARGET_FILE_DIR:${FPRIME_CURRENT_MODULE}>" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        string(REPLACE " " ";" COMMAND_WITH_INPUT "${COMMAND_WITH_INPUT}")
        list(APPEND COMMAND_SET_ARGUMENTS COMMAND ${COMMAND_WITH_INPUT} || true)
    endforeach()
    list(APPEND COMMAND_SET_ARGUMENTS COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "$<TARGET_FILE:${FPRIME_CURRENT_MODULE}>*" "${CMAKE_INSTALL_PREFIX}/${TOOLCHAIN_NAME}/${FPRIME_CURRENT_MODULE}/bin")
    add_custom_command(
        TARGET "${FPRIME_CURRENT_MODULE}" POST_BUILD ${COMMAND_SET_ARGUMENTS}
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