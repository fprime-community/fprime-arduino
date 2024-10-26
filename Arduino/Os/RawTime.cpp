// ======================================================================
// \title Arduino/Os/RawTime.cpp
// \brief Arduino implementation for Os::RawTime
// ======================================================================
#include "Arduino/Os/RawTime.hpp"

namespace Os {
namespace Arduino {
namespace RawTime {

void setDateTime(U32 hour, U32 min, U32 sec, U32 day, U32 month, U32 year) {
    setTime(hour, min, sec, day, month, year);
}

RawTimeHandle* ArduinoRawTime::getHandle() {
    return &this->m_handle;
}

ArduinoRawTime::Status ArduinoRawTime::now() {
    this->m_handle.m_sec_timespec = ::now();
    return Status::OP_OK;
}

ArduinoRawTime::Status ArduinoRawTime::getTimeInterval(const Os::RawTime& other, Fw::TimeInterval& interval) const {
    time_t t1 = this->m_handle.m_sec_timespec;
    time_t t2 = static_cast<ArduinoRawTimeHandle*>(const_cast<Os::RawTime&>(other).getHandle())->m_sec_timespec;

    // Guarantee t1 is the later time to make the calculation below easier
    if (t1 < t2) {
        t1 = static_cast<ArduinoRawTimeHandle*>(const_cast<Os::RawTime&>(other).getHandle())->m_sec_timespec;
        t2 = this->m_handle.m_sec_timespec;
    }

    // Here we have guaranteed that t1 > t2, so there is no underflow
    U32 sec = static_cast<U32>(t1 - t2);

    interval.set(sec, 0);
    return Status::OP_OK;
}

Fw::SerializeStatus ArduinoRawTime::serialize(Fw::SerializeBufferBase& buffer) const {
    static_assert(ArduinoRawTime::SERIALIZED_SIZE >= 2 * sizeof(U32),
                  "ArduinoRawTime implementation requires at least 2*sizeof(U32) serialization size");

    return buffer.serialize(static_cast<U32>(this->m_handle.m_sec_timespec));
}

Fw::SerializeStatus ArduinoRawTime::deserialize(Fw::SerializeBufferBase& buffer) {
    static_assert(ArduinoRawTime::SERIALIZED_SIZE >= 2 * sizeof(U32),
                  "ArduinoRawTime implementation requires at least 2*sizeof(U32) serialization size");

    U32 sec = 0;
    Fw::SerializeStatus status = buffer.deserialize(sec);
    if (status != Fw::SerializeStatus::FW_SERIALIZE_OK) {
        return status;
    }

    this->m_handle.m_sec_timespec = sec;

    return Fw::SerializeStatus::FW_SERIALIZE_OK;
}

}  // namespace RawTime
}  // namespace Arduino
}  // namespace Os
