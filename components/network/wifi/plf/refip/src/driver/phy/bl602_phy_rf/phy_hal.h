#ifndef _PHY_HAL_H_
#define _PHY_HAL_H_

#include <stdint.h>
#include <stdbool.h>

#if 0
void hal_fem_gpio_on();
void hal_fem_gpio_off();
#endif

uint8_t hal_get_capcode();
void hal_set_capcode(uint32_t capcode);
void hal_set_capcode_asymm(uint32_t capcode_in, uint32_t capcode_out);
void hal_get_capcode_asymm(uint8_t *capcode_in, uint8_t *capcode_out);
bool hal_get_temperature(int16_t *temperature);
void hal_set_temperature(int16_t temperature);

#endif
