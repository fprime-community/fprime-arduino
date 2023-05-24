#include <ATmega/ATmegaTime/ArduinoTimeImpl.hpp>
#include <Fw/Time/Time.hpp>
#include <time.h>

namespace Svc {

    ArduinoTimeImpl::ArduinoTimeImpl(const char* name) : TimeComponentBase(name) { }

    ArduinoTimeImpl::~ArduinoTimeImpl() { }

    void ArduinoTimeImpl::timeGetPort_handler(
            NATIVE_INT_TYPE portNum, /*!< The port number*/
            Fw::Time &time /*!< The U32 cmd argument*/
        ) {
        timespec stime;
        (void)clock_gettime(CLOCK_REALTIME,&stime);
        time.set(TB_WORKSTATION_TIME,0, stime.tv_sec, stime.tv_nsec/1000);
    }

    void ArduinoTimeImpl::init(NATIVE_INT_TYPE instance) {
        TimeComponentBase::init(instance);
    }

}
