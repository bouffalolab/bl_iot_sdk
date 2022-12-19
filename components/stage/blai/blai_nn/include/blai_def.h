#ifndef __BLAI_DEF_H__
#define __BLAI_DEF_H__

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdbool.h>

typedef int8_t fixed_point_t;
typedef uint8_t* blai_model_hdl_t;

#define MAX_Input_num       (8)
#define MAX_Output_num      (10)

#define MAX_WEI_PATCH_NUM   (64)   
#define INST_MAX_PATCH_NUM  (32)
#define NPU_INST_SIZE_BYTE  (16)
#define FP_bits             (8)


typedef enum {
    BLAI_DEVICE_CPU = 0,
    BLAI_DEVICE_NPU = 1,
    BLAI_DEVICE_UNKNOWN,
} BLAI_Device_Type_e;

typedef enum {
    BLAI_FEATURE_LEVEL_1 = 0,
    BLAI_FEATURE_LEVEL_UNKNOWN,
} BLAI_Feature_Level_e;

typedef enum {
    BLAI_PADDING_SAME = 1,
    BLAI_PADDING_VALID = 2
} BLAI_Padding_Mode_e;

typedef enum {
    BLAI_STATUS_NO_ERROR = 0,
    BLAI_STATUS_OUT_OF_MEMORY,
    BLAI_STATUS_INCOMPLETE,
    BLAI_STATUS_BAD_DATA,
    BLAI_STATUS_OP_FAILED,
    BLAI_STATUS_UNAVAILABLE_DEVICE,
    BLAI_STATUS_INVALID_INPUT,
} BLAI_Status_e;

typedef enum {
    BLAI_PROCESS_START = 0,
    BLAI_PROCESS_STOP,
    BLAI_PROCESS_RESUME,
    BLAI_PROCESS_CPU,
    BLAI_PROCESS_NPU,
    BLAI_PROCESS_DONE,
    BLAI_PROCESS_FAIL,
} BLAI_ProcStatus_e;

typedef enum {
    CONVOLUTIONAL,
    MAXPOOL,
    AVGPOOL,
    ROUTE,
    SHORTCUT,
    MATMUL,
    UPSAMPLE,
    YOLO,
    SOFTMAX,
    CONV_MAX,
    ROUTE_MAX,
    ROUTE_CONV,
    ROUTE_UPSAMPLE,
    RESHAPE,
    ROUTE_W,
    LOGISTIC_L,
    SSD,
    TRANSPOSE,
    PAD,
    LOG_SOFTMAX,
    DEQUANTIZE,
    TRANSPOSE_LK,
    MEAN,
    GATHER,  
    CUSTOM_L,
    PRE_TRANSCONV,
    UNKNOWN
} LAYER_TYPE;

typedef enum {
    LEAKY, RELU, LINEAR, RELU6, MISH, ELU, RELIE, LOGISTIC, RAMP, TANH, PLSE, LOGGY, STAIR, HARDTAN, LHTAN, SELU, GELU, SWISH, NORM_CHAN, NORM_CHAN_SOFTMAX, NORM_CHAN_SOFTMAX_MAXVAL, RELUN
} ACTIVATION;

typedef enum {
    DSP_HEADER, LAYER_INFO, GENERAL_FORM, DSP_STATUS, YOLO_INFO, EXTRA_LAYER, EXTRA_MULTIPLIER, TFLITE_MULTIPLIER, TFLITE_FLOAT, EXTRA_LAYER_6_8, EXTRA_MULTIPLIER_6_8, SSD_INFO, INPUT_LAYERS, DETAIL_GENERAL_FORM
} INSTRUCTION_TYPE;

enum APPLICATION_TYPE {
    CLASSIFICATION, OBJECT_DETECTION, KEYPOINT_DETECTION, FACE_RECONGNITION, FACE_LANDMARK, KEYWORD_SPOTTING, CUSTOM, RETINA_FACE, RETINA_PERSON, FR_REGISTRATION, FR_EVALUATION, RETINA
};

struct PSRAM_ctrl {
    int SRAM_in[MAX_Input_num];
    int SRAM_in_2;
    int SRAM_out[MAX_Input_num];
    int SRAM_mid_out;
    int SRAM_weight;
    int SRAM_bias;
    int dw_groups;

    int wei_patch_num;
    int line_patch_num;
    int line_w_0;
    int wei_patch_out_c[MAX_WEI_PATCH_NUM];
    int line_patch_w[MAX_WEI_PATCH_NUM];
    int psram_num;

    int PSRAM_patch_size;
    int PSRAM_patch_num;

    int PSRAM_mid_patch_num;
};

struct cpu_inst_layer_t {
    int type;
    int activation;
    bool output_layer;
    

    int h, w, c;
    int cn[MAX_Input_num - 1];
    int out_h, out_w, out_c;
    int n;
    int groups;
    int size;
    int stride;
    int dilation;
    int img_in;

