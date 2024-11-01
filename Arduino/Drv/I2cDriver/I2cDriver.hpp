// ======================================================================
// \title  I2cDriver.hpp
// \author ethanchee
// \brief  hpp file for I2cDriver component implementation class
// ======================================================================

#ifndef I2cDriver_HPP
#define I2cDriver_HPP

#include "Arduino/Drv/I2cDriver/I2cDriverComponentAc.hpp"
#include <FprimeArduino.hpp>
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

    PRIVATE:

      //! Read the actual data
      Drv::I2cStatus read_data(U32 addr, Fw::Buffer& fwBuffer);
      //! Write the actual data
      Drv::I2cStatus write_data(U32 addr, Fw::Buffer& fwBuffer);

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read
      //!
      Drv::I2cStatus read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, /*!< 
      I2C slave device address
      */
          Fw::Buffer &serBuffer /*!< 
      Buffer with data to read/write to/from
      */
      );

      //! Handler implementation for write
      //!
      Drv::I2cStatus write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 addr, /*!< 
      I2C slave device address
      */
          Fw::Buffer &serBuffer /*!< 
      Buffer with data to read/write to/from
      */
      );

      //! Stores the open wire port, POINTER_CAST so Linux and Ardunio may use different types
      void* m_port_pointer;

    };

} // end namespace Arduino

#endif
