#ifndef __BLAI_CORE_H__
#define __BLAI_CORE_H__

#include <stdbool.h>
#include "blai_def.h"
#include "blai_inst_cpu.h"
#include "blai_inst_npu.h"
#include "blai_inst_process.h"
#include "blai_inst_util.h"

blai_model_hdl_t blai_create(void);
struct blai_net_info_t *blai_getNetInfo(blai_model_hdl_t hdl);
BLAI_Status_e blai_load_model_from_file(blai_model_hdl_t hdl, const char *name);
BLAI_Status_e blai_load_model_from_buffer(blai_model_hdl_t hdl, const uint8_t *buffer);
uint8_t* blai_getInputBuffer(blai_model_hdl_t hdl);
uint8_t* blai_getOutputBuffer(blai_model_hdl_t hdl, uint32_t *size);
BLAI_Status_e blai_free(blai_model_hdl_t hdl);
BLAI_Status_e blai_setResultCB(blai_model_hdl_t hdl, blai_inference_cb cb);
BLAI_Status_e blai_setCustom_Postproc_CB(blai_model_hdl_t hdl, blai_custom_postproc_cb cb);
BLAI_Status_e blai_startCompute(blai_model_hdl_t hdl);
BLAI_Status_e blai_getInputResolution(blai_model_hdl_t hdl, uint32_t* width, uint32_t* height);
BLAI_Status_e blai_setSourceResolution(blai_model_hdl_t hdl, uint32_t width, uint32_t height);

#endif /* __BLAI_CORE_H__ */