    int in_layer1_mem;
    int in_layer2_mem;
    int out_layer_mem;
    int* in_layer_mem_n;
    int mid_layer_mem;
    int mid_out;
    int input_num;
    int halt; // for npu

    int fdata;
    int fweight;
    int fbias;
    int fout;
    int froute1;
    int froute2;
    int *frouten;

    int tf_input1_offset, tf_input2_offset;
    int* tf_input_offset_extra;
    int tf_input1_shift, tf_input2_shift;
    int* tf_input_shift_extra;
    int tf_output_offset;
    int tf_output_shift;    
    int tf_route_input_shift;
    int tf_route_input_multiplier;
    int quantized_activation_min, quantized_activation_max;
    int tf_input1_multiplier, tf_input2_multiplier, tf_output_multiplier;
    int* tf_input_multiplier_extra;
    int tf_left_shift;
    int axis;
    float input_scale, input2_scale, input3_scale, output_scale;
    
    int NPU_on;
    int DSP_on;

    int *weights;
    int *biases;

    // detail layer infomation
    int data_type;
    int size_x, size_y;
    int stride_x, stride_y;
    int padding_x, padding_y;
    bool detail_layer_form;

    float *output;
    float* mid_output;
    float* input[MAX_Input_num];

    fixed_point_t* output_i8;
    fixed_point_t* mid_output_i8;
    fixed_point_t* input_i8[MAX_Input_num];

    int classes;
    int total;
    int* mask;

    // TFLITE SSD INFO
    int w_scale, h_scale, x_scale, y_scale;
    int max_classes_per_detection;
    int max_detections;
    int anchors_offset;

    // GRAPH 
    int builtin_code;
    int layer_offset;
    int input_layers[MAX_Input_num];
    int graph_layer[2];

    int release_layers[8];
    int release_num;
    int release_mid_layers[8];
    int release_mid_num;

    // NPU
    fixed_point_t* NPU_inst;
    int inst_cnt;
    int buf_size;
    int DRAM_in[MAX_Input_num];
    int DRAM_out[MAX_Input_num];
    int DRAM_mid_out;
    int DRAM_patch_size;
    int DRAM_WEI_patch_num;
    int DRAM_patch_num;
    int DRAM_weight;
    int DRAM_nweight;
    int DRAM_bias;
    int DRAM_nbias;
};

struct blai_net_info_t {
    void *parent;
    struct cpu_inst_layer_t *layers;
    struct cpu_inst_layer_t *npu_layers;
    int* graph_layer_to_layer;
    float* input;
    fixed_point_t* input_i8;
    fixed_point_t* output_i8;
    fixed_point_t* npu_inst_buf[MAX_Input_num*NPU_INST_SIZE_BYTE*3];
    int cur_layer;
    int layer_cnt;
    int npu_layer_cnt;
    int mode;
    int w, h, c;
    uint16_t BLAI_version;
    int patch_size;
    int patch_count;
    int unsign_input;
    int relu_n;
    int use_tflite;
    int app_type;
    int use_npu_accel;
    int output_num;
    int output_layer[MAX_Output_num];
    float* prior_bbox;
    int prior_bbox_num;
    float* LUT;
    float* LUT2;
    uint8_t custom_postprocess;
};

struct blai_model_info_t {
    struct {
        uint8_t *inst_buf;
        uint8_t *weights_buf;
        uint8_t *bias_buf;
        uint32_t inst_buf_size;
        uint32_t weights_buf_size;
        uint32_t bias_buf_size;
        TickType_t process_time;
    } cpu;
    struct {
        uint8_t *inst_buf;
        uint8_t *weights_buf;
        uint8_t *bias_buf;
        uint32_t inst_buf_size;
        uint32_t weights_buf_size;
        uint32_t bias_buf_size;
        TickType_t process_time;
    } npu;    
};

struct blai_result_t {
    union {
        struct {
            int best_class;
            float prob;
            struct {
                uint32_t x;
                uint32_t y;
                uint32_t w;
                uint32_t h;
            } rect;
        } objdet;
        struct {
            int best_class;
        } classification;
        struct {
            int best_class;
        } fr;
        struct {
            int best_class;
            float prob;
            struct {
                uint32_t x;
                uint32_t y;
                uint32_t w;
                uint32_t h;
            } rect;
            struct {
                int pos;
                uint32_t x;
                uint32_t y;
            } lx1;
            struct {
                int pos;
                uint32_t x;
                uint32_t y;
            } lx2;
            struct {
                int pos;
                uint32_t x;
                uint32_t y;
            } lx3;
            struct {
                int pos;
                uint32_t x;
                uint32_t y;
            } lx4;
            struct {
                int pos;
                uint32_t x;
                uint32_t y;
            } lx5;
        } landmark;
    } r;
    int app_type;
};


