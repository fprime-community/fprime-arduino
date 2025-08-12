// ======================================================================
// \title  LifeLed.hpp
// \author mstarch
// \brief  hpp file for LifeLed component implementation class
// ======================================================================

#ifndef Arduino_LifeLed_HPP
#define Arduino_LifeLed_HPP

#include "Arduino/Svc/LifeLed/LifeLedComponentAc.hpp"
#include <Arduino/config/FprimeArduino.hpp>
#include "Fw/Types/OnEnumAc.hpp"

namespace Arduino {

class LifeLed : public LifeLedComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct LifeLed object
    LifeLed(const char* const compName  //!< The component name
    );

    //! Destroy LifeLed object
    ~LifeLed();

    //! Set the arduino pin to own
    void configure(PlatformIntType pin = Arduino::DEF_LED_BUILTIN);

    //! Set the pin state
    void set(const Fw::On::T& on_off);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Rate group port
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;
    U16 m_blink_count;
    PlatformIntType m_pin;
    bool m_configured;
};

}  // namespace Arduino

#endif
