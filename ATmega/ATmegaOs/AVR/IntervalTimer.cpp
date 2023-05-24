#include <Os/IntervalTimer.hpp>
#include <Fw/Types/Assert.hpp>
#include <time.h>
#include <string.h>

namespace Os {

    void IntervalTimer::getRawTime(RawTime& time) {
        // TODO: need to set up timekeeping
        U32 msec = 0;  // millis();
        U32 usec = 0;  // micros();

        time.upper = msec/1000;
        time.lower = usec;
    }

    // Adapted from: http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
    // should be t1In - t2In
    U32 IntervalTimer::getDiffUsec(const RawTime& t1In, const RawTime& t2In) {

        RawTime result = {t1In.upper - t2In.upper,0};

        if (t1In.lower < t2In.lower) {
            result.upper -= 1; // subtract nsec carry to seconds
            result.lower = t1In.lower + (1000000000 - t2In.lower);
        } else {
            result.lower = t1In.lower - t2In.lower;
        }

        return result.upper*1000000 + result.lower / 1000;
    }
}
