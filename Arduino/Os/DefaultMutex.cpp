// ======================================================================
// \title Arduino/Os/DefaultMutex.cpp
// \brief sets default Os::Mutex to no-op Arduino implementation via linker
// ======================================================================
#include "Arduino/Os/ConditionVariable.hpp"
#include "Arduino/Os/Mutex.hpp"
#include "Os/Delegate.hpp"

namespace Os {

//! \brief get a delegate for MutexInterface that intercepts calls for Arduino file usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
MutexInterface* MutexInterface::getDelegate(MutexHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<MutexInterface, Os::Arduino::Mutex::ArduinoMutex>(aligned_new_memory);
}

//! \brief get a delegate for condition variable
//! \param aligned_new_memory: aligned memory to fill
//! \return: pointer to delegate
ConditionVariableInterface* ConditionVariableInterface::getDelegate(
    ConditionVariableHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<ConditionVariableInterface, Os::Arduino::Mutex::ArduinoConditionVariable,
                                      ConditionVariableHandleStorage>(aligned_new_memory);
}
}  // namespace Os
