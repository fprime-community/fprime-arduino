// ======================================================================
// \title  TcpClient.cpp
// \author ethanchee
// \brief  cpp file for TcpClient component implementation class
// ======================================================================

#include <Arduino/Drv/TcpClient/TcpClient.hpp>

namespace Arduino {

SocketIpStatus TcpClient::configure(const char* ssid,
                                    const char* password,
                                    const char* hostname,
                                    const U16 port,
                                    FwSizeType buffer_size) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

SocketIpStatus TcpClient::reconnect() {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

SocketIpStatus TcpClient::send(const U8* data, U32 size) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

void TcpClient::readLoop() {
    return;  // Not implemented
}

}  // end namespace Arduino
