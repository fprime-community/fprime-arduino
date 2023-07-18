// ======================================================================
// \title  SpiDriver.cpp
// \author ethanchee
// \brief  cpp file for SpiDriver component implementation class
// ======================================================================


#include <Arduino/Drv/SpiDriver/SpiDriver.hpp>
#include <FpConfig.hpp>
#include "Fw/Types/Assert.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SpiDriver ::
    SpiDriver(
        const char *const compName
    ) : SpiDriverComponentBase(compName),
        m_port_pointer(static_cast<POINTER_CAST>(NULL))
  {

  }

  SpiDriver ::
    ~SpiDriver()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void SpiDriver ::
    SpiReadWrite_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
    FW_ASSERT(readBuffer.getData());
    FW_ASSERT(writeBuffer.getData());

    read_write_data(readBuffer, writeBuffer);
  }

} // end namespace Arduino
