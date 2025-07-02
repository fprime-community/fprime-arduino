// ======================================================================
// \title  AnalogDriver.hpp
// \author luke
// \brief  hpp file for AnalogDriver component implementation class
// ======================================================================

#ifndef AnalogDriver_HPP
#define AnalogDriver_HPP

#include "Arduino/Drv/AnalogDriver/AnalogDriverComponentAc.hpp"

namespace Arduino {

class AnalogDriver : public AnalogDriverComponentBase {
  public:
    //! configure GPIO
    enum GpioDirection {
        IN,   //!< input
        OUT,  //!< output
    };
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object AnalogDriver
    //!
    AnalogDriver(const char* const compName /*!< The component name*/
    );

    //! Destroy object AnalogDriver
    //!
    ~AnalogDriver();

    bool open(FwIndexType pin, GpioDirection direction);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for readAnalog
    //!
    Fw::Success readAnalog_handler(const FwIndexType portNum, /*!< The port number*/
                                   U16& val);

    //! Handler implementation for setAnalog
    //!
    Fw::Success setAnalog_handler(const FwIndexType portNum, /*!< The port number*/
                                  U8 val);

    PlatformIntType m_pin;
};

}  // end namespace Arduino

#endif
