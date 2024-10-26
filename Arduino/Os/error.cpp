// ======================================================================
// \title Arduino/Os/error.cpp
// \brief implementation for posix errno conversion
// ======================================================================
#include <Arduino/Os/error.hpp>

namespace Os {
namespace Arduino {

File::Status errno_to_file_status(PlatformIntType errno_input) {
    // TODO
    File::Status status = File::Status::OP_OK;
    return status;
}

FileSystem::Status errno_to_filesystem_status(PlatformIntType errno_input) {
    // TODO
    FileSystem::Status status = FileSystem::Status::OP_OK;
    return status;
}

Directory::Status errno_to_directory_status(PlatformIntType errno_input) {
    // TODO
    Directory::Status status = Directory::Status::OP_OK;
    return status;
}

RawTime::Status errno_to_rawtime_status(PlatformIntType errno_input) {
    // TODO
    RawTime::Status status = RawTime::Status::OP_OK;
    return status;
}

Task::Status arduino_status_to_task_status(PlatformIntType arduino_status) {
    // TODO
    Task::Status status = Task::Status::OP_OK;
    return status;
}

Mutex::Status arduino_status_to_mutex_status(PlatformIntType arduino_status) {
    // TODO
    Mutex::Status status = Mutex::Status::ERROR_OTHER;
    return status;
}
}  // namespace Arduino
}  // namespace Os
