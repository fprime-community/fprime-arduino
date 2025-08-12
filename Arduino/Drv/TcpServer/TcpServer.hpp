// ======================================================================
// \title  TcpServer.hpp
// \author ethan
// \brief  hpp file for TcpServer component implementation class
// ======================================================================

#ifndef Arduino_TcpServer_HPP
#define Arduino_TcpServer_HPP

#include <Arduino/Drv/Ip/IpSocket.hpp>
#include "Arduino/Drv/TcpServer/TcpServerComponentAc.hpp"

namespace Arduino {

class TcpServer final : public TcpServerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct TcpServer object
    TcpServer(const char* const compName  //!< The component name
    );

    //! Destroy TcpServer object
    ~TcpServer();

    // For WiFi if available
    SocketIpStatus configure(const char* ssid, const char* password, U16 port = 50000, FwSizeType buffer_size = 1024);

    SocketIpStatus send(const U8* data, U32 size);

    SocketIpStatus reconnect();

  protected:
    /**
     * \brief receive off the TCP socket
     */
    virtual void readLoop();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for recvReturnIn
    //!
    //! Port receiving back ownership of data sent out on $recv port
    void recvReturnIn_handler(FwIndexType portNum,  //!< The port number
                              Fw::Buffer& fwBuffer  //!< The buffer
                              ) override;

    //! Handler implementation for send
    //!
    //! Invoke this port to send data out the driver
    Drv::ByteStreamStatus send_handler(FwIndexType portNum,  //!< The port number
                                       Fw::Buffer& fwBuffer  //!< The buffer
                                       ) override;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const FwIndexType portNum, /*!< The port number*/
                         U32 context                /*!< The call order*/
    );

  protected:
    Os::Task m_task;
    SocketDescriptor m_socket;  //!< The socket descriptor for the TCP socket

  private:
    FwSizeType m_allocation_size;
};

}  // namespace Arduino

#endif
