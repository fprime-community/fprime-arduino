// ======================================================================
// \title  StreamDriverImpl.cpp
// \author lestarch
// \brief  cpp file for StreamDriver component implementation class
// ======================================================================

#include <Arduino/Drv/StreamDriver/StreamDriver.hpp>
#include <config/FprimeArduino.hpp>
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/BasicTypes.hpp"

namespace Arduino {

void StreamDriver::configure(Stream* streamDriver) {
    FW_ASSERT(streamDriver != nullptr);
    m_port_pointer = streamDriver;
    if (this->isConnected_ready_OutputPort(0)) {
        this->ready_out(0);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void StreamDriver ::write_data(Fw::Buffer& fwBuffer) {
    FW_ASSERT(m_port_pointer != 0);
    reinterpret_cast<Stream*>(m_port_pointer)->write(reinterpret_cast<U8*>(fwBuffer.getData()), fwBuffer.getSize());
}

void StreamDriver ::read_data(Fw::Buffer& fwBuffer) {
    Stream* stream_ptr = reinterpret_cast<Stream*>(m_port_pointer);
    int byte = 0;
    Fw::Buffer::SizeType count = 0;
    U8* raw_data = reinterpret_cast<U8*>(fwBuffer.getData());
    while ((stream_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = stream_ptr->read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }
    fwBuffer.setSize(count);
}
}  // namespace Arduino
