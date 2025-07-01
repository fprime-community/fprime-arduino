// ======================================================================
// \title  I2cDriver.cpp
// \author ethanchee
// \brief  cpp file for I2cDriver component implementation class
// ======================================================================

#include <Arduino/Drv/I2cDriver/I2cDriver.hpp>
#include "Fw/Types/Assert.hpp"

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

I2cDriver ::I2cDriver(const char* const compName) : I2cDriverComponentBase(compName), m_port_pointer(nullptr) {}

I2cDriver ::~I2cDriver() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::I2cStatus I2cDriver ::read_handler(const FwIndexType portNum, U32 addr, Fw::Buffer& serBuffer) {
    // Ensure buffer is not a nullptr
    FW_ASSERT(serBuffer.getData());

    return read_data(addr, serBuffer);
}

Drv::I2cStatus I2cDriver ::write_handler(const FwIndexType portNum, U32 addr, Fw::Buffer& serBuffer) {
    // Ensure buffer is not a nullptr
    FW_ASSERT(serBuffer.getData());

    return write_data(addr, serBuffer);
}

}  // end namespace Arduino
