#ifndef __BLAI_INST_CPU_H__
#define __BLAI_INST_CPU_H__

#include "blai_inst_cpu_ops.h"

BLAI_ProcStatus_e blai_cpu_inference(blai_model_hdl_t hdl);
BLAI_Status_e blai_cpu_inst_decode_layer(blai_model_hdl_t hdl);
BLAI_Status_e blai_cpu_release(blai_model_hdl_t hdl);
fixed_point_t* blai_get_output_buffer(blai_model_hdl_t hdl);
#endif /* __BLAI_INST_CPU_H__ */

