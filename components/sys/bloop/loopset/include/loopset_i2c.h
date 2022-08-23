#ifndef __LOOPSET_I2C_H__
#define __LOOPSET_I2C_H__

#include <bl_i2c.h>
#define EVT_MAP_INSERT_I2C_TRIGGER      (1U << 0)
#define EVT_MAP_NOTINSERT_I2C_TRIGGER   (1U << 1)
#define EVT_MAP_POST_EVENT_I2C_TRIGGER  (1U << 2)

#define NOT_INSERT_FLAG                 0
#define INSERT_FLAG                     1
#define POST_FLAG                       2


void i2c_async_trigger(i2c_msg_t *pst, int flag);
int loopset_i2c_hook_on_looprt(void);

#endif
