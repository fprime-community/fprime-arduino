// ======================================================================
// \title Arduino/Os/ConditionVariable.cpp
// \brief Arduino implementations for Os::ConditionVariable
// ======================================================================
#include "Arduino/Os/ConditionVariable.hpp"
#include "Fw/Types/Assert.hpp"

namespace Os {
namespace Arduino {
namespace Mutex {

void ArduinoConditionVariable::wait(Os::Mutex& mutex) {}
void ArduinoConditionVariable::notify() {}
void ArduinoConditionVariable::notifyAll() {}

ConditionVariableHandle* ArduinoConditionVariable::getHandle() {
    return &m_handle;
}

}  // namespace Mutex
}  // namespace Arduino
}  // namespace Os
