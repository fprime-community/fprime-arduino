// ======================================================================
// \title  ATmegaInternalAdcDriverComponentImpl.cpp
// \author Kaushik Manchikanti <kmanchikanti6@gatech.edu>
// \brief  Reads the value from a register in the ATmega Internal ADC
// ======================================================================


#include <ATmega/Drv/ATmegaInternalAdcDriver/ATmegaInternalAdcDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <avr/io.h>

#ifndef ADC_CONV_MAX_TIME
  #define ADC_CONV_MAX_TIME 1000 //usec
#endif

// debuging the output of the adc channels on arduino
// this will only work if debug is enabled on an arduino platform
#ifdef DEBUG_ATM_INT_ADC
  #ifdef ARDUINO
    #include <Arduino.h>
  #endif
  #ifndef DEBUG_SERIAL
    #define DEBUG_SERIAL Serial
  #endif
#endif

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaInternalAdcDriverComponentImpl ::
#if FW_OBJECT_NAMES == 1
    ATmegaInternalAdcDriverComponentImpl(
        const char *const compName
    ) :
      ATmegaInternalAdcDriverComponentBase(compName)
#else
    ATmegaInternalAdcDriverComponentImpl(void)
#endif
  {

  }

  void ATmegaInternalAdcDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const U8 prescalerSelect,
        const U8 referenceSelect
    )
  {
    ATmegaInternalAdcDriverComponentBase::init(instance);

    // initialize the ATmega ADC
    ADCSRA &= 0xF8; // clear the prescalar and select it based on init parameter (ADCSRA[0:2] = prescalar_bv, prescalar = 2^ADCSRA[0:2])
    ADCSRA |= (prescalerSelect & 0x07);
    ADMUX &= 0x3F; // clear the reference select and select it based on init parameter (ADCMUX[6:7] = reference_bv)
    ADMUX |= (referenceSelect << 6);
#ifdef LEFT_ADJUST
    ADMUX |= _BV(ADLAR);
#endif
    ADCSRA |= _BV(ADEN); //Enable ADC
    ADCSRA |= _BV(ADSC); //Do first, longest converstion to initialize circuitry

    this->m_reading = 0;

  }

  ATmegaInternalAdcDriverComponentImpl ::
    ~ATmegaInternalAdcDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  Drv::AdcStatus ATmegaInternalAdcDriverComponentImpl ::
    Read_ADC_handler(
        const NATIVE_INT_TYPE portNum,
        U16 &adc_counts
    )
  {

      ADMUX &= portNum & 0xE0; // Select channel, referred to by portNum
      ADMUX |= (portNum & 0x1F);
      ADCSRA |= _BV(ADSC); // Start conversion

      // start the timer
      this->m_timer.start();
      this->m_timer.stop();

      while((ADCSRA & _BV(ADSC)) && this->m_timer.getDiffUsec() <= ADC_CONV_MAX_TIME)
        // Wait for conversion to finish
        this->m_timer.stop();

      if (ADCSRA & _BV(ADSC)) {
        // tell the calling component that the adc conversion did not complete
        this->m_reading = -9999;
        adc_counts = this->m_reading;

#ifdef DEBUG_ATM_INT_ADC
        DEBUG_SERIAL.print("Counts from ADC Channel ");
        DEBUG_SERIAL.print(portNum);
        DEBUG_SERIAL.print(": ");
        DEBUG_SERIAL.println(this->m_reading);
#endif
        return Drv::AdcStatus::CONVERSION_TIMEOUT;

      }

      this->m_reading = ADCL | (ADCH << 8) ; //Read ADC (Note: ADCL MUST be read first)
      adc_counts = this->m_reading; // point the parameter in the input port to the read adc counts

#ifdef DEBUG_ATM_INT_ADC
      DEBUG_SERIAL.print("Counts from ADC Channel ");
      DEBUG_SERIAL.print(portNum);
      DEBUG_SERIAL.print(": ");
      DEBUG_SERIAL.println(this->m_reading);
#endif

      return Drv::AdcStatus::CONVERSION_OK;

  }

} // end namespace Drv
