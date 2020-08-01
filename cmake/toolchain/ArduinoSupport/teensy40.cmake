

# MCU unit and loader script used by the Teensy 4.0
set(TEENSY_MCU "IMXRT1062")
string(TOLOWER "${TEENSY_MCU}" TEENSY_MCU_LOWER)
set(MCU_LD "imxrt1062.ld")

set(TEENSY_FREQ 600000000)
set(TEENSY_ARDUINO_NUM 10808)
set(TEENSY_TEENSYDUINO_NUM 145)
set(TEENSY_CPU_ARCH  cortex-m7)

set(TEENSY_CPU_FLAGS "-mfloat-abi=hard -mfpu=fpv5-d16")
set(TEENSY_LIBS "arm_cortexM7lfsp_math")
set(TEENSY_SHIM_SOURCES "${CMAKE_CURRENT_LIST_DIR}/setup2main.c")
