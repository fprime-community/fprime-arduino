// ======================================================================
// \title  SpiDriver.cpp
// \author ethanchee
// \brief  cpp file for SpiDriver component implementation class
// ======================================================================


#include <Arduino/Drv/SpiDriver/SpiDriver.hpp>
#include <FpConfig.hpp>

namespace Arduino {

  void SpiDriver::open(SPIClass *spi, SpiFrequency clock, NATIVE_INT_TYPE ss_pin, SpiMode spiMode, SpiBitOrder bitOrder)
  {

  }

  void SpiDriver::close()
  {

  }

  void SpiDriver::read_write_data(Fw::Buffer& readBuffer, Fw::Buffer& writeBuffer)
  {
    
  }

} // end namespace Arduino
