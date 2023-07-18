// ======================================================================
// \title  I2cDriver.cpp
// \author ethanchee
// \brief  cpp file for I2cDriver component implementation class
// ======================================================================


#include <Arduino/Drv/I2cDriver/I2cDriver.hpp>
#include <FpConfig.hpp>

namespace Arduino {

    void I2cDriver::close() {
        
    }

    Drv::I2cStatus I2cDriver::read_data(U32 addr, Fw::Buffer& fwBuffer)
    {
        return Drv::I2cStatus::I2C_OK;
    }

    Drv::I2cStatus I2cDriver::write_data(U32 addr, Fw::Buffer& fwBuffer)
    {
        return Drv::I2cStatus::I2C_OK;        
    }

} // end namespace Arduino
