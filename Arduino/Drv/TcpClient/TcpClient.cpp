// ======================================================================
// \title  TcpClient.cpp
// \author ethanchee
// \brief  cpp file for TcpClient component implementation class
// ======================================================================

#include <Arduino/Drv/TcpClient/TcpClient.hpp>
#include <FpConfig.hpp>
#include <StaticMemoryConfig.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

TcpClient ::TcpClient(const char* const compName) : TcpClientComponentBase(compName), client_connected(false) {}

TcpClient ::~TcpClient() {
    if (client_connected)
        client.stop();
}

Drv::SocketIpStatus TcpClient::setupWiFi(char* ssid, const char* password) {
    WiFi.begin(ssid, password);

    if (WiFi.status() != WL_CONNECTED)
        return Drv::SocketIpStatus::SOCK_FAILED_TO_BIND;

    return Drv::SocketIpStatus::SOCK_SUCCESS;
}

Drv::SocketIpStatus TcpClient::configure(const char* hostname,
                                         const U16 port,
                                         const U32 send_timeout_seconds,
                                         const U32 send_timeout_microseconds) {
    if (not client.connect(hostname, port)) {
        return Drv::SocketIpStatus::SOCK_FAILED_TO_CONNECT;
    }

    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }

    client_connected = true;

    return Drv::SocketIpStatus::SOCK_SUCCESS;
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void TcpClient ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    if (not client_connected) {
        return;
    }

    Fw::Buffer recvBuffer = this->allocate_out(0, Svc::STATIC_MEMORY_ALLOCATION_SIZE);

    int byte = 0;
    NATIVE_UINT_TYPE count = 0;
    U8* raw_data = reinterpret_cast<U8*>(recvBuffer.getData());

    while ((client.available() > 0) && (count < recvBuffer.getSize()) && ((byte = client.read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }

    recvBuffer.setSize(count);

    this->recv_out(0, recvBuffer, Drv::RecvStatus::RECV_OK);
}

Drv::SendStatus TcpClient ::send_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& sendBuffer) {
    if (client_connected && sendBuffer.getSize() > 0) {
        client.write(sendBuffer.getData(), sendBuffer.getSize());
    }

    this->deallocate_out(0, sendBuffer);

    return Drv::SendStatus::SEND_OK;
}

}  // end namespace Arduino
