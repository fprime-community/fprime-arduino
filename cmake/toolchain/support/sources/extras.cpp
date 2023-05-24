#include <Fw/Logger/Logger.hpp>
extern "C" {
#include <stdlib.h>
int _write( int handle, char *buf, int count) {
    char output[static_cast<unsigned int>(count + 1)];
    for (int i = 0; i < count; i++) {
        output[i] = buf[i];
    }
    output[count] = '\0';
    Fw::Logger::logMsg(output);
    return count;
}
};
#include <new>
namespace std {
    const std::nothrow_t nothrow;
}
void* operator new(unsigned int size, std::nothrow_t const&){ return malloc(size); }
void* operator new[](unsigned int size, std::nothrow_t const&){ return malloc(size); }
