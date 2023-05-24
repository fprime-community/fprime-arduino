// ======================================================================
// \title  ATmegaGpioDriverImpl.cpp
// \author Sterling Peet
// \brief  cpp file for ATmegaGpioDriver component implementation class
// ======================================================================


#include <ATmega/Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaGpioDriverComponentImpl ::
    gpioRead_handler(
        const NATIVE_INT_TYPE portNum,
        bool &state
    )
  {
    // TODO
  }

  void ATmegaGpioDriverComponentImpl ::
    gpioWrite_handler(
        const NATIVE_INT_TYPE portNum,
        bool state
    )
  {
    // TODO
  }

  bool ATmegaGpioDriverComponentImpl ::
    open(NATIVE_INT_TYPE gpio, GpioDirection direction) {
      return false;
  }

  Os::Task::TaskStatus ATmegaGpioDriverComponentImpl ::
    startIntTask(NATIVE_INT_TYPE priority, NATIVE_INT_TYPE cpuAffinity) {
     return Os::Task::TASK_OK;
   }

  ATmegaGpioDriverComponentImpl ::
    ~ATmegaGpioDriverComponentImpl(void)
  {

  }

  void ATmegaGpioDriverComponentImpl ::
    exitThread(void) {
  }
} // end namespace Drv
