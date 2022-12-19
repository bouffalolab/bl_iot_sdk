#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bl808.h"
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"

bool check_BLAI_NPU_RUN(struct blai_net_info_t* net, struct cpu_inst_layer_t* l) {
    bool npu_run = false;
    // 808b0 stride subsample work around
    int remainder_p = (l->w % 2) + (l->h % 2);

    switch (l->type) {
    case CONVOLUTIONAL:
        npu_run = (l->size > 7 || l->dilation > 2 || l->stride > 2) ? false : (l->stride == 2 && remainder_p == 1) ? false : true;
        break;
    case CONV_MAX:
        npu_run = (l->size > 7 || l->dilation > 2 || l->stride > 2) ? false : true;
        break;
    case ROUTE_CONV:
        npu_run = (l->size > 7 || l->dilation > 2 || l->stride > 2) ? false : true;
        break;
    case MAXPOOL:
        npu_run = (l->size > 3 || l->stride > 2) ? false : true;
        break;
    case ROUTE_MAX:
    case ROUTE:
    case ROUTE_UPSAMPLE:
    case UPSAMPLE:
    case MATMUL:
    case SHORTCUT:
        npu_run = true;
        break;
    default:
        npu_run = false;
        break;
    }
    return npu_run;
}

bool BLAI_encode(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, int l_current, struct PSRAM_ctrl* ctrl) {

    bool npu_run = check_BLAI_NPU_RUN(net, l);
    if (!npu_run)
        return false;

    bool npu_alloc_success = BLAI_MEM_alloc(net, l, ctrl);

    if (!npu_alloc_success)
        return false;

    memset(l->NPU_inst, 0, MAX_Input_num*NPU_INST_SIZE_BYTE*3);

    if ((l->type == ROUTE || l->type == ROUTE_MAX) && l->input_num > 2)
        fetch_BLAI_data_route(net, l, ctrl, l_current);
    else
        fetch_BLAI_data_general(net, l, ctrl, l_current);

    return true;
}

static void gen_npu_inst_layer(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, int l_current) {
    struct PSRAM_ctrl ctrl = { 0 };

    bool npu_on = BLAI_encode(net, l, l_current, &ctrl);
    l->NPU_on = npu_on;
    if (npu_on == false)
        return;
    l->buf_size = net->layers[l_current].DRAM_patch_num * ctrl.PSRAM_patch_size;    
    //l->DRAM_in = ctrl.SRAM_in;
    memcpy(l->DRAM_in, ctrl.SRAM_in, sizeof(ctrl.SRAM_in));
    l->DRAM_mid_out = ctrl.SRAM_mid_out;
    //l->DRAM_out = ctrl.SRAM_out;
    memcpy(l->DRAM_out, ctrl.SRAM_out, sizeof(ctrl.SRAM_out));
    l->DRAM_patch_size = ctrl.PSRAM_patch_size;
    l->DRAM_weight = ctrl.SRAM_weight;
    l->DRAM_bias = ctrl.SRAM_bias;
}

