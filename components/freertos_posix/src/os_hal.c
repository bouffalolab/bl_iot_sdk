#include "os_hal.h"

#include "FreeRTOS.h"
#include "task.h"

pthread_mutex_t wifi_giant_lock;
pthread_mutexattr_t wifi_lock_attr;

uint32_t os_get_time_ms(void) {
  struct timespec ts;
  clock_gettime(WIFI_MGMR_DEFAULT_CLOCK_ID, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000; // convert to millisecond
}

int os_event_notify(os_event_t evt)
{
  aos_post_event(EV_WIFI, evt->type, (unsigned long)evt->value);
  return 0;
}

int os_api_init(void)
{
  pthread_mutexattr_init(&wifi_lock_attr);
  pthread_mutexattr_settype(&wifi_lock_attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&wifi_giant_lock, &wifi_lock_attr);
  return 0;
}

void os_lock_giant(void)
{
  pthread_mutex_lock(&wifi_giant_lock);
}

void os_unlock_giant(void)
{
  pthread_mutex_unlock(&wifi_giant_lock);
}

void os_critical_enter(os_critical_t crit)
{
  configASSERT(crit != NULL);

  if (xPortIsInsideInterrupt() == pdTRUE) {
    crit->irqstate = taskENTER_CRITICAL_FROM_ISR();
  } else {
    taskENTER_CRITICAL();
  }
}

void os_critical_exit(os_critical_t crit)
{
  configASSERT(crit != NULL);

  if (xPortIsInsideInterrupt() == pdTRUE) {
    taskEXIT_CRITICAL_FROM_ISR(crit->irqstate);
  } else {
    taskEXIT_CRITICAL();
  }
}

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
  vTaskDelay(pdMS_TO_TICKS(msec));
  return 0;
}
