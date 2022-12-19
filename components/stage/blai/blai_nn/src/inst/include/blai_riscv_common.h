#pragma once

#define BLAI_BITTURE 0
typedef enum {
    LEAKY, RELU, LINEAR, RELU6, MISH, ELU, RELIE, LOGISTIC, RAMP, TANH, PLSE, LOGGY, STAIR, HARDTAN, LHTAN, SELU, GELU, SWISH, NORM_CHAN, NORM_CHAN_SOFTMAX, NORM_CHAN_SOFTMAX_MAXVAL, RELUN
}ACTIVATION;

int32_t PE_LEAKY(int32_t pass_data);
int32_t PE_RELU(int32_t pass_data);
int32_t PE_RELU6(int32_t pass_data, int fshift);
int8_t PE_MISH(int32_t pass_data, int fin, int fout);
int32_t PE_RELUN(int32_t pass_data, int fshift, int n);
q7_t BLAI_ROUND(int conv_out, uint16_t out_shift, int round, int dbg);