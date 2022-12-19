#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"

void* blai_mem_alloc(size_t size, const char *func, const int line) {
    if (size == 0) {
        BL_LOGE("[%s] %zd bytes by %s:%d\r\n", __func__, size, func, line);
        return NULL;
    }

    void *ptr = BL_MallocDMA(0, size);
#ifdef BLAI_MEMALLOC_DEBUG
    BL_LOGI("[%s] 0x%x for %zd bytes by %s:%d\r\n", __func__, (uint32_t) ptr, size, func, line);
#endif
    return ptr;
}

void blai_mem_free(void* addr, const char *func, const int line) {
#ifdef BLAI_MEMALLOC_DEBUG
    BL_LOGI("[%s] 0x%x by %s:%d\r\n", __func__, (uint32_t) addr, func, line);
#endif
    BL_FreeDMA(addr);
}


int unsigned_to_signed(int in, int bit) {
    uint8_t  *b = (uint8_t*)BLAI_MALLOC(bit * sizeof(uint8_t));
    uint32_t output = 0;
    for (int i = 0; i < bit; i++) {
        b[i] = (in >> i) % 2;
    }
    output = (abs(b[bit - 1] % 2) == 1) ? ~output : 0;
    output = (output >> bit) << bit;
    output += in;
    BLAI_FREE(b);
    return (int)output;
}

float fixed_to_float(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS)
{
    return ((float)input / (float)(1 << FIXED_POINT_FRACTIONAL_BITS));
}

