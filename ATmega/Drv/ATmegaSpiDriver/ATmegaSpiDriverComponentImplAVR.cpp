// ======================================================================
// \title  ATmegaSpiDriverComponentImplAVR.cpp
// \author vagrant
// \brief  cpp file for ATmegaSpiDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ATmega/Drv/ATmegaSpiDriver/ATmegaSpiDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <avr/io.h>

namespace Drv {

  //! (Deprecated) This function left only for backwards compatibility, should be removed when possible
  void ATmegaSpiDriverComponentImpl ::
    open(
      volatile uint8_t &ss_data_dir_register,
      volatile uint8_t &ss_port_register,
      int ss_pin_number,
      SpiMode spi_mode
    )
  {
      m_ss_manage = true;

      m_ss_ddir = &ss_data_dir_register;
      m_ss_port = &ss_port_register;
      m_ss_pin = ss_pin_number;

      // Set SS pin to output high
      // TODO: Tunable to set SS polarity
      *m_ss_ddir |= _BV(m_ss_pin);
      *m_ss_port |= _BV(m_ss_pin);

      setup(SPI_CLOCK_DIV16, SPI_BIT_ORDER_MSB, spi_mode);
  }

  void ATmegaSpiDriverComponentImpl ::
    setup(
      SpiClockDiv spi_clock_div,
      SpiBitOrder spi_bit_order,
      SpiMode spi_mode
    )
  {
      // Set MOSI, SCK, hw SS as Output (hw SS required to be set as output for normal MSTR operation)
      PORTB |= _BV(DDB0); // Ensure SS is first configured to write high
      DDRB |= (0x0F & (_BV(DDB0) | _BV(DDB1) | _BV(DDB2)));

      // Enable SPI, Set as Master, Set mode, Set clock div, Set bit order
      SPSR = (SPSR & ~SPI_CLOCK_SPI2X_MASK) | ((spi_clock_div >> 2) & SPI_CLOCK_SPI2X_MASK);
      SPCR = _BV(SPE) | _BV(MSTR) | (spi_mode << CPHA) | (spi_clock_div & SPI_CLOCK_SPR_MASK) | (spi_bit_order << DORD);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaSpiDriverComponentImpl ::
    spiReadWrite_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
      // TODO: only transfer the the min of max size, or stop writing
      //       to read buffer when it is full
      readBuffer.setSize(writeBuffer.getSize());
      U8* readBufferData = (U8*)readBuffer.getData();
      U8* writeBufferData = (U8*)writeBuffer.getData();

      if (m_ss_manage) { *m_ss_port &= ~_BV(m_ss_pin); }
      for (NATIVE_UINT_TYPE i = 0; i < writeBuffer.getSize(); i++) {
          SPDR = writeBufferData[i];
          while ( !(SPSR & _BV(SPIF)) );  // TODO: add timeout
          readBufferData[i] = SPDR;
      }
      if (m_ss_manage) { *m_ss_port |= _BV(m_ss_pin); }
  }

} // end namespace Drv
