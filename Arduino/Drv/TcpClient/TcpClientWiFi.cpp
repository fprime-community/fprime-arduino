// ======================================================================
// \title  TcpClientWiFi.cpp
// \author ethanchee
// \brief  cpp file for TcpClientWiFi component implementation class
// ======================================================================

#include <WiFi.h>
#include <Arduino/Drv/TcpClient/TcpClient.hpp>
#include <Fw/Logger/Logger.hpp>

namespace Arduino {

SocketIpStatus TcpClient::configure(const char* ssid,
                                    const char* password,
                                    const char* hostname,
                                    const U16 port,
                                    FwSizeType buffer_size) {
    FW_ASSERT(buffer_size <= std::numeric_limits<U32>::max(), static_cast<FwAssertArgType>(buffer_size));
    this->m_allocation_size = buffer_size;
    this->m_hostname = hostname;
    this->m_port = port;

    Fw::Logger::log("Connecting to WiFi SSID: %s\nThis may take a moment...\n", ssid);

    WiFi.begin(ssid, password);

    if (WiFi.status() != WL_CONNECTED) {
        return SocketIpStatus::SOCK_FAILED_TO_BIND;
    }

    Fw::Logger::log("WiFi connected with IP: %s\n", WiFi.localIP().toString().c_str());

    this->m_socket.fd = new WiFiClient();
    if (not reinterpret_cast<WiFiClient*>(this->m_socket.fd)->connect(this->m_hostname, this->m_port)) {
        Fw::Logger::log("Failed to connect to server at %s:%d\n", this->m_hostname, this->m_port);
        return SocketIpStatus::SOCK_FAILED_TO_CONNECT;
    }
    Fw::Logger::log("Connected to server at %s:%d\n", this->m_hostname, this->m_port);

    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }

    return SocketIpStatus::SOCK_SUCCESS;
}

/**
 * NOT CURRENTLY BEING USED
 * WiFiClient.connect() function blocks so I am not using it for now.
 * 
 * I am keeping this function here in case I figure something out later.
 */
SocketIpStatus TcpClient::reconnect() {
    if (this->m_socket.fd == nullptr) {
        return SocketIpStatus::SOCK_NOT_STARTED;  // Socket not initialized
    }

    WiFiClient* client = reinterpret_cast<WiFiClient*>(this->m_socket.fd);
    if (client->connected()) {
        return SocketIpStatus::SOCK_SUCCESS;  // Already connected
    }

    // Attempt to reconnect
    if (not client->connect(this->m_hostname, this->m_port)) {
        return SocketIpStatus::SOCK_FAILED_TO_CONNECT;
    }

    Fw::Logger::log("Connected to server at %s:%d\n", this->m_hostname, this->m_port);
    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }
    return SocketIpStatus::SOCK_SUCCESS;
}

SocketIpStatus TcpClient::send(const U8* data, U32 size) {
    if (this->m_socket.fd == nullptr) {
        return SocketIpStatus::SOCK_NOT_STARTED;
    }

    WiFiClient* client = reinterpret_cast<WiFiClient*>(this->m_socket.fd);

    if (not client->connected()) {
        return SocketIpStatus::SOCK_DISCONNECTED;
    }

    FwSizeType bytesSent = client->write(data, size);
    if (bytesSent != size) {
        return SocketIpStatus::SOCK_INTERRUPTED_TRY_AGAIN;
    }

    return SocketIpStatus::SOCK_SUCCESS;
}

void TcpClient::readLoop() {
    if (this->m_socket.fd == nullptr) {
        return;  // Socket not initialized
    }

    WiFiClient* client = reinterpret_cast<WiFiClient*>(this->m_socket.fd);

    if (not client->connected()) {
        // TODO: non-blocking reconnect
        return;
    }

    Fw::Buffer buffer = this->allocate_out(0, static_cast<U32>(this->m_allocation_size));
    U8* data = buffer.getData();
    FW_ASSERT(data);
    U32 size = buffer.getSize();

    Drv::ByteStreamStatus recvStatus = Drv::ByteStreamStatus::OP_OK;
    if (client->available()) {
        FwSizeType recvSize = client->read(data, size);
        if (recvSize > 0) {
            buffer.setSize(recvSize);
        } else {
            buffer.setSize(0);  // Clear the buffer if no data was read
            recvStatus = Drv::ByteStreamStatus::RECV_NO_DATA;
        }
    } else {
        buffer.setSize(0);  // Clear the buffer if no data is available
        recvStatus = Drv::ByteStreamStatus::RECV_NO_DATA;
    }

    this->recv_out(0, buffer, recvStatus);
}

}  // end namespace Arduino
