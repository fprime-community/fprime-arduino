// ======================================================================
// \title  SpiDriver.cpp
// \author ethanchee
// \brief  cpp file for SpiDriver component implementation class
// ======================================================================


#include <Arduino/Drv/SpiDriver/SpiDriver.hpp>
#include <FpConfig.hpp>
#include "Fw/Types/Assert.hpp"
#include <FprimeArduino.hpp>

namespace Arduino {

  void SpiDriver::open(SPIClass *spi, SpiFrequency clock, NATIVE_INT_TYPE ss_pin, SpiMode spiMode, SpiBitOrder bitOrder)
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
    this->m_clock = clock;
    this->m_spiMode = mode;
    this->m_ss_pin = ss_pin;
    this->m_bitOrder = bitOrder;

    pinMode(m_ss_pin, Arduino::DEF_OUTPUT);
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

    if(this->m_bitOrder == SpiBitOrder::SPI_MSB_FIRST)
      spi_ptr->beginTransaction(SPISettings(this->m_clock, MSBFIRST, this->m_spiMode));
    else
      spi_ptr->beginTransaction(SPISettings(this->m_clock, LSBFIRST, this->m_spiMode));

    digitalWrite(m_ss_pin, Arduino::DEF_LOW);
    spi_ptr->transfer(reinterpret_cast<U8*>(writeBuffer.getData()), writeBuffer.getSize());
    digitalWrite(m_ss_pin, Arduino::DEF_HIGH);

    spi_ptr->endTransaction();

    memcpy(readBuffer.getData(), writeBuffer.getData(), writeBuffer.getSize());
  }

} // end namespace Arduino
