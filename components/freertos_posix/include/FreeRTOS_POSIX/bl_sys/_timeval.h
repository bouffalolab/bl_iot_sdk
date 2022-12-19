#ifndef _SYS_TIMEVAL_H_
#define _SYS_TIMEVAL_H_

#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED

/*
 * Structure returned by gettimeofday(2) system call, and used in other calls.
 */
struct timeval {
	time_t		tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

#endif

#endif