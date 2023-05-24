// ======================================================================
// \title  ATmegaTimeComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Provides Time reference via Arduino time functions.
// ======================================================================

/*
 * ArduinoTimeImpl.cpp:
 *
 * An implementation of LinuxTime used on Arduino so that standard system components can be run as
 * expected. The time format is (U32 seconds, U32 microseconds) and must be mapped to the Arduino
 * supplied "millis()" and "micros()" functions. Thus, the limitation is that this time will roll
 * over after 49 days of continuous use.
 *
 * @author lestarch
 */

#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Fw/Time/Time.hpp>
#include <Arduino.h>

namespace Svc {

#if FW_OBJECT_NAMES == 1
    LinuxTimeImpl::LinuxTimeImpl(const char* name) : TimeComponentBase(name)
#else
    LinuxTimeImpl::LinuxTimeImpl()
#endif
    {}

    LinuxTimeImpl::~LinuxTimeImpl() {}

    void LinuxTimeImpl::timeGetPort_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::Time &time /*!< The time to set */
    ) {
        U32 msec = millis();
        U32 usec = micros();
        time.set(msec/1000, usec % 1000000);
    }

    void LinuxTimeImpl::init(NATIVE_INT_TYPE instance) {
        TimeComponentBase::init(instance);
    }
}
