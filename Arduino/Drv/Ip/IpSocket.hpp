// ======================================================================
// \title  IpSocket.hpp
// \author ethan
// \brief  hpp file for IpSocket component implementation class
// ======================================================================
#ifndef Arduino_Drv_IP_IPHELPER_HPP_
#define Arduino_Drv_IP_IPHELPER_HPP_

namespace Arduino {

struct SocketDescriptor final {
    void* fd = nullptr;        //!< Used for all sockets to track the communication file descriptor
    void* serverFd = nullptr;  //!< Used for server sockets to track the server file descriptor
};

/**
 * \brief Status enumeration for socket return values
 */
enum SocketIpStatus {
    SOCK_SUCCESS = 0,                        //!< Socket operation successful
    SOCK_FAILED_TO_GET_SOCKET = -1,          //!< Socket open failed
    SOCK_FAILED_TO_GET_HOST_IP = -2,         //!< Host IP lookup failed
    SOCK_INVALID_IP_ADDRESS = -3,            //!< Bad IP address supplied
    SOCK_FAILED_TO_CONNECT = -4,             //!< Failed to connect socket
    SOCK_FAILED_TO_SET_SOCKET_OPTIONS = -5,  //!< Failed to configure socket
    SOCK_INTERRUPTED_TRY_AGAIN = -6,         //!< Interrupted status for retries
    SOCK_READ_ERROR = -7,                    //!< Failed to read socket
    SOCK_DISCONNECTED = -8,                  //!< Failed to read socket with disconnect
    SOCK_FAILED_TO_BIND = -9,                //!< Failed to bind to socket
    SOCK_FAILED_TO_LISTEN = -10,             //!< Failed to listen on socket
    SOCK_FAILED_TO_ACCEPT = -11,             //!< Failed to accept connection
    SOCK_SEND_ERROR = -13,                   //!< Failed to send after configured retries
    SOCK_NOT_STARTED = -14,                  //!< Socket has not been started
    SOCK_FAILED_TO_READ_BACK_PORT = -15,     //!< Failed to read back port from connection
    SOCK_NO_DATA_AVAILABLE = -16,            //!< No data available or read operation would block
    SOCK_ANOTHER_THREAD_OPENING = -17,       //!< Another thread is opening
    SOCK_AUTO_CONNECT_DISABLED = -18,        //!< Automatic connections are disabled
    SOCK_INVALID_CALL = -19                  //!< Operation is invalid
};

}  // namespace Arduino

#endif /* Arduino_Drv_SOCKETIPDRIVER_SOCKETHELPER_HPP_ */
