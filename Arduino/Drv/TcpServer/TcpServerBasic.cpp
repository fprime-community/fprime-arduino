// ======================================================================
// \title  TcpServer.cpp
// \author ethan
// \brief  cpp file for TcpServer component implementation class
// ======================================================================

#include "Arduino/Drv/TcpServer/TcpServer.hpp"

namespace Arduino {

SocketIpStatus TcpServer::configure(const char* ssid, const char* password, U16 port) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

SocketIpStatus TcpServer::send(const U8* data, U32 size) {
    // Not implemented
    return SocketIpStatus::SOCK_INVALID_CALL;
}

void TcpServer::readLoop() {
    // Not implemented
    return;
}

void TcpServer::readTask(void* pointer) {
    FW_ASSERT(pointer);
    TcpServer* self = reinterpret_cast<TcpServer*>(pointer);
    self->readLoop();
}

}  // namespace Arduino
