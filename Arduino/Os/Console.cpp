// ======================================================================
// \title Arduino/Os/Console.cpp
// \brief Arduino implementation for Os::Console
// ======================================================================
#include <Arduino/Os/Console.hpp>

namespace Os {
namespace Arduino {
namespace Console {

void ArduinoConsoleHandle::setOutputStream(Stream* stream) {
    this->m_stream = stream;
}

void ArduinoConsole::writeMessage(const CHAR* message, const FwSizeType size) {
    if (this->m_handle.m_stream == nullptr) {
        return;
    }

    FwSizeType capped_size = (size <= this->MAX_MESSAGE_SIZE) ? size : this->MAX_MESSAGE_SIZE;
    if (message != nullptr) {
        this->m_handle.m_stream->write(message, capped_size);
    }
}

ConsoleHandle* ArduinoConsole::getHandle() {
    return &this->m_handle;
}

}  // namespace Console
}  // namespace Arduino
}  // namespace Os
