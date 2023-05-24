// ======================================================================
// \title  ATmegaSpiDriverComponentImpl.hpp
// \author vagrant
// \brief  hpp file for ATmegaSpiDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ATmegaSpiDriver_HPP
#define ATmegaSpiDriver_HPP

#include "ATmega/Drv/ATmegaSpiDriver/ATmegaSpiDriverComponentAc.hpp"


namespace Drv {

  class ATmegaSpiDriverComponentImpl :
    public ATmegaSpiDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaSpiDriver
      //!
      ATmegaSpiDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      typedef enum SPI_MODE {
        SPI_MODE_0 = 0x0,
        SPI_MODE_1 = 0x1,
        SPI_MODE_2 = 0x2,
        SPI_MODE_3 = 0x3
      } SpiMode;

      typedef enum SPI_CLOCK_DIV {
        SPI_CLOCK_DIV4 = 0x0,
        SPI_CLOCK_DIV16 = 0x1,
        SPI_CLOCK_DIV64 = 0x2,
        SPI_CLOCK_DIV128 = 0x3,
        SPI_CLOCK_DIV2 = 0x4,
        SPI_CLOCK_DIV8 = 0x5,
        SPI_CLOCK_DIV32 = 0x6
      } SpiClockDiv;

      typedef enum SPI_BIT_ORDER {
        SPI_BIT_ORDER_MSB = 0,
        SPI_BIT_ORDER_LSB = 1
      } SpiBitOrder;

      #define SPI_CLOCK_SPR_MASK 0x1
      #define SPI_CLOCK_SPI2X_MASK 0x3

      //! Initialize object ATmegaSpiDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure SPI driver
      //!
      void open(
          volatile uint8_t &ss_data_dir_register,
          volatile uint8_t &ss_port_register,
          int ss_pin_number,
          SpiMode spi_mode = SPI_MODE_0
      );
      void setup(
          SpiClockDiv spi_clock_div,
          SpiBitOrder spi_bit_order,
          SpiMode spi_mode = SPI_MODE_0
      );

      //! Destroy object ATmegaSpiDriver
      //!
      ~ATmegaSpiDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for SpiReadWrite
      //!
      void spiReadWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &writeBuffer,
          Fw::Buffer &readBuffer
      );

      //! Data Direction Register for SS pin (needs to match m_ss_port)
      volatile uint8_t *m_ss_ddir;

      //! Port Register for SS pin (needs to match m_ss_ddir)
      volatile uint8_t *m_ss_port;

      //! SS Pin Number within Port
      uint8_t m_ss_pin;

      //! Whether SS pin is handled by component (deprecated)
      bool m_ss_manage = false;

    };

} // end namespace Drv

#endif
