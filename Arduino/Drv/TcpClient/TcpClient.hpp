// ======================================================================
// \title  TcpClient.hpp
// \author ethanchee
// \brief  hpp file for TcpClient component implementation class
// ======================================================================

#ifndef TcpClient_HPP
#define TcpClient_HPP

#include <Arduino/Drv/Ip/IpSocket.hpp>
#include "Arduino/Drv/TcpClient/TcpClientComponentAc.hpp"

namespace Arduino {

class TcpClient : public TcpClientComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object TcpClient
    //!
    TcpClient(const char* const compName /*!< The component name*/
    );

    //! Destroy object TcpClient
    //!
    ~TcpClient();

    /**
     * \brief Configures the TcpClient settings but does not open the connection
     *
     * The TcpClientComponent needs to connect to a remote TCP server. This call configures the hostname, port and send
     * timeouts for that socket connection. This call should be performed on system startup before recv or send
     * are called. Note: hostname must be a dot-notation IP address of the form "x.x.x.x". DNS translation is left up
     * to the user.
     *
     * \param hostname: ip address of remote tcp server in the form x.x.x.x
     * \param password: password for the WiFi connection
     * \param port: port of remote tcp server
     * \param buffer_size: size of the buffer to be allocated. Defaults to 1024.
     * \return status of the configure
     */
    SocketIpStatus configure(const char* ssid,
                             const char* password,
                             const char* hostname,
                             const U16 port = 50000,
                             FwSizeType buffer_size = 1024);

    SocketIpStatus send(const U8* data, U32 size);

    SocketIpStatus reconnect();

  protected:
    /**
     * \brief receive off the TCP socket
     */
    virtual void readLoop();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    /**
     * \brief Send data out of the TcpClient
     *
     * Passing data to this port will send data from the TcpClient to whatever TCP server this component has
     * connected to. Should the socket not be opened or was disconnected, then this port call will return SEND_RETRY
     * and critical transmissions should be retried. OTHER_ERROR indicates an unresolvable error. OP_OK is returned
     * when the data has been sent.
     *
     * Note: this component delegates the reopening of the socket to the read thread and thus the caller should
     * retry after the read thread has attempted to reopen the port but does not need to reopen the port manually.
     *
     * \param portNum: fprime port number of the incoming port call
     * \param fwBuffer: buffer containing data to be sent
     */
    void send_handler(const FwIndexType portNum, Fw::Buffer& fwBuffer) override;

    //! Handler implementation for recvReturnIn
    //!
    //! Port receiving back ownership of data sent out on $recv port
    void recvReturnIn_handler(FwIndexType portNum,  //!< The port number
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
    bool m_reopen = false;      //!< Flag to indicate if the socket should be reopened automatically

    const char* m_hostname;  //!< Hostname of the remote TCP server
    U16 m_port;              //!< Port of the remote TCP server

  private:
    FwSizeType m_allocation_size;
};

}  // end namespace Arduino

#endif
