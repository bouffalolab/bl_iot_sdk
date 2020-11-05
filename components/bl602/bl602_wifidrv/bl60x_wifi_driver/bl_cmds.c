/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <string.h>

#include "bl_cmds.h"
#include "bl_utils.h"
#include "bl_strs.h"
#include "os_hal.h"

#undef os_printf
#define os_printf(...) do {} while(0)
static void cmd_dump(const struct bl_cmd *cmd)
{
    os_printf("tkn[%d]  flags:%04x  result:%3d  cmd:%4d-%-24s - reqcfm(%4d-%-s)\n",
           cmd->tkn, cmd->flags, cmd->result, cmd->id, RWNX_ID2STR(cmd->id),
           cmd->reqid, cmd->reqid != (lmac_msg_id_t)-1 ? RWNX_ID2STR(cmd->reqid) : "none");
}

static void cmd_complete(struct bl_cmd_mgr *cmd_mgr, struct bl_cmd *cmd)
{
    os_printf("[CMDS] CMD complete: %p\r\n", cmd);

    cmd_mgr->queue_sz--;
    list_del(&cmd->list);
    cmd->flags |= RWNX_CMD_FLAG_DONE;
    if (cmd->flags & RWNX_CMD_FLAG_NONBLOCK) {
        os_printf("[CMDS] NONBLOCK CMD, free now %p\r\n", cmd);
        os_free(cmd);
    } else {
        if (RWNX_CMD_WAIT_COMPLETE(cmd->flags)) {
            os_printf("[CMDS] BLOCK EVENT is ready, complete now %p\r\n", cmd);
            cmd->result = 0;
            os_event_send(&(cmd->complete), 0x1);
        }
    }
}

static int cmd_mgr_queue(struct bl_cmd_mgr *cmd_mgr, struct bl_cmd *cmd)
{
    struct bl_hw *bl_hw = container_of(cmd_mgr, struct bl_hw, cmd_mgr);
    struct bl_cmd *last;
    unsigned long tout;
    bool defer_push = false;
    uint32_t e;

    RWNX_DBG(RWNX_FN_ENTRY_STR);

    os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);

    if (cmd_mgr->state == RWNX_CMD_MGR_STATE_CRASHED) {
        os_printf("cmd queue crashed\r\n");
        cmd->result = EPIPE;
        RWNX_DBG(RWNX_FN_LEAVE_STR);
        os_mutex_give(cmd_mgr->lock);
        return -EPIPE;
    }

    if (!list_empty(&cmd_mgr->cmds)) {
        if (cmd_mgr->queue_sz == cmd_mgr->max_queue_sz) {
            os_printf("Too many cmds (%d) already queued\r\n",
                   cmd_mgr->max_queue_sz);
            cmd->result = ENOMEM;
            RWNX_DBG(RWNX_FN_LEAVE_STR);
            os_mutex_give(cmd_mgr->lock);
            return -ENOMEM;
        }
        last = list_entry(cmd_mgr->cmds.prev, struct bl_cmd, list);
        //FIXME comment out the following code block, since it is buggy
#if 1
        if (last->flags & (RWNX_CMD_FLAG_WAIT_ACK | RWNX_CMD_FLAG_WAIT_PUSH)) {
#if 0 // queue even NONBLOCK command.
            if (cmd->flags & RWNX_CMD_FLAG_NONBLOCK) {
                printk(KERN_CRIT"cmd queue busy\n");
                cmd->result = -EBUSY;
                spin_unlock_bh(&cmd_mgr->lock);
                RWNX_DBG(RWNX_FN_LEAVE_STR);
                return -EBUSY;
            }
#endif
            cmd->flags |= RWNX_CMD_FLAG_WAIT_PUSH;
            defer_push = true;
        }
#endif
    }

    cmd->flags |= RWNX_CMD_FLAG_WAIT_ACK;
    if (cmd->flags & RWNX_CMD_FLAG_REQ_CFM)
        cmd->flags |= RWNX_CMD_FLAG_WAIT_CFM;

    cmd->tkn    = cmd_mgr->next_tkn++;
    cmd->result = EINTR;

    if (!(cmd->flags & RWNX_CMD_FLAG_NONBLOCK)) {
        os_event_init(&(cmd->complete));
    }


    list_add_tail(&cmd->list, &cmd_mgr->cmds);
    cmd_mgr->queue_sz++;
    tout = (RWNX_80211_CMD_TIMEOUT_MS * cmd_mgr->queue_sz);//TODO FIXME better timeout
    os_mutex_give(cmd_mgr->lock);

    if (!defer_push) {
        os_printf("pushing CMD, param_len is %d...\r\n", cmd->a2e_msg->param_len);
        ipc_host_msg_push(bl_hw->ipc_env, cmd, sizeof(struct lmac_msg) + cmd->a2e_msg->param_len);
        os_free(cmd->a2e_msg);
    }

    if (!(cmd->flags & RWNX_CMD_FLAG_NONBLOCK)) {
        os_printf("Waiting ACK...\r\n");
        os_event_recv(&(cmd->complete), ((1 << 0)), tout, e);
        if (e & (1 << 0)) {
            os_printf("cmd OK\r\n");
        } else {
            os_printf("cmd timed-out\r\n");
            cmd_dump(cmd);
            os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);
            cmd_mgr->state = RWNX_CMD_MGR_STATE_CRASHED;
            if (!(cmd->flags & RWNX_CMD_FLAG_DONE)) {
                cmd->result = ETIMEDOUT;
                cmd_complete(cmd_mgr, cmd);
            }
            os_mutex_give(cmd_mgr->lock);
        }
        os_event_delete((EventGroupHandle_t)&(cmd->complete));//detach after block read
    } else {
        os_printf("No need to wait for CMD\r\n");
        cmd->result = 0;
    }
    RWNX_DBG(RWNX_FN_LEAVE_STR);
    return 0;
}

