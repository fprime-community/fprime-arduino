// ====================================================================== 
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ====================================================================== 


#include <fprime-arduino/ArduinoDrv/SerialDriver/SerialDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Arduino.h>
#include <Os/Log.hpp>

namespace Arduino {

  void SerialDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const NATIVE_UINT_TYPE baud
    )
  {
      SerialDriverComponentBase::init(instance);
      switch (m_port_number) {
          case 0:
              m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial);
              break;
          case 1:
              m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial1);
              break;
          case 2:
              m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial2);
              break;
          case 3:
              m_port_pointer = reinterpret_cast<POINTER_CAST>(&Serial3);
              break;
      }
      reinterpret_cast<HardwareSerial*>(m_port_pointer)->begin(baud);
      reinterpret_cast<HardwareSerial*>(m_port_pointer)->setTimeout(4);
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SerialDriverComponentImpl ::
    write_data(
        Fw::Buffer &fwBuffer
    )
  {
      reinterpret_cast<HardwareSerial*>(m_port_pointer)->write(reinterpret_cast<U8*>(fwBuffer.getdata()),fwBuffer.getsize());
  }

  void SerialDriverComponentImpl ::
    read_data(Fw::Buffer& fwBuffer)
  {
      NATIVE_UINT_TYPE read = reinterpret_cast<HardwareSerial*>(m_port_pointer)->
                              readBytes(reinterpret_cast<U8*>(fwBuffer.getdata()), fwBuffer.getsize());
      fwBuffer.setsize(read);
  }
} // end namespace Svc
