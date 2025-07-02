// ======================================================================
// \title  SpiDriver.cpp
// \author ethanchee
// \brief  cpp file for SpiDriver component implementation class
// ======================================================================

#include <Arduino/Drv/SpiDriver/SpiDriver.hpp>
#include "Fw/Types/Assert.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

SpiDriver ::SpiDriver(const char* const compName) : SpiDriverComponentBase(compName), m_port_pointer(nullptr) {}

SpiDriver ::~SpiDriver() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void SpiDriver ::SpiReadWrite_handler(const FwIndexType portNum, Fw::Buffer& writeBuffer, Fw::Buffer& readBuffer) {
    FW_ASSERT(readBuffer.getData());
    FW_ASSERT(writeBuffer.getData());

    read_write_data(readBuffer, writeBuffer);
}

}  // end namespace Arduino