typedef void (* blai_inference_cb)(struct blai_result_t* detect_result);
typedef void (* blai_custom_postproc_cb)(struct blai_net_info_t* net, fixed_point_t* DATA_buf, int layer, int size);


typedef struct {
    struct blai_model_info_t inst;
    BLAI_Device_Type_e dev;
    BLAI_Feature_Level_e level;
    uint8_t *buffer;
    uint8_t share_buffer;
    struct blai_net_info_t* net;
    blai_inference_cb result_cb;
    blai_custom_postproc_cb custom_postproc_cb;
    union {
        struct {
            const char **classes_name;
            int classes_num;
        } classification;
        struct {
            const char **names;
            int names_num;            
            const float **features_list;
            int features_num;
        } face_recongnition;
    } post_info;
    struct {
        uint32_t width;
        uint32_t height;
    } in;
    struct {
        uint32_t width;
        uint32_t height;
    } out;
} BLAI_Model_t;

static const char* const tflite_230_names[128] = {
    "ADD",
    "AVERAGE_POOL_2D",
    "CONCATENATION",
    "CONV_2D",
    "DEPTHWISE_CONV_2D",
    "DEPTH_TO_SPACE",
    "DEQUANTIZE",
    "EMBEDDING_LOOKUP",
    "FLOOR",
    "FULLY_CONNECTED",
    "HASHTABLE_LOOKUP",
    "L2_NORMALIZATION",
    "L2_POOL_2D",
    "LOCAL_RESPONSE_NORMALIZATION",
    "LOGISTIC",
    "LSH_PROJECTION",
    "LSTM",
    "MAX_POOL_2D",
    "MUL",
    "RELU",
    "RELU_N1_TO_1",
    "RELU6",
    "RESHAPE",
    "RESIZE_BILINEAR",
    "RNN",
    "SOFTMAX",
    "SPACE_TO_DEPTH",
    "SVDF",
    "TANH",
    "CONCAT_EMBEDDINGS",
    "SKIP_GRAM",
    "CALL",
    "CUSTOM",
    "EMBEDDING_LOOKUP_SPARSE",
    "PAD",
    "UNIDIRECTIONAL_SEQUENCE_RNN",
    "GATHER",
    "BATCH_TO_SPACE_ND",
    "SPACE_TO_BATCH_ND",
    "TRANSPOSE",
    "MEAN",
    "SUB",
    "DIV",
    "SQUEEZE",
    "UNIDIRECTIONAL_SEQUENCE_LSTM",
    "STRIDED_SLICE",
    "BIDIRECTIONAL_SEQUENCE_RNN",
    "EXP",
    "TOPK_V2",
    "SPLIT",
    "LOG_SOFTMAX",
    "DELEGATE",
    "BIDIRECTIONAL_SEQUENCE_LSTM",
    "CAST",
    "PRELU",
    "MAXIMUM",
    "ARG_MAX",
    "MINIMUM",
    "LESS",
    "NEG",
    "PADV2",
    "GREATER",
    "GREATER_EQUAL",
    "LESS_EQUAL",
    "SELECT",
    "SLICE",
    "SIN",
    "TRANSPOSE_CONV",
    "SPARSE_TO_DENSE",
    "TILE",
    "EXPAND_DIMS",
    "EQUAL",
    "NOT_EQUAL",
    "LOG",
    "SUM",
    "SQRT",
    "RSQRT",
    "SHAPE",
    "POW",
    "ARG_MIN",
    "FAKE_QUANT",
    "REDUCE_PROD",
    "REDUCE_MAX",
    "PACK",
    "LOGICAL_OR",
    "ONE_HOT",
    "LOGICAL_AND",
    "LOGICAL_NOT",
    "UNPACK",
    "REDUCE_MIN",
    "FLOOR_DIV",
    "REDUCE_ANY",
    "SQUARE",
    "ZEROS_LIKE",
    "FILL",
    "FLOOR_MOD",
    "RANGE",
    "RESIZE_NEAREST_NEIGHBOR",
    "LEAKY_RELU",
    "SQUARED_DIFFERENCE",
    "MIRROR_PAD",
    "ABS",
    "SPLIT_V",
    "UNIQUE",
    "CEIL",
    "REVERSE_V2",
    "ADD_N",
    "GATHER_ND",
    "COS",
    "WHERE",
    "RANK",
    "ELU",
    "REVERSE_SEQUENCE",
    "MATRIX_DIAG",
    "QUANTIZE",
    "MATRIX_SET_DIAG",
    "ROUND",
    "HARD_SWISH",
    "IF",
    "WHILE",
    "NON_MAX_SUPPRESSION_V4",
    "NON_MAX_SUPPRESSION_V5",
    "SCATTER_ND",
    "SELECT_V2",
    "DENSIFY",
    "SEGMENT_SUM",
    "BATCH_MATMUL",
    "NULL"
};

#endif /* __BLAI_DEF_H__ */

