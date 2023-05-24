// ======================================================================
// \title  ATmegaAdcDriverComponentImpl.cpp
// \author Nathan Daniel <ndaniel9@gatech.edu>
// \brief  Reads multiple ADC channels from an ATmega microcontroller.
// ======================================================================

#ifndef ATmegaAdcDriver_HPP
#define ATmegaAdcDriver_HPP

#include "ATmega/Drv/ATmegaAdcDriver/ATmegaAdcDriverComponentAc.hpp"
#ifdef ARDUINO
  #include <Arduino.h>
#endif

namespace Drv {

  class ATmegaAdcDriverComponentImpl :
    public ATmegaAdcDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaAdcDriver
      //!
      ATmegaAdcDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
#endif
          U8 channels[], /*!< ADC channels to be used*/
          const U8 numChannels, /*!< Number of ADC channels*/
          U32 gains[] /*!< Channel gains*/
      );

      //! Initialize object ATmegaAdcDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0, /*!< The instance number*/
          const U8 prescalarSelect = 7, /*!<ADC clock prescalar select*/
          const U8 referenceSelect = 1 /*<ADC reference select*/
      );

      //! Destroy object ATmegaAdcDriver
      //!
      ~ATmegaAdcDriverComponentImpl(void);

    PRIVATE:

      U8* channels;
      U8 numChannels;
      U32* gains;

      U16* rawReadings;
      U16* readings;

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for tlmSched
      //!
      void tlmSched_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );


    };

} // end namespace Drv

#endif
