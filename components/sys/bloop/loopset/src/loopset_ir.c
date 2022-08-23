#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <stdlib.h>

#include <utils_debug.h>
#include <utils_log.h>
#include <blog.h>

#include <looprt.h>
#include <loopset.h>
#include <bl_gpio.h>
#include <bl_ir.h>
#include <aos/yloop.h>

#include <loopset_ir.h>

struct loop_evt_handler_holder {
    const struct loop_evt_handler handler;
};

static int _ir_bloop_evt(struct loop_ctx *loop, const struct loop_evt_handler *handler, uint32_t *bitmap_evt, uint32_t *evt_type_map)
{
    uint32_t data;

    data = bl_receivedata();
    if (0 == data) {
        aos_post_event(EV_IR, CODE_IR_RECEIVE_NEC_REPEAT, 0);        
    } else {
        aos_post_event(EV_IR, CODE_IR_RECEIVE_NEC, data);        
    }
    bl_enable_rx_int();

    return 0;
}

static int _ir_bloop_msg(struct loop_ctx *loop, const struct loop_evt_handler *handler, struct loop_msg *msg)
{
    blog_debug("[IR] [MSG] called with msg info\r\n");

    return 0;
}

int loopset_ir_hook_on_looprt(void)
{
    static const struct loop_evt_handler_holder _ir_bloop_handler_holder = {
        .handler = {
            .name = "IR Trigger",
            .evt = _ir_bloop_evt,
            .handle = _ir_bloop_msg,
        }, 
    };

    //TODO use run-time priority based register
    return looprt_handler_register(&_ir_bloop_handler_holder.handler, IR_PRIORITY);
}

void ir_async_post(void)
{
    looprt_evt_notify_async_fromISR(IR_PRIORITY, EVT_MAP_IR_TRIGGER);

    return;
}

