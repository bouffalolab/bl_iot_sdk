#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

typedef enum {
    GPIO_INT_TRIG_NEG_PULSE,            /*!< GPIO negedge pulse trigger interrupt */
    GPIO_INT_TRIG_POS_PULSE,            /*!< GPIO posedge pulse trigger interrupt */
    GPIO_INT_TRIG_NEG_LEVEL,            /*!< GPIO negedge level trigger interrupt (32k 3T) */
    GPIO_INT_TRIG_POS_LEVEL,            /*!< GPIO posedge level trigger interrupt (32k 3T) */
} hal_gpio_int_trig_type;

typedef enum {
    GPIO_INT_CONTROL_SYNC,              /*!< GPIO interrupt sync mode */
    GPIO_INT_CONTROL_ASYNC,             /*!< GPIO interrupt async mode */
} hal_gpio_int_ctl_type;

int hal_gpio_register_handler(void *func, int gpioPin, int intCtrlMod, int intTrgMod, void *arg);
int hal_gpio_init_from_dts(uint32_t fdt, uint32_t dtb_offset);
int hal_gpio_led_on(void);
int hal_gpio_led_off(void);

#endif
