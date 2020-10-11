#include <sys/time.h>

void _write(){}
int _gettimeofday(struct timeval *tv, void *tzvp)
{
    tv->tv_sec = 0;
    tv->tv_usec = 0;
    return 0;  // return non-zero for error
}
