/*
 * StreamLog.hpp:
 *
 * A file defining the functions used to set and configure the Stream used in the Arduino Log::Os
 * handler function.
 *
 *  Created on: Apr 13, 2019
 *      Author: lestarch
 */
#include <FprimeArduino.hpp>
#ifndef ARDUINO_OS_STREAMLOG_HPP_
#define ARDUINO_OS_STREAMLOG_HPP_

namespace Os {
/**
 * Sets the global A_STREAM arduino stream used to log Arudino messages through a hardware "Steam"
 * like UART or I2C.
 */
void setArduinoStreamLogHandler(Stream* stream);
}
#endif /* OS_ARDUINO_STREAMLOG_HPP_ */
