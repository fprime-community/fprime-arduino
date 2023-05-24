// ======================================================================
// \title  ATmegaSpiDriverComponentImplLinux.cpp
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

  //! (Deprecated) This function left only for backwards compatibility, should be removed when possible
  void ATmegaSpiDriverComponentImpl ::
    open(
      volatile uint8_t &ss_data_dir_register,
      volatile uint8_t &ss_port_register,
      int ss_pin_number,
      SpiMode spi_mode
    )
  {

  }

  void ATmegaSpiDriverComponentImpl ::
    setup(
      SpiClockDiv spi_clock_div,
      SpiBitOrder spi_bit_order,
      SpiMode spi_mode
    )
  {
      
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
      
  }

} // end namespace Drv
