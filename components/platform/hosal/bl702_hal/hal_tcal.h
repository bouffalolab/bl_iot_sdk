#ifndef __HAL_TCAL_H__
#define __HAL_TCAL_H__

#include <stdint.h>
#include <stdio.h>

int hal_tcal_init(void);
int hal_tcal_restart(void);
int hal_tcal_pause(void);
int hal_tcal_resume(void);
int16_t hal_tcal_get_temperature(void);

#endif
