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
                             const U16 port=50000,
                             FwSizeType buffer_size = 1024);

    /**
     * \brief start the socket read task to start producing data
     *
     * Starts up the socket reading task and when reopen was configured, will open up the socket.
     *
     * \note: users must now use `setAutomaticOpen` to configure the socket to automatically open connections. The
     *        default behavior is to automatically open connections.
     *
     * \param name: name of the task
     * \param priority: priority of the started task. See: Os::Task::start. Default: TASK_DEFAULT, not prioritized
     * \param stack: stack size provided to the task. See: Os::Task::start. Default: TASK_DEFAULT, posix threads default
     * \param cpuAffinity: cpu affinity provided to task. See: Os::Task::start. Default: TASK_DEFAULT, don't care
     */
    void start(const Fw::StringBase& name,
               const Os::Task::ParamType priority = Os::Task::TASK_DEFAULT,
               const Os::Task::ParamType stack = Os::Task::TASK_DEFAULT,
               const Os::Task::ParamType cpuAffinity = Os::Task::TASK_DEFAULT);

    SocketIpStatus send(const U8* data, U32 size);

    SocketIpStatus reconnect();

  protected:
    /**
     * \brief receive off the TCP socket
     */
    virtual void readLoop();
    /**
     * \brief a task designed to read from the socket and output incoming data
     *
     * \param pointer: pointer to "this" component
     */
    static void readTask(void* pointer);

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

  protected:
    Os::Task m_task;
    SocketDescriptor m_socket;  //!< The socket descriptor for the TCP socket
    bool m_reopen = false;  //!< Flag to indicate if the socket should be reopened automatically

    const char* m_hostname;  //!< Hostname of the remote TCP server
    U16 m_port;  //!< Port of the remote TCP server

  private:
    FwSizeType m_allocation_size;
};

}  // end namespace Arduino

#endif
