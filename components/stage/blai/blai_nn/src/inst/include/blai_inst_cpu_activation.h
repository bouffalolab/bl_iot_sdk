#ifndef __BLAI_INST_CPU_ACTIVATION_H__
#define __BLAI_INST_CPU_ACTIVATION_H__
int32_t PE_LEAKY(int32_t pass_data);
int32_t PE_RELU(int32_t pass_data);
int32_t PE_RELU6(int32_t pass_data, int fshift);
fixed_point_t PE_MISH(int32_t pass_data, int fin, int fout);
#endif // __BLAI_INST_CPU_ACTIVATION_H__
