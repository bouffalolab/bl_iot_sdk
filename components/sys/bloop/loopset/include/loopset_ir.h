#ifndef __LOOPSET_IR_H__
#define __LOOPSET_IR_H__

#define EVT_MAP_IR_TRIGGER     (1U << 0)

void loopset_ir_trigger(void);
int loopset_ir_hook_on_looprt(void);
void ir_async_post(void);

#endif
