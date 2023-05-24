// ======================================================================
// \title  ATmegaSerialDriverComponentArduinoImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>

#include <Arduino.h>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  bool ATmegaSerialDriverComponentImpl ::
    open(
        UartDevice device,
        UartBaudRate baud,
        UartParity parity
    )
  {
      HardwareSerial* serPort;
      switch(device) {
          case USART0:
            serPort = &Serial;
            break;
          case USART1:
            serPort = &Serial1;
            break;
          default:
            FW_ASSERT(0,device);
            break;
      }

      I32 relayRate = 0;
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

      // Start the serial device
      serPort->begin(relayRate);

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
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    NATIVE_INT_TYPE i = 0;
    U8* readBuf = reinterpret_cast<U8*>(serBuffer.getData());
    FW_ASSERT(serBuffer.getSize()>0, serBuffer.getSize());
    while(serPort->available() > 0 && i < serBuffer.getSize())
    {
      readBuf[i] = serPort->read();
      i++;
    }
    serBuffer.setSize(i);
    this->m_UartBytesRecv[portNum] += i;
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSend_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    FW_ASSERT(serBuffer.getSize()>0, serBuffer.getSize());
    serPort->write((U8*)serBuffer.getData(), serBuffer.getSize());
    this->m_UartBytesSent[portNum] += serBuffer.getSize();
  }

  void ATmegaSerialDriverComponentImpl ::
    serialRecvFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    NATIVE_INT_TYPE i = 0;
    U8* readBuf = reinterpret_cast<U8*>(fwBuffer.getData());
    FW_ASSERT(fwBuffer.getSize()>0, fwBuffer.getSize());
    while(serPort->available() > 0 && i < fwBuffer.getSize())
    {
      readBuf[i] = serPort->read();
      i++;
    }
    fwBuffer.setSize(i);
    this->m_UartBytesRecv[portNum] += i;
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSendFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    HardwareSerial* serPort;
    if(portNum == 0)
    {
      serPort = &Serial;
    }
    else
    {
      serPort = &Serial1;
    }
    FW_ASSERT(fwBuffer.getSize()>0, fwBuffer.getSize());
    serPort->write((U8*)fwBuffer.getData(), fwBuffer.getSize());
    this->m_UartBytesSent[portNum] += fwBuffer.getSize();
  }

} // end namespace Drv
