// ======================================================================
// \title  ATmegaGpioDriverImpl.cpp
// \author Sterling Peet
// \brief  cpp file for ATmegaGpioDriver component implementation class
// ======================================================================


#include <ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaGpioDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaGpioDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaGpioDriverComponentBase(compName),
#else
    ATmegaGpioDriverComponentImpl(void) :
#endif
     m_ddir(0)   // 0 is a null pointer
    ,m_port(0)   // 0 is a null pointer
    ,m_pin(INVALID_PIN_NUMBER)  // number of left shifts for pin, 8 and up are nonsense
    ,m_direction(GPIO_IN)
  {

  }

  void ATmegaGpioDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaGpioDriverComponentBase::init(instance);
  }

  ATmegaGpioDriverComponentImpl ::
    ~ATmegaGpioDriverComponentImpl(void){}

} // end namespace Drv
