// ======================================================================
// \title  LifeLed.cpp
// \author mstarch
// \brief  cpp file for LifeLed component implementation class
// ======================================================================

#include "Arduino/Svc/LifeLed/LifeLed.hpp"
#include "FpConfig.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LifeLed ::LifeLed(const char* const compName) : LifeLedComponentBase(compName), m_blink_count(0), m_pin(Arduino::DEF_LED_BUILTIN), m_configured(false) {}

LifeLed ::~LifeLed() {}

void LifeLed::configure(pin_size_t pin) {
    this->m_pin = pin;
    pinMode(this->m_pin, Arduino::DEF_OUTPUT);
    digitalWrite(this->m_pin, Arduino::DEF_LOW);
    this->m_configured = true;
}

void LifeLed::set(const Fw::On::T &on_off) {
    if (this->m_configured) {
        digitalWrite(this->m_pin, (on_off == Fw::On::ON) ? Arduino::DEF_HIGH : Arduino::DEF_LOW);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void LifeLed ::run_handler(NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    Fw::ParamValid is_valid;
    U16 count_period = this->paramGet_LED_PERIOD(is_valid);
    // Only operate when the parameter is valid
    if (is_valid != Fw::ParamValid::INVALID) {
        this->m_blink_count = (this->m_blink_count + 1) % count_period;
        this->set((this->m_blink_count < (count_period/2)) ? Fw::On::ON : Fw::On::OFF);
    }
}


}  // namespace Arduino
