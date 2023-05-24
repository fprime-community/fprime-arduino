// ======================================================================
// \title  ATmegaI2cDriverComponentImplAVR.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).
// ======================================================================


#include "ATmega/Drv/ATmegaI2cDriver/ATmegaI2cDriverComponentImpl.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

#include <avr/io.h>
#include <util/twi.h>

#include "Arduino.h"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  void ATmegaI2cDriverComponentImpl ::
    config(
        I2cClockRate scl_rate
    )
  {
    switch (scl_rate) {
      case SCL_100KHZ:
        m_freq = 100000L;
        break;
      case SCL_400KHZ:
        m_freq = 400000L;
        break;
      case SCL_1MHZ:
        // m_freq = 1000000L;
        FW_ASSERT(0); // Bus Frequency Not Supported
        break;
    }

    /*
     * From the ATmega128 datasheet:
     *  TWBR = ( (CPU Clock freq)/(SCL freq) - 16 ) / ( 2 * 4^(Prescalar value) )
     *
     * Disable prescalar value in TWSR and set TWBR according to CPU freq and SCL freq.
     */
    TWSR &= ~(_BV(TWPS1) | _BV(TWPS0));
    TWBR = ( (F_CPU/m_freq) - 16 ) / (2 * 1);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  //! Check that we are in a sane state, and do our best to reset if not
  void ATmegaI2cDriverComponentImpl ::
  check_start_state(void)
  {
    if(TWCR & ~(_BV(TWEN))) {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.print(F("Clearing TWCR"));
      DEBUG_Serial.println(TWCR, HEX);
#endif
      TWCR = _BV(TWEN);
      if(TWCR & _BV(TWSTO))
      {
        TWCR &= ~(_BV(TWSTO));
#ifdef DEBUG_I2C_AVR
        DEBUG_Serial.print(F("Clearing TWCR TWSTO"));
#endif
      }
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(TWCR, HEX);
#endif
    }

    //check that we're in a sane I2C state and try to recover if not
    if((TW_STATUS != TW_NO_INFO) || (TWCR & _BV(TWINT)))
    {
      TW_timeout(0);
#ifdef DEBUG_I2C_AVR
      if(this->m_err_flag)
      {
        DEBUG_Serial.print(F("I2C stuck at start."));
      }
      DEBUG_Serial.print(F("I2C bus in strange state "));
      DEBUG_Serial.println(TW_STATUS, HEX);
#endif
      stop();
      #ifdef DEBUG_I2C_AVR
      if(this->m_err_flag)
      {
        DEBUG_Serial.print(F("I2C timeout on bus reset."));
      }
      DEBUG_Serial.print(F("I2C now in state 2 "));
      DEBUG_Serial.println(TW_STATUS, HEX);
#endif
      this->m_err_flag = false;
    }
  }

  //! Transmit an I2C start condition
  void ATmegaI2cDriverComponentImpl ::
    start(void)
  {
    // Send start condition
    TW_timeout(_BV(TWINT) | _BV(TWSTA) | _BV(TWEN));

    if(this->m_err_flag)
    {
      m_return = Drv::I2cStatus::I2C_START_TIMEOUT_ERR;
    }

    // Check if start condition or repeated start condition was sucessfully transmitted
    if (TW_STATUS != TW_START && TW_STATUS != TW_REP_START) // TODO: this is not cross platform
    {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C Start Error State"));
      DEBUG_Serial.println(TW_STATUS, HEX);
      DEBUG_Serial.println(TWCR, HEX);
      DEBUG_Serial.println(TWSR, HEX);
#endif

      m_err_flag = true;
      m_return = Drv::I2cStatus::I2C_START_ERR;
    }
  }

  //! Transmit an I2C stop condition
  void ATmegaI2cDriverComponentImpl ::
    stop(void)
  {
    // Send stop condition
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
  }

  void ATmegaI2cDriverComponentImpl ::
    transmit(U8 address, U8* data, U32 len)
  {
    // Write the slave address
    write((address << 1) | TW_WRITE);
    if(m_err_flag)
    {
      return;
    }

    // Check if we received a NACK
    if ((TW_STATUS) == TW_MT_SLA_NACK)
    {
      m_err_flag = true;
      m_return = Drv:: I2cStatus::I2C_ADDRESS_ERR;
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C unexpected NACK"));
#endif
      return;
    }
    //check if we are in some other state
    if ((TW_STATUS) != TW_MT_SLA_ACK)
    {
      m_err_flag = true;
      m_return = Drv:: I2cStatus::I2C_OTHER_ERR;
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C in unexpected state tx"));
      DEBUG_Serial.println(TW_STATUS, HEX);
#endif
    }

    for (NATIVE_UINT_TYPE i = 0; i < len; i++)
    {
      write(data[i]);
      if(m_err_flag)
      {
        return;
      }
      // Check if we received a NACK
      if ((TW_STATUS) == TW_MT_SLA_NACK)
      {
        m_err_flag = true;
        m_return = Drv:: I2cStatus::I2C_ADDRESS_ERR;
#ifdef DEBUG_I2C_AVR
        DEBUG_Serial.println(F("I2C unexpected NACK"));
#endif
        return;
      }
    }
  }

  void ATmegaI2cDriverComponentImpl ::
    receive(U8 address, U8* data, U32 len)
  {
    // Write the slave address and set Read bit
    write((address << 1) | TW_READ);
    if(m_err_flag)
    {
      return;
    }

    // Check if we received a NACK
    if (TW_STATUS == TW_MR_SLA_NACK)
    {
      m_err_flag = true;
      m_return = Drv:: I2cStatus::I2C_ADDRESS_ERR;
      #ifdef DEBUG_I2C_AVR
        DEBUG_Serial.println(F("I2C RX slave didn't ack or error"));
      #endif
      return;
    }
    //check if we are in some other state
    if ((TW_STATUS) != TW_MR_SLA_ACK)
    {
      m_err_flag = true;
      m_return = Drv:: I2cStatus::I2C_OTHER_ERR;
      #ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C in unexpected state rx"));
      DEBUG_Serial.println(TW_STATUS, HEX);
      #endif
    }

    // Check length to see if reading one byte
    if (len == 1)
    {
      // Read byte and NACK
      data[0] = readNack();
      if(m_err_flag)
      {
        return;
      }
    }
    else
    {
      // Read byte and ACK
      for (NATIVE_UINT_TYPE i = 0; i < len - 1; i++)
      {
        data[i] = readAck();
        if(m_err_flag)
        {
          return;
        }
      }
      data[len - 1] = readNack();
      if(m_err_flag)
      {
        return;
      }
    }
  }

  void ATmegaI2cDriverComponentImpl ::
    write(U8 data)
  {
    // Load into into data register
    TWDR = data;

    // Start transmission of data
    TW_timeout(_BV(TWINT) | _BV(TWEN));
    if(this->m_err_flag)
    {
      this->m_return = Drv::I2cStatus::I2C_START_TIMEOUT_ERR;
    }
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readAck(void)
  {
    // Start receive with an acknowledge
    TW_timeout(_BV(TWINT) | _BV(TWEN) | _BV(TWEA));

    // We have no error, are in a valid state, and got an ack
    if ( (!this->m_err_flag)
      && ((TW_STATUS == TW_MR_DATA_ACK) || (TW_STATUS == TW_MR_SLA_ACK)))
    {
      // Return received data
      return TWDR;
    }

    // We timed out, or we got a nack
    if ( (this->m_err_flag)
      || (TW_STATUS == TW_MR_DATA_NACK) || (TW_STATUS == TW_MR_SLA_NACK))
    {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C unexpected nack"));
#endif
      this->m_err_flag = true;
      this->m_return = Drv::I2cStatus::I2C_READ_ERR;
      // Return received data, even if it may be nonsense
      return TWDR;
    }

#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C unexpected state in ack"));
#endif
    // We must not be in any valid state, return error
    this->m_err_flag = true;
    this->m_return = Drv::I2cStatus::I2C_OTHER_ERR;

    return TWDR;
  }

  U8 ATmegaI2cDriverComponentImpl ::
    readNack(void)
  {
    // Start receive without an acknowledge
    TW_timeout(_BV(TWINT) | _BV(TWEN));

    // Check for an invalid TWI hardware state.
    if ( (TW_STATUS != TW_MR_DATA_NACK)
      && (TW_STATUS != TW_MR_SLA_NACK)
      && (TW_STATUS != TW_MR_DATA_ACK)
      && (TW_STATUS != TW_MR_SLA_ACK))
    {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C unexpected state in nack"));
#endif
      this->m_err_flag = true;
      this->m_return = Drv::I2cStatus::I2C_OTHER_ERR;
      // Return received data, even if it may be nonsense
      return TWDR;
    }

    //check for a timeout
    if(this->m_err_flag)
    {
#ifdef DEBUG_I2C_AVR
      DEBUG_Serial.println(F("I2C read error"));
#endif
      this->m_return = Drv::I2cStatus::I2C_READ_ERR;
    }

    // Return received data
    return TWDR;
  }

  void ATmegaI2cDriverComponentImpl ::
    TW_timeout(U8 twcr)
  {
    TWCR = twcr;

    if(!(TWCR & _BV(TWINT))) // Don't bother setting up timers to drop straight through
    {
      this->m_timer.start(); // set begin time to now
      this->m_timer.stop();  // zero the timer

      // Wait for TWINT to be set to confirm transmission
      while(!(TWCR & _BV(TWINT)) && (m_timer.getDiffUsec() < m_timeout))
      {
        this->m_timer.stop();
      }
      // If we dropped out of the while loop but the TWINT bit is not
      // set, we timed out!
      if(!(TWCR & _BV(TWINT)))
      {
#ifdef DEBUG_I2C_AVR
        DEBUG_Serial.println(F("I2C timeout"));
#endif
        this->m_err_flag = true;
      }
    }
  }

} // end namespace Drv
