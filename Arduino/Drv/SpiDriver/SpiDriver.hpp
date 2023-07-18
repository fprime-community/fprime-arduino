// ======================================================================
// \title  SpiDriver.hpp
// \author ethanchee
// \brief  hpp file for SpiDriver component implementation class
// ======================================================================

#ifndef SpiDriver_HPP
#define SpiDriver_HPP

#include "Arduino/Drv/SpiDriver/SpiDriverComponentAc.hpp"
#include <SPI.h>

namespace Arduino {

  class SpiDriver :
    public SpiDriverComponentBase
  {

    public:

      enum SpiFrequency
      {
        SPI_FREQUENCY_1MHZ = 1000000UL,
        SPI_FREQUENCY_2MHZ = 2000000UL,
        SPI_FREQUENCY_3MHZ = 3000000UL,
        SPI_FREQUENCY_4MHZ = 4000000UL,
      };

      enum SpiMode
      {
        SPI_MODE_CPOL_LOW_CPHA_LOW,   ///< (CPOL = 0, CPHA = 0) 
        SPI_MODE_CPOL_LOW_CPHA_HIGH,  ///< (CPOL = 0, CPHA = 1)
        SPI_MODE_CPOL_HIGH_CPHA_LOW,  ///< (CPOL = 1, CPHA = 0)
        SPI_MODE_CPOL_HIGH_CPHA_HIGH, ///< (CPOL = 1, CPHA = 1)
      };

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SpiDriver
      //!
      SpiDriver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object SpiDriver
      //!
      ~SpiDriver();

      void open(SPIClass *spi, SpiFrequency clock, SpiMode spiMode = SpiMode::SPI_MODE_CPOL_LOW_CPHA_LOW);
      void close();

    PRIVATE:

      //! Read the actual data
      void read_write_data(Fw::Buffer& readBuffer, Fw::Buffer& writeBuffer);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for SpiReadWrite
      //!
      void SpiReadWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &writeBuffer, 
          Fw::Buffer &readBuffer 
      );

      //! Stores the open SPI port, POINTER_CAST so Linux and Ardunio may use different types
      void* m_port_pointer;
      SpiFrequency clock;
      SpiMode spiMode;

    };

} // end namespace Arduino

#endif
