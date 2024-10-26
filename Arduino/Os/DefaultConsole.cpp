// ======================================================================
// \title Arduino/Os/DefaultConsole.cpp
// \brief sets default Os::Console to Arduino implementation via linker
// ======================================================================
#include "Arduino/Os/Console.hpp"
#include "Os/Console.hpp"
#include "Os/Delegate.hpp"

namespace Os {
ConsoleInterface* ConsoleInterface::getDelegate(ConsoleHandleStorage& aligned_new_memory,
                                                const ConsoleInterface* to_copy) {
    return Os::Delegate::makeDelegate<ConsoleInterface, Os::Arduino::Console::ArduinoConsole>(aligned_new_memory,
                                                                                              to_copy);
}

}  // namespace Os
