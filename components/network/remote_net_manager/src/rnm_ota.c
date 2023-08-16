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
#include <rnm_ota.h>

#include <stdbool.h>
#include <string.h>
#include <hal_sys.h>

typedef struct ota_header {
    union {
        struct {
            uint8_t header[16];

            uint8_t type[4];//RAW XZ
            uint32_t len;//body len
            uint8_t pad0[8];

            uint8_t ver_hardware[16];
            uint8_t ver_software[16];

            uint8_t sha256[32];
        } s;
        uint8_t _pad[512];
    } u;
} ota_header_t;
#define OTA_HEADER_SIZE (sizeof(ota_header_t))

static rnm_ota_t *ota_ctx_alloc()
{
    rnm_ota_t *ota = rnm_malloc(sizeof(*ota));
    if (ota) {
        memset(ota, 0, sizeof(*ota));
        ota->write_buf = rnm_malloc(RNM_OTA_PART_SIZE);
        if (!ota->write_buf) {
            rnm_free(ota);
            ota = NULL;
        }
    }
    return ota;
}

static void ota_ctx_free(rnm_ota_t **pctx)
{
    if (!*pctx) {
        return;
    }
    rnm_free((*pctx)->write_buf);
    rnm_free(*pctx);
    *pctx = NULL;
}

