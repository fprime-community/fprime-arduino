// ======================================================================
// \title  ATmegaAdcDriverComponentImpl.cpp
// \author Nathan Daniel <ndaniel9@gatech.edu>
// \brief  Reads multiple ADC channels from an ATmega microcontroller.
// ======================================================================

// #define DEBUG_ATmegaAdcDriver_HPP
// #define LEFT_ADJUST

#include <ATmega/Drv/ATmegaAdcDriver/ATmegaAdcDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ATmegaAdcDriverComponentImpl ::
    ATmegaAdcDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        U8 channels[], /*!< ADC channels to be used*/
        const U8 numChannels, /*!< Number of ADC channels*/
        U32 gains[] /*!< Channel gains*/
    ) :
      ATmegaAdcDriverComponentBase(compName)
#else
    ATmegaAdcDriverComponentImpl(
        U8 channels[], /*!< ADC channels to be used*/
        const U8 numChannels, /*!< Number of ADC channels*/
        U32 gains[] /*!< Channel gains*/
    )
#endif
  {
    this->channels = channels;
    this->numChannels = numChannels;
    this->gains = gains;
    this->rawReadings = new U16[this->numChannels];
    this->readings = new U16[this->numChannels];
  }

  void ATmegaAdcDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance,
        const U8 prescalerSelect,
        const U8 referenceSelect
    )
  {
    ATmegaAdcDriverComponentBase::init(instance);

    //ADC configuration
#ifdef ARDUINO
    ADCSRA &= !(prescalerSelect | 0xF8);  //Set prescalar based on init parameter (ADCSRA[0:2] = prescalar_bv, prescalar = 2^ADCSRA[0:2])
    ADCSRA |= (prescalerSelect & 0x07);
    ADMUX &= !(referenceSelect<<6); //Set voltage reference based on init parameter (ADCMUX[6:7] = reference_bv)
    ADMUX |= (referenceSelect<<6);
  #ifdef LEFT_ADJUST
    ADMUX |= ADLAR;
  #endif
    ADCSRA |= bit(ADEN); //Enable ADC
    ADCSRA |= bit(ADSC); //Do first, longest converstion to initialize circuitry
#endif
    for(int i=0; i<this->numChannels; i++) {
      this->rawReadings[i] = 0;
      this->readings[i] = 0;
    }
  }

  ATmegaAdcDriverComponentImpl ::
    ~ATmegaAdcDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ATmegaAdcDriverComponentImpl ::
    tlmSched_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // Take measurements of each ADC channel and output to telemetry
    for(int i=0; i<this->numChannels; i++) {
#ifdef ARDUINO
      ADMUX &= !(this->channels[i] | 0xE0);
      ADMUX |= (this->channels[i] & 0x1F); //Select channel
      ADCSRA |= bit(ADSC); //Start conversion
      while(ADCSRA & bit(ADSC)) {// Wait for conversion to finish
        //TODO: Is code here necessary to avoid infinite while loop?
      }
      //TODO: is a different statement necessary here for left adjusting
      this->rawReadings[i] = ADCL | (ADCH<<8) ; //Read ADC (Note: ADCL MUST be read first)
#else
      //If not running on AVR, report half full-scale value (to distinguish from erronious zeros or full-scale)
      this->rawReadings[i] = 512; 
#endif
      //Multiply by gain, then divide by 1024 (i.e. bit shifted by 10)
      this->readings[i] = (this->gains[i]*this->rawReadings[i])>>10;
      
#ifdef DEBUG_ATmegaAdcDriver_HPP
  #ifdef ARDUINO
      Serial1.print("Channel "); Serial1.print(i);
      Serial1.print(": raw-"); Serial1.print(this->rawReadings[i]);
      Serial1.print(", gain-"); Serial1.print(this->gains[i]);
      Serial1.print(", value-"); Serial1.print(this->readings[i],HEX);
      Serial1.println();
  #else
      printf("Channel %d: raw-%d, gain-%d, value-%x\n",i,this->rawReadings[i],this->gains[i],this->readings[i]);
  #endif
#endif

    }
    //Report telemetry
    this->tlmWrite_ADC_CNTS(this->rawReadings);
    this->tlmWrite_ADC_VAL(this->readings);
    //Report to downstream components, if ports are connected
    for (NATIVE_INT_TYPE port = 0; port < this->getNum_Report_OutputPorts(); port++) {
      if (this->isConnected_Report_OutputPort(port)) {
        this->Report_out(port,(U64)this->readings,this->numChannels);
      }
    }
  }
} // end namespace Drv
