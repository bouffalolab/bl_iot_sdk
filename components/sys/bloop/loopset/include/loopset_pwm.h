#ifndef __LOOPSET_PWM_H__
#define __LOOPSET_PWM_H__

#define PWM_TASK_PRIORITY         4

typedef void (*loopset_func_t) (void *p_arg);

int loopset_pwm_hook_on_looprt(void);
int loopset_pwm_hook_off_looprt(void);

void loopset_pwm_trigger_stop (void);
void loopset_pwm_trigger_start (void);

void loopset_pwm_trigger_on(unsigned int timeon_ms, loopset_func_t cb, void *p_arg);
void loopset_pwm_trigger_off(void);

#endif
