// ======================================================================
// \title  AnalogDriver.cpp
// \author luke
// \brief  cpp file for AnalogDriver component implementation class
// ======================================================================

#include <Arduino/Drv/AnalogDriver/AnalogDriver.hpp>
#include <config/FprimeArduino.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

AnalogDriver ::AnalogDriver(const char* const compName) : AnalogDriverComponentBase(compName), m_pin(-1) {}

AnalogDriver ::~AnalogDriver() {}

bool AnalogDriver ::open(FwIndexType pin, GpioDirection direction) {
    m_pin = pin;
    pinMode(m_pin, (direction == IN) ? Arduino::DEF_INPUT : Arduino::DEF_OUTPUT);
    return true;
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Fw::Success AnalogDriver ::readAnalog_handler(const FwIndexType portNum, U16& val) {
    val = analogRead(m_pin);
    return Fw::Success::SUCCESS;
}

Fw::Success AnalogDriver ::setAnalog_handler(const FwIndexType portNum, U8 val) {
    analogWrite(m_pin, val);
    return Fw::Success::SUCCESS;
}

}  // end namespace Arduino
