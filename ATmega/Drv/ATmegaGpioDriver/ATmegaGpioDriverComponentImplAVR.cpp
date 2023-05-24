// ======================================================================
// \title  ATmegaGpioDriverComponentImplAVR.cpp
// \author Sterling Peet
// \brief  cpp file for ATmegaGpioDriver component implementation class
// ======================================================================


#include <ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <avr/io.h>

namespace Drv {

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaGpioDriverComponentImpl ::
    gpioRead_handler(
        const NATIVE_INT_TYPE portNum,
        bool &state
    )
  {
      FW_ASSERT(this->m_pin != INVALID_PIN_NUMBER);
      FW_ASSERT(this->m_port != 0);
      FW_ASSERT(this->m_ddir != 0);

      // TODO Check direction too?

      state = *m_port & _BV(m_pin);  // UNTESTED!!!
  }

  void ATmegaGpioDriverComponentImpl ::
    gpioWrite_handler(
        const NATIVE_INT_TYPE portNum,
        bool state
    )
  {
      FW_ASSERT(this->m_pin != INVALID_PIN_NUMBER);
      FW_ASSERT(this->m_port != 0);
      FW_ASSERT(this->m_ddir != 0);

      // TODO Check direction too?

      if(state)
      {
        *m_port |= _BV(m_pin);
      }
      else
      {
        *m_port &= ~_BV(m_pin);
      }

      // TDOD: check pin appears to have correct state
  }

  bool ATmegaGpioDriverComponentImpl ::
    setup(volatile uint8_t &data_dir_register, volatile uint8_t &port_register, int pin_number, GpioDirection direction) {

      // TODO check for invalid DDir register
      // TODO check for invalid PORT register
      // TODO check for invalid DDir/PORT combo
      // TODO check for invalid pin number

      m_ddir = &data_dir_register;
      m_port = &port_register;
      m_pin = pin_number;

      if(direction == GPIO_OUT)
      {
        *m_ddir |= _BV(m_pin);
      }
      else
      {
        *m_ddir &= ~_BV(m_pin);
      }

      return true;
  }

} // end namespace Drv
