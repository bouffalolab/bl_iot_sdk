#include <stdio.h>
#include <stdint.h>
#include <bl602.h>
#include <bl602_gpio.h>
#include <bl602_glb.h>
#include <bl_pwm.h>
#include <hosal_pwm.h>
#include <blog.h>
#define _HAL_PWM_DUTY_ACCURACY  100
#define PWM_CHANNAL_MAX     5

/**
 * Initialises a PWM pin
 *
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_init(hosal_pwm_dev_t *pwm)
{
    uint8_t ch;
	GLB_GPIO_Cfg_Type cfg = {
        .drive = 0,
        .smtCtrl = 1,
        .gpioMode = GPIO_MODE_OUTPUT,
        .pullType = GPIO_PULL_DOWN,
        .gpioPin = 0,
        .gpioFun = 8,
    };
    
    if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }
    ch = pwm->config.pin % PWM_CHANNAL_MAX;
    if (ch != pwm->port) {
        blog_error("error:pwm pin and port do not correspond!  mapping rules: pwm_ch = pin %% 5\r\n");
        return -1;
    }
    cfg.gpioPin = pwm->config.pin; 
    GLB_GPIO_Init(&cfg);

    PWM_Channel_Disable(ch);
    PWM_Smart_Configure(ch, pwm->config.freq, (uint8_t)(pwm->config.duty_cycle/100));

    return 0;
}

/**
 * Starts Pulse-Width Modulation signal output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_start(hosal_pwm_dev_t *pwm)
{
    uint8_t ch;

    if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }

    ch = pwm->port;
    bl_pwm_start(ch);
    return 0;
}

/**
 * Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device, para  set duty and  freq
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_para_chg(hosal_pwm_dev_t *pwm, hosal_pwm_config_t para)
{
    uint8_t ch;

    if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }
    
    ch = pwm->port;
    pwm->config.freq = para.freq;
    pwm->config.duty_cycle = para.duty_cycle;
    PWM_Smart_Configure(ch, para.freq, (uint8_t)(para.duty_cycle/100));
    
    return 0;
}

/**
 * set pwm freq
 *
 *@param[in] id pwm channel
 *@param[in] freq pwm freq
 *
 *@return 0 : on success -1 : fail
 */
int hosal_pwm_freq_set(hosal_pwm_dev_t *pwm, uint32_t freq)
{
    if (NULL == pwm || pwm->port > PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }
    if (freq <= (BL_PWM_CLK / (1UL << 16)) || freq > (BL_PWM_CLK / 100)) {
        return -1;
    }
    pwm->config.freq = freq;
    PWM_Smart_Configure(pwm->port, freq, (uint8_t)(pwm->config.duty_cycle/100));
    return 0;
}

int hosal_pwm_freq_get(hosal_pwm_dev_t *pwm,  uint32_t *p_freq)
{
    if (NULL == pwm || pwm->port > PWM_CHANNAL_MAX || NULL == p_freq) {
        blog_error("arg error.\r\n");
        return -1;
    }
    *p_freq = pwm->config.freq;
    return 0;
}

int hosal_pwm_duty_set(hosal_pwm_dev_t *pwm, uint32_t duty)
{
	if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX || duty > 10000) {
        blog_error("arg error.\r\n");
        return -1;
    }
    pwm->config.duty_cycle = duty;
    PWM_Smart_Configure(pwm->port, pwm->config.freq, (uint8_t)(pwm->config.duty_cycle/100));
    return 0;
}

int hosal_pwm_duty_get(hosal_pwm_dev_t *pwm, uint32_t *p_duty)
{
	if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX || NULL == p_duty) {
        blog_error("arg error.\r\n");
        return -1;
    }
    *p_duty = pwm->config.duty_cycle;
    return 0;
}
/**
 * Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_stop(hosal_pwm_dev_t *pwm)
{
    uint8_t ch;

    if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }

    ch = pwm->port;
    bl_pwm_stop(ch);
    return 0;
}

/**
 * De-initialises an PWM interface, Turns off an PWM hardware interface
 *
 * @param[in]  pwm  the interface which should be de-initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_finalize(hosal_pwm_dev_t *pwm)
{
    uint8_t ch;

    if (NULL == pwm || pwm->port >= PWM_CHANNAL_MAX) {
        blog_error("arg error.\r\n");
        return -1;
    }

    ch = pwm->port;
    bl_pwm_stop(ch);
    return 0;
}