static void cmd_mgr_print(struct bl_cmd_mgr *cmd_mgr)
{
    struct bl_cmd *cur;

    os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);
    RWNX_DBG("q_sz/max: %2d / %2d - next tkn: %d\r\n",
             cmd_mgr->queue_sz, cmd_mgr->max_queue_sz,
             cmd_mgr->next_tkn);
    list_for_each_entry(cur, &cmd_mgr->cmds, list) {
        cmd_dump(cur);
    }

    os_mutex_give(cmd_mgr->lock);
}

static void cmd_mgr_drain(struct bl_cmd_mgr *cmd_mgr)
{
    struct bl_cmd *cur, *nxt;

    RWNX_DBG(RWNX_FN_ENTRY_STR);

    os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);
    list_for_each_entry_safe(cur, nxt, &cmd_mgr->cmds, list) {
        list_del(&cur->list);
        cmd_mgr->queue_sz--;
        if (!(cur->flags & RWNX_CMD_FLAG_NONBLOCK)) {
            os_event_send(&(cur->complete), 0x1);
        }
    }
    os_mutex_give(cmd_mgr->lock);
}

static int cmd_mgr_llind(struct bl_cmd_mgr *cmd_mgr, struct bl_cmd *cmd)
{
    struct bl_cmd *cur, *acked = NULL, *next = NULL;

    RWNX_DBG(RWNX_FN_ENTRY_STR);

    os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);
    list_for_each_entry(cur, &cmd_mgr->cmds, list) {
        os_printf("Search cmds list cmd %p vs cur %p...\r\n", cmd, cur);
        if (!acked) {
            os_printf("Finding acked...\r\n");
            if (cur->tkn == cmd->tkn) {
                os_printf("Found acked\r\n");
                if (WARN_ON_ONCE(cur != cmd)) {
                    cmd_dump(cmd);
                }
                acked = cur;
                continue;
            }
        }
        if (cur->flags & RWNX_CMD_FLAG_WAIT_PUSH) {
                os_printf("Found WAIT_PUSH\r\n");
                next = cur;
                break;
        }
    }
    if (!acked) {
        os_printf("Error: acked cmd not found\r\n");
    } else {
        cmd->flags &= ~RWNX_CMD_FLAG_WAIT_ACK;
        if (RWNX_CMD_WAIT_COMPLETE(cmd->flags)) {
            os_printf("[BUG] should cmd complete allowed here?\r\n");//FIXME attention
            cmd_complete(cmd_mgr, cmd);// XXX potential buggy
        } else {
            os_printf("[IPC] Wait Until ACKED for cmd %p, flags %08X\r\n", cmd, cmd->flags);
        }
    }
    if (next) {
        struct bl_hw *bl_hw = container_of(cmd_mgr, struct bl_hw, cmd_mgr);
        next->flags &= ~RWNX_CMD_FLAG_WAIT_PUSH;
        os_printf("Pushing new CMD in llind...\r\n");
        ipc_host_msg_push(bl_hw->ipc_env, next,
                          sizeof(struct lmac_msg) + next->a2e_msg->param_len);
        os_free(next->a2e_msg);
    }
    os_mutex_give(cmd_mgr->lock);

    return 0;
}

