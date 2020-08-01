// ====================================================================== 
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ====================================================================== 


#include <fprime-arduino/ArduinoDrv/SerialDriver/SerialDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SERIAL_FILE_LINUX_TMPL "/dev/pts/%d"

namespace Arduino {
  char** SERIAL_PORT = NULL;
  void SerialDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const NATIVE_UINT_TYPE baud
    ) 
  {
    char name[1024];
    SerialDriverComponentBase::init(instance);
    // NULL ports use above template
    if (SERIAL_PORT == NULL) {
        snprintf(name, 1024, SERIAL_FILE_LINUX_TMPL, m_port_number + 20);
        SERIAL_PORT = reinterpret_cast<char**>(&name);
    }
    printf("Opening serial port: '%s'\n", *SERIAL_PORT);
    m_port_pointer = open(*SERIAL_PORT, O_RDWR);
    int flags = fcntl(m_port_pointer, F_GETFL, 0);
    fcntl(m_port_pointer, F_SETFL, flags | O_NONBLOCK);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SerialDriverComponentImpl ::
    write_data(
        Fw::Buffer &fwBuffer
    )
  {
      if (m_port_pointer != -1) {
          write(m_port_pointer, reinterpret_cast<U8*>(fwBuffer.getdata()),fwBuffer.getsize());
      }
  }

  void SerialDriverComponentImpl ::
    read_data(Fw::Buffer &fwBuffer)
  {
      NATIVE_INT_TYPE result;
      if ((m_port_pointer != -1) && (-1 != (result = read(m_port_pointer, reinterpret_cast<U8*>(fwBuffer.getdata()), fwBuffer.getsize())))) {
          fwBuffer.setsize(result);
      }
      else {
          fwBuffer.setsize(0);
      }
  }
} // end namespace Svc
