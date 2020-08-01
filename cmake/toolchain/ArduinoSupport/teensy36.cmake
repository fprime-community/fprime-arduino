####
# teensy32.cmake:
#
# Teensy 3.2 support file. This file ensures that the Teensy 3.2 can be useds as a target for the
# CMake system's output. This sets the teensy target to be the most beloved teensy 32. Bless this
# beautiful little chip.
####

# MCU unit and loader script used by the Teensy 3.2
set(TEENSY_MCU "MK66FX1M0")
string(TOLOWER "${TEENSY_MCU}" TEENSY_MCU_LOWER)
set(MCU_LD "${TEENSY_MCU_LOWER}.ld")

# Set the Teensy 3.2 values required for the overlord building program
set(TEENSY_FREQ 180000000)
set(TEENSY_ARDUINO_NUM 10805)
set(TEENSY_TEENSYDUINO_NUM 144)
set(TEENSY_CPU_ARCH  cortex-m4)

# Teensy extras (maybe not needed)
set(TEENSY_CPU_FLAGS "")
set(TEENSY_LIBS "")
set(TEENSY_SHIM_SOURCES "")