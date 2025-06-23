// ======================================================================
// \title Os/Arduino/File.cpp
// \brief Arduino implementation for Os::File
// ======================================================================
#include "Arduino/Os/FileSystem.hpp"

namespace Os {
namespace Arduino {

ArduinoFileSystem::Status ArduinoFileSystem::_removeDirectory(const char* path) {
    if (!SD.exists(path)) {
        return Status::INVALID_PATH;
    }
    if (SD.rmdir(path)) {
        return Status::OP_OK;
    }
    return Status::OTHER_ERROR;
}

ArduinoFileSystem::Status ArduinoFileSystem::_removeFile(const char* path) {
    if (!SD.exists(path)) {
        return Status::INVALID_PATH;
    }
    if (SD.remove(path)) {
        return Status::OP_OK;
    }
    return Status::OTHER_ERROR;
}

ArduinoFileSystem::Status ArduinoFileSystem::_rename(const char* originPath, const char* destPath) {
    Status stat;
    
    stat = Os::FileSystem::copyFile(originPath, destPath);
    if (stat != OP_OK) {
        return stat;
    }

    stat = this->_removeFile(originPath);

    return stat;
}

ArduinoFileSystem::Status ArduinoFileSystem::_getPathType(const char* path, PathType& pathType) {
    ::File fd = SD.open(path);
    if (!fd) {
        return Status::INVALID_PATH;
    }

    if (fd.isDirectory()) {
        pathType = PathType::DIRECTORY;
    } else {
        pathType = PathType::FILE;
    }

    fd.close();
    return Status::OP_OK;
}

ArduinoFileSystem::Status ArduinoFileSystem::_getWorkingDirectory(char* path, FwSizeType bufferSize) {
    return Status::NOT_SUPPORTED;
}

ArduinoFileSystem::Status ArduinoFileSystem::_changeWorkingDirectory(const char* path) {
    return Status::NOT_SUPPORTED;
}

ArduinoFileSystem::Status ArduinoFileSystem::_getFreeSpace(const char* path, FwSizeType& totalBytes, FwSizeType& freeBytes) {
    return Status::NOT_SUPPORTED;
}

FileSystemHandle* ArduinoFileSystem::getHandle() {
    return &this->m_handle;
}

} // namespace Arduino
} // namespace Os
