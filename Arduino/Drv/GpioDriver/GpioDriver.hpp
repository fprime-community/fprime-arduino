// ======================================================================
// \title  GpioDriver.hpp
// \author lestarch
// \brief  hpp file for GpioDriver component implementation class
// ======================================================================

#ifndef ARDUINO_DRV_GpioDriver_HPP
#define ARDUINO_DRV_GpioDriver_HPP

#include "Arduino/Drv/GpioDriver/GpioDriverComponentAc.hpp"

namespace Arduino {

class GpioDriver : public GpioDriverComponentBase {
  public:
    //! configure GPIO
    enum GpioDirection {
        IN,   //!< input
        OUT,  //!< output
    };
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object GpioDriver
    //!
    GpioDriver(const char* const compName /*!< The component name*/
    );

    //! Initialize object GpioDriver
    //!
    void init(const FwEnumStoreType instance = 0 /*!< The instance number*/
    );

    //! Destroy object GpioDriver
    //!
    ~GpioDriver();

    //! open GPIO
    bool open(FwIndexType gpio, GpioDirection direction);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for gpioRead
    Drv::GpioStatus gpioRead_handler(FwIndexType portNum,  //!< The port number
                                     Fw::Logic& state) override;

    //! Handler implementation for gpioWrite
    Drv::GpioStatus gpioWrite_handler(FwIndexType portNum,  //!< The port number
                                      const Fw::Logic& state) override;

    //! device direction
    FwIndexType m_pin;
};

}  // namespace Arduino

#endif