static int cmd_mgr_msgind(struct bl_cmd_mgr *cmd_mgr, struct ipc_e2a_msg *msg, msg_cb_fct cb)
{
    struct bl_hw *bl_hw = container_of(cmd_mgr, struct bl_hw, cmd_mgr);
    struct bl_cmd *cmd;
    bool found = false;

#if 0
    RWNX_DBG(RWNX_FN_ENTRY_STR);
#endif

    os_mutex_take(cmd_mgr->lock, OS_WAITING_FOREVER);
    list_for_each_entry(cmd, &cmd_mgr->cmds, list) {
        if (cmd->reqid == msg->id &&
            (cmd->flags & RWNX_CMD_FLAG_WAIT_CFM)) {
#if 0
            os_printf("[IPC] Found cb %p for cmd %p , msg id %08X\r\n", cb, cmd, msg->id);
#endif
            if (!cb || (cb && !cb(bl_hw, cmd, msg))) {
#if 0
                os_printf("[IPC] NOT handed by static handler, cb %p\r\n", cb);
#endif
                found = true;
                cmd->flags &= ~RWNX_CMD_FLAG_WAIT_CFM;

                if (cmd->e2a_msg && msg->param_len) {
#if 0
                    os_printf("[IPC] copy back RSP to cmd %p, e2a_msg %p, len %d\r\n",
                            cmd, cmd->e2a_msg, msg->param_len);
#endif
                    memcpy(cmd->e2a_msg, &msg->param, msg->param_len);
                }

                if (RWNX_CMD_WAIT_COMPLETE(cmd->flags)) {
                    cmd_complete(cmd_mgr, cmd);
                }

                break;
            } else {
#if 0
                os_printf("[IPC] MSG is handled by static handler\r\n");
#endif
            }
        }
    }
    os_mutex_give(cmd_mgr->lock);

    if (!found && cb)
        cb(bl_hw, NULL, msg);

    return 0;
}

void bl_cmd_mgr_init(struct bl_cmd_mgr *cmd_mgr)
{
    INIT_LIST_HEAD(&cmd_mgr->cmds);
    cmd_mgr->lock = os_mutex_create("wifi_cmd_lock");
    ASSERT_ERR(NULL != cmd_mgr->lock);

    cmd_mgr->max_queue_sz = RWNX_CMD_MAX_QUEUED;
    cmd_mgr->queue  = &cmd_mgr_queue;
    cmd_mgr->print  = &cmd_mgr_print;
    cmd_mgr->drain  = &cmd_mgr_drain;
    cmd_mgr->llind  = &cmd_mgr_llind;
    cmd_mgr->msgind = &cmd_mgr_msgind;
}
