// ======================================================================
// \title Arduino/Os/Mutex.hpp
// \brief Arduino definitions for Os::Mutex
// ======================================================================
#include "Os/Mutex.hpp"

#ifndef OS_ARDUINO_MUTEX_HPP
#define OS_ARDUINO_MUTEX_HPP
namespace Os {
namespace Arduino {
namespace Mutex {

struct ArduinoMutexHandle : public MutexHandle {};

//! \brief Arduino implementation of Os::Mutex
//!
//! Arduino implementation of `MutexInterface` for use as a delegate class handling error-only file operations.
//!
class ArduinoMutex : public MutexInterface {
  public:
    //! \brief constructor
    //!
    ArduinoMutex() = default;

    //! \brief destructor
    //!
    ~ArduinoMutex() override = default;

    //! \brief return the underlying mutex handle (implementation specific)
    //! \return internal mutex handle representation
    MutexHandle* getHandle() override;

    Status take() override;     //!<  lock the mutex and get return status
    Status release() override;  //!<  unlock the mutex and get return status

  private:
    //! Handle for ArduinoMutex
    ArduinoMutexHandle m_handle;
};

}  // namespace Mutex
}  // namespace Arduino
}  // namespace Os
#endif  // OS_ARDUINO_MUTEX_HPP
