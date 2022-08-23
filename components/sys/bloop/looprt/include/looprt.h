#ifndef __LOOPRT_H__
#define __LOOPRT_H__
#include <FreeRTOS.h>
#include <task.h>
#include <bloop.h>
int looprt_test_cli_init(void);
int looprt_start(StackType_t *proc_stack_looprt, int stack_count, StaticTask_t *proc_task_looprt);
int looprt_start_auto(void);
void looprt_evt_status_dump(void);
void looprt_evt_notify_async(unsigned int task, uint32_t evt_map);
void looprt_evt_notify_async_fromISR(unsigned int task, uint32_t evt_map);
void looprt_evt_schedule(int task, uint32_t evt_map, int delay_ms);

/* API for register EVT handlers on looprt looper*/
int looprt_handler_register(const struct loop_evt_handler *handler, int priority);
int looprt_timer_register(struct loop_timer *timer);
#endif
