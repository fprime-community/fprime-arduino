// ======================================================================
// \title Os/Stub/Console.cpp
// \brief stub implementation for Os::Console
// ======================================================================
#include <Arduino/Os/Console.hpp>

namespace Os {
namespace Arduino {
namespace Console {


void ArduinoConsole::setOutputStream(Stream* stream) {
    this->m_handle.m_stream = stream;
}

void ArduinoConsole::writeMessage(const CHAR *message, const FwSizeType size) {
    Serial.println("test");
    if (this->m_handle.m_stream == NULL) {
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



} // namespace Console
} // namespace Arduino
} // namespace Os