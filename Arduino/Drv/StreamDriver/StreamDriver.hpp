// ======================================================================
// \title  StreamDriverImpl.hpp
// \author lestarch
// \brief  hpp file for StreamDriver component implementation class
// ======================================================================

#ifndef StreamDriver_HPP
#define StreamDriver_HPP

#include <Arduino/config/FprimeArduino.hpp>
#include "Arduino/Drv/StreamDriver/StreamDriverComponentAc.hpp"
#include "Os/Task.hpp"

namespace Arduino {
// Allow for setting serial ports on linux from the inputs
#ifndef ARDUINO
extern char** SERIAL_PORT;
#endif

class StreamDriver : public StreamDriverComponentBase {
  public:
    const static FwSizeType SERIAL_BUFFER_SIZE = 64;  // Maximum Arduino buffer size
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object StreamDriver
    //!
    StreamDriver(const char* compName /*!< The component name*/
    );

    //! Destroy object StreamDriver
    //!
    ~StreamDriver(void);

    //! Configure this port
    //!
    void configure(Stream* streamDriver);

  private:
    //! Read the actual data
    void read_data(Fw::Buffer& fwBuffer);
    //! Write the actual data
    void write_data(Fw::Buffer& serBuffer);
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler for handling buffer returns
    //!
    void recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer);

    //! Handler implementation for send
    //!
    void send_handler(const FwIndexType portNum, /*!< The port number*/
                      Fw::Buffer& fwBuffer) override;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const FwIndexType portNum, /*!< The port number*/
                         U32 context                /*!< The call order*/
    );

    //! Port number to open
    FwIndexType m_port_number;
    //! Stores the open stream port, POINTER_CAST so Linux and Ardunio may use different types
    void* m_port_pointer;
};

}  // end namespace Arduino

#endif