void Load_NPU_data_to_tensor(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int layer_cnt) {
    // Load data from buf
    int out_c = l->out_c;
    out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    if (l->out_c % 4 == 0) {
        csi_dcache_invalid_range(DATA_buf + l->DRAM_out[0] * l->DRAM_patch_size, l->out_w * l->out_h * l->out_c * sizeof(fixed_point_t));
        memcpy(l->output_i8, DATA_buf + l->DRAM_out[0] * l->DRAM_patch_size, l->out_w * l->out_h * l->out_c * sizeof(fixed_point_t));
    }
    else {
        csi_dcache_invalid_range(DATA_buf + l->DRAM_out[0] * l->DRAM_patch_size, l->w * l->h * out_c * sizeof(fixed_point_t));
        for (int i = 0; i < l->w * l->h; i++) {
            int index = i * out_c;
            int index_out = i * l->out_c;            
            memcpy(l->output_i8 + index_out, DATA_buf + l->DRAM_out[0] * l->DRAM_patch_size + index, l->out_c * sizeof(fixed_point_t));
        }
    }
#ifdef BLAI_NPU_OPS_DEBUG
    BL_LOGI("l->output_i8=0x%x, l->DRAM_out[0]=%d, size = %ld\r\n", (uint32_t)l->output_i8, l->DRAM_out[0], l->out_w * l->out_h * out_c * sizeof(fixed_point_t));
#endif
    if (l->mid_out) {
        bool ROUTE_CHECK = (l->type == ROUTE_CONV || l->type == ROUTE_MAX || l->type == ROUTE_UPSAMPLE || l->type == ROUTE);
        int input_c = l->c;
        if (ROUTE_CHECK)
            for (int i = 0; i < l->n - 1; i++)
                input_c += l->cn[i];
        int mem_size = (l->type == CONV_MAX) ? l->w * l->h * l->out_c : l->w * l->h * input_c;

        csi_dcache_invalid_range(DATA_buf + l->DRAM_mid_out * l->DRAM_patch_size, mem_size * sizeof(fixed_point_t));
        memcpy(l->mid_output_i8, DATA_buf + l->DRAM_mid_out * l->DRAM_patch_size, mem_size * sizeof(fixed_point_t));
#ifdef BLAI_NPU_OPS_DEBUG
        BL_LOGI("l->mid_output_i8=0x%x, l->DRAM_mid_out=%d, size = %d\r\n", (uint32_t)l->mid_output_i8, l->DRAM_mid_out, mem_size);
#endif
    }
}

void Store_tensor_data_to_NPU(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int layer_cnt) {
    int pad_c = l->c;
    if (layer_cnt == 0 && l->c == 3) 
        pad_c = 4;
    // Store data from tensor to buf
    int first_layer_pad = (layer_cnt == 0) && ((l->c == 3) || (l->c == 1));
    if (l->c % 4 == 0 || first_layer_pad) {
        memcpy(DATA_buf + l->DRAM_in[0] * l->DRAM_patch_size, l->input_i8[0], l->w * l->h * pad_c * sizeof(fixed_point_t));
        csi_dcache_clean_range(DATA_buf + l->DRAM_in[0] * l->DRAM_patch_size,l->w * l->h * pad_c * sizeof(fixed_point_t));
    } else {
        for (int i = 0; i < l->w * l->h; i++) {
            pad_c = (l->c / 4 + 1) * 4;
            int index = i * pad_c;
            int index_in = i * l->c;
            memcpy(DATA_buf + l->DRAM_in[0] * l->DRAM_patch_size + index, l->input_i8[0] + index_in, l->c * sizeof(fixed_point_t));
            memset(DATA_buf + l->DRAM_in[0] * l->DRAM_patch_size + index + l->c, 0, (pad_c - l->c) * sizeof(fixed_point_t));
        }
        csi_dcache_clean_range(DATA_buf + l->DRAM_in[0] * l->DRAM_patch_size, l->w * l->h * pad_c * sizeof(fixed_point_t));
    }
#ifdef BLAI_NPU_OPS_DEBUG
    BL_LOGI("[%s] dram_in[0]=%d size %ld\r\n", __func__, l->DRAM_in[0], l->w * l->h * pad_c * sizeof(fixed_point_t));
#endif
    bool multi_input_layer = check_MultiInput_layer(l);
    if (l->input_num > 1 && multi_input_layer) {
        for (int k = 1; k < l->input_num; k++) {
            if (l->cn[k - 1] % 4 == 0) {
                memcpy(DATA_buf + l->DRAM_in[k] * l->DRAM_patch_size, l->input_i8[k], l->w * l->h * l->cn[k - 1] * sizeof(fixed_point_t));
                csi_dcache_clean_range(DATA_buf + l->DRAM_in[k] * l->DRAM_patch_size, l->w * l->h * l->cn[k - 1] * sizeof(fixed_point_t));
            } else {
                int pad_cn = (l->cn[k - 1] / 4 + 1) * 4;
                for (int i = 0; i < l->w * l->h; i++) {
                    int index = i * pad_cn;
                    int index_in = i * l->cn[k-1];
                    memcpy(DATA_buf + l->DRAM_in[k] * l->DRAM_patch_size + index, l->input_i8[k] + index_in, l->cn[k - 1] * sizeof(fixed_point_t));
                    memset(DATA_buf + l->DRAM_in[k] * l->DRAM_patch_size + index + l->cn[k - 1], 0, (pad_cn - l->cn[k - 1]) * sizeof(fixed_point_t));
                }
                csi_dcache_clean_range(DATA_buf + l->DRAM_in[k] * l->DRAM_patch_size,  l->w * l->h * pad_cn * sizeof(fixed_point_t));
            }
        }
    }
}

