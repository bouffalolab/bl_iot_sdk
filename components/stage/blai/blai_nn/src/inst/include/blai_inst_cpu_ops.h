#ifndef __BLAI_INST_CPU_OPS_H__
#define __BLAI_INST_CPU_OPS_H__

#include "blai_inst_cpu_activation.h"
#include "blai_inst_obj_det_ops.h"

struct BoxCornerEncoding {
    float ymin;
    float xmin;
    float ymax;
    float xmax;
};

struct CenterSizeEncoding {
    float y;
    float x;
    float h;
    float w;
};

struct BLAI_data_t {
    int image_width, image_height;
    char* name_list;
};

fixed_point_t MEM_RW(int write, int addr, fixed_point_t in, int mux, fixed_point_t* DATA_buf, int patch_size);
float MEM_RW_F32(int write, int addr, float in, int mux, fixed_point_t* DATA_buf, int patch_size);
void fetch_data(struct cpu_inst_layer_t* l, fixed_point_t* data_in, int data_index, int SRAM_in, int win, int hin, fixed_point_t padding, fixed_point_t* DATA_buf, int patch_size);
void fetch_data_even(struct cpu_inst_layer_t* l, fixed_point_t* data_in, int data_index, int SRAM_in, int win, int hin, fixed_point_t padding, fixed_point_t* DATA_buf, int patch_size);
int32_t PE_CONV(fixed_point_t* data_in, fixed_point_t* weights, int size, int unsgn);
int32_t PE_LEAKY(int32_t pass_data);
int32_t PE_RELU(int32_t pass_data);
int32_t PE_RELU6(int32_t pass_data, int fshift);
int32_t PE_RELUN(int32_t pass_data, int fshift, int n);
fixed_point_t PE_MISH(int32_t pass_data, int fin, int fout);

void forward_CONVOLUTIONAL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_CONVOLUTIONAL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current);
void forward_DEPTHWISE_CONVOLUTIONAL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current);
void forward_CONVOLUTIONAL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_CONV_MAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_CONV_MAX(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_MAXPOOL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_MAXPOOL_tflite_nmsis(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current);
void forward_MAXPOOL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_AVGPOOL_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_CONV(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_UPSAMPLE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_UPSAMPLE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_MAX(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_W_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_ROUTE_MAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_SHORTCUT(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_SHORTCUT_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_YOLO(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_YOLO_lm(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_RESHAPE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_PRE_TRANSCONV_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_TRANSPOSE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_TRANSPOSELK_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_TRANSPOSELK_V2_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_PAD_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_MEAN_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_LOGISTIC_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_SOFTMAX_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_MATMUL(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);
void forward_SSD_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current, struct BLAI_data_t *BL_data, const char** name_list, blai_inference_cb result_cb);
void forward_DEQUANTIZE_tflite(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current);

#endif // __BLAI_INST_CPU_OPS_H__
