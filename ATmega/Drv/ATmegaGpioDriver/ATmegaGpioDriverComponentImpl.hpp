// ======================================================================
// \title  ATmegaGpioDriverComponentImpl.hpp
// \author Sterling Peet
// \brief  hpp file for ATmegaGpioDriver component implementation class
//
// ======================================================================

#ifndef ATmegaGpioDriver_HPP
#define ATmegaGpioDriver_HPP

#include "ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentAc.hpp"
#include <Os/Task.hpp>

namespace Drv {
  constexpr uint8_t INVALID_PIN_NUMBER = 255;

  class ATmegaGpioDriverComponentImpl :
    public ATmegaGpioDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaGpioDriver
      //!
      ATmegaGpioDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaGpioDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ATmegaGpioDriver
      //!
      ~ATmegaGpioDriverComponentImpl(void);

      //! configure GPIO
      enum GpioDirection {
          GPIO_IN = 0, //!< input
          GPIO_OUT = 1, //!< output
          GPIO_INT //!< interrupt
      };

      //! setup GPIO
      bool setup(volatile uint8_t &data_dir_register, volatile uint8_t &port_register, int pin_number, GpioDirection direction);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for gpioRead
      //!
      void gpioRead_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          bool &state
      );

      //! Handler implementation for gpioWrite
      //!
      void gpioWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          bool state
      );

      //! Data Direction Register (needs to match m_port)
      volatile uint8_t *m_ddir;

      //! Port Register (needs to match m_ddir)
      volatile uint8_t *m_port;

      //! Pin Number within Port
      uint8_t m_pin;

      //! device direction
      GpioDirection m_direction;
    };

} // end namespace Drv

#endif
