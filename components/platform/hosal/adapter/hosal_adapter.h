#ifndef _HOSAL_ADAPTER_H_
#define _HOSAL_ADAPTER_H_

#include <stdint.h>

uintptr_t hosal_adpt_critical_enter(void);
void hosal_adpt_critical_exit(uintptr_t);

#endif
