#ifndef __BLAI_INST_NPU_ENCODE__
#define __BLAI_INST_NPU_ENCODE__

bool BLAI_MEM_alloc(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, struct PSRAM_ctrl* ctrl);
void fetch_BLAI_data_route(struct blai_net_info_t* net, struct cpu_inst_layer_t *l, struct PSRAM_ctrl* ctrl, int l_current);
void fetch_BLAI_data_general(struct blai_net_info_t* net, struct cpu_inst_layer_t *l, struct PSRAM_ctrl* ctrl, int l_current);
void Load_NPU_weights(struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf,
            fixed_point_t* weight_buf, int* bias_buf, bool use_tflite);
bool BLAI_encode(struct blai_net_info_t* net, struct cpu_inst_layer_t *l, int l_current, struct PSRAM_ctrl* ctrl);
bool check_BLAI_NPU_RUN(struct blai_net_info_t* net, struct cpu_inst_layer_t *l);

#endif //__BLAI_INST_NPU_ENCODE__