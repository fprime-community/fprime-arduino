// ======================================================================
// \title Arduino/Os/DefaultRawTime.cpp
// \brief sets default Os::RawTime to no-op Arduino implementation via linker
// ======================================================================
#include "Arduino/Os/RawTime.hpp"
#include "Os/Delegate.hpp"

namespace Os {

//! \brief get a delegate for RawTimeInterface that intercepts calls for Arduino RawTime usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
RawTimeInterface *RawTimeInterface::getDelegate(RawTimeHandleStorage& aligned_placement_new_memory, const RawTimeInterface* to_copy) {
    return Os::Delegate::makeDelegate<RawTimeInterface, Os::Arduino::RawTime::ArduinoRawTime, RawTimeHandleStorage>(
            aligned_placement_new_memory, to_copy
    );
}

} // namespace Os
