// ======================================================================
// \title  PwmDriver.hpp
// \author ethan
// \brief  hpp file for PwmDriver component implementation class
// ======================================================================

#ifndef PwmDriver_HPP
#define PwmDriver_HPP

#include "Arduino/Drv/PwmDriver/PwmDriverComponentAc.hpp"

namespace Arduino {

  class PwmDriver :
    public PwmDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PwmDriver
      //!
      PwmDriver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object PwmDriver
      //!
      ~PwmDriver();

      //! Setup PWM Pin
      //!
      void open(NATIVE_INT_TYPE gpio);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for setDutyCycle
      //!
      Fw::Success setDutyCycle_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 dutyCycle 
      );

      PlatformIntType m_pin;

    };

} // end namespace Arduino

#endif
