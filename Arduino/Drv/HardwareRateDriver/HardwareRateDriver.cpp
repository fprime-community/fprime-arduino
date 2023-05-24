#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <FpConfig.hpp>
#ifdef ARDUINO
#include <FprimeArduino.hpp>  // Needed for call to sei()
#endif

namespace Arduino {

HardwareRateDriver* HardwareRateDriver::s_driver = NULL;

HardwareRateDriver::HardwareRateDriver(const char* compName)
    : HardwareRateDriverComponentBase(compName), m_interval(std::numeric_limits<U32>::max()) {
    s_driver = this;
}

HardwareRateDriver::~HardwareRateDriver(void) {}


void HardwareRateDriver::configure(U32 intervalMs) {
    m_interval = intervalMs;
}

void HardwareRateDriver::s_timer(void* comp) {
    Svc::TimerVal now;
    now.take();
    interrupts();  // Enable interrupts so UART RX interrupt handler can receive incoming bytes during remainder of this ISR
    HardwareRateDriver* driver = reinterpret_cast<HardwareRateDriver*>(comp);
    // Check if it is time to run the group
    if(driver->isConnected_CycleOut_OutputPort(0))
    {
        driver->CycleOut_out(0, now);
    }
    driver->m_last = now;
}
}  // namespace Arduino
