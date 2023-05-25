#include <FpConfig.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Fw/Logger/Logger.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {
U32 last_us;
U32 u_interval;

void HardwareRateDriver::start() {
    last_us = micros();
    u_interval = m_interval * 1000;
}

void HardwareRateDriver::cycle() {
    if((micros() - last_us) >= u_interval)
    {
        this->s_timerISR();
        last_us += u_interval;
    }
}

void HardwareRateDriver::stop() {
    
}

void HardwareRateDriver::s_timerISR() {    
    s_timer(s_driver);
}

};
