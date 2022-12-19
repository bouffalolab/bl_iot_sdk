#ifndef __BLAI_INST_NPU_H__
#define __BLAI_INST_NPU_H__

#include "blai_inst_npu_encode.h"


BLAI_Status_e blai_npu_inst_decode_layer(blai_model_hdl_t hdl);
BLAI_ProcStatus_e blai_npu_inference();
BLAI_Status_e blai_npu_stop(void);
BLAI_Status_e blai_npu_initCfg(blai_model_hdl_t hdl);
BLAI_Status_e blai_npu_release(blai_model_hdl_t hdl);
BLAI_Status_e blai_npu_layer_config(uint8_t *inst_buf, uint8_t *weights_buf,
    uint8_t *bias_buf, uint8_t *input_buf, int patch_size, uint8_t b_isFirstLayers);
bool forward_NPU(struct blai_net_info_t* net, fixed_point_t* DATA_buf, int l_current);
void blai_npu_exec_lock_required(void);
void blai_npu_exec_lock_release(bool in_isr);
void blai_npu_init(void);
void blai_npu_destroy(void);

#endif /* __BLAI_INST_NPU_H__ */

