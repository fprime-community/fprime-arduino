####
# ArduinoOs:
#
# The Arudino Os support layer uses the F prime baremetal virtualization technology and a custom
# rebuild of the Arduino framework in order to ensure that all the code can compile into a sensible
# binary. This file sets up the Os layer to support all of that.
####
restrict_platforms(ArduinoFw)
add_custom_target("${FPRIME_CURRENT_MODULE}")

# -----------------------------------------
## Shared Section
# -----------------------------------------

set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/error.cpp"
)
set(HEADER_FILES
    "${CMAKE_CURRENT_LIST_DIR}/error.hpp"
)
set(MOD_DEPS config)
register_fprime_module(Os_Arduino_Shared)

# Set up Arduino implementations
add_fprime_supplied_os_module(Console Arduino)
add_fprime_supplied_os_module(Task Arduino)
add_fprime_supplied_os_module("Mutex;ConditionVariable" Arduino)
