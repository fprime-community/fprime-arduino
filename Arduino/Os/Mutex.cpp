// ======================================================================
// \title Arduino/Os/Mutex.cpp
// \brief Arduino implementation for Os::Mutex
// ======================================================================
#include "Arduino/Os/Mutex.hpp"

namespace Os {
namespace Arduino {
namespace Mutex {

    ArduinoMutex::Status ArduinoMutex::take() {
        return Status::OP_OK;
    }

    ArduinoMutex::Status ArduinoMutex::release() {
        return Status::OP_OK;
    }

    MutexHandle* ArduinoMutex::getHandle() {
        return &this->m_handle;
    }
} // namespace Mutex
} // namespace Arduino
} // namespace Os
