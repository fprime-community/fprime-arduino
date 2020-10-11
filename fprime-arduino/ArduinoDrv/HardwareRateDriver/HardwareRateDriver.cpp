#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <fprime-arduino/ArduinoDrv/HardwareRateDriver/HardwareRateDriver.hpp>

namespace Arduino {

HardwareRateDriver* HardwareRateDriver::s_driver = NULL;

    HardwareRateDriver::HardwareRateDriver(const char* compName, U32 intervalMs) :
        HardwareRateDriverComponentBase(compName),
        m_interval(intervalMs)
    {
        s_driver = this;
    }

    HardwareRateDriver::~HardwareRateDriver(void) {}

    void HardwareRateDriver::s_timer(void* comp) {
        Svc::TimerVal now;
        now.take();
        HardwareRateDriver* driver = reinterpret_cast<HardwareRateDriver*>(comp);
        //Check if it is time to run the group
        driver->CycleOut_out(0, now);
        driver->m_last = now;
    }
}
