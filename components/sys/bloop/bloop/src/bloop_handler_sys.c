#include <stdio.h>

#include <bloop.h>
#include <utils_debug.h>

static int loop_evt_entity_sys_evt(struct loop_ctx *loop, const struct loop_evt_handler *handler, uint32_t *bitmap_evt, uint32_t *evt_type_map)
{
    uint32_t map = *evt_type_map;

    printf("[SYS] [EVT] called with bitmap_evt %08lx, bitmap_task %08lx\r\n", *bitmap_evt,  *evt_type_map);

redo:
    if (map & LOOP_TASK_SYS_EVT_DUMP) {
        bloop_status_dump(loop);
        map &= (~LOOP_TASK_SYS_EVT_DUMP);
    } else {
        BL_ASSERT_ERROR(0 == map);
    }
    if (map) {
        goto redo;
    }

    *evt_type_map = 0;

    return 0;
}

static int loop_evt_entity_sys_handler(struct loop_ctx *loop, const struct loop_evt_handler *handler, struct loop_msg *msg)
{
    printf("[SYS] [MSG] called with msg info\r\n"
           "    priority %u\r\n"
           "    dst %u\r\n"
           "    msgid %u\r\n"
           "    src %u\r\n"
           "    arg1 %p\r\n"
           "    arg2 %p\r\n",
           msg->u.header.priority,
           msg->u.header.id_dst,
           msg->u.header.id_msg,
           msg->u.header.id_src,
           msg->arg1,
           msg->arg2
    );
    return 0;
}

struct loop_evt_handler bloop_handler_sys = {
    .name = "SYS [built-in]",
    .evt = loop_evt_entity_sys_evt,
    .handle = loop_evt_entity_sys_handler,
};

