// ======================================================================
// \title Arduino/Os/error.hpp
// \brief header for Arduino errno conversion
// ======================================================================
#ifndef OS_ARDUINO_ERRNO_HPP
#define OS_ARDUINO_ERRNO_HPP
#include "Os/File.hpp"
#include "Os/Task.hpp"
#include "Os/FileSystem.hpp"
#include "Os/Directory.hpp"
#include "Os/RawTime.hpp"

namespace Os {
namespace Arduino {

//! Convert an errno representation of an error to the Os::File::Status representation.
//! \param errno_input: errno representation of the error
//! \return: Os::File::Status representation of the error
//!
Os::File::Status errno_to_file_status(PlatformIntType errno_input);

//! Convert an errno representation of an error to the Os::FileSystem::Status representation.
//! \param errno_input: errno representation of the error
//! \return: Os::FileSystem::Status representation of the error
//!
Os::FileSystem::Status errno_to_filesystem_status(PlatformIntType errno_input);

//! Convert an errno representation of an error to the Os::FileSystem::Status representation.
//! \param errno_input: errno representation of the error
//! \return: Os::Directory::Status representation of the error
//!
Os::Directory::Status errno_to_directory_status(PlatformIntType errno_input);

//! Convert an errno representation of an error to the Os::RawTime::Status representation.
//! \param errno_input: errno representation of the error
//! \return: Os::RawTime::Status representation of the error
//!
Os::RawTime::Status errno_to_rawtime_status(PlatformIntType errno_input);

//! Convert an Arduino task representation of an error to the Os::Task::Status representation.
//! \param arduino_status: errno representation of the error
//! \return: Os::Task::Status representation of the error
//!
Os::Task::Status arduino_status_to_task_status(PlatformIntType arduino_status);

//! Convert a Arduino return status (int) for mutex operations to the Os::Mutex::Status representation.
//! \param arduino_status: return status
//! \return: Os::Mutex::Status representation of the error
//!
Os::Mutex::Status arduino_status_to_mutex_status(PlatformIntType arduino_status);

}
}
#endif
