#include <FpConfig.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Arduino.h>

namespace Arduino {
IntervalTimer s_itimer;

void HardwareRateDriver::start() {
    (void) s_itimer.begin(HardwareRateDriver::s_timerISR, m_interval * 1000);
}

void HardwareRateDriver::stop() {
    s_itimer.end();
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
