// ======================================================================
// \title  GpioDriverImpl.cpp
// \author lestarch
// \brief  cpp file for GpioDriver component implementation class
// ======================================================================

#include <Arduino/Drv/GpioDriver/GpioDriver.hpp>
#include <FpConfig.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

GpioDriver ::GpioDriver(const char* const compName)
    : GpioDriverComponentBase(compName), m_pin(-1) {}

void GpioDriver ::init(const NATIVE_INT_TYPE instance) {
    GpioDriverComponentBase::init(instance);
}

GpioDriver ::~GpioDriver() {}

}  // end namespace Drv
