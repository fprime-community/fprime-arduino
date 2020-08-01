// ====================================================================== 
// \title  GpsImpl.cpp
// \author lestarch
// \brief  cpp implementation of the Linux UART readiing
//
// \copyright
// Copyright 2018, lestarch.
// ====================================================================== 

#include <Drv/Uart/UartComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

//File path to UART device on UNIX system
#include <cstring>
#include <iostream>
//POSIX includes for UART communication
extern "C" {
    #include <unistd.h>
    #include <fcntl.h>
    #include <termios.h>
}

namespace Drv {

  void UartComponentImpl ::
    setup(void)
  {
      if (m_setup) {
          return;
      }
      //Open the UART, and configure it for a raw-socket in read-only mode
      m_handle = open(reinterpret_cast<char*>(m_handle), O_RDONLY);
      if (m_handle < 0) {
          std::cerr << "[ERROR] Failed to open file: " << reinterpret_cast<char*>(m_handle) << std::endl;
          return;
      }
      //Setup the struct for termios configuration
      struct termios options;
      std::memset(&options, 0, sizeof(options));
      //Set to raw socket, remove modem control, allow input
      cfmakeraw(&options);
      options.c_cflag |= (CLOCAL | CREAD);
      //Set to 9600 baud
      cfsetispeed(&options, B9600);
      //Make the above options stick
      NATIVE_INT_TYPE status = tcsetattr(m_handle, TCSANOW, &options);
      if (status != 0) {
          std::cerr << "[ERROR] Failed to setup UART options" << std::endl;
          return;
      }
      m_setup = true;
  }
  
  void UartComponentImpl ::
    read_uart(Fw::Buffer& buffer)
  {
      ssize_t size;
      if (!m_setup) {
          setup();
      }
      size = read(m_handle, reinterpret_cast<U8*>(buffer.getdata()), 
                  static_cast<size_t>(buffer.getsize()));
      if (size <= 0) {
          std::cerr << "[ERROR] Failed to read from UART with: " << size << std::endl;
          return;
      }
      buffer.setsize(static_cast<NATIVE_UINT_TYPE>(size));
  }

  void UartComponentImpl ::
    write_uart(Fw::Buffer& buffer)
  {
      ssize_t size;
      if (!m_setup) {
          setup();
      }
      size = write(m_handle, reinterpret_cast<U8*>(buffer.getdata()),
                   static_cast<size_t>(buffer.getsize()));
      if (size <= 0) {
          std::cerr << "[ERROR] Failed to read from UART with: " << size << std::endl;
          return;
      }
  }
} // end namespace Drv
