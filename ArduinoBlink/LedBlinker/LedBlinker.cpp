// ====================================================================== 
// \title  LedBlinkerImpl.cpp
// \author lestarch
// \brief  cpp file for LedBlinker component implementation class
// ====================================================================== 


#include <examples/ArduinoGpsTracker/LedBlinker/LedBlinker.hpp>
#include "Fw/Types/BasicTypes.hpp"

#define LED_PIN 13
namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  LedBlinkerComponentImpl ::
#if FW_OBJECT_NAMES == 1
    LedBlinkerComponentImpl(
        const char *const compName
    ) :
      LedBlinkerComponentBase(compName), 
#else
    LedBlinkerComponentBase(void),
#endif
    m_pin(LED_PIN),
    m_state(false)
  {}

  LedBlinkerComponentImpl ::
    ~LedBlinkerComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void LedBlinkerComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
	  blink();
	  m_state = !m_state;
  }

} // end namespace Arduino