bool forward_NPU(struct blai_net_info_t* net, fixed_point_t* DATA_buf, int l_current) {
    struct cpu_inst_layer_t *l = &net->layers[l_current];
    fixed_point_t* weight_buf = NULL;
    int* bias_buf = NULL;
    uint32_t patch_size = 0;

    /***********************************
            NPU patch_size: l.DRAM_patch_size
            NPU patch_num:  l.DRAM_patch_num
            NPU input buf  : DATA_buf + l.DRAM_in * l.DRAM_patch_size
            NPU output buf : DATA_buf + l.DRAM_out * l.DRAM_patch_size
            NPU weight buf : DATA_buf + l.DRAM_weight * l.DRAM_patch_size
            NPU bias buf   : DATA_buf + l.DRAM_bias * l.DRAM_patch_size
            NPU instruction: l.NPU_inst
    ************************************/
    l->NPU_inst = net->npu_inst_buf;
    gen_npu_inst_layer(net, l, l_current);
    if (l->NPU_on == false)
        return false;
    bool weight_layer = check_weight_layer(l);
    if (weight_layer) {
        int weight_size = ((l->DRAM_nweight * sizeof(fixed_point_t) + 3) >> 2) << 2;
        int bias_size = l->DRAM_nbias * sizeof(int);
        weight_buf = (fixed_point_t*)BLAI_MALLOC(weight_size + bias_size);
        bias_buf = (int* ) (weight_buf + weight_size);
        Load_NPU_weights(l, DATA_buf, weight_buf, bias_buf, net->use_tflite);
#ifdef BLAI_NPU_OPS_DEBUG
        BL_LOGI("[%s] weight_buf: 0x%x, bias_buf: 0x%x\r\n", __func__, (uint32_t)weight_buf, (uint32_t)bias_buf);
#endif   
    }
    patch_size = l->DRAM_patch_size;
#ifdef BLAI_NPU_OPS_DEBUG
    BL_LOGI("[%s] patch_size: %d\r\n", __func__, patch_size);
#endif
    Store_tensor_data_to_NPU(net, l, DATA_buf, l_current);
#ifdef BLAI_PROFILING
    TickType_t tick_process = xTaskGetTickCount();
#endif
    blai_npu_exec_lock_required();
    blai_npu_layer_config((uint8_t *)l->NPU_inst, (uint8_t *)weight_buf, (uint8_t *)bias_buf,
        (uint8_t *)DATA_buf, patch_size, l_current == 0);
#ifdef BLAI_NPU_OPS_DEBUG
    uint32_t *baddr = 0x30024000;
    for (int i = 0; i < 12; i+=4)
        BL_LOGI("0x%08x - 0x%08x, 0x%08x, 0x%08x, 0x%08x\r\n", (uint32_t) (baddr+i), *(baddr+i) & 0xFFFFFFFF, *(baddr+i+1) & 0xFFFFFFFF, *(baddr+i+2) & 0xFFFFFFFF, *(baddr+i+3) & 0xFFFFFFFF);
#endif
    blai_npu_inference();
    blai_npu_stop();
    blai_npu_exec_lock_release(0);
#ifdef BLAI_PROFILING
    if (net->parent)
        ((BLAI_Model_t *)net->parent)->inst.npu.process_time += (xTaskGetTickCount() - tick_process);
#endif
    Load_NPU_data_to_tensor(net, l, DATA_buf, l_current);
    if (weight_buf)
        BLAI_FREE(weight_buf);
    return true;
}
