#include <Fw/Types/BasicTypes.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Arduino.h>
#include <TimerOne.h>

namespace Arduino {

void HardwareRateDriver::init(
        const NATIVE_INT_TYPE instance
    )
  {
    HardwareRateDriverComponentBase::init(instance);
  }

void HardwareRateDriver::start() {
    Timer1.initialize(m_interval * 1000);
    Timer1.attachInterrupt(HardwareRateDriver::s_timerISR);
    Timer1.start();
}

void HardwareRateDriver::stop() {
    Timer1.stop();
    Timer1.detachInterrupt();
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
