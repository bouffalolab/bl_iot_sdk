#ifndef __BLAI_INST_UTIL_H__
#define __BLAI_INST_UTIL_H__

#define BLAI_MALLOC(sz) blai_mem_alloc(sz, __func__, __LINE__)
#define BLAI_FREE(addr) blai_mem_free(addr, __func__, __LINE__)
#define BALI_CHN_ALIGN(sz)  (((sz + 3) >> 2) << 2)

void* blai_mem_alloc(size_t size, const char *func, const int line);
void blai_mem_free(void* addr, const char *func, const int line);
int unsigned_to_signed(int in, int bit);
float fixed_to_float(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS);
fixed_point_t fixed32_to_fixed8(int32_t input, int FIXED_POINT_FRACTIONAL_BITS);
fixed_point_t fixed8_to_fixed8(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS);
int32_t fixed32_to_fixed32(int32_t input, int FIXED_POINT_FRACTIONAL_BITS);
fixed_point_t float_to_fixed(float input, int FIXED_POINT_FRACTIONAL_BITS);
int32_t fixed8_to_fixed32(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS);
int fetch_info(uint8_t* inst, int base, int len);
int8_t* MEM_PTR(int mux, fixed_point_t* DATA_buf, int PATCH_SIZE);
void set_output_wh(struct blai_net_info_t* net, int layer_cnt);
void set_output_wh_later(struct blai_net_info_t* net, int layer_cnt);
void set_npu_output_wh(struct blai_net_info_t* net, int layer_cnt);
void check_merge_layer(struct blai_net_info_t* net, int layer_cnt);
bool check_combomax_layer(struct cpu_inst_layer_t* l);
bool check_upsample_layer(struct cpu_inst_layer_t* l);
bool check_conv_layer(struct cpu_inst_layer_t *l);
bool check_weight_layer(struct cpu_inst_layer_t *l);
bool check_MultiInput_layer(struct cpu_inst_layer_t *l);
bool check_route_layer(struct cpu_inst_layer_t *l);
bool check_combine_layer(struct cpu_inst_layer_t *l);

#endif // __BLAI_INST_UTIL_H__
