#include <sys/time.h>


unsigned int millis() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    unsigned long long millis = ((unsigned long long)(tv.tv_sec) * 1000000ll) +  (unsigned long long)(tv.tv_usec);
    return millis/1000;
}
unsigned int micros() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    unsigned long long millis = ((unsigned long long)(tv.tv_sec) * 1000000ll) +  (unsigned long long)(tv.tv_usec);
    return millis;
}
