// ======================================================================
// \title Os/Arduino/DefaultConsole.cpp
// \brief sets default Os::Console to arduino implementation via linker
// ======================================================================
#include "Os/Console.hpp"
#include "Arduino/Os/Console.hpp"
#include "Os/Delegate.hpp"

namespace Os {
ConsoleInterface* ConsoleInterface::getDelegate(ConsoleHandleStorage& aligned_new_memory, const ConsoleInterface* to_copy) {
    return Os::Delegate::makeDelegate<ConsoleInterface, Os::Arduino::StreamConsole>(aligned_new_memory, to_copy);
}
}
