// ====================================================================== 
// \title  SerialDriverImpl.hpp
// \author lestarch
// \brief  hpp file for SerialDriver component implementation class
// ====================================================================== 

#ifndef SerialDriver_HPP
#define SerialDriver_HPP

#include "Os/Task.hpp"
#include "fprime-arduino/ArduinoDrv/SerialDriver/SerialDriverComponentAc.hpp"

namespace Arduino {
//Allow for setting serial ports from the inputs
#ifndef ARDUINO
    extern char** SERIAL_PORT;
#endif
  class SerialDriverComponentImpl :
    public SerialDriverComponentBase
  {

    public:
      const static NATIVE_UINT_TYPE SERIAL_BUFFER_SIZE = 64; // Maximum Arduino Serial buffer size
      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SerialDriver
      //!
      SerialDriverComponentImpl(
          const char *const compName, /*!< The component name*/
          NATIVE_UINT_TYPE portNumber
      );

      //! Initialize object SerialDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const NATIVE_UINT_TYPE baud
      );

      //! Destroy object SerialDriver
      //!
      ~SerialDriverComponentImpl(void);

    PRIVATE:
      //! Read the actual data
      void read_data(Fw::Buffer &fwBuffer);
      //! Write the actual data
      void write_data(Fw::Buffer &fwBuffer);
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for write
      //!
      void write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer 
      );

      //! Handler implementation for readPoll
      //!
      void readPoll_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer 
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Port number to open
      NATIVE_UINT_TYPE m_port_number;
      //! Stores the open serial port, POINTER_CAST so Linux and Ardunio may use different types
      POINTER_CAST m_port_pointer;
      //! Data store for self-generated serial data
      U8 m_data[SERIAL_BUFFER_SIZE]; // Max data in 1/10th second at 115200
      //! Buffer to wrap
      Fw::Buffer m_local_buffer;
    };

} // end namespace Arduino

#endif
