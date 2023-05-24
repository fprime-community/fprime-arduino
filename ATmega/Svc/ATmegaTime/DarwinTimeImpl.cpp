#include <ATmega/ATmegaTime/ArduinoTimeImpl.hpp>
#include <Fw/Time/Time.hpp>
#include <sys/time.h>

namespace Svc {

    ArduinoTimeImpl::ArduinoTimeImpl(const char* name) : TimeComponentBase(name) { }

    ArduinoTimeImpl::~ArduinoTimeImpl() { }

    void ArduinoTimeImpl::timeGetPort_handler(
            NATIVE_INT_TYPE portNum, /*!< The port number*/
            Fw::Time &time /*!< The U32 cmd argument*/
        ) {
        timeval stime;
        (void)gettimeofday(&stime,0);
        time.set(TB_WORKSTATION_TIME,0,stime.tv_sec, stime.tv_usec);
    }

    void ArduinoTimeImpl::init(NATIVE_INT_TYPE instance) {
        Svc::TimeComponentBase::init(instance);
    }

}
