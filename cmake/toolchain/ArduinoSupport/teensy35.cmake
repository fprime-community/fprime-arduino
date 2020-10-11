####
# teensy35.cmake:
#
# Teensy 3.5 support file. This file ensures that the Teensy 3.5 can be useds as a target for the
# CMake system's output. This sets the teensy target to be the most beloved teensy 35. Bless this
# beautiful little chip.
####

# MCU unit and loader script used by the Teensy 3.5
set(TEENSY_MCU "MK64FX512")
string(TOLOWER "${TEENSY_MCU}" TEENSY_MCU_LOWER)
set(MCU_LD "${TEENSY_MCU_LOWER}.ld")

# Set the Teensy 3.5 values required for the overlord building program
set(TEENSY_FREQ 120000000)
set(TEENSY_ARDUINO_NUM 10813)
set(TEENSY_TEENSYDUINO_NUM 153)
set(TEENSY_CPU_ARCH  cortex-m4)

# Teensy extras (maybe not needed)
set(TEENSY_CPU_FLAGS "")
set(TEENSY_LIBS "")
set(TEENSY_SHIM_SOURCES "")
