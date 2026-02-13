// ======================================================================
// \title  I2cDriver.hpp
// \author ethanchee
// \brief  hpp file for I2cDriver component implementation class
// ======================================================================

#ifndef I2cDriver_HPP
#define I2cDriver_HPP

#include "Arduino/Drv/I2cDriver/I2cDriverComponentAc.hpp"
#include <Arduino/config/FprimeArduino.hpp>
#include <Wire.h>

namespace Arduino {

  class I2cDriver :
    public I2cDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object I2cDriver
      //!
      I2cDriver(
          const char *const compName /*!< The component name*/
      );

      void open(TwoWire* wire);
      void close();

      //! Destroy object I2cDriver
      //!
      ~I2cDriver();

    private:

      //! Read the actual data
      Drv::I2cStatus read_data(U32 addr, Fw::Buffer& fwBuffer);
      //! Write the actual data
      Drv::I2cStatus write_data(U32 addr, Fw::Buffer& fwBuffer);
      //! Write and read the actual data
      Drv::I2cStatus writeRead_data(U32 addr, Fw::Buffer& writeBuffer, Fw::Buffer& readBuffer);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for write
      //!
      Drv::I2cStatus write_handler(const FwIndexType portNum, /*!< The port number*/
                                  U32 addr,
                                  Fw::Buffer& serBuffer);

      //! Handler implementation for read
      //!
      Drv::I2cStatus read_handler(const FwIndexType portNum, /*!< The port number*/
                                  U32 addr,
                                  Fw::Buffer& serBuffer);

      //! Handler implementation for writeRead
      //!
      Drv::I2cStatus writeRead_handler(const FwIndexType portNum, /*!< The port number*/
                                      U32 addr,
                                      Fw::Buffer& writeBuffer,
                                      Fw::Buffer& readBuffer);

      //! Stores the open wire port, POINTER_CAST so Linux and Ardunio may use different types
      void* m_port_pointer;

    };

} // end namespace Arduino

#endif
