// ======================================================================
// \title  I2cDriver.cpp
// \author ethanchee
// \brief  cpp file for I2cDriver component implementation class
// ======================================================================

#include <Arduino/Drv/I2cDriver/I2cDriver.hpp>
#include "Fw/Types/Assert.hpp"

namespace Arduino {

void I2cDriver::open(TwoWire* wire) {
    FW_ASSERT(wire != nullptr);
    m_port_pointer = wire;
    wire->begin();
}

void I2cDriver::close() {
    FW_ASSERT(m_port_pointer != 0);
    TwoWire* wire_ptr = reinterpret_cast<TwoWire*>(m_port_pointer);
    wire_ptr->end();
}

Drv::I2cStatus I2cDriver::read_data(U32 addr, Fw::Buffer& fwBuffer) {
    TwoWire* wire_ptr = reinterpret_cast<TwoWire*>(m_port_pointer);

    wire_ptr->requestFrom(static_cast<U8>(addr), fwBuffer.getSize());

    int byte = 0;
    Fw::Buffer::SizeType count = 0;
    U8* raw_data = reinterpret_cast<U8*>(fwBuffer.getData());
    while ((wire_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = wire_ptr->read()) != -1)) {
        *(raw_data + count) = static_cast<U8>(byte);
        count++;
    }
    fwBuffer.setSize(count);

    return Drv::I2cStatus::I2C_OK;
}

Drv::I2cStatus I2cDriver::write_data(U32 addr, Fw::Buffer& fwBuffer) {
    FW_ASSERT(m_port_pointer != 0);
    TwoWire* wire_ptr = reinterpret_cast<TwoWire*>(m_port_pointer);

    wire_ptr->beginTransmission(static_cast<U8>(addr));
    wire_ptr->write(reinterpret_cast<U8*>(fwBuffer.getData()), fwBuffer.getSize());
    wire_ptr->endTransmission();

    return Drv::I2cStatus::I2C_OK;
}

}  // end namespace Arduino
