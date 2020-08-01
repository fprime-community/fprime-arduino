#include <Fw/Types/BasicTypes.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>
#include <Fw/Types/EightyCharString.hpp>
#include <fprime-arduino/ArduinoDrv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <sys/time.h>

namespace Arduino {
Os::Task s_task;
//Temporary function used to time for linux
void linux_task_function(void* vself) {
    HardwareRateDriver* self = reinterpret_cast<HardwareRateDriver*>(vself);
    struct timeval time;
    gettimeofday(&time, NULL);
    U64 time_us = time.tv_sec * (int)1e6 + time.tv_usec;
    if ((time_us % (self->m_interval * 1000)) == 0) {
        HardwareRateDriver::s_timer(self);
    }
}

void HardwareRateDriver::start() {
    Fw::EightyCharString fake("FakeArduino");
    s_task.setStarted(true);
    s_task.start(fake, 0xdeafbeef, 255, 0, linux_task_function, this, 0);
}
void HardwareRateDriver::stop() {
    s_task.setStarted(false);
}
void HardwareRateDriver::s_timerISR() {}
};
