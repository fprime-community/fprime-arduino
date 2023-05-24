// ======================================================================
// \title  ATmegaSerialDriverComponentLinuxImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Log/LogString.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>

#ifndef USART0_LINUX_DEVICE
  #define USART0_LINUX_DEVICE "/dev/ttyUSB0"
#endif
#ifndef USART1_LINUX_DEVICE
  #define USART1_LINUX_DEVICE "/dev/ttyUSB1"
#endif

#define DEBUG_PRINT(x,...) printf(x,##__VA_ARGS__); fflush(stdout)
// #define DEBUG_PRINT(x,...)

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
      NATIVE_INT_TYPE fd;
      NATIVE_INT_TYPE stat;
      const char* dev_str;

      this->m_device = device;

      switch (device) {
          case USART0:
              dev_str = USART0_LINUX_DEVICE;
              break;
          case USART1:
              dev_str = USART1_LINUX_DEVICE;
              break;
          default:
              FW_ASSERT(0,device);
              break;
      }

      DEBUG_PRINT("Opening UART device %s\n", dev_str);

      // TODO cant use O_NDELAY and block (it is same as O_NONBLOCK), so removing NDELAY for now
      /*
       The O_NOCTTY flag tells UNIX that this program doesn't want to be the "controlling terminal" for that port. If you don't specify this then any input (such as keyboard abort signals and so forth) will affect your process. Programs like getty(1M/8) use this feature when starting the login process, but normally a user program does not want this behavior.

       The O_NDELAY flag tells UNIX that this program doesn't care what state the DCD signal line is in - whether the other end of the port is up and running. If you do not specify this flag, your process will be put to sleep until the DCD signal line is the space voltage.
       */
      fd = ::open(dev_str, O_RDWR | O_NOCTTY | O_NDELAY);
      //fd = open(device, O_RDWR | O_NONBLOCK | O_SYNC);

      if (fd == -1) {
          DEBUG_PRINT("open UART device %s failed.\n", dev_str);
          // Fw::LogStringArg _arg = dev_str;
          // Fw::LogStringArg _err = strerror(errno);
          // this->log_WARNING_HI_DR_OpenError(_arg,this->m_fd,_err);
          return false;
      } else {
          DEBUG_PRINT("Successfully opened UART device %s fd %d\n", dev_str, fd);
      }


      switch (device) {
          case USART0:
              this->m_fd[0] = fd;
              break;
          case USART1:
              this->m_fd[1] = fd;
              break;
          default:
              FW_ASSERT(0,device);
              break;
      }

      // Configure blocking reads
      struct termios cfg;

      stat = tcgetattr(fd,&cfg);
      if (-1 == stat) {
          DEBUG_PRINT("tcgetattr failed: (%d): %s\n",stat,strerror(errno));
          close(fd);
          // Fw::LogStringArg _arg = device;
          // Fw::LogStringArg _err = strerror(errno);
          // this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
          return false;
      } else {
          DEBUG_PRINT("tcgetattr passed.\n");
      }

      /*
       If MIN > 0 and TIME = 0, MIN sets the number of characters to receive before the read is satisfied. As TIME is zero, the timer is not used.

       If MIN = 0 and TIME > 0, TIME serves as a timeout value. The read will be satisfied if a single character is read, or TIME is exceeded (t = TIME *0.1 s). If TIME is exceeded, no character will be returned.

       If MIN > 0 and TIME > 0, TIME serves as an inter-character timer. The read will be satisfied if MIN characters are received, or the time between two characters exceeds TIME. The timer is restarted every time a character is received and only becomes active after the first character has been received.

       If MIN = 0 and TIME = 0, read will be satisfied immediately. The number of characters currently available, or the number of characters requested will be returned. According to Antonino (see contributions), you could issue a fcntl(fd, F_SETFL, FNDELAY); before reading to get the same result.
       */
      // wait for at least 1 byte for 1 second
      // TODO VMIN should be 0 when using VTIME, and then it would give the timeout behavior Tim wants
      cfg.c_cc[VMIN] = 0; // TODO back to 0
      cfg.c_cc[VTIME] = 1; // 1 sec, TODO back to 10

      stat = tcsetattr(fd,TCSANOW,&cfg);
      if (-1 == stat) {
          DEBUG_PRINT("tcsetattr failed: (%d): %s\n",stat,strerror(errno));
          close(fd);
          // Fw::LogStringArg _arg = device;
          // Fw::LogStringArg _err = strerror(errno);
          // this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
          return false;
      } else {
          DEBUG_PRINT("tcsetattr passed.\n");
      }

      // Set flow control
      // TODO: Fix if somebody needs to use hardware flow control
      // if (fc == HW_FLOW) {

      //     struct termios t;

      //     int stat = tcgetattr(fd, &t);
      //     if (-1 == stat) {
      //         DEBUG_PRINT("tcgetattr UART fd %d failed\n", fd);
      //         close(fd);
      //         Fw::LogStringArg _arg = device;
      //         Fw::LogStringArg _err = strerror(errno);
      //         this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
      //         return false;
      //     }

      //     // modify flow control flags
      //     t.c_cflag |= CRTSCTS;

      //     stat = tcsetattr(fd, TCSANOW, &t);
      //     if (-1 == stat) {
      //         DEBUG_PRINT("tcsetattr UART fd %d failed\n", fd);
      //         close(fd);
      //         Fw::LogStringArg _arg = device;
      //         Fw::LogStringArg _err = strerror(errno);
      //         this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
      //         return false;
      //     }
      // }

      NATIVE_INT_TYPE relayRate = B0;
      switch (baud) {
          // TODO add more as needed
          case BAUD_9600:
              relayRate = B9600;
              break;
          case BAUD_19200:
              relayRate = B19200;
              break;
          case BAUD_38400:
              relayRate = B38400;
              break;
          case BAUD_57600:
              relayRate = B57600;
              break;
          case BAUD_115K:
              relayRate = B115200;
              break;
          default:
              FW_ASSERT(0,baud);
              break;
      }

      struct termios newtio;

      stat = tcgetattr(fd, &newtio);
      if (-1 == stat) {
          DEBUG_PRINT("tcgetattr UART fd %d failed\n", fd);
          close(fd);
          // Fw::LogStringArg _arg = device;
          // Fw::LogStringArg _err = strerror(errno);
          // this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
          return false;
      }

      // CS8 = 8 data bits, CLOCAL = Local line, CREAD = Enable Reciever
      // TODO PARENB for parity bit
      /*
        Even parity (7E1):
        options.c_cflag |= PARENB
        options.c_cflag &= ~PARODD
        options.c_cflag &= ~CSTOPB
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS7;
        Odd parity (7O1):
        options.c_cflag |= PARENB
        options.c_cflag |= PARODD
        options.c_cflag &= ~CSTOPB
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS7;
       */
      newtio.c_cflag = CS8 | CLOCAL | CREAD;

      switch (parity) {
          case PARITY_ODD:
              newtio.c_cflag |= (PARENB | PARODD) ;
              break;
          case PARITY_EVEN:
              newtio.c_cflag |= PARENB ;
              break;
          case PARITY_NONE:
              newtio.c_cflag &= ~PARENB ;
              break;
          default:
              FW_ASSERT(0,parity);
              break;
      }

      // Set baud rate:
      stat = cfsetispeed(&newtio, relayRate);
      stat = cfsetospeed(&newtio, relayRate);

      // Raw output:
      newtio.c_oflag = 0;

      // set input mode (non-canonical, no echo,...)
      newtio.c_lflag = 0;

      // TODO if parity, then do input parity too
      //options.c_iflag |=INPCK;
      newtio.c_iflag = INPCK;

      // Flush old data:
      (void) tcflush(fd, TCIFLUSH);

      // Set attributes:
      stat = tcsetattr(fd,TCSANOW,&newtio);
      if (-1 == stat) {
          DEBUG_PRINT("tcsetattr UART fd %d failed\n", fd);
          close(fd);
          // Fw::LogStringArg _arg = device;
          // Fw::LogStringArg _err = strerror(errno);
          // this->log_WARNING_HI_DR_OpenError(_arg,fd,_err);
          return false;
      }

      // All done!
      // Fw::LogStringArg _arg = device;
      // this->log_ACTIVITY_HI_DR_PortOpened(_arg);
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
    const char* dev_str;
    int sizeRead = 0;
    int stat = 0;

    switch (portNum) {
        case 0:
            dev_str = USART0_LINUX_DEVICE;
            break;
        case 1:
            dev_str = USART1_LINUX_DEVICE;
            break;
        default:
            FW_ASSERT(0,portNum);
            break;
    }

    stat = ::read(this->m_fd[portNum],
                  reinterpret_cast<unsigned char*>(serBuffer.getData()),
                  serBuffer.getSize());

    // TODO: add stat value to telemetry for bytes read
    if (stat > 0) {
        sizeRead = stat;
    }

    // check for timeout
    if (0 == stat) {
      // we timed out. so return an empty buffer.
    }

    // check stat, maybe output event
    if (stat == -1) {
        // Fw::LogStringArg _arg = dev_str;
        // comp->log_WARNING_HI_DR_ReadError(_arg,stat);
        status = Drv::SER_OTHER_ERR;
    } else {
        serBuffer.setSize(sizeRead);
        status = Drv::SER_OK;
        //comp->serialRecv_out(0,buff,Drv::SER_OK);
    }
    this->m_UartBytesRecv[portNum] += serBuffer.getSize();
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSend_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &serBuffer
    )
  {
    const char* dev_str;

    switch (portNum) {
        case 0:
            dev_str = USART0_LINUX_DEVICE;
            break;
        case 1:
            dev_str = USART1_LINUX_DEVICE;
            break;
        default:
            FW_ASSERT(0,portNum);
            break;
    }

    if (this->m_fd[portNum] == -1) {
      return;
    }

    unsigned char* data = reinterpret_cast<unsigned char*>(serBuffer.getData());
    NATIVE_INT_TYPE xferSize = serBuffer.getSize();

    NATIVE_INT_TYPE stat = ::write(this->m_fd[portNum],data,xferSize);

    // TODO no need to delay for writes b/c the write blocks
    // not sure if it will block until everything is transmitted, but seems to

    if (-1 == stat || stat != xferSize) {
      DEBUG_PRINT("Write to UART device %s failed.\n", dev_str);
      // Fw::LogStringArg _arg = this->m_device;
      // this->log_WARNING_HI_DR_WriteError(_arg,stat);
    }
    this->m_UartBytesSent[portNum] += serBuffer.getSize();
  }

  void ATmegaSerialDriverComponentImpl ::
    serialRecvFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    const char* dev_str;
    int sizeRead = 0;
    int stat = 0;

    switch (portNum) {
        case 0:
            dev_str = USART0_LINUX_DEVICE;
            break;
        case 1:
            dev_str = USART1_LINUX_DEVICE;
            break;
        default:
            FW_ASSERT(0,portNum);
            break;
    }

    stat = ::read(this->m_fd[portNum],
                  reinterpret_cast<unsigned char*>(fwBuffer.getData()),
                  fwBuffer.getSize());

    // TODO: add stat value to telemetry for bytes read
    if (stat > 0) {
        sizeRead = stat;
    }

    // check for timeout
    if (0 == stat) {
      // we timed out. so return an empty buffer.
    }

    // check stat, maybe output event
    if (stat == -1) {
        // Fw::LogStringArg _arg = dev_str;
        // comp->log_WARNING_HI_DR_ReadError(_arg,stat);
        // serReadStat = Drv::SER_OTHER_ERR;
    } else {
        fwBuffer.setSize(sizeRead);
        // serReadStat = Drv::SER_OK;
        //comp->serialRecv_out(0,buff,Drv::SER_OK);
    }
    this->m_UartBytesRecv[portNum] += fwBuffer.getSize();
  }

  void ATmegaSerialDriverComponentImpl ::
    serialSendFwBuf_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    const char* dev_str;

    switch (portNum) {
        case 0:
            dev_str = USART0_LINUX_DEVICE;
            break;
        case 1:
            dev_str = USART1_LINUX_DEVICE;
            break;
        default:
            FW_ASSERT(0,portNum);
            break;
    }

    if (this->m_fd[portNum] == -1) {
        return;
    }

    unsigned char* data = reinterpret_cast<unsigned char*>(fwBuffer.getData());
    NATIVE_INT_TYPE xferSize = fwBuffer.getSize();

    NATIVE_INT_TYPE stat = ::write(this->m_fd[portNum],data,xferSize);

    // TODO no need to delay for writes b/c the write blocks
    // not sure if it will block until everything is transmitted, but seems to

    if (-1 == stat || stat != xferSize) {
      DEBUG_PRINT("Write to UART device %s failed.\n", dev_str);
      // Fw::LogStringArg _arg = this->m_device;
      // this->log_WARNING_HI_DR_WriteError(_arg,stat);
    }
    this->m_UartBytesSent[portNum] += fwBuffer.getSize();
  }

} // end namespace Drv
