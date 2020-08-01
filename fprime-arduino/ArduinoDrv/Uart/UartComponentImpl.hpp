// ====================================================================== 
// \title  UartImpl.hpp
// \author starchmd
// \brief  hpp file for Uart component implementation class
//
// \copyright
// Copyright 2018, LeStarch
// ====================================================================== 

#ifndef Uart_HPP
#define Uart_HPP

#include "Drv/Uart/UartComponentAc.hpp"

namespace Drv {

  class UartComponentImpl :
    public UartComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Uart
      //!
      UartComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object Uart
      //!
      void init(
          const POINTER_CAST device, /*!< Device to open */
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object Uart
      //!
      ~UartComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for read
      //!
      void read_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer fwBuffer /*!< Buffer whose data pointer will be filled */
      );

      //! Handler implementation for write
      //!
      void write_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer fwBuffer /*!< Buffer whose data pointer will be used */
      );
      // ----------------------------------------------------------------------
      // Specific implementations for helper functions
      // ----------------------------------------------------------------------

      //! Used to setup the UART in a specific way, fills m_handle and sets
      //! m_setup when complete. Is called on every request, if m_setup not set.
      //!
      void setup();
      //! Reads the UART device from the UART handle in a specific way
      //!
      void read_uart(
          Fw::Buffer& fwBuffer /*!< Buffer whose data pointer will be filled */
      );

      //! Writes to the UART device from the UART handle in a specific way
      //!
      void write_uart(
          Fw::Buffer& fwBuffer /*!< Buffer whose data pointer will be used */
      );
      POINTER_CAST m_device; //!< Used to capture a device number, or device path
      NATIVE_INT_TYPE m_handle; //!< Handle used to identify the opened device
      bool m_setup; //!< Was setup successful

    };

} // end namespace Drv

#endif
