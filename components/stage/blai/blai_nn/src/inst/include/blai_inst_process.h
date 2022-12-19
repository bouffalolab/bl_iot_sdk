#ifndef __BLAI_INST_PROCESS_H__
#define __BLAI_INST_PROCESS_H__

BLAI_Status_e blai_inst_inference(blai_model_hdl_t hdl);
BLAI_Status_e blai_inst_decode_layer(blai_model_hdl_t hdl);
BLAI_Status_e blai_inst_release(blai_model_hdl_t hdl);

#endif /* __BLAI_INST_PROCESS_H__ */

