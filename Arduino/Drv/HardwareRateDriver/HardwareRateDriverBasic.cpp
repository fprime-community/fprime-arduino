#include <config/FpConfig.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Fw/Logger/Logger.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {
static U32 last_us;
static U32 interval_us;

void HardwareRateDriver::start() {
    interval_us = m_interval * 1000;
    last_us = micros();
}

void HardwareRateDriver::cycle() {
    if((micros() - last_us) >= interval_us)
    {
        this->s_timerISR();
        last_us += interval_us;
    }
}

void HardwareRateDriver::stop() {
    
}

void HardwareRateDriver::s_timerISR() {    
    s_timer(s_driver);
}

};
