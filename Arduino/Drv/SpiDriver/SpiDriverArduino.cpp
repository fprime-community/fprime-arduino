// ======================================================================
// \title  SpiDriver.cpp
// \author ethanchee
// \brief  cpp file for SpiDriver component implementation class
// ======================================================================


#include <Arduino/Drv/SpiDriver/SpiDriver.hpp>
#include <FpConfig.hpp>
#include "Fw/Types/Assert.hpp"

namespace Arduino {

  void SpiDriver::open(SPIClass *spi, SpiFrequency clock, SpiMode spiMode)
  {
    FW_ASSERT(spi != nullptr);

    U8 mode = SPI_MODE0;
    switch(spiMode) {
      case SpiMode::SPI_MODE_CPOL_LOW_CPHA_LOW:
        mode = SPI_MODE0;
        break;
      case SpiMode::SPI_MODE_CPOL_LOW_CPHA_HIGH:
        mode = SPI_MODE1;
        break;
      case SpiMode::SPI_MODE_CPOL_HIGH_CPHA_LOW:
        mode = SPI_MODE2;
        break;
      case SpiMode::SPI_MODE_CPOL_HIGH_CPHA_HIGH:
        mode = SPI_MODE3;
        break;
      default:
        //Assert if the device SPI Mode is not in the correct range
        FW_ASSERT(0, spiMode);                
        break;
    }

    this->m_port_pointer = spi;
    this->clock = clock;
    this->spiMode = spiMode;

    spi->begin();
  }

  void SpiDriver::close()
  {
    FW_ASSERT(m_port_pointer != 0);
    SPIClass* spi_ptr = reinterpret_cast<SPIClass*>(m_port_pointer);

    spi_ptr->end();
  }

  void SpiDriver::read_write_data(Fw::Buffer& readBuffer, Fw::Buffer& writeBuffer)
  {
    FW_ASSERT(m_port_pointer != 0);
    SPIClass* spi_ptr = reinterpret_cast<SPIClass*>(m_port_pointer);

    spi_ptr->beginTransaction(SPISettings(this->clock, MSBFIRST, this->spiMode));
    spi_ptr->transfer(reinterpret_cast<U8*>(writeBuffer.getData()), reinterpret_cast<U8*>(readBuffer.getData()), writeBuffer.getSize());
    spi_ptr->endTransaction();
  }

} // end namespace Arduino
