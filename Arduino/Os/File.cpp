// ======================================================================
// \title Os/Arduino/File.cpp
// \brief Arduino implementation for Os::File
// ======================================================================
#include "Arduino/Os/File.hpp"
#include <Fw/Types/Assert.hpp>

namespace Os {
namespace Arduino {

ArduinoFile::~ArduinoFile() {
    this->close();
}

ArduinoFile::Status ArduinoFile::open(const char* filepath, ArduinoFile::Mode open_mode, OverwriteType overwrite) {
    PlatformIntType flags = 0;

    switch (open_mode) {
        case OPEN_READ:
            flags = O_RDONLY;
            break;
        case OPEN_WRITE:
            flags = O_WRONLY | O_CREAT;
            break;
        case OPEN_SYNC_WRITE:
            flags = O_WRONLY | O_CREAT | O_SYNC;
            break;
        case OPEN_CREATE:
            flags = O_WRONLY | O_CREAT | O_TRUNC | ((overwrite == ArduinoFile::OverwriteType::OVERWRITE) ? 0 : O_EXCL);
            break;
        case OPEN_APPEND:
            flags = FILE_WRITE;
            break;
        default:
            FW_ASSERT(0, open_mode);
            break;
    }

    this->m_handle.m_fd = SD.open(filepath, flags);

    if (!this->m_handle.m_fd) {
        return Status::OTHER_ERROR;
    }

    return Status::OP_OK;
}

void ArduinoFile::close() {
    if (this->m_handle.m_fd) {
        this->m_handle.m_fd.close();
        this->m_handle.m_fd = 0;
    }
}

ArduinoFile::Status ArduinoFile::size(FwSignedSizeType& size_result) {
    if (!this->m_handle.m_fd) {
        size_result = 0;
        return Status::NOT_OPENED;
    }

    size_result = this->m_handle.m_fd.size();

    return Status::OP_OK;
}

ArduinoFile::Status ArduinoFile::position(FwSignedSizeType& position_result) {
    if (!this->m_handle.m_fd) {
        position_result = 0;
        return Status::NOT_OPENED;
    }

    position_result = this->m_handle.m_fd.position();

    return Status::OP_OK;
}

ArduinoFile::Status ArduinoFile::preallocate(FwSignedSizeType offset, FwSignedSizeType length) {
    Status status = Status::NOT_SUPPORTED;
    return status;
}

ArduinoFile::Status ArduinoFile::seek(FwSignedSizeType offset, SeekType seekType) {
    if (!this->m_handle.m_fd) {
        return Status::NOT_OPENED;
    }

    if (this->m_handle.m_fd.seek(offset)) {
        return Status::OP_OK;
    }

    return Status::OTHER_ERROR;
}

ArduinoFile::Status ArduinoFile::flush() {
    Status status = Status::NOT_SUPPORTED;
    return status;
}

ArduinoFile::Status ArduinoFile::read(U8* buffer, FwSignedSizeType& size, ArduinoFile::WaitType wait) {
    FW_ASSERT(buffer);

    if (!this->m_handle.m_fd) {
        size = 0;
        return Status::NOT_OPENED;
    }

    if (size <= 0) {
        size = 0;
        return Status::BAD_SIZE;
    }

    if (this->m_handle.m_fd.available()) {
        size = this->m_handle.m_fd.read(static_cast<U8*>(buffer), size);
    } else {
        size = 0;
    }

    return OP_OK;
}

ArduinoFile::Status ArduinoFile::write(const U8* buffer, FwSignedSizeType& size, ArduinoFile::WaitType wait) {
    if (!this->m_handle.m_fd) {
        size = 0;
        return Status::NOT_OPENED;
    }

    if (size <= 0) {
        size = 0;
        return Status::BAD_SIZE;
    }

    size = this->m_handle.m_fd.write(buffer, size);

    if (size == 0) {
        return Status::OTHER_ERROR;
    }

    return OP_OK;
}

FileHandle* ArduinoFile::getHandle() {
    return &this->m_handle;
}

}  // namespace Arduino
}  // namespace Os
