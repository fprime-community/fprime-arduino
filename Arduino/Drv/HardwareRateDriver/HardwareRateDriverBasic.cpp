#include <FpConfig.hpp>
#include <Fw/Types/Assert.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Fw/Logger/Logger.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {
U32 last_ms;

void HardwareRateDriver::start() {
    last_ms = micros() / 1000;
}

void HardwareRateDriver::cycle() {
    if((micros() / 1000) - last_ms >= m_interval)
    {
        this->s_timerISR();
        last_ms += m_interval;
    }
}

void HardwareRateDriver::stop() {
    
}

void HardwareRateDriver::s_timerISR() {    
    s_timer(s_driver);
}

};
