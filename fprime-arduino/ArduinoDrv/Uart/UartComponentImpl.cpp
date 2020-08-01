// ====================================================================== 
// \title  UartImpl.cpp
// \author starchmd
// \brief  cpp file for Uart component implementation class
//
// \copyright
// Copyright 2018, LeStarch
// ====================================================================== 


#include <Drv/Uart/UartComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  UartComponentImpl ::
#if FW_OBJECT_NAMES == 1
    UartComponentImpl(
        const char *const compName
    ) :
      UartComponentBase(compName)
#else
    UartImpl(void)
#endif
  {

  }

  void UartComponentImpl ::
    init(
        const POINTER_CAST device,
        const NATIVE_INT_TYPE instance
    ) 
  {
    UartComponentBase::init(instance);
    m_device = device;
    setup();
  }

  UartComponentImpl ::
    ~UartComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void UartComponentImpl ::
    read_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer fwBuffer
    )
  {
    read_uart(fwBuffer);
  }

  void UartComponentImpl ::
    write_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer fwBuffer
    )
  {
    write_uart(fwBuffer);
  }

} // end namespace Drv
