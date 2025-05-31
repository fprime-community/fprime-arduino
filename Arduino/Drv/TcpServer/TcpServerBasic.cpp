// ======================================================================
// \title  TcpServer.cpp
// \author ethan
// \brief  cpp file for TcpServer component implementation class
// ======================================================================

#include "Arduino/Drv/TcpServer/TcpServer.hpp"

namespace Arduino {

SocketIpStatus TcpServer::configure(const char* ssid, const char* password, U16 port, FwSizeType buffer_size) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

SocketIpStatus TcpServer::reconnect() {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

SocketIpStatus TcpServer::send(const U8* data, U32 size) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

void TcpServer::readLoop() {
    return;  // Not implemented
}

}  // namespace Arduino
