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

void TcpClient::start(const Fw::StringBase& name,
                      const Os::Task::ParamType priority,
                      const Os::Task::ParamType stack,
                      const Os::Task::ParamType cpuAffinity) {
    FW_ASSERT(m_task.getState() ==
              Os::Task::State::NOT_STARTED);  // It is a coding error to start this task multiple times
    // Note: the first step is for the IP socket to open the port
    Os::Task::Arguments arguments(name, TcpClient::readTask, this, priority, stack, cpuAffinity);
    Os::Task::Status stat = m_task.start(arguments);
    FW_ASSERT(Os::Task::OP_OK == stat, static_cast<FwAssertArgType>(stat));
}

void TcpClient::readTask(void* pointer) {
    FW_ASSERT(pointer);
    TcpClient* self = reinterpret_cast<TcpClient*>(pointer);
    self->readLoop();
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void TcpClient::send_handler(const FwIndexType portNum, Fw::Buffer& fwBuffer) {
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
    // Return the buffer and status to the caller
    this->sendReturnOut_out(0, fwBuffer, returnStatus);
}

void TcpClient::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

}  // end namespace Arduino
