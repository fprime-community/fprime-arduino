// ======================================================================
// \title  TcpServer.cpp
// \author ethan
// \brief  cpp file for TcpServer component implementation class
// ======================================================================

#include <WiFi.h>
#include <Fw/Logger/Logger.hpp>
#include "Arduino/Drv/TcpServer/TcpServer.hpp"

namespace Arduino {

SocketIpStatus TcpServer::configure(const char* ssid, const char* password, U16 port, FwSizeType buffer_size) {
    FW_ASSERT(buffer_size <= std::numeric_limits<U32>::max(), static_cast<FwAssertArgType>(buffer_size));
    this->m_allocation_size = buffer_size;

    Fw::Logger::log("Connecting to WiFi SSID: %s\nThis may take a moment...\n", ssid);

    this->m_socket.serverFd = new WiFiServer(port);

    WiFi.begin(ssid, password);

    if (WiFi.status() != WL_CONNECTED)
        return SocketIpStatus::SOCK_FAILED_TO_BIND;

    Fw::Logger::log("WiFi connected with IP: %s\n", WiFi.localIP().toString().c_str());

    reinterpret_cast<WiFiServer*>(this->m_socket.serverFd)->begin();

    return SocketIpStatus::SOCK_SUCCESS;
}

SocketIpStatus TcpServer::send(const U8* data, U32 size) {
    if (this->m_socket.serverFd == nullptr) {
        return SocketIpStatus::SOCK_NOT_STARTED;  // Socket not initialized
    }

    if (this->m_socket.fd == nullptr) {
        return SocketIpStatus::SOCK_NO_DATA_AVAILABLE;  // No client connected
    }

    FwSizeType status = reinterpret_cast<WiFiClient*>(this->m_socket.fd)->write(data, size);

    if (status == -1) {
        return SocketIpStatus::SOCK_SEND_ERROR;  // Failed to send data
    }

    return SocketIpStatus::SOCK_SUCCESS;
}

void TcpServer::readLoop() {
    if (this->m_socket.serverFd == nullptr) {
        return;  // Socket not initialized
    }

    if (this->m_socket.fd == nullptr) {
        WiFiClient client = reinterpret_cast<WiFiServer*>(this->m_socket.serverFd)->accept();
        if (!client) {
            return;  // No client connected
        }
        this->m_socket.fd = new WiFiClient(client);
        if (this->isConnected_ready_OutputPort(0)) {
            this->ready_out(0);
        }

        Fw::Logger::log("Client connected: %s\n",
                        reinterpret_cast<WiFiClient*>(this->m_socket.fd)->remoteIP().toString().c_str());
    }

    if (not reinterpret_cast<WiFiClient*>(this->m_socket.fd)->connected()) {
        Fw::Logger::log("Client disconnected\n");
        delete reinterpret_cast<WiFiClient*>(this->m_socket.fd);
        this->m_socket.fd = nullptr;
    }

    Fw::Buffer buffer = this->allocate_out(0, static_cast<U32>(this->m_allocation_size));
    U8* data = buffer.getData();
    FW_ASSERT(data);
    U32 size = buffer.getSize();
    FwSizeType recvSize = reinterpret_cast<WiFiClient*>(this->m_socket.fd)->read(data, size);
    buffer.setSize(recvSize);

    Drv::ByteStreamStatus recvStatus = Drv::ByteStreamStatus::OP_OK;
    if (recvSize == 0) {
        recvStatus = Drv::ByteStreamStatus::RECV_NO_DATA;
    }

    this->recv_out(0, buffer, recvStatus);
}

void TcpServer::readTask(void* pointer) {
    FW_ASSERT(pointer);
    TcpServer* self = reinterpret_cast<TcpServer*>(pointer);
    self->readLoop();
}

}  // namespace Arduino
