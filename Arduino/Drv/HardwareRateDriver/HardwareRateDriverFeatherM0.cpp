#include <FpConfig.hpp>
#include <Fw/Types/Assert.hpp>
#include <ATmega/Drv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <Fw/Logger/Logger.hpp>
#include "Adafruit_ZeroTimer.h"

namespace Arduino {
Adafruit_ZeroTimer s_itimer = Adafruit_ZeroTimer(3);

void HardwareRateDriver::start() {
    U32 seconds = m_interval / 1000;
    U32 freq = 1 / seconds;
    Fw::Logger::log("Starting base rate group clock with period of %" PRIu32 " seconds\n", seconds);

    // Set up the flexible divider/compare
    U16 divider  = 1;
    U16 compare = 0;
    tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;

    if ((freq < 24000000) && (freq > 800)) {
        divider = 1;
        prescaler = TC_CLOCK_PRESCALER_DIV1;
    } else if (freq > 400) {
        divider = 2;
        prescaler = TC_CLOCK_PRESCALER_DIV2;
    } else if (freq > 200) {
        divider = 4;
        prescaler = TC_CLOCK_PRESCALER_DIV4;
    } else if (freq > 100) {
        divider = 8;
        prescaler = TC_CLOCK_PRESCALER_DIV8;
    } else if (freq > 50) {
        divider = 16;
        prescaler = TC_CLOCK_PRESCALER_DIV16;
    } else if (freq > 12) {
        divider = 64;
        prescaler = TC_CLOCK_PRESCALER_DIV64;
    } else if (freq > 3) {
        divider = 256;
        prescaler = TC_CLOCK_PRESCALER_DIV256;
    } else if (freq >= 0.75) {
        divider = 1024;
        prescaler = TC_CLOCK_PRESCALER_DIV1024;
    } else {
        FW_ASSERT(0);
    }

    s_itimer.enable(false);
    s_itimer.configure(prescaler,       // prescaler
        TC_COUNTER_SIZE_16BIT,          // bit width of timer/counter
        TC_WAVE_GENERATION_MATCH_PWM    // frequency or PWM mode
        );
    s_itimer.setCompare(0, (48000000/divider)/freq);
    s_itimer.setCallback(true, TC_CALLBACK_CC_CHANNEL0, HardwareRateDriver::s_timerISR);
    s_itimer.enable(true);
}

void HardwareRateDriver::stop() {
    s_itimer.enable(false);
}

void HardwareRateDriver::s_timerISR() {
    s_timer(s_driver);
}

};
