// ======================================================================
// \title  ATmegaI2cDriverComponentImplLinux.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================

#include "ATmega/Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  void ATmegaI2cDriverComponentImpl ::
    config(
        I2cClockRate scl_rate
    )
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  //! Transmit an I2C start condition
  void ATmegaI2cDriverComponentImpl ::
    start(void)
  {

  }

  //! Transmit an I2C stop condition
  void ATmegaI2cDriverComponentImpl ::
    stop(void)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    transmit(U8 address, U8* data, U32 len)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    receive(U8 address, U8* data, U32 len)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    write(U8 data)
  {

  }

  U8 ATmegaI2cDriverComponentImpl ::
    readAck(void)
  {
    return 0;
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readNack(void)
  {
    return 0;
  }

  void ATmegaI2cDriverComponentImpl ::
    TW_timeout(U8 twcr)
  {

  }

} // end namespace Drv
