#include "oadc_cmdproc.h"
#include "oad.h"

struct oad_cmdproc_block_req_t
{
    struct oad_file_info file_info;
    uint32_t file_offset;
    uint8_t data_len;
}__packed;

struct oad_cmdproc_upgrd_end_t
{
    uint8_t status;
    struct oad_file_info file_info;
}__packed;

struct oad_cmdproc_req_t
{
    uint8_t cmd_id;
    union{
        struct oad_file_info file_info;
        struct oad_cmdproc_block_req_t block_req;
        struct oad_cmdproc_upgrd_end_t upgrd_end;
    }q;
}__packed;

void oad_cmdproc_start(void)
{
    uint8_t req[1];
    req[0] = OAD_CMDPROC_START;

    cmdproc_data_send(CMDPROC_TYPE_OAD, req, sizeof(req));
}

void oad_cmdproc_image_identity(struct oad_file_info* file_info)
{    
    struct oad_cmdproc_req_t req;
    req.cmd_id = OAD_CMDPROC_IMAGE_IDENTITY;
    memcpy(&req.q.file_info, file_info, sizeof(*file_info));
    cmdproc_data_send(CMDPROC_TYPE_OAD, (uint8_t *)&req, sizeof(req)); 
}

void oad_cmdproc_block_req(struct oad_file_info* file_info, uint32_t file_offset, uint8_t data_len)
{
    struct oad_cmdproc_req_t req;

    req.cmd_id = OAD_CMDPROC_BLOCK_REQ;
    memcpy(&req.q.block_req.file_info, file_info, sizeof(*file_info));
    req.q.block_req.file_offset = file_offset;
    req.q.block_req.data_len = data_len;
    cmdproc_data_send(CMDPROC_TYPE_OAD, (uint8_t *)&req, sizeof(req)); 
}

void oad_cmdproc_upgrd_end(uint8_t status, struct oad_file_info* file_info)
{
    struct oad_cmdproc_req_t req;

    req.cmd_id = OAD_CMDPROC_UPGRD_END;
    req.q.upgrd_end.status = status;
    memcpy(&req.q.upgrd_end.file_info, file_info, sizeof(*file_info));

    cmdproc_data_send(CMDPROC_TYPE_OAD, (uint8_t *)&req, sizeof(req)); 
}
void oad_cmdproc_enable(cmdproc_recv_cb cb)
{
    cmdproc_callback_set(CMDPROC_TYPE_OAD, cb);
    cmdproc_init();
}
