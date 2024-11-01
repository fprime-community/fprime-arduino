// ======================================================================
// \title Os/Stub/Console.cpp
// \brief stub implementation for Os::Console
// ======================================================================
#include <Arduino/Os/Console.hpp>

namespace Os {
namespace Arduino {

void StreamConsoleHandle::setStreamHandler(Stream& stream) {
    this->m_stream = &stream;
}

void StreamConsole::writeMessage(const CHAR *message, const FwSizeType size) {
    Stream* output_stream = this->m_handle.m_stream;
    if (output_stream != nullptr) {
        size_t output_size = FW_MIN(size, std::numeric_limits<size_t>::max());
        output_stream->write(message, output_size);
    }
}

ConsoleHandle* StreamConsole::getHandle() {
    return &this->m_handle;
}


} // namespace Stub
} // namespace Os
