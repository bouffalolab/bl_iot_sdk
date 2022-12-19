/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef HAL_PWM_H
#define HAL_PWM_H

typedef struct {
    float    duty_cycle;  /* the pwm duty_cycle */
    uint32_t freq;        /* the pwm freq */
} pwm_config_t;

typedef struct {
    uint8_t      port;    /* pwm port */
    pwm_config_t config;  /* spi config */
    void        *priv;    /* priv data */
} pwm_dev_t;

/**
 * Initialises a PWM pin
 *
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_pwm_init_bydev(pwm_dev_t *pwm);

/**
 * Starts Pulse-Width Modulation signal output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_pwm_start_bydev(pwm_dev_t *pwm);

/**
 * Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_pwm_stop_bydev(pwm_dev_t *pwm);

/**
 * change the para of pwm
 *
 * @param[in]  pwm  the PWM device
 * @param[in]  para the para of pwm
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_pwm_para_chg_bydev(pwm_dev_t *pwm, pwm_config_t para);

int32_t hal_pwm_set_duty_bydev(pwm_dev_t *pwm, float duty);
int32_t hal_pwm_set_freq_bydev(pwm_dev_t *pwm, uint32_t freq);
/**
 * De-initialises an PWM interface, Turns off an PWM hardware interface
 *
 * @param[in]  pwm  the interface which should be de-initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_pwm_finalize_bydev(pwm_dev_t *pwm);

#endif /* HAL_PWM_H */
