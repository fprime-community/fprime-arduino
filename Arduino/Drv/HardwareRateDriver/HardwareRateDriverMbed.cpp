#include <FpConfig.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Arduino.h>
#include <mbed.h>

namespace Arduino {

mbed::Ticker s_ticker;

void HardwareRateDriver::start() {
    // Microsecond ticker
    //s_ticker.attach_us(&HardwareRateDriver::s_timerISR, m_interval * 1000);
}

void HardwareRateDriver::stop() {
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
