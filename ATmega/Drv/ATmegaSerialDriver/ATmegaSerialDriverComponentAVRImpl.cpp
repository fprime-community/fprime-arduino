// ======================================================================
// \title  ATmegaSerialDriverComponentAVRImpl
// \author Andrew Fear <afear@gatech.edu>
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <avr/io.h>
#include <avr/interrupt.h>

namespace Drv {

  U8 readBufferData[DR_MAX_NUM_BUFFERS];
  Types::CircularBuffer readBuffer(readBufferData,DR_MAX_NUM_BUFFERS);

  bool ATmegaSerialDriverComponentImpl ::
    open(
        UartDevice device,
        UartBaudRate baud,
        UartParity parity
    )
  {
      /* TODO: Make device switch registers to use
      switch(device) {
          case USART0:
            break;
          case USART1:
            break;
          default:
            break;
            FW_ASSERT(0,device);
      }
      */

      NATIVE_UINT_TYPE relayRate = 0;
      switch (baud) {
          case BAUD_9600:
              relayRate = 9600;
              break;
          case BAUD_19200:
              relayRate = 19200;
              break;
          case BAUD_38400:
              relayRate = 38400;
              break;
          case BAUD_57600:
              relayRate = 57600;
              break;
          case BAUD_115K:
              relayRate = 115200;
              break;
          default:
              FW_ASSERT(0,baud);
              break;
      }

      // Set Baud rate register
      UBRR1L = (F_CPU / (16UL * relayRate)) - 1;

      // Set TX/RX enable and interrupts
      UCSR1B = (1 << RXEN1) | _BV(TXEN1);

      // Set frame format: 8N1
      UCSR1C = (3 << UCSZ10);

      // Enable Receive interrupt
      UCSR1B |= (1 << RXCIE1);
      sei();

      return true;
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaSerialDriverComponentImpl ::
    serialRecv_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer,
        SerialReadStatus &status
    )
  {
    // TODO
      serBuffer.setSize(readBuffer.get_remaining_size(false));
      readBuffer.peek((U8*)serBuffer.getData(), readBuffer.get_remaining_size(false));
      readBuffer.rotate(readBuffer.get_remaining_size(false));
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSend_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer
    )
  {
      transmit((U8*)serBuffer.getData(), serBuffer.getSize());
  }

  void ATmegaSerialDriverComponentImpl ::
    serialRecvFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    // TODO
      fwBuffer.setSize(readBuffer.get_remaining_size(false));
      readBuffer.peek((U8*)fwBuffer.getData(), readBuffer.get_remaining_size(false));
      readBuffer.rotate(readBuffer.get_remaining_size(false));
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSendFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
      transmit((U8*)fwBuffer.getData(), fwBuffer.getSize());
  }

  void ATmegaSerialDriverComponentImpl ::
    transmit(
        U8* data, const NATIVE_UINT_TYPE len
    )
  {
      for (NATIVE_UINT_TYPE i = 0; i < len; i++) {
        while ( !(UCSR1A & (1 << UDRE1)) );
          UDR1 = data[i];
      }
  }

  ISR(USART1_RX_vect)
  {
      U8 data;
      data = UDR1;
      FW_ASSERT(readBuffer.serialize(&data,1) == Fw::FW_SERIALIZE_OK);
        // TODO: Error or something?
  }

} // end namespace Drv
