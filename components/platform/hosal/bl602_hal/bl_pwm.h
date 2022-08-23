#ifndef __BL_PWM_H__
#define __BL_PWM_H__
#include <stdint.h>
#include <bl602_pwm.h>

#define BL_PWM_XTAL_CLK 40000000
#define BL_PWM_BUS_BCLK 80000000
#define BL_PWM_CLK BL_PWM_XTAL_CLK

int32_t bl_pwm_init(uint8_t id, uint8_t pin, uint32_t freq);
int32_t bl_pwm_start(uint8_t id);
int32_t bl_pwm_stop(uint8_t id);
int32_t bl_pwm_set_freq(uint8_t id, uint32_t freq);
int32_t bl_pwm_set_duty(uint8_t id, float duty);
int32_t bl_pwm_get_duty(uint8_t id, float *p_duty);

#endif
