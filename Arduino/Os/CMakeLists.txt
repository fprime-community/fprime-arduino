####
# ArduinoOs:
#
# The Arudino Os support layer uses the F prime baremetal virtualization technology and a custom
# rebuild of the Arduino framework in order to ensure that all the code can compile into a sensible
# binary. This file sets up the Os layer to support all of that.
####
restrict_platforms(ArduinoFw)
add_custom_target("${FPRIME_CURRENT_MODULE}")

arduino_lib_installed("SD" LIB_SD_INSTALLED)

# Set up Arduino implementations
add_fprime_supplied_os_module(Console Arduino)
add_fprime_supplied_os_module(RawTime Arduino)
if (LIB_SD_INSTALLED)
    target_use_arduino_libraries("SD")
    add_fprime_supplied_os_module("File;FileSystem;Directory" Arduino)
endif()
