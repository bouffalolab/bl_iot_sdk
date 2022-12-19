#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "FreeRTOS_POSIX.h"
#include <time.h>
#include <sys/_timeval.h>

#define CLOCK_REALTIME     1     /**< The identifier of the system-wide clock measuring real time. */
#define CLOCK_MONOTONIC    4     /**< The identifier for the system-wide monotonic clock.*/

struct timezone {
  int tz_minuteswest; /* Minutes west of GMT.  */
  int tz_dsttime;     /* Nonzero if DST is ever in effect.  */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(struct timeval *tv, struct timezone *tz);

#define timersub(tvp, uvp, vvp)                                         \
        do {                                                            \
                (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;          \
                (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;       \
                if ((vvp)->tv_usec < 0) {                               \
                        (vvp)->tv_sec--;                                \
                        (vvp)->tv_usec += 1000000;                      \
                }                                                       \
        } while (0)

#endif
