#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "bl808_common.h"
#include "bl_npu.h"
#include "blai_core.h"
#include "blai_def_internal.h"

static uint8_t g_bNPUInited = 0;
#define BLAI_MODEL_ON_PSRAM

blai_model_hdl_t blai_create(void)
{
    BLAI_Model_t* model;

    if (!g_bNPUInited) {
        bl_npu_init();
        g_bNPUInited = 1;
    }
    model = (BLAI_Model_t*) BLAI_MALLOC(sizeof(BLAI_Model_t));
    
    model->net = (struct blai_net_info_t *)BLAI_MALLOC(sizeof(struct blai_net_info_t));
    if (model->net == NULL) {
        BLAI_FREE(model);
        return NULL;
    }
    memset(model->net, 0, sizeof(struct blai_net_info_t));
    model->net->parent = (void *) model;
    model->share_buffer = 0;
    blai_npu_init();

    return (blai_model_hdl_t) model;
}

struct blai_net_info_t *blai_getNetInfo(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    return model->net;
}

BLAI_Status_e blai_load_model_from_file(blai_model_hdl_t hdl, const char *name)
{
    return BLAI_STATUS_INVALID_INPUT;
}

BLAI_Status_e blai_load_model_from_buffer(blai_model_hdl_t hdl, const uint8_t *buffer)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    uint8_t *file_pos = buffer;

    memset(&model->inst, 0, sizeof(model->inst));
    model->inst.cpu.inst_buf_size = *((uint32_t*) buffer);
    model->inst.cpu.bias_buf_size = *((uint32_t*) (buffer+4));
    model->inst.cpu.weights_buf_size = *((uint32_t*) (buffer+8));

    model->inst.npu.inst_buf_size = *((uint32_t*) (buffer+16));
    model->inst.npu.bias_buf_size = *((uint32_t*) (buffer+20));
    model->inst.npu.weights_buf_size = *((uint32_t*) (buffer+24));
    file_pos += 32;

#ifdef BLAI_MODEL_ON_PSRAM
    if (model->inst.cpu.inst_buf_size > 0) {
        model->inst.cpu.inst_buf = (uint8_t *) BLAI_MALLOC(model->inst.cpu.inst_buf_size);
        memcpy(model->inst.cpu.inst_buf, file_pos, model->inst.cpu.inst_buf_size);
        file_pos += model->inst.cpu.inst_buf_size;
    }

    if (model->inst.cpu.bias_buf_size > 0) {
        model->inst.cpu.bias_buf = (uint8_t *) BLAI_MALLOC(model->inst.cpu.bias_buf_size);
        memcpy(model->inst.cpu.bias_buf, file_pos, model->inst.cpu.bias_buf_size);
        file_pos += model->inst.cpu.bias_buf_size;
    }

    if (model->inst.cpu.inst_buf_size > 0) {
        model->inst.cpu.weights_buf = (uint8_t *) BLAI_MALLOC(model->inst.cpu.weights_buf_size);
        memcpy(model->inst.cpu.weights_buf, file_pos, model->inst.cpu.weights_buf_size);
        file_pos += model->inst.cpu.weights_buf_size;
    }

    if (model->inst.npu.inst_buf_size > 0) {
        model->inst.npu.inst_buf = (uint8_t *) BLAI_MALLOC(model->inst.npu.inst_buf_size);
        memcpy(model->inst.npu.inst_buf, file_pos, model->inst.npu.inst_buf_size);
        csi_dcache_clean_range(model->inst.npu.inst_buf, model->inst.npu.inst_buf_size);
        file_pos += model->inst.npu.inst_buf_size;
    }
    if (model->inst.npu.bias_buf_size > 0) {
        model->inst.npu.bias_buf = (uint8_t *) BLAI_MALLOC(model->inst.npu.bias_buf_size);
        memcpy(model->inst.npu.bias_buf, file_pos, model->inst.npu.bias_buf_size);
        csi_dcache_clean_range(model->inst.npu.bias_buf, model->inst.npu.bias_buf_size);
        file_pos += model->inst.npu.bias_buf_size;
    }
    if (model->inst.npu.weights_buf_size > 0) {
        model->inst.npu.weights_buf = (uint8_t *) BLAI_MALLOC(model->inst.npu.weights_buf_size);
        memcpy(model->inst.npu.weights_buf, file_pos, model->inst.npu.weights_buf_size);
        csi_dcache_clean_range(model->inst.npu.weights_buf, model->inst.npu.weights_buf_size);
        file_pos += model->inst.npu.weights_buf_size;
    }
