// ======================================================================
// \title  I2cNodeDriver.cpp
// \author mstarch
// \brief  cpp file for I2cNodeDriver component implementation class
// ======================================================================

#include "Arduino/Drv/I2cNodeDriver/I2cNodeDriver.hpp"
#include "Fw/Types/Assert.hpp"

namespace Arduino {

I2cNodeDriver* I2cNodeDriver ::s_component = nullptr;
// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

I2cNodeDriver ::I2cNodeDriver(const char* const compName) : I2cNodeDriverComponentBase(compName), m_wire(nullptr) {}

I2cNodeDriver ::~I2cNodeDriver() {}

void I2cNodeDriver ::configure(const U16 address, TwoWire& wire) {
    FW_ASSERT(this->m_wire == nullptr);
    FW_ASSERT(I2cNodeDriver::s_component == nullptr);  // Cannot run multiple I2cNodes at once
    this->m_wire = &wire;
    I2cNodeDriver ::s_component = this;
    this->m_wire->begin(address);
    this->m_wire->onReceive(I2cNodeDriver::writeCallback);
    this->m_wire->onRequest(I2cNodeDriver::readCallback);
}

void I2cNodeDriver ::write(int size) {
    FW_ASSERT(this->m_wire != nullptr);
    FW_ASSERT(this->m_wire->available() >= size);  // If size was reported available, then at least that size must be
    this->m_wire->readBytes(this->m_buffer, size);
    Fw::Buffer writeData(this->m_buffer, size);
    this->write_out(0, this->m_address, writeData);
}

void I2cNodeDriver ::writeCallback(int size) {
    FW_ASSERT(I2cNodeDriver::s_component != nullptr);  // To reach this statement, this variable must be set
    I2cNodeDriver::s_component->write(size);
}

void I2cNodeDriver ::read() {
    FW_ASSERT(this->m_wire != nullptr);
    Fw::Buffer readData(this->m_buffer, sizeof this->m_buffer);
    this->read_out(0, this->m_address, readData);
    this->m_wire->write(readData.getData(), readData.getSize());
}

void I2cNodeDriver ::readCallback() {
    FW_ASSERT(I2cNodeDriver::s_component != nullptr);  // To reach this statement, this variable must be set
    I2cNodeDriver::s_component->read();
}

}  // namespace Arduino