/* TODO: do the real check */
static int _check_ota_header(ota_header_t *ota_header, uint32_t *ota_len, int *use_xz)
{
    char str[33];//assume max segment size
    int i;

    memcpy(str, ota_header->u.s.header, sizeof(ota_header->u.s.header));
    str[sizeof(ota_header->u.s.header)] = '\0';
    puts("[OTA] [HEADER] ota header is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.type, sizeof(ota_header->u.s.type));
    str[sizeof(ota_header->u.s.type)] = '\0';
    puts("[OTA] [HEADER] file type is ");
    puts(str);
    puts("\r\n");
    if (strstr(str, "XZ")) {
        *use_xz = 1;
    } else {
        *use_xz = 0;
    }

    memcpy(ota_len, &(ota_header->u.s.len), 4);
    printf("[OTA] [HEADER] file length (exclude ota header) is %lu\r\n", *ota_len);

    memcpy(str, ota_header->u.s.ver_hardware, sizeof(ota_header->u.s.ver_hardware));
    str[sizeof(ota_header->u.s.ver_hardware)] = '\0';
    puts("[OTA] [HEADER] ver_hardware is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.ver_software, sizeof(ota_header->u.s.ver_software));
    str[sizeof(ota_header->u.s.ver_software)] = '\0';
    puts("[OTA] [HEADER] ver_software is ");
    puts(str);
    puts("\r\n");

    memcpy(str, ota_header->u.s.sha256, sizeof(ota_header->u.s.sha256));
    str[sizeof(ota_header->u.s.sha256)] = '\0';
    puts("[OTA] [HEADER] sha256 is ");
    for (i = 0; i < sizeof(ota_header->u.s.sha256); i++) {
        printf("%02X", str[i]);
    }
    puts("\r\n");

    return 0;
}

static void fill_ota_status(rnms_t *rnm, rnm_msg_t *cmd, rnm_ota_msg_t *msg, uint16_t status_type)
{
    memset(msg, 0, sizeof(*msg));
    msg->hdr.cmd = BF1B_CMD_OTA;
    msg->hdr.flags = RNM_MSG_FLAG_ACK;
    msg->hdr.session_id = ((rnm_base_msg_t *)cmd->data)->session_id;
    msg->hdr.msg_id = ++rnm->last_msg_id;
    msg->hdr.msg_id_replying = cmd->cmd.msg_id;
    msg->msg_type = BFLB_OTA_MSG_STATUS;
    msg->status.status_type = status_type;
}

static void reply_error(rnms_t *rnm, rnm_msg_t *cmd, bflb_ota_error_code_t code)
{
    rnm_ota_msg_t msg;

    fill_ota_status(rnm, cmd, &msg, BFLB_OTA_ERROR);
    msg.status.error.code = code;

    rnms_msg_output(rnm, &msg, sizeof(msg));
}

static int handle_start(rnms_t *rnm, rnm_msg_t *cmd)
{
#define MY_ERROR_OUT(e, r, p) error = e; ret = r; goto p
    int ret;
    bflb_ota_error_code_t error;
    rnm_ota_msg_t msg;
    rnm_debug("handle ota start\r\n");

    if (rnm->ota) {
        rnm_err("ota in progress?\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_STATUS_INCORRECT, -1, error1);
    }
    rnm->ota = ota_ctx_alloc();
    if (!rnm->ota) {
        rnm_err("ota malloc failed\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_MISC, -1, error1);
    }
    rnm_ota_t *octx = (rnm_ota_t *)rnm->ota;

    ret = bl_mtd_open(BL_MTD_PARTITION_NAME_FW_DEFAULT, &octx->mtd_hdl, BL_MTD_OPEN_FLAG_BACKUP);
    if (ret) {
        rnm_err("Open Default FW partition failed\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_MISC, -1, error1);
    }


    if (hal_boot2_get_active_entries(BOOT2_PARTITION_TYPE_FW, &octx->ptEntry)) {
        printf("PtTable_Get_Active_Entries fail\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_MISC, -1, error2);
    }
    octx->tgt_part_size = octx->ptEntry.maxLen[!octx->ptEntry.activeIndex];
    {   // debug
        uint32_t ota_addr, part_size;
        uint8_t activeID;
        activeID = hal_boot2_get_active_partition();
        ota_addr = octx->ptEntry.Address[!octx->ptEntry.activeIndex];
        part_size = octx->ptEntry.maxLen[!octx->ptEntry.activeIndex];
        (void)ota_addr;
        (void)part_size;
        (void)activeID;
        rnm_debug("current partition activeID %u, to use ID %u\r\n", activeID, !octx->ptEntry.activeIndex);
        rnm_debug("tgt partition ota_addr 0x%08lX, part_size 0x%08lX\r\n", ota_addr, part_size);
    }
    rnm_warning("to erase\r\n");
    bl_mtd_erase_all(octx->mtd_hdl);
    rnm_warning("done\r\n");

    fill_ota_status(rnm, cmd, &msg, BFLB_OTA_START_ACK);

    rnms_msg_output(rnm, &msg, sizeof(msg));
    return 0;
error2:
    bl_mtd_close(octx->mtd_hdl);
error1:
    reply_error(rnm, cmd, error);
    ota_ctx_free((rnm_ota_t **)&rnm->ota);
    return ret;
#undef MY_ERROR_OUT
}

static int handle_abort(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_ota_msg_t msg;
    rnm_ota_t *octx = (rnm_ota_t *)rnm->ota;
    rnm_debug("handle ota abort\r\n");

    bl_mtd_close(octx->mtd_hdl);
    ota_ctx_free((rnm_ota_t **)&rnm->ota);

    fill_ota_status(rnm, cmd, &msg, BFLB_OTA_ABORT_ACK);

    rnms_msg_output(rnm, &msg, sizeof(msg));
    return 0;
}

static int handle_program_part(rnms_t *rnm, rnm_msg_t *cmd)
{
#define MY_ERROR_OUT(e, r, p) error = e; ret = r; goto p
    int ret;
    bflb_ota_error_code_t error;
    rnm_ota_msg_t ack_msg;
    rnm_ota_msg_t *msg = (rnm_ota_msg_t *)cmd->data;
    rnm_ota_t *octx      = (rnm_ota_t *)rnm->ota;
    uint32_t part_offset          = msg->program_part.offset;
    uint32_t part_size            = msg->program_part.data_len;
    uint8_t *pb                   = octx->write_buf;
    bool is_first_part            = false;
    bool is_last_part             = false;

    if (!((part_offset == 0 && octx->offset_written == 0) ||
            part_offset == octx->offset_written + OTA_HEADER_SIZE)) {
        rnm_err("part missing?\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_PART_MISSING, -1, error1);
    }
    if (!(part_size <= RNM_OTA_PART_SIZE)) {
        rnm_err("part size too large %lu\r\n", part_size);
        MY_ERROR_OUT(BFLB_OTA_ERROR_SIZE_NOT_EXPECTED, -1, error1);
    }

    memcpy(pb, msg->program_part.data, part_size);

    if (part_offset == 0) {
        is_first_part = true;
        utils_sha256_init(&octx->sha_ctx);
        utils_sha256_starts(&octx->sha_ctx);
        memset(octx->sha256_this, 0, sizeof(octx->sha256_this));

        ota_header_t *ota_header = (ota_header_t *)pb;
        uint32_t hdr_adv_bin_size = 0;
        int use_xz;
        if (_check_ota_header(ota_header, &hdr_adv_bin_size, &use_xz)) {
            MY_ERROR_OUT(BFLB_OTA_ERROR_MALFORMED_HEADER, -1, error1);
        }
        rnm_debug("OTA header claimed body size %lu, use_xz %d\r\n", hdr_adv_bin_size, use_xz);
        if (!(hdr_adv_bin_size > 0 && hdr_adv_bin_size <= octx->tgt_part_size)) {
            MY_ERROR_OUT(BFLB_OTA_ERROR_HEADER_ADV_LEN_TOO_BIG, -1, error1);
        }
        octx->body_length = hdr_adv_bin_size;
        memcpy(octx->sha256_that, ota_header->u.s.sha256, sizeof(octx->sha256_that));

        pb += OTA_HEADER_SIZE;
        part_size = RNM_OTA_PART_SIZE - OTA_HEADER_SIZE;
    }

    if (!(part_size + octx->offset_written <= octx->body_length)) {
        rnm_err("part size overflow\r\n");
        MY_ERROR_OUT(BFLB_OTA_ERROR_SIZE_NOT_EXPECTED, -1, error1);
    } else if (part_size + octx->offset_written == octx->body_length) {
        is_last_part = true;
    }
    if (!is_first_part && !is_last_part && part_size != RNM_OTA_PART_SIZE) {
        rnm_err("not last part and part_size is not %u\r\n", RNM_OTA_PART_SIZE);
        MY_ERROR_OUT(BFLB_OTA_ERROR_SIZE_NOT_EXPECTED, -1, error1);
    }

    bl_mtd_write(octx->mtd_hdl, octx->offset_written, part_size, pb);
    bl_mtd_read(octx->mtd_hdl, octx->offset_written, part_size, pb);
    utils_sha256_update(&octx->sha_ctx, pb, part_size);
    octx->offset_written += part_size;

    if (is_last_part) {
        utils_sha256_finish(&octx->sha_ctx, octx->sha256_this);
        if (memcmp(octx->sha256_this, octx->sha256_that, sizeof(octx->sha256_this))) {
            rnm_err("SHA256 not correct\r\n");
            MY_ERROR_OUT(BFLB_OTA_ERROR_CKSUM_MISMATCH, -1, error1);
        } else {
            rnm_debug("SHA256 check OK\r\n");
        }
    }

    fill_ota_status(rnm, cmd, &ack_msg, 0);
    if (is_last_part) {
        ack_msg.status.status_type = BFLB_OTA_FIN_ACK;
    } else {
        ack_msg.status.status_type = BFLB_OTA_PROGRAM_ACK;
        ack_msg.status.program_ack.offset = msg->program_part.offset;
    }

    rnms_msg_output(rnm, &ack_msg, sizeof(ack_msg));
    return 0;
error1:
    reply_error(rnm, cmd, error);
    bl_mtd_close(octx->mtd_hdl);
    ota_ctx_free((rnm_ota_t **)&rnm->ota);
    return ret;
#undef MY_ERROR_OUT
}

static int handle_commit(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_ota_msg_t msg;
    rnm_ota_t *octx = (rnm_ota_t *)rnm->ota;

    rnm_log("OTA done.\r\n");

    octx->ptEntry.len = octx->body_length;
    hal_boot2_update_ptable(&octx->ptEntry);
    bl_mtd_close(octx->mtd_hdl);
    ota_ctx_free((rnm_ota_t **)&rnm->ota);

    fill_ota_status(rnm, cmd, &msg, BFLB_OTA_COMMIT_ACK);

    rnms_msg_output(rnm, &msg, sizeof(msg));
    return 0;
}

void rnms_handle_ota(rnms_t *rnm, rnm_msg_t *cmd)
{
    rnm_ota_msg_t *msg;

    msg = (rnm_ota_msg_t *)cmd->data;

    switch (msg->msg_type) {
    case BFLB_OTA_MSG_START:
        handle_start(rnm, cmd);
        break;
    case BFLB_OTA_MSG_ABORT:
        handle_abort(rnm, cmd);
        break;
    case BFLB_OTA_MSG_PROGRAM_PART:
        handle_program_part(rnm, cmd);
        break;
    case BFLB_OTA_MSG_COMMIT:
        handle_commit(rnm, cmd);
        break;
    default:
        rnm_err("unknown msg type %u\r\n", msg->msg_type);
        break;
    }
}
