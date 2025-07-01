// ======================================================================
// \title  PwmDriver.cpp
// \author ethan
// \brief  cpp file for PwmDriver component implementation class
// ======================================================================

#include <Arduino/Drv/PwmDriver/PwmDriver.hpp>
#include <config/FprimeArduino.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

PwmDriver ::PwmDriver(const char* const compName) : PwmDriverComponentBase(compName), m_pin(-1) {}

PwmDriver ::~PwmDriver() {}

void PwmDriver::open(FwIndexType gpio) {
    this->m_pin = gpio;
    pinMode(this->m_pin, Arduino::DEF_OUTPUT);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Fw::Success PwmDriver ::setDutyCycle_handler(const FwIndexType portNum, U8 dutyCycle) {
    if (dutyCycle > 100) {
        dutyCycle = 100;
    }

    analogWrite(this->m_pin, 255 * (static_cast<F32>(dutyCycle) / 100));
    return Fw::Success::SUCCESS;
}

}  // end namespace Arduino
