// ======================================================================
// \title  TcpClient.cpp
// \author ethanchee
// \brief  cpp file for TcpClient component implementation class
// ======================================================================

#include <Arduino/Drv/TcpClient/TcpClient.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

TcpClient ::TcpClient(const char* const compName) : TcpClientComponentBase(compName) {}

TcpClient ::~TcpClient() {}

void TcpClient ::schedIn_handler(const FwIndexType portNum, U32 context) {
    this->readLoop();
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::ByteStreamStatus TcpClient::send_handler(const FwIndexType portNum, Fw::Buffer& fwBuffer) {
    SocketIpStatus status = this->send(fwBuffer.getData(), fwBuffer.getSize());
    Drv::ByteStreamStatus returnStatus;
    switch (status) {
        case SOCK_INTERRUPTED_TRY_AGAIN:
            returnStatus = Drv::ByteStreamStatus::SEND_RETRY;
            break;
        case SOCK_SUCCESS:
            returnStatus = Drv::ByteStreamStatus::OP_OK;
            break;
        default:
            returnStatus = Drv::ByteStreamStatus::OTHER_ERROR;
            break;
    }
    return returnStatus;
}

void TcpClient::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

}  // end namespace Arduino
