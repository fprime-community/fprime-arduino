// ======================================================================
// \title  SerialDriverImpl.hpp
// \author lestarch
// \brief  hpp file for SerialDriver component implementation class
// ======================================================================

#ifndef SerialDriver_HPP
#define SerialDriver_HPP

#include "Arduino/Drv/SerialDriver/SerialDriverComponentAc.hpp"
#include "Os/Task.hpp"

namespace Arduino {
// Allow for setting serial ports from the inputs
#ifndef ARDUINO
extern char** SERIAL_PORT;
#endif
class SerialDriver : public SerialDriverComponentBase {
  public:
    const static FwSizeType SERIAL_BUFFER_SIZE = 64;  // Maximum Arduino Serial buffer size
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object SerialDriver
    //!
    SerialDriver(const char* compName /*!< The component name*/
    );

    //! Initialize object SerialDriver
    //!
    void init(const NATIVE_INT_TYPE instance /*!< The instance number*/
              );

    //! Destroy object SerialDriver
    //!
    ~SerialDriver(void);

    //! Configure this port
    //!
    void configure(FwIndexType port_number, const PlatformIntType baud);

  private:
    //! Read the actual data
    void read_data(Fw::Buffer& fwBuffer);
    //! Write the actual data
    void write_data(Fw::Buffer& fwBuffer);
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for send
    //!
    Drv::SendStatus send_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                                 Fw::Buffer& fwBuffer) override;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                         NATIVE_UINT_TYPE context       /*!< The call order*/
    );

    //! Port number to open
    NATIVE_UINT_TYPE m_port_number;
    //! Stores the open serial port, POINTER_CAST so Linux and Ardunio may use different types
    void* m_port_pointer;
};

}  // end namespace Arduino

#endif
