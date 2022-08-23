#ifndef __BL_I2C_H__
#define __BL_I2C_H__
#include <stdint.h>

#define I2C_M_READ           1
#define I2C_M_WRITE          0
#define I2C_M_BLOCK          0
#define I2C_M_NO_BLOCK       1

typedef struct i2c_msg {
	uint16_t addr;	
	uint8_t direct;
    uint8_t subflag;
    uint32_t subaddr;
    uint8_t sublen;
	uint32_t len;		
    uint8_t *buf;
    int event;
    int idex;
    int block;
    int stop;
    int ins_num;
    int i2cx;
} i2c_msg_t;

void i2c_set_freq(int freq, int i2cx);
void i2c_gpio_init(int i2cx);
void i2c_clear_status(int i2cx);
void do_write_data(i2c_msg_t *pstmsg);
void do_read_data(i2c_msg_t *pstmsg);
void i2c_transfer_start(i2c_msg_t *pstmsg);

#endif
