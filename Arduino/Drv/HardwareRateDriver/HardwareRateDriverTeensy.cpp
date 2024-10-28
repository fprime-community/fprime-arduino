#include <FpConfig.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <FprimeArduino.hpp>
#include <IntervalTimer.h>
#include <Fw/Logger/Logger.hpp>

namespace Arduino {
IntervalTimer s_itimer;

void HardwareRateDriver::start() {
    U32 microseconds = m_interval * 1000;
    (void) s_itimer.begin(HardwareRateDriver::s_timerISR, microseconds);
    Fw::Logger::log("Starting base rate group clock with period of %" PRIu32 " microseconds\n", microseconds);
}

void HardwareRateDriver::stop() {
    s_itimer.end();
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
