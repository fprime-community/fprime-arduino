// ======================================================================
// \title  ATmegaSerialDriverComponentImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu
// \brief  UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include <ATmega/Drv/ATmegaSerialDriver/ATmegaSerialDriverComponentImpl.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BasicTypes.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaSerialDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaSerialDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaSerialDriverComponentBase(compName)
#else
    ATmegaSerialDriverComponentImpl(void)
#endif
  {
    this->m_UartBytesSent[0] = 0;
    this->m_UartBytesSent[1] = 0;
    this->m_UartBytesRecv[0] = 0;
    this->m_UartBytesRecv[1] = 0;
  }

  void ATmegaSerialDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaSerialDriverComponentBase::init(instance);
  }

  ATmegaSerialDriverComponentImpl ::
    ~ATmegaSerialDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaSerialDriverComponentImpl ::
    reportTlm_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    tlmWrite_UART0_Bytes_Sent(this->m_UartBytesSent[0]);
    tlmWrite_UART1_Bytes_Sent(this->m_UartBytesSent[1]);
    tlmWrite_UART0_Bytes_Recv(this->m_UartBytesRecv[0]);
    tlmWrite_UART1_Bytes_Recv(this->m_UartBytesRecv[1]);
  }

} // end namespace Drv
