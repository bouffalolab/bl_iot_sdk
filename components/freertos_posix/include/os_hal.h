#ifndef __OS_HAL_H__
#define __OS_HAL_H__

/* FreeRTOS includes. */
#include "FreeRTOS_POSIX.h"

/* System headers. */
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#ifndef _POSIX_TIMERS
#define _POSIX_TIMERS
#endif

#include <time.h>

/* FreeRTOS+POSIX. */
#include "FreeRTOS_POSIX/pthread.h"
#include "FreeRTOS_POSIX/mqueue.h"
#include "FreeRTOS_POSIX/signal.h"

#include "FreeRTOS_POSIX/semaphore.h"

#include "aos/yloop.h"

extern int printf(const char *fmt, ...);

/* Constants */
#define os_printf printf
#define os_free vPortFree
#define os_malloc pvPortMalloc
#define assert(x) while(!(x));

#define WIFI_MGMR_DEFAULT_CLOCK_ID 0
#define WIFI_MGMR_CMD_QUEUE_NAME  "/mgmr_cmd_q"

uint32_t os_get_time_ms(void);

/* post event */
struct os_event {
  int type;
  void *value;
};
typedef struct os_event *os_event_t;

/* Critical context */
struct os_critical {
  UBaseType_t irqstate;
};
typedef struct os_critical *os_critical_t;

int os_api_init(void);
int os_event_notify(os_event_t);
void os_lock_giant(void);
void os_unlock_giant(void);

void os_critical_enter(os_critical_t crit);
void os_critical_exit(os_critical_t crit);

int msleep(long msec);
#endif
