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
#include <Arduino/ArduinoTime/ArduinoTimeImpl.hpp>
#include <Fw/Time/Time.hpp>
#include <FprimeArduino.hpp>

namespace Svc {

    ArduinoTimeImpl::ArduinoTimeImpl(const char* name) : TimeComponentBase(name) {} 
    ArduinoTimeImpl::~ArduinoTimeImpl() {}

    void ArduinoTimeImpl::timeGetPort_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::Time &time /*!< The time to set */
    ) {
        U32 msec = millis();
        U32 usec = micros();
        time.set(msec/1000, usec);
    }

    void ArduinoTimeImpl::init(NATIVE_INT_TYPE instance) {
        TimeComponentBase::init(instance);
    }
}
