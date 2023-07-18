// ======================================================================
// \title  FprimeArduino.hpp
// \author lestarch
// \brief  Compatibility header for use of Arduino.h in fprime-arduino
// ======================================================================
#ifndef ARDUINOBLINK_FPRIMEARDUINO_HPP
#define ARDUINOBLINK_FPRIMEARDUINO_HPP
#include <Arduino.h>
/**
 * Arduino.h often uses #define constants to setup values like HIGH and LOW. This means that other tokens that contain
 * these #define constants get clobbered by the preprocessor. This remap pulls these tokens into enumeration constants,
 * where possible, to side-step this issue.
 *
 * Examples:
 *   HIGH -> Arduino::DEF_HIGH
 *   LOW -> Arduino::DEF_LOW
 *
 */
namespace Arduino {
enum ARDUINO_DEFINITION_REMAP {
    DEF_HIGH = HIGH,
    DEF_LOW = LOW,
    DEF_INPUT = INPUT,
    DEF_OUTPUT = OUTPUT,
    DEF_INPUT_PULLUP = INPUT_PULLUP,
#ifdef LED_BUILTIN
    DEF_LED_BUILTIN = LED_BUILTIN
#endif //LED_BUILTIN
};
};
#undef INPUT
#undef OUTPUT
#undef INPUT_PULLUP
#undef HIGH
#undef LOW
#undef LED_BUILTIN
#undef SERIAL_BUFFER_SIZE
#undef DEFAULT
#undef DISABLED

#endif  // ARDUINOBLINK_FPRIMEARDUINO_HPP
