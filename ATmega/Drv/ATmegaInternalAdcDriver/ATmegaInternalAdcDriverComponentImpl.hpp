// ======================================================================
// \title  ATmegaInternalAdcDriverComponentImpl.hpp
// \author Kaushik Manchikanti <kmanchikanti6@gatech.edu>
// \brief  Reads the value from a register in the ATmega Internal ADC
// ======================================================================

#ifndef ATmegaInternalAdcDriver_HPP
#define ATmegaInternalAdcDriver_HPP

#include "ATmega/Drv/ATmegaInternalAdcDriver/ATmegaInternalAdcDriverComponentAc.hpp"
#include "Os/IntervalTimer.hpp"

namespace Drv {

  class ATmegaInternalAdcDriverComponentImpl :
    public ATmegaInternalAdcDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ATmegaInternalAdcDriver
      //!
      ATmegaInternalAdcDriverComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ATmegaInternalAdcDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0, /*!< The instance number*/
          const U8 prescalarSelect = 7, /*!<ADC clock prescalar select*/
          const U8 referenceSelect = 0 /*<ADC reference select*/
               
      );

      //! Destroy object ATmegaInternalAdcDriver
      //!
      ~ATmegaInternalAdcDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for Read_ADC
      //!
      Drv::AdcStatus Read_ADC_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 &adc_counts /*!< pointer to variable that will store ADC counts*/
      );

      U16 m_reading;

      // for breaking out any infinite loops while reading channels
      Os::IntervalTimer m_timer;

    };

} // end namespace Drv

#endif
