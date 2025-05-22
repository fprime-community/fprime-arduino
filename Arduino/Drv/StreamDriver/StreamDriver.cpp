// ======================================================================
// \title  StreamDriverImpl.cpp
// \author lestarch
// \brief  cpp file for StreamDriver component implementation class
// ======================================================================

#include <Arduino/Drv/StreamDriver/StreamDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

StreamDriver ::StreamDriver(const char* compName)
    : StreamDriverComponentBase(compName),
      m_port_number(0),
      m_port_pointer(nullptr) {}

StreamDriver ::~StreamDriver(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void StreamDriver::recvReturnIn_handler(FwIndexType portNum, Fw::Buffer& fwBuffer) {
    this->deallocate_out(0, fwBuffer);
}

void StreamDriver ::send_handler(const FwIndexType portNum, Fw::Buffer& serBuffer) {
    write_data(serBuffer);
    sendReturnOut_out(0, serBuffer, Drv::ByteStreamStatus::OP_OK);
}

void StreamDriver ::schedIn_handler(const FwIndexType portNum, U32 context) {
    if (not reinterpret_cast<Stream*>(m_port_pointer)->available()) {
        return;
    }
    
    Fw::Buffer recv_buffer = this->allocate_out(0, SERIAL_BUFFER_SIZE);
    read_data(recv_buffer);
    recv_out(0, recv_buffer, Drv::ByteStreamStatus::OP_OK);
}

}  // namespace Arduino
