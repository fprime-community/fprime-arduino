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
    SocketIpStatus configure(const char* ssid, const char* password, U16 port, FwSizeType buffer_size=1024);

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
    void send_handler(FwIndexType portNum,  //!< The port number
                      Fw::Buffer& fwBuffer  //!< The buffer
                      ) override;

  protected:
    Os::Task m_task;
    SocketDescriptor m_socket;  //!< The socket descriptor for the TCP socket

  private:
    FwSizeType m_allocation_size;
};

}  // namespace Arduino

#endif
