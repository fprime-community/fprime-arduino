// ======================================================================
// \title  ATmegaI2cDriverComponentImpl.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include "ATmega/Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"


// TODO: Separate the code cleanly enough that AVR specific things are
//       all in the AVR Impl cpp file.
#ifdef __AVR__
  #include <util/atomic.h>
#endif

#if defined(DEBUG_I2C_AVR) || defined(DEBUG_I2C_AVR_Q) || defined(DEBUG_I2C_AVR_TRANS)
  #ifdef ARDUINO
    #include <Arduino.h>
    #ifndef DEBUG_Serial
      #define DEBUG_Serial Serial
    #endif
  #endif
#endif

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaI2cDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaI2cDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaI2cDriverComponentBase(compName),
#else
    ATmegaI2cDriverComponentImpl(void) :
#endif
     m_freq(0)
    ,m_timeout(5000)
    ,m_state(I2C_DRV_STATE::TRANS_IDLE)
  {

  }

  void ATmegaI2cDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ATmegaI2cDriverComponentBase::init(instance);
    m_timer = Os::IntervalTimer();
  }

  void ATmegaI2cDriverComponentImpl ::
    setTimeout(NATIVE_UINT_TYPE timeout)
  {
    m_timeout = timeout;
  }

  ATmegaI2cDriverComponentImpl ::
    ~ATmegaI2cDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  Drv::I2cStatus ATmegaI2cDriverComponentImpl ::
    i2cTransaction_handler(
        const NATIVE_INT_TYPE portNum,
        U8 slaveAddress,
        Fw::Buffer &writeBuffer,
        Fw::Buffer &readBuffer
    )
  {
    // Slave address above 127 is a mistake, should only be using bottom 7 bits
    FW_ASSERT(slaveAddress < 128, slaveAddress, 128);

    // Check that at least one of the buffers is non-zero length
    FW_ASSERT(writeBuffer.getsize() > 0 || readBuffer.getsize() > 0);

    Drv::I2cStatus ret = I2cStatus::I2C_OK;

#ifdef DEBUG_I2C_AVR_TRANS
    DEBUG_Serial.print(F("I2c txn to "));
    DEBUG_Serial.println(slaveAddress);
    DEBUG_Serial.print(F("I2c state "));
    if(m_state == I2C_DRV_STATE::TRANS_IDLE)
    {
      DEBUG_Serial.println(F("IDLE"));
    }
    else
    {
      DEBUG_Serial.println(F("IN_PROG"));
    }
#endif

#ifdef __AVR__
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
#endif
#ifdef __AVR__
      // Temorarilty disable timer3 interrupt.
      // This is the only ISR that can lead to this function, so by disabling this, we should prevent
      // any reentrancy, at the cost of tangling this code with the ValveTimer code.
      // we will save the value, so we can restore it when we are done.
      uint8_t timer_mask_temp = ETIMSK;
      ETIMSK = 0;
#endif
      // If we are somehow reentering this code, something has failed.
      // To use this code with multiple ISRs, we need to go back to the queue implementation.
      FW_ASSERT(m_state == I2C_DRV_STATE::TRANS_IDLE);

#ifdef DEBUG_I2C_AVR_TRANS
      DEBUG_Serial.print(F("I2c txn to "));
      DEBUG_Serial.println(slaveAddress);
      DEBUG_Serial.print(F("I2c state "));
      if(m_state == I2C_DRV_STATE::TRANS_IDLE)
      {
        DEBUG_Serial.println(F("IDLE"));
      }
      else
      {
        DEBUG_Serial.println(F("IN_PROG"));
      }
#endif

#ifdef DEBUG_I2C_AVR_TRANS
      DEBUG_Serial.println(F("I2c Start TXN"));
#endif
      m_state = I2C_DRV_STATE::TRANS_IN_PROGRESS;

      // re-enable the ISRs (minus Timer3) for the slow I2C transaction
      NONATOMIC_BLOCK(NONATOMIC_FORCEOFF)
      {
      ret = this->execute_txn(slaveAddress,
                              writeBuffer,
                              readBuffer);
      }

    m_state = I2C_DRV_STATE::TRANS_IDLE;
#ifdef DEBUG_I2C_AVR_TRANS
    DEBUG_Serial.println(F("I2c State IDLE"));
#endif

#ifdef __AVR__
    //re-enable timer 3 interrupt
    ETIMSK = timer_mask_temp;
#endif

#ifdef __AVR__
    }
#endif

    return ret;
  }

  Drv::I2cStatus ATmegaI2cDriverComponentImpl ::
    execute_txn(
        U8 slaveAddress, /*!< I2C slave address of the device*/
        Fw::Buffer &writeBuffer, /*!< Buffer containing write data*/
        Fw::Buffer &readBuffer /*!< Buffer containing data*/
    )
  {
    this->m_err_flag = false;
    this->m_return = Drv::I2cStatus::I2C_OK;

    check_start_state();
    if (m_err_flag) { stop(); return m_return; }

    // Send start condition
    start();
    if (m_err_flag) { stop(); return m_return; }

    if (writeBuffer.getsize() != 0)
    {
      // Send data
      transmit(slaveAddress, (U8*)writeBuffer.getdata(), writeBuffer.getsize());
      if (m_err_flag) { stop(); return m_return; }

      if (readBuffer.getsize() != 0)
      {
        // Repeated start
        start();
        if (m_err_flag) { stop(); return m_return; }

        // Receive data
        receive(slaveAddress, (U8*)readBuffer.getdata(), readBuffer.getsize());
        if (m_err_flag) { stop(); return m_return; }
      }
    }
    else if(readBuffer.getsize() != 0)
    {
      // Receive data
      receive(slaveAddress, (U8*)readBuffer.getdata(), readBuffer.getsize());
      if (m_err_flag) { stop(); return m_return; }
    }

    // Send stop condition and release bus
    stop();

    return m_return;
  }

} // end namespace Drv
