#ifndef __OAD_TL_H__
#define __OAD_TL_H__

#include "oad.h"
#include "cmdproc.h"

enum
{
    OAD_CMDPROC_START  = 0x00,
    OAD_CMDPROC_IMAGE_IDENTITY,
    OAD_CMDPROC_BLOCK_REQ,
    OAD_CMDPROC_BLOCK_RESP,
    OAD_CMDPROC_UPGRD_END,
};

void oad_cmdproc_enable(cmdproc_recv_cb cb);
void oad_cmdproc_start(void);
void oad_cmdproc_image_identity(struct oad_file_info* file_info);
void oad_cmdproc_block_req(struct oad_file_info* file_info, uint32_t file_offset, uint8_t data_len);
void oad_cmdproc_upgrd_end(uint8_t status, struct oad_file_info* file_info);

#endif
