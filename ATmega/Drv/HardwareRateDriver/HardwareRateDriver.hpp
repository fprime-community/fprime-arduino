#ifndef examples_ARDUINO_HPP
#define examples_ARDUINO_HPP
#include <Os/RawTime.hpp>
#include <Arduino/Drv/HardwareRateDriver/HardwareRateDriverComponentAc.hpp>

namespace Arduino {
    /**
     * HardwareRateDriver:
     *
     * Used to drive the rate group driver via the CycleIn port. That port is
     * triggered via a timer interrupt.
     */
    class HardwareRateDriver : public HardwareRateDriverComponentBase  {
        public:
    #if FW_OBJECT_NAMES == 1
            /**
             * Construct the rate driver. Takes in a name (if configured) and a
             * rate at witch to drive.
             * \param const char* compName: name of the component (only supply if configured)
             * \param U32 intervalMs: interval to ping in milliseconds
             */
            HardwareRateDriver(const char* compName, U32 intervalMs);
    #else
            HardwareRateDriver(U32 intervalMs);
    #endif
            HardwareRateDriver(const char* compName);
            /**
             * Starts this driver, kicking off the hardware interrupt or the Linux
             * task that virtualizes this driver.
             */
            void start();
            /**
             * Stops the hardware driver, enabling some clean-up.
             */
            void stop();

            //! Initialize object HardwareRateDriver
            //!
            void init(
               const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
            );

            //!< Driver deconstructor
            ~HardwareRateDriver(void);
            //!< Static callback for task function
            static void s_timer(void * comp);
            //!< Interval of the driver
            U32 m_interval;
        private:
            //!< Last time of run
            Os::RawTime m_last;
            //!< Pointer to the driver
            static HardwareRateDriver* s_driver;
            //!< Static callback to the ISR triggered via a timer
            static void s_timerISR();
            void configure(U32 intervalMs);
    };
}
#endif
