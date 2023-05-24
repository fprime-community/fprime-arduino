// ======================================================================
// \title  ATmegaGpioDriverComponentImplLinux.cpp
// \author Sterling Peet
// \brief  cpp file for ATmegaGpioDriver component implementation class
// ======================================================================


#include <ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>

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

      state = 0;
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

#if FW_OBJECT_NAMES == 1
      printf("Comp %s: ", this->m_objName);
#endif
      printf("Setting GPIO state to ");
      if(state)
      {
        printf("1\n");
      }
      else
      {
        printf("0\n");
      }
  }

  bool ATmegaGpioDriverComponentImpl ::
    setup(volatile uint8_t &data_dir_register, volatile uint8_t &port_register, int pin_number, GpioDirection direction) {

      // TODO check for invalid DDir register
      // TODO check for invalid PORT register
      // TODO check for invalid DDir/PORT combo
      // TODO check for invalid pin number
      // volatile uint8_t *ddir = &data_dir_register;

      m_ddir = &data_dir_register;
      m_port = &port_register;
      m_pin = pin_number;
      return true;
  }

} // end namespace Drv
