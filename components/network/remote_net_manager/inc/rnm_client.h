/*
 * Copyright (c) 2016-2023 Bouffalolab.
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
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include <rnm_common.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO hide info that should be kept private

#define RNMC_TASK_PRIORITY              21
#define RNMC_TASK_STACK_SIZE            2048
#define RNMC_TASK_STACK_DEPTH           (RNMC_TASK_STACK_SIZE / sizeof(StackType_t))
#define RNMC_CMD_MSG_QUEUE_CAP          4
#define RNMC_CMD_MSG_SIZE               sizeof(rnm_msg_t)
#define RNMC_CMD_MSG_QUEUE_STORAGE_SIZE (RNMC_CMD_MSG_QUEUE_CAP * RNMC_CMD_MSG_SIZE)

#define RNMC_CMD_RPC_WAIT_SLOT_CNT RNMC_CMD_MSG_QUEUE_CAP


#define RNMC_DEFAULT_CMD_TIMEOUT_MS (5 * 1000)

typedef void (*rnm_async_event_cb_t)(void *cb_arg, rnm_base_msg_t *msg);
typedef void (*rnmc_sniffer_cb_t)(void *cb_arg, const void *data, size_t data_len);

typedef enum {
    RNMC_WIFI_MODE_NONE,
    RNMC_WIFI_MODE_AP,
    RNMC_WIFI_MODE_STA,
    // STA/AP coexistence is not supported in this client
    // RNM_WIFI_MODE_AP_STA,
    RNMC_WIFI_MODE_SNIFFER,
} rnm_wifi_mode_t;

struct cmd_rpc {
    struct wait_slot {
        bool used;
        uint16_t session_id;
        SemaphoreHandle_t sem;
        StaticSemaphore_t sem_buffer;
        rnm_msg_t *resp;
    } wait_slots[RNMC_CMD_RPC_WAIT_SLOT_CNT];
    SemaphoreHandle_t mutex;
    StaticSemaphore_t mutex_buffer;
    uint16_t last_msg_id;     // 0 is used but only after overflow happened
    uint16_t last_session_id; // 0 is never used
};

typedef struct {
    rnm_wifi_mode_t mode;
    void *output_fn_env;
    rnm_output_t output_fn;

    void *async_event_cb_arg;
    rnm_async_event_cb_t async_event_cb;

    void *sniffer_cb_arg;
    rnmc_sniffer_cb_t sniffer_cb;

    struct cmd_rpc cmd_rpc;

    StaticTask_t cmd_task_buffer;
    StackType_t cmd_task_stack_buffer[RNMC_TASK_STACK_DEPTH];

    QueueHandle_t cmd_msg_queue;
    StaticQueue_t cmd_msg_queue_buffer;
    uint8_t cmd_msg_queue_storage_buffer[RNMC_CMD_MSG_QUEUE_STORAGE_SIZE];

    rnm_statistic_t statistic;
} rnmc_t;

enum {
    RNMC_STAT_ERR_CMD_ID_NOT_IN_RANGE,
    RNMC_STAT_ERR_INPUT_NOMEM,
    RNMC_STAT_ERR_OUTPUT_NOMEM,
    RNMC_STAT_ERR_CMD_TIMEOUT,
    RNMC_STAT_ERR_RPC_NO_FREE_SLOT,
    RNMC_STAT_ERR_RPC_NO_MATCHING_SLOT,
    RNMC_STAT_SNIFFER_PKT_CNT,
    RNMC_STAT_SNIFFER_PKT_BYTES,
    RNMC_STAT_MAX,
};

typedef enum {
    RNMC_OK,
    RNMC_NOMEM,
    RNMC_TIMEOUT,
    RNMC_NO_FREE_SLOT,
    RNMC_INVALID_INPUT,
    RNMC_INVALID_MODE,
    RNMC_NOT_IMPLEMENTED,
    RNMC_ERROR_MISC,
    // >= 128, error code from server, see cmd_status_t
} rnmc_ret_t;

/**
 * @brief  Init RNM client.
 *
 * @param output_fn_env       Callback argument passed to ouput_fn.
 * @param output_fn           Callback called to transfer data by lower layer.
 * @param async_event_cb_arg  Callback argument passed to async_event_cb.
 * @param async_event_cb      Optional callback called to notify async events such as STA_CONNECTED.
 *                            To omit, pass NULL and async events will be dropped.
 *
 * @return  Context of RNM or NULL on error.
 */
rnmc_t *rnm_client_init(void *output_fn_env, rnm_output_t output_fn, void *async_event_cb_arg, rnm_async_event_cb_t async_event_cb);

/**
 * @brief  Register sniffer callback.
 *
 * @param rnm             RNM client.
 * @param sniffer_cb_arg  Callback argument passed to sniffer_cb.
 * @param sniffer_cb      Callback.
 *
 * @note  The context of the callback is the same as rnmc_sniffer_packet_input().
 *
 * @return  0 on success, -1 on error.
 */
int rnmc_sniffer_callback_register(rnmc_t *rnm, void *sniffer_cb_arg, rnmc_sniffer_cb_t sniffer_cb);

/**
 * @brief  Pass command to RNM to process.
 *
 * @param rnm       RNM client.
 * @param data      Data.
 * @param data_len  Length of data.
 *
 * @return  0 on success, -1 on error.
 */
int rnmc_cmd_input_raw(rnmc_t *rnm, void *data, uint16_t data_len);

/**
 * @brief  Send cmd to queue and wait for response.
 *
 * @param rnm         RNM client.
 * @param cmd         Command to send.
 * @param cmd_len     Length of command.
 * @param resp        Response to fill.
 * @param ms_to_wait  Timeout in ms.
 *
 * @return  See rnmc_ret_t.
 */
rnmc_ret_t rnmc_cmd_send(rnmc_t *rnm, void *cmd, uint16_t cmd_len, rnm_msg_t *resp, int ms_to_wait);

/**
 * @brief  Send cmd to queue and wait for response of which payload is not cared about.
 *
 * @param rnm         RNM client.
 * @param cmd         Command to send.
 * @param cmd_len     Length of command.
 * @param ms_to_wait  Timeout in ms.
 *
 * @return  See rnmc_ret_t.
 */
rnmc_ret_t rnmc_cmd_send_simple(rnmc_t *rnm, void *cmd, uint16_t cmd_len, int ms_to_wait);

/**
 * @brief  Get current mode of RNM.
 *
 * @param rnm  RNM client.
 *
 * @return  See rnm_wifi_mode_t.
 */
rnm_wifi_mode_t rnmc_get_mode(rnmc_t *rnm);

/**
 * @brief  Input sniffer packets. If callback is available, call it.
 *
 * @param rnm  RNM client.
 * @param data      Sniffer packet.
 * @param data_len  Sniffer packet length.
 *
 * @return  0 on success, -1 on error.
 */
int rnmc_sniffer_packet_input(rnmc_t *rnm, const void *data, size_t data_len);

/**
 * @brief  Dump statistic of RNM.
 *
 * @param rnm  RNM client.
 *
 * @note  RNM log should be enabled to output statistic data.
 *
 * @return  0 on success, -1 on error.
 */
int rnmc_statistic_dump(rnmc_t *rnm);

#ifdef __cplusplus
}
#endif
