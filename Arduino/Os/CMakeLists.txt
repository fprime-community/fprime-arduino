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
register_os_implementation("Console" Arduino)
register_os_implementation("RawTime" Arduino)
if (LIB_SD_INSTALLED)
    target_use_arduino_libraries("SD")
    register_os_implementation("File;FileSystem;Directory" Arduino_SD)
endif()