#else
    model->inst.cpu.inst_buf = (uint8_t *)file_pos;
    model->inst.cpu.bias_buf = (uint8_t *) (model->inst.cpu.inst_buf+model->inst.cpu.inst_buf_size);
    model->inst.cpu.weights_buf = (uint8_t *) (model->inst.cpu.bias_buf+model->inst.cpu.bias_buf_size);
    if (model->inst.npu.inst_buf_size > 0)
        model->inst.npu.inst_buf = (uint8_t *) (model->inst.cpu.weights_buf+model->inst.cpu.weights_buf_size);
    if (model->inst.npu.bias_buf_size > 0)
        model->inst.npu.bias_buf = (uint8_t *) (model->inst.npu.inst_buf+model->inst.npu.inst_buf_size);
    if (model->inst.npu.weights_buf_size > 0)
        model->inst.npu.weights_buf = (uint8_t *) (model->inst.npu.bias_buf+model->inst.npu.bias_buf_size);
#endif
    BL_LOGE("[NPU]model buf size: %d, %d, %d\r\n", 
        model->inst.npu.inst_buf_size, model->inst.npu.weights_buf_size, model->inst.npu.bias_buf_size);
    BL_LOGE("[NPU]model buf addr: 0x%x, 0x%x, 0x%x\r\n",
        (uint32_t)model->inst.npu.inst_buf, (uint32_t)model->inst.npu.weights_buf, (uint32_t)model->inst.npu.bias_buf);
    BL_LOGE("[CPU]model buf size: %d, %d, %d\r\n",
        model->inst.cpu.inst_buf_size, model->inst.cpu.weights_buf_size, model->inst.cpu.bias_buf_size);
    BL_LOGE("[CPU]model buf addr: 0x%x, 0x%x, 0x%x\r\n",
        (uint32_t)model->inst.cpu.inst_buf, (uint32_t)model->inst.cpu.weights_buf, (uint32_t)model->inst.cpu.bias_buf);

    blai_inst_decode_layer(hdl);

    return BLAI_STATUS_NO_ERROR;
}

uint8_t* blai_getInputBuffer(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    return model->buffer;
}

BLAI_Status_e blai_getInputResolution(blai_model_hdl_t hdl, uint32_t* width, uint32_t* height)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    *width = model->net->w;
    *height = model->net->h;
    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_setSourceResolution(blai_model_hdl_t hdl, uint32_t width, uint32_t height)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    model->in.width = width;
    model->in.height = height;
    return BLAI_STATUS_NO_ERROR;
}

uint8_t* blai_getOutputBuffer(blai_model_hdl_t hdl, uint32_t *size)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    *size = model->net->patch_size;
    return model->buffer + model->net->layers[model->net->layer_cnt-1].out_layer_mem*model->net->patch_size;
}

BLAI_Status_e blai_setResultCB(blai_model_hdl_t hdl, blai_inference_cb cb)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    model->result_cb = cb;
    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_setCustom_Postproc_CB(blai_model_hdl_t hdl, blai_custom_postproc_cb cb)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    model->net->custom_postprocess = 1;
    model->custom_postproc_cb = cb;
    return BLAI_STATUS_NO_ERROR;
}


BLAI_Status_e blai_free(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    blai_inst_release(hdl);

    if (model->buffer)
        BLAI_FREE(model->buffer);
    model->buffer = NULL;
    if (model->net)
        BLAI_FREE(model->net);
    model->net = NULL;
#ifdef BLAI_MODEL_ON_PSRAM
    if (model->inst.cpu.inst_buf)
        BLAI_FREE(model->inst.cpu.inst_buf);
    if (model->inst.cpu.bias_buf)
        BLAI_FREE(model->inst.cpu.bias_buf);
    if (model->inst.cpu.weights_buf)
        BLAI_FREE(model->inst.cpu.weights_buf);
    if (model->inst.npu.inst_buf)
        BLAI_FREE(model->inst.npu.inst_buf);
    if (model->inst.npu.bias_buf)
        BLAI_FREE(model->inst.npu.bias_buf);
    if (model->inst.npu.weights_buf)
        BLAI_FREE(model->inst.npu.weights_buf);
#endif
    if (model)
        BLAI_FREE(model);

    /* do not free semaphore, and keep the 2 semaphore 
     * for npu for furthur used (384 bytes for each)
     */
    //blai_npu_destroy();

    return 0;
}

BLAI_Status_e blai_startCompute(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    if (model == NULL)
        return BLAI_STATUS_UNAVAILABLE_DEVICE;

    return blai_inst_inference(hdl);
}
