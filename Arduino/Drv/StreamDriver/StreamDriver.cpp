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
      m_port_pointer(static_cast<POINTER_CAST>(NULL)) {}

StreamDriver ::~StreamDriver(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::SendStatus StreamDriver ::send_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    write_data(fwBuffer);
    deallocate_out(0, fwBuffer);
    return Drv::SendStatus::SEND_OK;
}

void StreamDriver ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    Fw::Buffer recv_buffer = this->allocate_out(0, SERIAL_BUFFER_SIZE);
    read_data(recv_buffer);
    recv_out(0, recv_buffer, Drv::RecvStatus::RECV_OK);
}

}  // namespace Arduino
