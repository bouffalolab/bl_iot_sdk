#ifndef __HAL_IR_H__
#define __HAL_IR_H__

#define HAL_IR_CHECK_NONE   (0)
#define HAL_IR_CHECK_CMD    (1 << 0)
#define HAL_IR_CHECK_ADDR   (1 << 1)

int hal_ir_init_from_dts(uint32_t fdt, uint32_t dtb_offset);
int hal_irled_init(int chip_type);
int hal_irled_send_data(int data_num, uint32_t *buf);
int hal_ir_config(uint32_t data_check);
#endif