fixed_point_t fixed32_to_fixed8(int32_t input, int FIXED_POINT_FRACTIONAL_BITS)
{
    fixed_point_t output;
    int32_t mod;
    int32_t output_32 = (FIXED_POINT_FRACTIONAL_BITS > 0) ? (input >> FIXED_POINT_FRACTIONAL_BITS)
        : (input << abs(FIXED_POINT_FRACTIONAL_BITS));
    output = (fixed_point_t)output_32;
    if (abs(abs(input) - abs(output_32 << FIXED_POINT_FRACTIONAL_BITS)) >= (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input > 0)
        mod = 1;
    else
        mod = (abs(abs(input) - abs(output_32 << FIXED_POINT_FRACTIONAL_BITS)) > (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input < 0) ? 1 : 0;
    output = (FIXED_POINT_FRACTIONAL_BITS > 0 && output < INT8_MAX) ? output + mod : output;

    if (output_32 > INT8_MAX)
        output = INT8_MAX;
    if (output_32 < INT8_MIN)
        output = INT8_MIN;

    return output;
}

fixed_point_t fixed8_to_fixed8(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS)
{
    fixed_point_t output = 0;
    fixed_point_t mod;
    int32_t input_32 = (int32_t)input;
    int32_t output_32 = (FIXED_POINT_FRACTIONAL_BITS > 0) ? (input_32 >> FIXED_POINT_FRACTIONAL_BITS)
        : (input_32 << abs(FIXED_POINT_FRACTIONAL_BITS));
    output = (fixed_point_t)output_32;
    if (abs(abs(input) - abs(output_32 << FIXED_POINT_FRACTIONAL_BITS)) >= (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input > 0)
        mod = 1;
    else
        mod = (abs(abs(input) - abs(output_32 << FIXED_POINT_FRACTIONAL_BITS)) > (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input < 0) ? 1 : 0;
    output = (FIXED_POINT_FRACTIONAL_BITS > 0 && output < INT8_MAX) ? output + mod : output;

    if (output_32 > INT8_MAX)
        output = INT8_MAX;
    if (output_32 < INT8_MIN)
        output = INT8_MIN;

    return output;
}

int32_t fixed32_to_fixed32(int32_t input, int FIXED_POINT_FRACTIONAL_BITS)
{
    int32_t mod;
    int64_t output = (FIXED_POINT_FRACTIONAL_BITS > 0) ? ((int64_t)input >> FIXED_POINT_FRACTIONAL_BITS)
        : ((int64_t)input << abs(FIXED_POINT_FRACTIONAL_BITS));

    if (abs(abs(input) - abs(output << FIXED_POINT_FRACTIONAL_BITS)) >= (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input > 0)
        mod = 1;
    else
        mod = (abs(abs(input) - abs(output << FIXED_POINT_FRACTIONAL_BITS)) > (1 << (FIXED_POINT_FRACTIONAL_BITS - 1)) && input < 0) ? 1 : 0;

    output = (FIXED_POINT_FRACTIONAL_BITS > 0) ? output + mod : output;
    output = (output < INT32_MIN) ? INT32_MIN : (output > INT32_MAX) ? INT32_MAX : output;

    return (int32_t)output;
}

fixed_point_t float_to_fixed(float input, int FIXED_POINT_FRACTIONAL_BITS)
{
    int SIGN_BIT = 1;
    float output;
    float sat_p = pow(2, FP_bits - SIGN_BIT - FIXED_POINT_FRACTIONAL_BITS);
    float min_p = (float)1 / (1 << FIXED_POINT_FRACTIONAL_BITS);
    if (input > sat_p - min_p) output = sat_p - min_p;
    else if (input < -sat_p) output = -sat_p;
    else output = input;

    return (fixed_point_t)(round(output * (1 << FIXED_POINT_FRACTIONAL_BITS)));
}

int32_t fixed8_to_fixed32(fixed_point_t input, int FIXED_POINT_FRACTIONAL_BITS)
{
    int32_t output = (FIXED_POINT_FRACTIONAL_BITS > 0) ? (int32_t)(input >> FIXED_POINT_FRACTIONAL_BITS)
        : (int32_t)(input << abs(FIXED_POINT_FRACTIONAL_BITS));

    return output;
}

int fetch_info(uint8_t* inst, int base, int len) {
    int output = 0;
    for (int j = 0; j < len; j++) {
        int w_off = base;
        int sub_i = (j + w_off) / 8;
        int index = j + w_off - 8 * sub_i;
        output += ((*(inst + sub_i) >> index) % 2) * pow(2, j);
    }
    return output;
}

int8_t* MEM_PTR(int mux, fixed_point_t* DATA_buf, int PATCH_SIZE) {
    return DATA_buf + mux * PATCH_SIZE;
}


void set_output_wh(struct blai_net_info_t* net, int layer_cnt) {
    bool pool_layer = (net->layers[layer_cnt].type == CONV_MAX || net->layers[layer_cnt].type == ROUTE_MAX);
    bool upsample_layer = net->layers[layer_cnt].type == UPSAMPLE || net->layers[layer_cnt].type == ROUTE_UPSAMPLE;

    int stride = (net->layers[layer_cnt].stride < 1) ? 1 : net->layers[layer_cnt].stride;
    bool mod_w = (net->layers[layer_cnt].w % stride == 1);
    bool mod_h = (net->layers[layer_cnt].h % stride == 1);

    net->layers[layer_cnt].stride = (net->layers[layer_cnt].stride > 0) ? net->layers[layer_cnt].stride : 1;
//    net->layers[layer_cnt].out_w = (upsample_layer) ? net->layers[layer_cnt].w * 2 : (pool_layer) ? net->layers[layer_cnt].w / 2 : net->layers[layer_cnt].w / net->layers[layer_cnt].stride;
//    net->layers[layer_cnt].out_h = (upsample_layer) ? net->layers[layer_cnt].h * 2 : (pool_layer) ? net->layers[layer_cnt].h / 2 : net->layers[layer_cnt].h / net->layers[layer_cnt].stride;
    net->layers[layer_cnt].out_w = (upsample_layer) ? net->layers[layer_cnt].w * 2 : net->layers[layer_cnt].out_w;
    net->layers[layer_cnt].out_h = (upsample_layer) ? net->layers[layer_cnt].h * 2 : net->layers[layer_cnt].out_h;

    net->layers[layer_cnt].stride = (upsample_layer) ? 2 : net->layers[layer_cnt].stride;

    if (net->layers[layer_cnt].type == TRANSPOSE) {

        int c_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 1];
        int w_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 2];
        int h_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 3];

        net->layers[layer_cnt].out_c = (c_perm_mux == 1) ? net->layers[layer_cnt].h : (c_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
        net->layers[layer_cnt].out_w = (w_perm_mux == 1) ? net->layers[layer_cnt].h : (w_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
        net->layers[layer_cnt].out_h = (h_perm_mux == 1) ? net->layers[layer_cnt].h : (h_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
    }
}

void set_output_wh_later(struct blai_net_info_t* net, int layer_cnt) {
    if (net->layers[layer_cnt].type == TRANSPOSE) {

        int c_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 1];
        int w_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 2];
        int h_perm_mux = net->layers[layer_cnt].mask[net->layers[layer_cnt].n - 3];
        if (net->layers[layer_cnt].n == 4) {
            net->layers[layer_cnt].out_c = (c_perm_mux == 1) ? net->layers[layer_cnt].h : (c_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
            net->layers[layer_cnt].out_w = (w_perm_mux == 1) ? net->layers[layer_cnt].h : (w_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
            net->layers[layer_cnt].out_h = (h_perm_mux == 1) ? net->layers[layer_cnt].h : (h_perm_mux == 2) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
        }
        else {
            net->layers[layer_cnt].out_c = (c_perm_mux == 0) ? net->layers[layer_cnt].h : (c_perm_mux == 1) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
            net->layers[layer_cnt].out_w = (w_perm_mux == 0) ? net->layers[layer_cnt].h : (w_perm_mux == 1) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
            net->layers[layer_cnt].out_h = (h_perm_mux == 0) ? net->layers[layer_cnt].h : (h_perm_mux == 1) ? net->layers[layer_cnt].w : net->layers[layer_cnt].c;
        }
    }
    if (net->layers[layer_cnt].type == PAD) {
        net->layers[layer_cnt].out_c = net->layers[layer_cnt].c + 2 * net->layers[layer_cnt].biases[0];
        net->layers[layer_cnt].out_w = net->layers[layer_cnt].w + 2 * net->layers[layer_cnt].biases[2];
        net->layers[layer_cnt].out_h = net->layers[layer_cnt].h + 2 * net->layers[layer_cnt].biases[4];
    }
    if (net->layers[layer_cnt].type == TRANSPOSE_LK) {
         net->layers[layer_cnt].size = net->layers[layer_cnt].tf_input1_multiplier;
        int l_size = (net->layers[layer_cnt].tf_input1_multiplier % 4 == 0) ? net->layers[layer_cnt].tf_input1_multiplier : (net->layers[layer_cnt].tf_input1_multiplier / 4 + 1) * 4;
        int dilation_width_factor = net->layers[layer_cnt].tf_input1_offset;
        int dilation_height_factor = net->layers[layer_cnt].tf_input2_offset;
        int dila_h = (net->layers[layer_cnt].w == 1) ? dilation_height_factor : dilation_width_factor;
        int fetch_size = (dila_h == 2) ? net->layers[layer_cnt].tf_input1_multiplier * dila_h - 1 : net->layers[layer_cnt].tf_input1_multiplier;
        net->layers[layer_cnt].out_c = net->layers[layer_cnt].c * l_size;
        net->layers[layer_cnt].out_w = net->layers[layer_cnt].w;
        net->layers[layer_cnt].out_h = (net->layers[layer_cnt].h - fetch_size + 1) / net->layers[layer_cnt].stride;
    }
}


void set_npu_output_wh(struct blai_net_info_t* net, int layer_cnt) {
    bool pool_layer = (net->npu_layers[layer_cnt].type == CONV_MAX || net->npu_layers[layer_cnt].type == ROUTE_MAX);
    bool upsample_layer = net->npu_layers[layer_cnt].type == UPSAMPLE || net->npu_layers[layer_cnt].type == ROUTE_UPSAMPLE;

    net->npu_layers[layer_cnt].stride = (net->npu_layers[layer_cnt].stride > 0) ? net->npu_layers[layer_cnt].stride : 1;
    net->npu_layers[layer_cnt].out_w = (upsample_layer) ? net->npu_layers[layer_cnt].w * 2
        : (pool_layer) ? net->npu_layers[layer_cnt].w / 2 : net->npu_layers[layer_cnt].w / net->npu_layers[layer_cnt].stride;
    net->npu_layers[layer_cnt].out_h = (upsample_layer) ? net->npu_layers[layer_cnt].h * 2
        : (pool_layer) ? net->npu_layers[layer_cnt].h / 2 : net->npu_layers[layer_cnt].h / net->npu_layers[layer_cnt].stride;
    net->npu_layers[layer_cnt].stride = (upsample_layer) ? 2 : net->npu_layers[layer_cnt].stride;
}

void check_merge_layer(struct blai_net_info_t* net, int layer_cnt) {
    bool merge_layer = (net->layers[layer_cnt].type == CONV_MAX
        || net->layers[layer_cnt].type == ROUTE_CONV
        || net->layers[layer_cnt].type == ROUTE_MAX
        || net->layers[layer_cnt].type == ROUTE_UPSAMPLE);
    net->layer_cnt = (merge_layer) ? net->layer_cnt - 1 : net->layer_cnt;
}

bool check_combomax_layer(struct cpu_inst_layer_t* l) {
       return (l->type == MAXPOOL && l->stride == 2 && l->size == 2);
}

bool check_upsample_layer(struct cpu_inst_layer_t* l) {
    return (l->type == UPSAMPLE || l->type == ROUTE_UPSAMPLE);
}

bool check_conv_layer(struct cpu_inst_layer_t* l) {
    return (l->type == CONVOLUTIONAL || l->type == CONV_MAX || l->type == ROUTE_CONV);
}

bool check_weight_layer(struct cpu_inst_layer_t* l) {
    return (l->type == CONVOLUTIONAL || l->type == CONV_MAX || l->type == ROUTE_CONV || l->type == MATMUL);
}

bool check_MultiInput_layer(struct cpu_inst_layer_t* l) {
    return (l->type == ROUTE_MAX || l->type == ROUTE_CONV || l->type == ROUTE_UPSAMPLE || l->type == ROUTE || l->type == SHORTCUT || l->type == ROUTE_W || l->type == SSD);
}

bool check_route_layer(struct cpu_inst_layer_t* l) {
    return (l->type == ROUTE_MAX || l->type == ROUTE_CONV || l->type == ROUTE_UPSAMPLE || l->type == ROUTE || l->type == ROUTE_W);
}

bool check_combine_layer(struct cpu_inst_layer_t* l) {
    return (l->type == CONV_MAX || l->type == ROUTE_MAX || l->type == ROUTE_CONV || l->type == ROUTE_UPSAMPLE);
}

