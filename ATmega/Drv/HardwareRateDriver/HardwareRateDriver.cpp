#include <Fw/Types/BasicTypes.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#ifdef ARDUINO
    #include <Arduino.h> // Needed for call to sei()
#endif

namespace Arduino {

HardwareRateDriver* HardwareRateDriver::s_driver = NULL;

#if FW_OBJECT_NAMES == 1
    HardwareRateDriver::HardwareRateDriver(const char* compName, U32 intervalMs) :
        HardwareRateDriverComponentBase(compName),
#else
    HardwareRateDriver::HardwareRateDriver(U32 intervalMs) :
#endif
        m_interval(intervalMs)
    {
        s_driver = this;
    }

    HardwareRateDriver::~HardwareRateDriver(void) {}

    void HardwareRateDriver::s_timer(void* comp) {
        Svc::TimerVal now;
        now.take();
#ifdef ARDUINO
        sei(); // Enable interrupts so UART RX interrupt handler can receive incoming bytes during the remainder of this ISR
#endif
        HardwareRateDriver* driver = reinterpret_cast<HardwareRateDriver*>(comp);
        //Check if it is time to run the group
        driver->CycleOut_out(0, now);
        driver->m_last = now;
    }
}
