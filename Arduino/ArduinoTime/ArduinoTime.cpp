/*
 * ArduinoTimeImpl.cpp:
 *
 * An implementation of ArduinoTime used on Arduino so that standard system components can be run as
 * expected. The time format is (U32 seconds, U32 microseconds) and must be mapped to the Arduino
 * supplied "millis()" and "micros()" functions. Thus, the limitation is that this time will roll
 * over after 49 days of continuous use.
 *
 * @author lestarch
 */
#include <Arduino/ArduinoTime/ArduinoTime.hpp>
#include <Fw/Time/Time.hpp>
#include <FprimeArduino.hpp>

namespace Arduino {

    ArduinoTime::ArduinoTime(const char* name) : ArduinoTimeComponentBase(name) {} 
    ArduinoTime::~ArduinoTime() {}

    void ArduinoTime::timeGetPort_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::Time &time /*!< The time to set */
    ) {
        time_t sec = now();
        U32 msec = sec * 1000;
        U32 usec = msec * 1000;
        time.set(sec, usec);
    }

    void ArduinoTime::init(NATIVE_INT_TYPE instance) {
        ArduinoTimeComponentBase::init(instance);
    }
}
