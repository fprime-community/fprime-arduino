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

// @ DEPRECATED: Use SpiWriteRead port instead (same operation with a return value)
void SpiDriver::SpiReadWrite_handler(const FwIndexType portNum,
                                                       Fw::Buffer& writeBuffer,
                                                       Fw::Buffer& readBuffer) {
    FW_ASSERT(portNum >= 0, static_cast<FwAssertArgType>(portNum));
    FW_ASSERT(writeBuffer.isValid());
    FW_ASSERT(readBuffer.isValid());
    (void)SpiWriteRead_handler(portNum, writeBuffer, readBuffer);
}

Drv::SpiStatus SpiDriver::SpiWriteRead_handler(const FwIndexType portNum, Fw::Buffer& writeBuffer, Fw::Buffer& readBuffer) {
    FW_ASSERT(portNum >= 0, static_cast<FwAssertArgType>(portNum));
    FW_ASSERT(readBuffer.isValid());
    FW_ASSERT(writeBuffer.isValid());
    FW_ASSERT(writeBuffer.getSize() == readBuffer.getSize());

    read_write_data(readBuffer, writeBuffer);
    return Drv::SpiStatus::SPI_OK;
}

}  // end namespace Arduino
