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
#include <FprimeArduino.hpp>

namespace Arduino {

ArduinoTime::ArduinoTime(const char* name) : ArduinoTimeComponentBase(name) {}
ArduinoTime::~ArduinoTime() {}

void ArduinoTime::timeGetPort_handler(NATIVE_INT_TYPE portNum, /*!< The port number*/
                                      Fw::Time& time           /*!< The time to set */
) {
    this->rawTime.now();
    U32 sec = reinterpret_cast<Os::Arduino::RawTime::ArduinoRawTimeHandle*>(this->rawTime.getHandle())->m_sec_timespec;
    U32 nsec = reinterpret_cast<Os::Arduino::RawTime::ArduinoRawTimeHandle*>(this->rawTime.getHandle())->m_nsec_timespec;

    time.set(sec, nsec);
}

void ArduinoTime::init(NATIVE_INT_TYPE instance) {
    ArduinoTimeComponentBase::init(instance);
}
}  // namespace Arduino
