// ======================================================================
// \title Arduino/Os/ConditionVariable.hpp
// \brief Arduino definitions for Os::ConditionVariable
// ======================================================================
#ifndef OS_ARDUINO_CONDITION_VARIABLE_HPP
#define OS_ARDUINO_CONDITION_VARIABLE_HPP
#include <Os/Condition.hpp>

namespace Os {
namespace Arduino {
namespace Mutex {

struct ArduinoConditionVariableHandle : public ConditionVariableHandle {};

//! \brief Arduino implementation of Os::ConditionVariable
//!
//! Arduino implementation of `ConditionVariable` for use as a delegate class handling error-only file operations.
//!
class ArduinoConditionVariable : public ConditionVariableInterface {
  public:
    //! \brief constructor
    //!
    ArduinoConditionVariable() = default;

    //! \brief destructor
    //!
    ~ArduinoConditionVariable() override = default;

    //! \brief assignment operator is forbidden
    ConditionVariableInterface& operator=(const ConditionVariableInterface& other) override = delete;

    //! \brief wait releasing mutex
    void wait(Os::Mutex& mutex) override;

    //! \brief notify a single waiter
    void notify() override;

    //! \brief notify all current waiters
    void notifyAll() override;

    //! \brief get handle
    ConditionVariableHandle* getHandle() override;

  private:
    //! Handle for PosixMutex
    ArduinoConditionVariableHandle m_handle;
};

}  // namespace Mutex
}  // namespace Arduino
}  // namespace Os
#endif  // OS_ArduinoB_CONDITION_VARIABLE_HPP
