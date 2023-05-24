// ======================================================================
// \title  ATmegaSpiDriverComponentImpl.cpp
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

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaSpiDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaSpiDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaSpiDriverComponentBase(compName)
#else
    ATmegaSpiDriverComponentImpl(void)
#endif
  {

  }

  void ATmegaSpiDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaSpiDriverComponentBase::init(instance);
  }

  void ATmegaSpiDriverComponentImpl ::
    open(
      volatile uint8_t &ss_data_dir_register,
      volatile uint8_t &ss_port_register,
      int ss_pin_number,
      SpiMode spi_mode
    )
  {
      m_ss_ddir = &ss_data_dir_register;
      m_ss_port = &ss_port_register;
      m_ss_pin = ss_pin_number;

      // Set MOSI, SCK, hw SS as Output
      DDRB |= (0x0F & (_BV(DDB0) | _BV(DDB1) | _BV(DDB2)));

      // Set SS pin to output high
      // TODO: Tunable to set SS polarity
      *m_ss_ddir |= _BV(m_ss_pin);
      *m_ss_port |= _BV(m_ss_pin);

      // Enable SPI, Set as Master
      // FCK = Osc/16
      SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | (spi_mode << CPHA);
  }

  ATmegaSpiDriverComponentImpl ::
    ~ATmegaSpiDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaSpiDriverComponentImpl ::
    SpiReadWrite_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
      // TODO: only transfer the the min of max size, or stop writing
      //       to read buffer when it is full
      readBuffer.setSize(writeBuffer.getsize());
      U8* readBufferData = (U8*)readBuffer.getdata();
      U8* writeBufferData = (U8*)writeBuffer.getdata();

      *m_ss_port &= ~_BV(m_ss_pin);
      for (NATIVE_UINT_TYPE i = 0; i < writeBuffer.getsize(); i++) {
          SPDR = writeBufferData[i];
          while ( !(SPSR & _BV(SPIF)) );  // TODO: add timeout
          readBufferData[i] = SPDR;
      }
      *m_ss_port |= _BV(m_ss_pin);

  }

} // end namespace Drv
