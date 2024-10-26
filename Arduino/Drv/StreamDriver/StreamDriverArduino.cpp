// ======================================================================
// \title  StreamDriverImpl.cpp
// \author lestarch
// \brief  cpp file for StreamDriver component implementation class
// ======================================================================

#include <Arduino/Drv/StreamDriver/StreamDriver.hpp>
#include <FprimeArduino.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
#include "Fw/Logger/Logger.hpp"

namespace Arduino {

void StreamDriver::configure(Stream* streamDriver) {
    Fw::Logger::log("CONFIGURE: %p\n", streamDriver);
    delay(1000);
    FW_ASSERT(streamDriver != nullptr);
    m_port_pointer = streamDriver;
    if (this->isConnected_ready_OutputPort(0)) {
        Fw::Logger::log("READY OUT\n");
        delay(1000);
        this->ready_out(0);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void StreamDriver ::write_data(Fw::Buffer& fwBuffer) {
    FW_ASSERT(m_port_pointer != 0);
    reinterpret_cast<Stream*>(m_port_pointer)
        ->write(reinterpret_cast<U8*>(fwBuffer.getData()), fwBuffer.getSize());
}

void StreamDriver ::read_data(Fw::Buffer& fwBuffer) {
    Stream* stream_ptr = reinterpret_cast<Stream*>(m_port_pointer);
    int byte = 0;
    NATIVE_UINT_TYPE count = 0;
    U8* raw_data = reinterpret_cast<U8*>(fwBuffer.getData());
    while ((stream_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = stream_ptr->read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }
    fwBuffer.setSize(count);
}
}  // namespace Arduino
