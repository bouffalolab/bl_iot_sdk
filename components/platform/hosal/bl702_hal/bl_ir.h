#ifndef __BL_IR_H__
#define __BL_IR_H__
#include <stdint.h>
uint32_t bl_receivedata(void);
uint32_t bl_getbitcount(void);
void bl_enable_rx_int(void);
int bl_ir_init(int pin, int ctrltype);
void bl_irmask(int mask);

static inline int bl_ir_get_addr(unsigned int val)
{
    return (val & 0xFF);
}

static inline int bl_ir_get_cmd(unsigned int val)
{
    return ((val & 0xFF0000) >> 16);
}

#endif
