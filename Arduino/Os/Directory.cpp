// ======================================================================
// \title Os/Arduino/Directory.cpp
// \brief Arduino implementation for Os::Directory
// ======================================================================
#include "Arduino/Os/Directory.hpp"
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/StringUtils.hpp>

namespace Os {
namespace Arduino {

ArduinoDirectory::~ArduinoDirectory() {
    this->close();
}

ArduinoDirectory::Status ArduinoDirectory::open(const char* path, OpenMode mode) {
    ::File dir;

    switch (mode) {
        case OpenMode::READ:
            // Check if path exists
            if (!SD.exists(path)) {
                return Status::DOESNT_EXIST;
            }

            // Open path
            dir = SD.open(path);

            // Handle error opening path
            if (!dir) {
                return Status::OTHER_ERROR;
            }

            // Check if path is a directory
            if (!dir.isDirectory()) {
                dir.close();
                return Status::NOT_DIR;
            }

            // Store file descriptor
            this->m_handle.m_dir = dir;
            break;
        case OpenMode::CREATE_IF_MISSING:
            // If path does not exist, create it
            if (!SD.exists(path) && !SD.mkdir(path)) {
                return Status::OTHER_ERROR;
            }

            // Open path
            dir = SD.open(path);

            // Handle error opening path
            if (!dir) {
                return Status::OTHER_ERROR;
            }

            // Check if path is a directory
            if (!dir.isDirectory()) {
                dir.close();
                return Status::NOT_DIR;
            }

            // Store file descriptor
            this->m_handle.m_dir = dir;
            break;
        case OpenMode::CREATE_EXCLUSIVE:
            // Check if path exists. If it does, return error
            if (SD.exists(path)) {
                return Status::ALREADY_EXISTS;
            }

            // Create directory
            if (!SD.mkdir(path)) {
                return Status::OTHER_ERROR;
            }

            // Open path
            dir = SD.open(path);

            // Handle error opening path
            if (!dir) {
                return Status::DOESNT_EXIST;
            }

            // Check if path is a directory
            if (!dir.isDirectory()) {
                dir.close();
                return Status::NOT_DIR;
            }

            // Store file descriptor
            this->m_handle.m_dir = dir;
            break;
        default:
            return Status::OTHER_ERROR;
    }

    return Status::OP_OK;
}

ArduinoDirectory::Status ArduinoDirectory::rewind() {
    return Status::NOT_SUPPORTED;
}

ArduinoDirectory::Status ArduinoDirectory::read(char* fileNameBuffer, FwSizeType bufSize) {
    FW_ASSERT(fileNameBuffer);

    if (!this->m_handle.m_dir) {
        return Status::NOT_OPENED;
    }

    ::File fd;
    // Open next file
    while ((fd = this->m_handle.m_dir.openNextFile())) {
        // Check if open was successful. If not, then no entries in directory
        if (!fd) {
            return Status::NO_MORE_FILES;
        }

        // Check if entry is a directory. If it is, skip it
        if (fd.isDirectory()) {
            fd.close();
            continue;
        }

        // Opened next file. Break loop
        break;
    }

    (void)Fw::StringUtils::string_copy(fileNameBuffer, fd.name(), bufSize);

    this->close();
    return Status::OP_OK;
}

void ArduinoDirectory::close() {
    if (this->m_handle.m_dir) {
        this->m_handle.m_dir.close();
        this->m_handle.m_dir = 0;
    }
}

DirectoryHandle* ArduinoDirectory::getHandle() {
    return &this->m_handle;
}

}  // namespace Arduino
}  // namespace Os
