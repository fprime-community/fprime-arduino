// ======================================================================
// \title  ATmegaSpiDriverComponentImplCommon.cpp
// \author vagrant
// \brief  cpp file for ATmegaSpiDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <ATmega/Drv/ATmegaSpiDriver/ATmegaSpiDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaSpiDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaSpiDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaSpiDriverComponentBase(compName)
#else
    ATmegaSpiDriverComponentImpl(void)
#endif
  {

  }

  void ATmegaSpiDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaSpiDriverComponentBase::init(instance);
  }

  ATmegaSpiDriverComponentImpl ::
    ~ATmegaSpiDriverComponentImpl(void)
  {

  }

} // end namespace Drv
