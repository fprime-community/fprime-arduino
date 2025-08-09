// ======================================================================
// \title  I2cNodeDriver.hpp
// \author mstarch
// \brief  hpp file for I2cNodeDriver component implementation class
// ======================================================================

#ifndef Arduino_I2cNodeDriver_HPP
#define Arduino_I2cNodeDriver_HPP

#include <Wire.h>
#include <Arduino/config/FprimeArduino.hpp>
#include "Arduino/Drv/I2cNodeDriver/I2cNodeDriverComponentAc.hpp"

namespace Arduino {

class I2cNodeDriver : public I2cNodeDriverComponentBase {

#ifdef WIRE_BUFFER_SIZE
    static constexpr FwSizeType INCOMING_BUFFER_SIZE=WIRE_BUFFER_SIZE;
#else
    #ifdef BUFFER_LENGTH 
    static constexpr FwSizeType INCOMING_BUFFER_SIZE=BUFFER_LENGTH;
    #else
    static constexpr FwSizeType INCOMING_BUFFER_SIZE=256;
    #endif
#endif

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct I2cNodeDriver object
    I2cNodeDriver(const char* const compName  //!< The component name
    );

    //! Destroy I2cNodeDriver object
    ~I2cNodeDriver();

    //! Configure the wire to wrap
    void configure(const U16 address, TwoWire& wire);

    //! Member instance of the receive function
    void write(int size);

    //! Member instance of the receive function
    void read();

  private:
    //! Arduino wire device to wrap
    TwoWire* m_wire;

    //! Store for the current address
    U16 m_address;

    //! Incoming data byte buffer
    U8 m_buffer[INCOMING_BUFFER_SIZE];

    //! Callback for client read requests
    static void readCallback();

    //! Callback for client write requests
    static void writeCallback(int size);


    //! Driver associated with this callback
    static I2cNodeDriver* s_component;
};

}  // namespace Arduino

#endif
