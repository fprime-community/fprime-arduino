// ======================================================================
// \title Os/Arduino/DefaultRawTime.cpp
// \brief sets default Os::RawTime to the Arduino implementation via linker
// ======================================================================
#include <config/RawTimeSource.hpp>
#include "Arduino/Os/RawTime.hpp"
#include "Os/Delegate.hpp"

namespace Os {

//! \brief get a delegate for RawTimeInterface that intercepts calls for Arduino RawTime usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \param source: timer source selection (ignored)
//! \return: pointer to delegate
RawTimeInterface *RawTimeInterface::getDelegate(RawTimeHandleStorage& aligned_placement_new_memory, const RawTimeInterface* to_copy, RawTimeSource source) {
    (void)source;
    return Os::Delegate::makeDelegate<RawTimeInterface, Os::Arduino::ArduinoRawTime, RawTimeHandleStorage>(
            aligned_placement_new_memory, to_copy
    );
}

} // namespace Os
