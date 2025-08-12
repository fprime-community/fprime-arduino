// ======================================================================
// \title  TcpServer.cpp
// \author ethan
// \brief  cpp file for TcpServer component implementation class
// ======================================================================

#include "Arduino/Drv/TcpServer/TcpServer.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

TcpServer ::TcpServer(const char* const compName) : TcpServerComponentBase(compName) {}

TcpServer ::~TcpServer() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void TcpServer ::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

Drv::ByteStreamStatus TcpServer ::send_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    SocketIpStatus status = this->send(fwBuffer.getData(), fwBuffer.getSize());
    Drv::ByteStreamStatus returnStatus;
    switch (status) {
        case SOCK_SUCCESS:
            returnStatus = Drv::ByteStreamStatus::OP_OK;
            break;
        default:
            returnStatus = Drv::ByteStreamStatus::OTHER_ERROR;
            break;
    }
    return returnStatus;
}

void TcpServer ::schedIn_handler(const FwIndexType portNum, U32 context) {
    this->readLoop();
}

}  // namespace Arduino
