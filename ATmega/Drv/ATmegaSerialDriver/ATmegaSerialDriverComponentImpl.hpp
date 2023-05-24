// ======================================================================
// \title  ATmegaSerialDriverComponentImpl.hpp
// \author Andrew Fear <afear@gatech.edu>
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================

#ifndef ATmegaSerialDriver_HPP
#define ATmegaSerialDriver_HPP

#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentAc.hpp>
#include <Utils/Types/CircularBuffer.hpp>

namespace Drv {

  class ATmegaSerialDriverComponentImpl :
    public ATmegaSerialDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaSerialDriver
      //!
      ATmegaSerialDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaSerialDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure UART parameters
      typedef enum DEVICE {
        USART0,
        USART1
      } UartDevice;

      typedef enum BAUD_RATE {
          BAUD_9600,
          BAUD_19200,
          BAUD_38400,
          BAUD_57600,
          BAUD_115K
      } UartBaudRate;

      typedef enum PARITY  {
          PARITY_NONE,
          PARITY_ODD,
          PARITY_EVEN
      } UartParity;

      //! Open device with specified baud and parity.
      //!   This must be called for each UART that will be used.
      //!
      bool open(UartDevice device, UartBaudRate baud, UartParity parity);

      //! Destroy object ATmegaSerialDriver
      //!
      ~ATmegaSerialDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for reportTlm
      //!
      void reportTlm_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Handler implementation for serialRecv
      //!
      void serialRecv_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &serBuffer, /*!< Buffer containing data*/
          SerialReadStatus &status /*!< Status of read*/
      );

      //! Handler implementation for serialSend
      //!
      void serialSend_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &serBuffer
      );

      //! Handler implementation for serialRecvFwBuf
      //!
      void serialRecvFwBuf_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer /*!< Buffer containing data*/
      );

      //! Handler implementation for serialSendFwBuf
      //!
      void serialSendFwBuf_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer
      );

      //! Transmit a byte array
      //!
      void transmit(
          U8* data, /*!< Pointer to data buffer*/
          const NATIVE_UINT_TYPE len  /*!< Length of data to transmit*/
      );

      UartDevice m_device;  //!< USART device
      U32 m_UartBytesSent[2];
      U32 m_UartBytesRecv[2];

#ifndef __avr__
      NATIVE_INT_TYPE m_fd[2]; //!< file descriptor returned for I/O device
#endif

    };

} // end namespace Drv

#endif
