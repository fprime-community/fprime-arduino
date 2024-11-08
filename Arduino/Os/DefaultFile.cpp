// ======================================================================
// \title Os/Arduino/DefaultFile.cpp
// \brief sets default Os::File to no-op Arduino implementation via linker
// ======================================================================
#include "Arduino/Os/File.hpp"
#include "Arduino/Os/FileSystem.hpp"
#include "Arduino/Os/Directory.hpp"
#include "Os/Delegate.hpp"
namespace Os {

//! \brief get a delegate for FileInterface that intercepts calls for Arduino file usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
FileInterface *FileInterface::getDelegate(FileHandleStorage& aligned_placement_new_memory, const FileInterface* to_copy) {
    return Os::Delegate::makeDelegate<FileInterface, Os::Arduino::ArduinoFile>(
            aligned_placement_new_memory, to_copy
    );
}

//! \brief get a delegate for FileSystemInterface that intercepts calls for Arduino fileSystem usage
//! \param aligned_new_memory: aligned memory to fill
//! \param to_copy: pointer to copy-constructor input
//! \return: pointer to delegate
FileSystemInterface *FileSystemInterface::getDelegate(FileSystemHandleStorage& aligned_placement_new_memory) {
    return Os::Delegate::makeDelegate<FileSystemInterface, Os::Arduino::ArduinoFileSystem>(
        aligned_placement_new_memory
    );
}

//! \brief get a delegate for DirectoryInterface that intercepts calls for Arduino Directory usage
//! \param aligned_new_memory: aligned memory to fill
//! \return: pointer to delegate
DirectoryInterface *DirectoryInterface::getDelegate(DirectoryHandleStorage& aligned_placement_new_memory) {
    return Os::Delegate::makeDelegate<DirectoryInterface, Os::Arduino::ArduinoDirectory>(
        aligned_placement_new_memory
    );
}
}
