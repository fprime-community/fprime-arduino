// ======================================================================
// \title  GpioDriverImpl.cpp
// \author lestarch
// \brief  cpp file for GpioDriver component implementation class
// ======================================================================

#include <Arduino/Drv/GpioDriver/GpioDriver.hpp>
#include <FpConfig.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

GpioDriver ::GpioDriver(const char* const compName)
    : GpioDriverComponentBase(compName), m_pin(-1) {}

void GpioDriver ::init(const NATIVE_INT_TYPE instance) {
    GpioDriverComponentBase::init(instance);
}

GpioDriver ::~GpioDriver() {}

bool GpioDriver ::open(NATIVE_INT_TYPE gpio, GpioDirection direction) {
    m_pin = gpio;
    pinMode(m_pin, (direction == IN) ? Arduino::DEF_INPUT : Arduino::DEF_OUTPUT);
    return true;
}

Drv::GpioStatus GpioDriver ::gpioRead_handler(const NATIVE_INT_TYPE portNum, Fw::Logic& state) {
    U8 value = digitalRead(m_pin);
    state = (value == Arduino::DEF_HIGH) ? Fw::Logic::HIGH : Fw::Logic::LOW;
    return Drv::GpioStatus::OP_OK;
}

Drv::GpioStatus GpioDriver ::gpioWrite_handler(const NATIVE_INT_TYPE portNum, const Fw::Logic& state) {
    digitalWrite(m_pin, (state == Fw::Logic::HIGH) ? Arduino::DEF_HIGH : Arduino::DEF_LOW);
    return Drv::GpioStatus::OP_OK;
}

}  // end namespace Drv
