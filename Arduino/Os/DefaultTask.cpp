// ======================================================================
// \title Arduino/Os/DefaultTask.cpp
// \brief sets default Os::Task to test Arduino implementation via linker
// ======================================================================
#include <sys/time.h>
#include <cerrno>
#include "Arduino/Os//Task.hpp"
#include "Os/Delegate.hpp"
#include "Os/Task.hpp"

namespace Os {
    
TaskInterface* TaskInterface::getDelegate(TaskHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<TaskInterface, Os::Arduino::Task::ArduinoTask>(aligned_new_memory);
}

}  // namespace Os
