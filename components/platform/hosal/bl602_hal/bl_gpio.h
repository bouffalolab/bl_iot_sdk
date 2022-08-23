#ifndef __BL_GPIO_H__
#define __BL_GPIO_H__
#include <stdint.h>

typedef struct _gpio_ctx_desc {
    struct _gpio_ctx_desc *next;
    void (*gpio_handler)(void *);
    void *arg;

    uint8_t gpioPin;
    uint8_t intCtrlMod;
    uint8_t intTrgMod;
} gpio_ctx_t;

int bl_gpio_enable_output(uint8_t pin, uint8_t pullup, uint8_t pulldown);
int bl_gpio_enable_input(uint8_t pin, uint8_t pullup, uint8_t pulldown);
int bl_gpio_output_set(uint8_t pin, uint8_t value);
int bl_gpio_input_get(uint8_t pin, uint8_t *value);
int bl_gpio_input_get_value(uint8_t pin);
int bl_gpio_int_clear(uint8_t gpioPin,uint8_t intClear);
void bl_gpio_intmask(uint8_t gpiopin, uint8_t mask);
void bl_set_gpio_intmod(uint8_t gpioPin, uint8_t intCtrlMod, uint8_t intTrgMod);
void bl_gpio_register(gpio_ctx_t *pstnode);

#endif
