// ======================================================================
// \title  ATmegaI2cDriverComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================

#ifndef ATmegaI2cDriver_HPP
#define ATmegaI2cDriver_HPP

#include <Os/IntervalTimer.hpp>
#include "ATmega/Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentAc.hpp"

namespace Drv {

  class ATmegaI2cDriverComponentImpl :
    public ATmegaI2cDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaI2cDriver
      //!
      ATmegaI2cDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaI2cDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! I2C Parameters.
      typedef enum SCL_RATE {
        SCL_100KHZ,
        SCL_400KHZ,
        SCL_1MHZ,
      } I2cClockRate;

      //! Open device with specified clock rate.
      void config(I2cClockRate scl_rate);

      //! Set timeout value in microseconds.
      //! Default is 50, approximately 2 byte transactions plus 10
      //! percent at 400 kHz SCL.
      //!
      void setTimeout(NATIVE_UINT_TYPE timeout);

      //! Destroy object ATmegaI2cDriver
      //!
      ~ATmegaI2cDriverComponentImpl(void);

    PRIVATE:
      typedef enum I2C_DRV_STATE {
        TRANS_IDLE,
        TRANS_IN_PROGRESS,
      } I2cDrvState;

      I32 m_freq; /*!< The I2C device speed*/
      bool m_err_flag;
      Os::IntervalTimer m_timer;
      Drv::I2cStatus m_return; /*!< Status for port return value*/
      NATIVE_UINT_TYPE m_timeout; /*!< Timeout value for I2C transaction events*/
      volatile I2cDrvState m_state;


      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for i2cRead
      //!
      Drv::I2cStatus i2cTransaction_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 slaveAddress, /*!< I2C slave address of the device*/
          Fw::Buffer &writeBuffer, /*!< Buffer containing write data*/
          Fw::Buffer &readBuffer /*!< Buffer containing data*/
      );

      //! Transaction execution logic
      Drv::I2cStatus execute_txn(
          U8 slaveAddress, /*!< I2C slave address of the device*/
          Fw::Buffer &writeBuffer, /*!< Buffer containing write data*/
          Fw::Buffer &readBuffer /*!< Buffer containing data*/
      );

      //! Check that we are in a sane state, and do our best to reset if not
      void check_start_state(void);

      //! Transmit an I2C start condition
      void start(void);

      //! Transmit an I2C stop condition
      void stop(void);

      //! Transmit data
      void transmit(U8 address, U8* data, U32 len);

      //! Receive data
      void receive(U8 address, U8* data, U32 len);

      //! Write a byte
      void write(U8 data);

      //! Read and request an Ack
      U8 readAck(void);

      //! Read and request NAck
      U8 readNack(void);

      //! Two Wire Timeout helper
      void TW_timeout(U8 twcr);
    };

} // end namespace Drv

#endif
