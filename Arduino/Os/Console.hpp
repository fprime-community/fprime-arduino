// ======================================================================
// \title Arduino/Os/Console.hpp
// \brief Arduino implementation for Os::Console, header and test definitions
// ======================================================================
#include <FprimeArduino.hpp>
#include <Os/Console.hpp>
#include <cstdio>

#ifndef OS_Arduino_Console_HPP
#define OS_Arduino_Console_HPP

namespace Os {
namespace Arduino {
namespace Console {

//! ConsoleHandle class definition for Arduino implementations.
//!
struct ArduinoConsoleHandle : public ConsoleHandle {
    Stream* m_stream = nullptr;

  public:
    /**
     * Sets the global m_stream arduino stream used to log Arudino messages through a hardware "Stream"
     * like UART or I2C.
     */
    void setOutputStream(Stream* stream);
};

//! \brief Arduino implementation of Os::ConsoleInterface
//!
//! Arduino implementation of `ConsoleInterface` for use as a delegate class handling Arduino console operations.
//!
class ArduinoConsole : public ConsoleInterface {
  public:
    //! \brief constructor
    //!
    ArduinoConsole() = default;

    //! \brief copy constructor
    ArduinoConsole(const ArduinoConsole& other) = default;

    //! \brief default copy assignment
    ArduinoConsole& operator=(const ArduinoConsole& other) = default;

    //! \brief destructor
    //!
    ~ArduinoConsole() override = default;

    // ------------------------------------
    // Functions overrides
    // ------------------------------------

    //! \brief write message to console
    //!
    //! Write a message to the console with a bounded size. This will use the active file descriptor as the output
    //! destination.
    //!
    //! \param message: raw message to write
    //! \param size: size of the message to write to the console
    void writeMessage(const CHAR* message, const FwSizeType size) override;

    //! \brief returns the raw console handle
    //!
    //! Gets the raw console handle from the implementation. Note: users must include the implementation specific
    //! header to make any real use of this handle. Otherwise it will be as an opaque type.
    //!
    //! \return raw console handle
    //!
    ConsoleHandle* getHandle() override;

  private:
    //! File handle for PosixFile
    ArduinoConsoleHandle m_handle;

    FwSizeType MAX_MESSAGE_SIZE = 128;
};

}  // namespace Console
}  // namespace Arduino
}  // namespace Os

#endif  // OS_Arduino_Console_HPP
