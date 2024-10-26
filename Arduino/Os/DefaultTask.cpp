// ======================================================================
// \title Arduino/Os/DefaultTask.cpp
// \brief sets default Os::Task to test Arduino implementation via linker
// ======================================================================
#include <cerrno>
#include "Os/Task.hpp"
#include "Arduino/Os//Task.hpp"
#include "Os/Delegate.hpp"
#include <sys/time.h>

namespace Os {
    TaskInterface* TaskInterface::getDelegate(TaskHandleStorage& aligned_new_memory) {
        return Os::Delegate::makeDelegate<TaskInterface, Os::Arduino::Task::ArduinoTask>(aligned_new_memory);
    }

}
