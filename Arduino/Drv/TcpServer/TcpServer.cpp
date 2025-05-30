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

void TcpServer::start(const Fw::StringBase &name,
                                  const Os::Task::ParamType priority,
                                  const Os::Task::ParamType stack,
                                  const Os::Task::ParamType cpuAffinity) {
    FW_ASSERT(m_task.getState() == Os::Task::State::NOT_STARTED);  // It is a coding error to start this task multiple times
    // Note: the first step is for the IP socket to open the port
    Os::Task::Arguments arguments(name, TcpServer::readTask, this, priority, stack, cpuAffinity);
    Os::Task::Status stat = m_task.start(arguments);
    FW_ASSERT(Os::Task::OP_OK == stat, static_cast<FwAssertArgType>(stat));
}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void TcpServer ::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

void TcpServer ::send_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
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
    // Return the buffer and status to the caller
    this->sendReturnOut_out(0, fwBuffer, returnStatus);
}

}  // namespace Arduino
