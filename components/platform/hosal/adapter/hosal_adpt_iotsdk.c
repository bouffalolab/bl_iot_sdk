#include "hosal_adapter.h"
#include "FreeRTOS.h"
#include "task.h"

uintptr_t hosal_adpt_critical_enter(void)
{
  taskENTER_CRITICAL();
  return 0;
}

void hosal_adpt_critical_exit(uintptr_t irq_state)
{
  (void)irq_state;
  taskEXIT_CRITICAL();
}

