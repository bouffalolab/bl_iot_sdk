#ifndef __HAL_BOARD_H__
#define __HAL_BOARD_H__
int hal_board_cfg(uint8_t board_code);
uint32_t hal_board_get_factory_addr(void);
int hal_board_reload_power_offset(void);
int hal_board_get_dts_addr(const char *name, uint32_t *start, uint32_t *off);
#endif
