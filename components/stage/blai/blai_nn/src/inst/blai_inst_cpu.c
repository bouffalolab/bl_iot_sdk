#include <math.h>
#include <string.h> // for memset

#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"

static void assign_release_layer(struct blai_net_info_t* net);

#ifdef BLAI_SHOW_NETWORK
static void show_BLAI_network(struct blai_net_info_t *net) {
    printf("//////////////////////////////////BLAI HEADER////////////////////////////////////\r\n");
    printf("BLAI version: %d\r\n", net->BLAI_version);
    printf("Patch size: %d\r\n", net->patch_size);
    printf("Patch count: %d\r\n", net->patch_count);
    printf("Unsigned input: %d\r\n", net->unsign_input);
    printf("Relu-n: %d\r\n", net->relu_n);
    printf("Use TFLITE: %d\r\n", net->use_tflite);
    printf("Layer num: %d\r\n", net->layer_cnt);
    printf("APP type: %d\r\n", net->app_type);
    
    printf("\n//////////////////////////////////BLAI MODEL PROFILE////////////////////////////////////\r\n");
    // BLAI_status
    if (net->use_npu_accel) 
        printf("      layer                      filters  size/strd(dil)      input                output       processor  input_layer    graph_layer\r\n");
    else
        printf("      layer                      filters  size/strd(dil)      input                output       processor\r\n");
    
    struct cpu_inst_layer_t *net_layer = net->layers;
    for (int i = 0; i < net->layer_cnt; i++) {
        struct cpu_inst_layer_t *l = &net_layer[i];

        char *type = "";
        if (l->type == CONVOLUTIONAL)      type = "CONVOLUTIONAL ";
        else if (l->type == SHORTCUT)      type = "SHORTCUT      ";
        else if (l->type == ROUTE)         type = "ROUTE         ";
        else if (l->type == ROUTE_W)       type = "ROUTE_W       ";
        else if (l->type == AVGPOOL)       type = "AVGPOOL       ";
        else if (l->type == YOLO)          type = "YOLO          ";
        else if (l->type == UPSAMPLE)      type = "UPSAMPLE      ";
        else if (l->type == MAXPOOL)       type = "MAXPOOL       ";
        else if (l->type == MATMUL)        type = "MATMUL        ";
        else if (l->type == SOFTMAX)       type = "SOFTMAX       ";
        else if (l->type == CONV_MAX)      type = "CONV_MAX      ";
        else if (l->type == ROUTE_MAX)     type = "ROUTE_MAX     ";
        else if (l->type == ROUTE_CONV)    type = "ROUTE_CONV    ";
        else if (l->type == ROUTE_UPSAMPLE)type = "ROUTE_UPSAMPLE";
        else if (l->type == RESHAPE)       type = "RESHAPE       ";
        else if (l->type == LOGISTIC_L)    type = "LOGISTIC      ";
        else if (l->type == SSD)           type = "SSD           ";
        else if (l->type == TRANSPOSE)     type = "TRANSPOSE     ";
        else if (l->type == PAD)           type = "PAD           ";
        else if (l->type == DEQUANTIZE)    type = "DEQUANTIZE    ";
        else if (l->type == TRANSPOSE_LK)  type = "TRANSPOSE_LK  ";
        else if (l->type == MEAN)          type = "MEAN          ";
        else if (l->type == CUSTOM_L)      type = "CUSTOM        ";
        else if (l->type == PRE_TRANSCONV) type = "PRE_TRANSCONV ";
        else                               type = "UNKNOWN       ";

        char* process = "";
        if(net->use_npu_accel){
            bool npu_on = check_BLAI_NPU_RUN(net, l);
            if (npu_on)
                process = "NPU    ";
            else
                process = "DSP    ";
        }
        else{
            if (l->DSP_on)
                process = "DSP    ";
            else
                process = "NPU    ";

        }
        bool ROUTE_CHECK = (l->type == ROUTE_CONV || l->type == ROUTE_MAX || l->type == ROUTE_UPSAMPLE || l->type == ROUTE || l->type == ROUTE_W);
        int out_w = (l->type == ROUTE_MAX || l->type == CONV_MAX) ? l->out_w / 2 : l->out_w;
        int out_h = (l->type == ROUTE_MAX || l->type == CONV_MAX) ? l->out_h / 2 : l->out_h;
        int size_x = (l->size_x != 0) ? l->size_x : l->size;
        int size_y = (l->size_y != 0) ? l->size_y : l->size;
        int input_c = l->c;
        if (ROUTE_CHECK)
            for (int i = 0; i < l->n - 1; i++)
                input_c += l->cn[i];

        input_c = (l->type == ROUTE_W) ? l->out_c : input_c;
        if (net->use_npu_accel) {
            // BLAI_status
            int in_1 = 0;
            in_1 = (l->input_layers[0] == 1023) ? -1 : l->input_layers[0];
            int in_2 = 0;
            if (l->input_num > 1)
                in_2 = l->input_layers[1];
            char input_layer[100];
            int length = 0;
            length += snprintf(input_layer, 100-length, "%d", in_1);
            if (ROUTE_CHECK || l->type == SHORTCUT) {
                for (int k = 0; k < l->input_num - 1; k++) {
                    length += snprintf(input_layer + length, 100-length, "%d", l->input_layers[k + 1]);
                }
            }


            int combine_layer = (l->type == CONV_MAX || l->type == ROUTE_MAX || l->type == ROUTE_CONV || l->type == ROUTE_UPSAMPLE);
            char graph_layer[100];
            sprintf(graph_layer, "%d\r\n", l->graph_layer[0]);
            if (combine_layer)
                sprintf(graph_layer, "%d, %d\r\n", l->graph_layer[1], l->graph_layer[0]);
            printf("   %5d %15s %6d/%3d %3d x%2d /%2d(%d)%6d x%4d x%4d  -> %4d x%4d x%4d %10s %12s %15s\r\n", i, type, l->out_c, l->groups, size_x, size_y, l->stride, l->dilation, l->w, l->h, input_c, out_w, out_h, l->out_c, process, input_layer, graph_layer);
        }
        else {
            printf("   %5d %15s %6d/%3d %3d x%2d /%2d(%d)%6d x%4d x%4d  -> %4d x%4d x%4d %10s\r\n", i, type, l->out_c, l->groups, size_x, size_y, l->stride, l->dilation, l->w, l->h, input_c, out_w, out_h, l->out_c, process);
        }   
    }
}
#endif

static int get_model_output_layer(struct blai_net_info_t* net)
{
    return (net->app_type == CLASSIFICATION) ? net->layer_cnt - 1 : net->layer_cnt - 1;
}

static void merge_graph(struct blai_net_info_t *net) {
    if (net->layers[0].NPU_on == 0) {
        net->w = net->layers[0].w;
        net->h = net->layers[0].h;
        net->c = net->layers[0].c;
    }
    else{
        net->w = net->npu_layers[0].w;
        net->h = net->npu_layers[0].h;
        net->c = net->npu_layers[0].c;
    }

    int NPU_count = 0;
    int route_cnt = 0;
    for (int i = 0; i < net->layer_cnt; i++) {
        if (net->layers[i].NPU_on == 1) {
            route_cnt = (net->layers[i].input_num > 2 && route_cnt == 0) ? net->layers[i].input_num - 2 : 0;
            NPU_count += route_cnt;

            int groups = (net->npu_layers[NPU_count].groups == 0 || net->npu_layers[NPU_count].c == net->npu_layers[NPU_count].groups) ? 1 : net->npu_layers[NPU_count].groups;
            net->layers[i].type = net->npu_layers[NPU_count].type;
            net->layers[i].w = net->npu_layers[NPU_count].w;
            net->layers[i].h = net->npu_layers[NPU_count].h;
            net->layers[i].c = net->npu_layers[NPU_count].c;
            net->layers[i].out_w = net->npu_layers[NPU_count].out_w;
            net->layers[i].out_h = net->npu_layers[NPU_count].out_h;
            net->layers[i].out_c = net->npu_layers[NPU_count].out_c;
            net->layers[i].in_layer1_mem = net->npu_layers[NPU_count].in_layer1_mem;
            net->layers[i].in_layer2_mem = net->npu_layers[NPU_count].in_layer2_mem;
            net->layers[i].out_layer_mem = net->npu_layers[NPU_count].out_layer_mem;
            net->layers[i].stride = net->npu_layers[NPU_count].stride;
            net->layers[i].dilation = net->npu_layers[NPU_count].dilation;
            net->layers[i].groups = (net->npu_layers[NPU_count].c / groups == 4) ? net->npu_layers[NPU_count].c : groups;
            net->layers[i].size = net->npu_layers[NPU_count].size;
            net->layers[i].tf_output_offset = net->npu_layers[NPU_count].tf_output_offset;
            
            NPU_count++;
            
        }
    }
}


static BLAI_Status_e blai_cpu_get_header(BLAI_Model_t *model)
{
    int count = 0;

    model->net->layer_cnt = 0;
    ///////////////calculate layer num////////////////////
    while (count < model->inst.cpu.inst_buf_size) {
        if (count % 16 == 0) {
            int instruction_type = fetch_info(model->inst.cpu.inst_buf + count, 0, 5);
            switch (instruction_type) {
                case DSP_HEADER:
                    model->net->BLAI_version = fetch_info(model->inst.cpu.inst_buf + count, 5, 8);
                    model->net->patch_size = pow(2, fetch_info(model->inst.cpu.inst_buf + count, 13, 6));
                    model->net->patch_count = fetch_info(model->inst.cpu.inst_buf + count, 19, 7);
                    model->net->unsign_input = fetch_info(model->inst.cpu.inst_buf + count, 26, 1);
                    model->net->relu_n = fetch_info(model->inst.cpu.inst_buf + count, 27, 5);
                    model->net->use_tflite = fetch_info(model->inst.cpu.inst_buf + count, 32, 1);
                    model->net->layer_cnt = fetch_info(model->inst.cpu.inst_buf + count, 33, 10);
                    if(model->net->BLAI_version == 0){
                        model->net->app_type = fetch_info(model->inst.cpu.inst_buf + count, 43, 3);                      
                        model->net->use_npu_accel = fetch_info(model->inst.cpu.inst_buf + count, 46, 1);
                    }
                    else{
                        model->net->app_type = fetch_info(model->inst.cpu.inst_buf + count, 43, 5);
                        model->net->use_npu_accel = fetch_info(model->inst.cpu.inst_buf + count, 48, 1);
                    }
                    model->net->mode = 0;
                    model->net->custom_postprocess = 0;
                    model->net->layers = BLAI_MALLOC(model->net->layer_cnt*sizeof(struct cpu_inst_layer_t));
                    if (model->net->layers == NULL) {
                        printf("Cannot allocate layer info for %ld bytes\r\n", model->net->layer_cnt*sizeof(struct cpu_inst_layer_t));
                        return BLAI_STATUS_OUT_OF_MEMORY;
                    }
                    memset(model->net->layers, 0, model->net->layer_cnt*sizeof(struct cpu_inst_layer_t));
                    return BLAI_STATUS_NO_ERROR;
                default:
                    break;
            }
        }
        count+=16;
    }
    return BLAI_STATUS_BAD_DATA;
}

static void blai_cpu_load_weights(BLAI_Model_t* model) {
    int loadc = 0;
    int word = 0;
    int32_t current_layer = 0;
    uint32_t cur;
    char ch;
    struct blai_net_info_t* net = model->net;

    /////////// Load weights ///////////
    for (cur = 0; cur < model->inst.cpu.weights_buf_size;) {
        ch = model->inst.cpu.weights_buf[cur++];

        while (current_layer < net->layer_cnt) {
            if (net->layers[current_layer].DSP_on == 1 
                    && (net->layers[current_layer].type == CONVOLUTIONAL || net->layers[current_layer].type == MATMUL || net->layers[current_layer].type == CONV_MAX
                           || net->layers[current_layer].type == ROUTE_CONV || net->layers[current_layer].type == SSD))
                           break;
            current_layer++;
            if (current_layer >= net->layer_cnt)
                printf("LOAD WEIGHT ERROR\r\n");
        }

        struct cpu_inst_layer_t *l = &net->layers[current_layer];

        int input_c = l->c;
        if (l->input_num > 1)
            input_c += l->cn[0];
        l->groups = (l->groups == 0) ? 1 : l->groups;
        int size_x = (l->size_x > 0) ? l->size_x : l->size;
        int size_y = (l->size_y > 0) ? l->size_y : l->size;
        int layer_weight_size = (l->type == SSD) ? l->w * l->h * l->c : size_x * size_y * l->out_c * input_c / l->groups;
        if (loadc == 0)
            l->weights = (int*)BLAI_MALLOC(layer_weight_size * sizeof(int));

        if(l->data_type == 1)
            ((fixed_point_t*)l->weights)[loadc] = (fixed_point_t) ch;
        else
            l->weights[loadc] = (fixed_point_t) ch;

        loadc++;

        if (loadc >= layer_weight_size) {
            loadc = 0;
            current_layer++;
        }
    }
    printf("Load Weights Done\r\n");

    /////////// Load biases ///////////
    loadc = 0;
    word = 0;
    current_layer = 0;
    
    uint32_t accu_bias;
    int byte_num = (net->use_tflite) ? 4 : 1;

    for (cur = 0; cur < model->inst.cpu.bias_buf_size;) {
        accu_bias = 0;
        if (cur+byte_num > model->inst.cpu.bias_buf_size) {
            printf("out of bias buffer!\r\n");
            break;
        }
        for (int k = 0; k < byte_num; k++) {
            ch = model->inst.cpu.bias_buf[cur++];
            accu_bias += ((uint8_t) ch) << 8 * k;
        }

        while (current_layer < net->layer_cnt) {
            if (net->layers[current_layer].DSP_on == 1 
                    && (net->layers[current_layer].type == CONVOLUTIONAL || net->layers[current_layer].type == MATMUL || net->layers[current_layer].type == CONV_MAX
                           || net->layers[current_layer].type == ROUTE_CONV))
                           break;
            if (current_layer >= net->layer_cnt - 1)
                printf("LOAD BIAS ERROR\r\n");
            current_layer++;
        }

        struct cpu_inst_layer_t *l = &net->layers[current_layer];

        int layer_biases_size = l->out_c;

        if (loadc == 0) l->biases = (int*)BLAI_MALLOC(layer_biases_size * sizeof(int));

        l->biases[loadc] = accu_bias;
        loadc++;

        if (loadc >= layer_biases_size) {
            loadc = 0;
            current_layer++;
        }
    }
    printf("Load Biases Done\r\n");
}

static void make_layer(struct blai_net_info_t* net, int layer_cnt) {
    struct cpu_inst_layer_t *l = &net->layers[layer_cnt];
    int output_size = 0;
    switch (l->type) {
    case YOLO:
        output_size = l->w * l->h * l->c;
        l->output = (float*)BLAI_MALLOC(output_size * sizeof(float));
        break;
    default:
        break;
    }
}

struct mlayer_input_info_t {
    int in_layer_mem_n[MAX_Input_num-2];
    int frouten[MAX_Input_num-2];
    int tf_input_offset_extra[MAX_Input_num-2];
    int tf_input_shift_extra[MAX_Input_num-2];
    int tf_input_multiplier_extra[MAX_Input_num-2];
};

BLAI_Status_e blai_cpu_inst_decode_layer(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    BLAI_Status_e ret = BLAI_STATUS_NO_ERROR;
    struct cpu_inst_layer_t *layer_info;
    int count = 0, dsp_end = 0;

    blai_cpu_get_header(model);

    if(!model->share_buffer){
        model->buffer = BLAI_MALLOC(model->net->patch_size * model->net->patch_count);
        if (model->buffer == NULL)
            return BLAI_STATUS_OUT_OF_MEMORY;
    }

    layer_info = model->net->layers;
    count = 0;
    int layer_cnt = 0;
    int input_num = 0;
    int input_scale = 0;
    int output_scale = 0;
    int input2_scale = 0;
    int input3_scale = 0;
    int offset = 0;
    int combine_layer = 0;

    ///////////////layer parser////////////////////
    while (count < model->inst.cpu.inst_buf_size) {
        if (count % 16 == 0) {
            int instruction_type = fetch_info(model->inst.cpu.inst_buf + count, 0, 5);

            switch (instruction_type) {
            case DSP_HEADER:

                break;
            case LAYER_INFO:
                layer_info[layer_cnt].w = fetch_info(model->inst.cpu.inst_buf + count, 5, 14);
                layer_info[layer_cnt].h = fetch_info(model->inst.cpu.inst_buf + count, 19, 14);
                layer_info[layer_cnt].c = fetch_info(model->inst.cpu.inst_buf + count, 33, 13);
                layer_info[layer_cnt].out_c = fetch_info(model->inst.cpu.inst_buf + count, 59, 13);
                layer_info[layer_cnt].img_in = fetch_info(model->inst.cpu.inst_buf + count, 72, 1);
                layer_info[layer_cnt].in_layer1_mem = fetch_info(model->inst.cpu.inst_buf + count, 73, 7);
                layer_info[layer_cnt].in_layer2_mem = fetch_info(model->inst.cpu.inst_buf + count, 80, 7);
                layer_info[layer_cnt].out_layer_mem = fetch_info(model->inst.cpu.inst_buf + count, 87, 7);
                //layer_info[layer_cnt].mid_layer_mem = fetch_info(model->inst.cpu.inst_buf + count, 87, 7);
                //layer_info[layer_cnt].mid_out = fetch_info(model->inst.cpu.inst_buf + count, 94, 1);
                layer_info[layer_cnt].input_num = fetch_info(model->inst.cpu.inst_buf + count, 94, 4);
                layer_info[layer_cnt].n = fetch_info(model->inst.cpu.inst_buf + count, 94, 4);
                layer_info[layer_cnt].out_w = fetch_info(model->inst.cpu.inst_buf + count, 98, 14);
                layer_info[layer_cnt].out_h = fetch_info(model->inst.cpu.inst_buf + count, 112, 14);

                if (layer_info[layer_cnt].input_num > 1) {
                    layer_info[layer_cnt].cn[0] = fetch_info(model->inst.cpu.inst_buf + count, 46, 13);
                } else {
                    layer_info[layer_cnt].cn[0] = 0;
                }
                if (layer_info[layer_cnt].input_num > 2) {
                    struct mlayer_input_info_t *alloc_buf = (struct mlayer_input_info_t *)BLAI_MALLOC(sizeof(struct mlayer_input_info_t));
                    layer_info[layer_cnt].in_layer_mem_n = alloc_buf->in_layer_mem_n;
                    layer_info[layer_cnt].frouten = alloc_buf->frouten;
                    layer_info[layer_cnt].tf_input_offset_extra = alloc_buf->tf_input_offset_extra;
                    layer_info[layer_cnt].tf_input_shift_extra = alloc_buf->tf_input_shift_extra;
                    layer_info[layer_cnt].tf_input_multiplier_extra = alloc_buf->tf_input_multiplier_extra;
                } else {
                    layer_info[layer_cnt].in_layer_mem_n = NULL;
                    layer_info[layer_cnt].frouten = NULL;
                    layer_info[layer_cnt].tf_input_offset_extra = NULL;
                    layer_info[layer_cnt].tf_input_shift_extra = NULL;
                    layer_info[layer_cnt].tf_input_multiplier_extra = NULL;
                }
                break;

            case EXTRA_LAYER:
                input_num = (layer_info[layer_cnt].input_num > 5 && model->net->use_tflite) ? 5 : (layer_info[layer_cnt].input_num > 6) ? 6 : layer_info[layer_cnt].input_num;
                if (model->net->use_tflite == 0) {
                    for (int k = 2; k < input_num; k++) {
                        layer_info[layer_cnt].in_layer_mem_n[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 7 * (k - 2), 7);
                        layer_info[layer_cnt].frouten[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 33 + 5 * (k - 2), 5);
                        layer_info[layer_cnt].cn[k - 1] = fetch_info(model->inst.cpu.inst_buf + count, 53 + 12 * (k - 2), 12);
                    }
                } else {
                    for (int k = 2; k < input_num; k++) {
                        layer_info[layer_cnt].in_layer_mem_n[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 7 * (k - 2), 7);
                        layer_info[layer_cnt].cn[k - 1] = fetch_info(model->inst.cpu.inst_buf + count, 26 + 12 * (k - 2), 12);
                        layer_info[layer_cnt].tf_input_offset_extra[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 62 + 8 * (k - 2), 8);
                        layer_info[layer_cnt].tf_input_shift_extra[k - 2] = unsigned_to_signed(fetch_info(model->inst.cpu.inst_buf + count, 86 + 6 * (k - 2), 6), 6);
                    }
                }
                break;

            case EXTRA_LAYER_6_8:
                input_num = (layer_info[layer_cnt].input_num > 8 && model->net->use_tflite) ? 8 : (layer_info[layer_cnt].input_num > 10) ? 10 : layer_info[layer_cnt].input_num;
                offset = (model->net->use_tflite) ? 5 : 6;
                if (model->net->use_tflite == 0) {
                    for (int k = offset; k < input_num; k++) {
                        layer_info[layer_cnt].in_layer_mem_n[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 7 * (k - offset), 7);
                        layer_info[layer_cnt].frouten[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 33 + 5 * (k - offset), 5);
                        layer_info[layer_cnt].cn[k - 1] = fetch_info(model->inst.cpu.inst_buf + count, 53 + 12 * (k - offset), 12);
                    }
                }
                else {
                    for (int k = offset; k < input_num; k++) {
                        layer_info[layer_cnt].in_layer_mem_n[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 7 * (k - offset), 7);
                        layer_info[layer_cnt].cn[k - 1] = fetch_info(model->inst.cpu.inst_buf + count, 26 + 12 * (k - offset), 12);
                        layer_info[layer_cnt].tf_input_offset_extra[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 62 + 8 * (k - offset), 8);
                        layer_info[layer_cnt].tf_input_shift_extra[k - 2] = unsigned_to_signed(fetch_info(model->inst.cpu.inst_buf + count, 86 + 6 * (k - offset), 6), 6);
                    }
                }

                break;
            case GENERAL_FORM:
                layer_info[layer_cnt].type = fetch_info(model->inst.cpu.inst_buf + count, 5, 5);
                layer_info[layer_cnt].size = fetch_info(model->inst.cpu.inst_buf + count, 10, 5);
                layer_info[layer_cnt].activation = fetch_info(model->inst.cpu.inst_buf + count, 15, 5);
                layer_info[layer_cnt].stride = fetch_info(model->inst.cpu.inst_buf + count, 20, 3) + 1;
                layer_info[layer_cnt].dilation = fetch_info(model->inst.cpu.inst_buf + count, 23, 3) + 1;
                layer_info[layer_cnt].groups = fetch_info(model->inst.cpu.inst_buf + count, 26, 12);
                if (model->net->use_tflite == 0) {
                    layer_info[layer_cnt].fdata = fetch_info(model->inst.cpu.inst_buf + count, 38, 5);
                    layer_info[layer_cnt].fweight = fetch_info(model->inst.cpu.inst_buf + count, 43, 5);
                    layer_info[layer_cnt].fbias = fetch_info(model->inst.cpu.inst_buf + count, 48, 5);
                    layer_info[layer_cnt].froute1 = fetch_info(model->inst.cpu.inst_buf + count, 53, 5);
                    layer_info[layer_cnt].froute2 = fetch_info(model->inst.cpu.inst_buf + count, 58, 5);
                    layer_info[layer_cnt].fout = fetch_info(model->inst.cpu.inst_buf + count, 63, 5);
                } else {
                    layer_info[layer_cnt].tf_input1_offset = fetch_info(model->inst.cpu.inst_buf + count, 38, 8);
                    layer_info[layer_cnt].tf_input2_offset = fetch_info(model->inst.cpu.inst_buf + count, 46, 8);
                    layer_info[layer_cnt].tf_input1_shift = unsigned_to_signed(fetch_info(model->inst.cpu.inst_buf + count, 54, 6), 6);
                    layer_info[layer_cnt].tf_input2_shift = unsigned_to_signed(fetch_info(model->inst.cpu.inst_buf + count, 60, 6), 6);
                    layer_info[layer_cnt].tf_output_offset = fetch_info(model->inst.cpu.inst_buf + count, 66, 8);
                    layer_info[layer_cnt].tf_output_shift = unsigned_to_signed(fetch_info(model->inst.cpu.inst_buf + count, 74, 6), 6);
                    layer_info[layer_cnt].quantized_activation_min = fetch_info(model->inst.cpu.inst_buf + count, 80, 8);
                    layer_info[layer_cnt].quantized_activation_max = fetch_info(model->inst.cpu.inst_buf + count, 88, 8);
                    layer_info[layer_cnt].axis = fetch_info(model->inst.cpu.inst_buf + count, 96, 1);
                    layer_info[layer_cnt].tf_left_shift = 20; // TFLITE default 20
                    layer_info[layer_cnt].tf_route_input_shift = fetch_info(model->inst.cpu.inst_buf + count, 97, 6);
                    layer_info[layer_cnt].tf_route_input_multiplier = fetch_info(model->inst.cpu.inst_buf + count, 103, 16) << 16;
                    layer_info[layer_cnt].data_type = fetch_info(model->inst.cpu.inst_buf + count, 119, 2);
                    layer_info[layer_cnt].builtin_code = fetch_info(model->inst.cpu.inst_buf + count, 121, 7);

                }
                check_merge_layer(model->net, layer_cnt);
                set_output_wh(model->net, layer_cnt);
                make_layer(model->net, layer_cnt);
                break;

            case YOLO_INFO:
                layer_info[layer_cnt].classes = fetch_info(model->inst.cpu.inst_buf + count, 5, 7);
                layer_info[layer_cnt].total = fetch_info(model->inst.cpu.inst_buf + count, 12, 4) + 1;
                layer_info[layer_cnt].biases = (int*)BLAI_MALLOC(layer_info[layer_cnt].total * 2 * sizeof(int));
                layer_info[layer_cnt].mask = (int*)BLAI_MALLOC(layer_info[layer_cnt].n * sizeof(int));
                for (int k = 0; k < layer_info[layer_cnt].n; k++) {
                    layer_info[layer_cnt].mask[k] = fetch_info(model->inst.cpu.inst_buf + count, 16 + k * 3, 3);

                }

                for (int k = 0; k < layer_info[layer_cnt].n; k++) {
                    layer_info[layer_cnt].biases[layer_info[layer_cnt].mask[k] * 2] = fetch_info(model->inst.cpu.inst_buf + count, 28 + k * 20, 10);
                    layer_info[layer_cnt].biases[layer_info[layer_cnt].mask[k] * 2 + 1] = fetch_info(model->inst.cpu.inst_buf + count, 38 + k * 20, 10);
                }

                break;
            case EXTRA_MULTIPLIER:
                input_num = (layer_info[layer_cnt].input_num > 5) ? 5 : layer_info[layer_cnt].input_num;
                for (int k = 2; k < input_num; k++)
                    layer_info[layer_cnt].tf_input_multiplier_extra[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 32 * (k - 2), 32);
                break;
            case EXTRA_MULTIPLIER_6_8:            
                input_num = (layer_info[layer_cnt].input_num > 8) ? 8 : layer_info[layer_cnt].input_num;
                for (int k = 5; k < input_num; k++)
                    layer_info[layer_cnt].tf_input_multiplier_extra[k - 2] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 32 * (k - 5), 32);
                break;
            case TFLITE_MULTIPLIER:                
                layer_info[layer_cnt].tf_input1_multiplier = fetch_info(model->inst.cpu.inst_buf + count, 5, 32);
                layer_info[layer_cnt].tf_input2_multiplier = fetch_info(model->inst.cpu.inst_buf + count, 37, 32);
                layer_info[layer_cnt].tf_output_multiplier = fetch_info(model->inst.cpu.inst_buf + count, 69, 32);
                layer_info[layer_cnt].tf_route_input_multiplier = fetch_info(model->inst.cpu.inst_buf + count, 101, 16) \
                        + layer_info[layer_cnt].tf_route_input_multiplier;
                break;

            case TFLITE_FLOAT:
                input_scale = fetch_info(model->inst.cpu.inst_buf + count, 5, 32);
                layer_info[layer_cnt].input_scale = *((float*) &input_scale);
                output_scale = fetch_info(model->inst.cpu.inst_buf + count, 37, 32);
                layer_info[layer_cnt].output_scale = *((float*) &output_scale);
                break;

            case SSD_INFO:
                layer_info[layer_cnt].w_scale = fetch_info(model->inst.cpu.inst_buf + count, 5, 6);
                layer_info[layer_cnt].h_scale = fetch_info(model->inst.cpu.inst_buf + count, 11, 6);
                layer_info[layer_cnt].x_scale = fetch_info(model->inst.cpu.inst_buf + count, 17, 6);
                layer_info[layer_cnt].y_scale = fetch_info(model->inst.cpu.inst_buf + count, 23, 6);
                layer_info[layer_cnt].classes = fetch_info(model->inst.cpu.inst_buf + count, 29, 7);
                layer_info[layer_cnt].max_classes_per_detection = fetch_info(model->inst.cpu.inst_buf + count, 36, 3);
                layer_info[layer_cnt].max_detections = fetch_info(model->inst.cpu.inst_buf + count, 39, 5);
                input2_scale = fetch_info(model->inst.cpu.inst_buf + count, 44, 32);
                input3_scale = fetch_info(model->inst.cpu.inst_buf + count, 76, 32);
                layer_info[layer_cnt].input2_scale = *((float*)&input2_scale);
                layer_info[layer_cnt].input3_scale = *((float*)&input3_scale);
                layer_info[layer_cnt].anchors_offset = fetch_info(model->inst.cpu.inst_buf + count, 108, 8);
                break;

            case INPUT_LAYERS:
                combine_layer = (layer_info[layer_cnt].type == CONV_MAX || layer_info[layer_cnt].type == ROUTE_MAX ||
                    layer_info[layer_cnt].type == ROUTE_CONV || layer_info[layer_cnt].type == ROUTE_UPSAMPLE);
                layer_info[layer_cnt + 1].layer_offset = (layer_cnt == 0) ? 0 : (combine_layer) ? layer_info[layer_cnt].layer_offset + 1 : layer_info[layer_cnt].layer_offset;
                layer_info[layer_cnt].graph_layer[0] = layer_cnt + layer_info[layer_cnt].layer_offset;
                if (combine_layer) {
                    layer_info[layer_cnt].graph_layer[1] = layer_info[layer_cnt].graph_layer[0];
                    layer_info[layer_cnt].graph_layer[0] = layer_info[layer_cnt].graph_layer[1] + 1;
                }
                for (int i = 0; i < layer_info[layer_cnt].input_num; i++) {
                    layer_info[layer_cnt].input_layers[i] = fetch_info(model->inst.cpu.inst_buf + count, 5 + 10 * i, 10);
                }
                break;

            case DETAIL_GENERAL_FORM:
                layer_info[layer_cnt].size_x = fetch_info(model->inst.cpu.inst_buf + count, 5, 10);
                layer_info[layer_cnt].size_y = fetch_info(model->inst.cpu.inst_buf + count, 15, 10);
                layer_info[layer_cnt].stride_x = fetch_info(model->inst.cpu.inst_buf + count, 25, 3);
                layer_info[layer_cnt].stride_y = fetch_info(model->inst.cpu.inst_buf + count, 28, 3);
                layer_info[layer_cnt].padding_x = fetch_info(model->inst.cpu.inst_buf + count, 31, 9);
                layer_info[layer_cnt].padding_y = fetch_info(model->inst.cpu.inst_buf + count, 40, 9);

                break;

            case DSP_STATUS:
                set_output_wh_later(model->net, layer_cnt);
                layer_info[layer_cnt].NPU_on = fetch_info(model->inst.cpu.inst_buf + count, 5, 1);
                layer_info[layer_cnt].DSP_on = fetch_info(model->inst.cpu.inst_buf + count, 6, 1);
                dsp_end = fetch_info(model->inst.cpu.inst_buf + count, 7, 1);
                layer_info[layer_cnt].input_num = fetch_info(model->inst.cpu.inst_buf + count, 8, 4);
                output_scale = fetch_info(model->inst.cpu.inst_buf + count, 12, 32);
                layer_info[layer_cnt].output_scale = *((float*) &output_scale);
                layer_info[layer_cnt].output_layer = (fetch_info(model->inst.cpu.inst_buf + count, 44, 1) == 1) ? true : false;
                if(layer_info[layer_cnt].output_layer){
                    model->net->output_layer[model->net->output_num] = layer_cnt;
                    model->net->output_num = model->net->output_num + 1;                   
                }
                layer_cnt++;
                if (dsp_end)
                    break;
                break;

            default:
                break;
            }

            if (dsp_end)
                break;
        }
        count+=16;
    }
    if (model->net->layer_cnt != layer_cnt) {
        //printf("layer count mismatch in header(%d) and instruction(%d)\r\n", model->net->layer_cnt, layer_cnt);
        model->net->layer_cnt = layer_cnt;
    }
    blai_cpu_load_weights(model);

    if(!model->net->use_npu_accel) {
        ret = blai_npu_inst_decode_layer(hdl);
        if (ret != BLAI_STATUS_NO_ERROR)
            return ret;
        merge_graph(model->net);
    } else {
        model->net->w = model->net->layers[0].w;
        model->net->h = model->net->layers[0].h;
        model->net->c = model->net->layers[0].c;
    }

    if(model->net->use_npu_accel) {
        struct cpu_inst_layer_t *lout = &model->net->layers[get_model_output_layer(model->net)];
        for (int i = 0; i < model->net->layer_cnt; i++)
            model->net->layers[i].NPU_on = check_BLAI_NPU_RUN(model->net, &model->net->layers[i]);
        model->net->input_i8 = (fixed_point_t *)model->buffer;
        int out_c = (lout->NPU_on) ? BALI_CHN_ALIGN(lout->out_c) : lout->out_c;
        model->net->output_i8 = (fixed_point_t*)BLAI_MALLOC(lout->out_w * lout->out_h * out_c * sizeof(int));
        assign_release_layer(model->net);
    }

#ifdef BLAI_SHOW_NETWORK
    show_BLAI_network(model->net);
#endif
    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_cpu_release(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    for (int i = 0; i < model->net->layer_cnt; i++) {

        if (model->net->layers[i].in_layer_mem_n)
            BLAI_FREE(model->net->layers[i].in_layer_mem_n);
        /* The following memory are allocated togather with in_layer_mem_n
         * BLAI_FREE(model->net->layers[i].frouten);
         * BLAI_FREE(model->net->layers[i].tf_input_offset_extra);
         * BLAI_FREE(model->net->layers[i].tf_input_shift_extra);
         * BLAI_FREE(model->net->layers[i].tf_input_multiplier_extra);
         */

        if (model->net->layers[i].weights)
            BLAI_FREE(model->net->layers[i].weights);
        if (model->net->layers[i].biases)
            BLAI_FREE(model->net->layers[i].biases);
        if (model->net->layers[i].mask)
            BLAI_FREE(model->net->layers[i].mask);
        if (model->net->layers[i].output)
            BLAI_FREE(model->net->layers[i].output);
    }
    if (model->net->layers)
        BLAI_FREE(model->net->layers);
    if (model->net->output_i8)
        BLAI_FREE(model->net->output_i8);
    if (model->net->graph_layer_to_layer)
        BLAI_FREE(model->net->graph_layer_to_layer);
    return BLAI_STATUS_NO_ERROR;
}

void allocate_dsp_tensor(struct blai_net_info_t *net, struct cpu_inst_layer_t *l, fixed_point_t* DATA_buf, int l_current) {
    bool MULTI_INPUT_CHECK = check_MultiInput_layer(l);

    int input_layer = (l_current == 0) ? 0 : net->graph_layer_to_layer[l->input_layers[0]];
    struct cpu_inst_layer_t *in_l = &net->layers[input_layer];
    //l->input_i8 = (MULTI_INPUT_CHECK) ? (fixed_point_t**)xcalloc(l->input_num, sizeof(fixed_point_t)) : (fixed_point_t**)xcalloc(1, sizeof(fixed_point_t));
    l->input_i8[0] = (l_current == 0) ? net->input_i8 : net->layers[input_layer].output_i8;
    
    if (MULTI_INPUT_CHECK) {
        l->input_i8[0] = (in_l->mid_out == 1 && l->input_layers[0] == in_l->graph_layer[1]) ? in_l->mid_output_i8 : l->input_i8[0];
        for (int i = 1; i < l->input_num; i++) {
            input_layer = net->graph_layer_to_layer[l->input_layers[i]];
            in_l = &net->layers[input_layer];
            l->input_i8[i] = (in_l->mid_out == 1 && l->input_layers[i] == in_l->graph_layer[1]) ? in_l->mid_output_i8 : in_l->output_i8;
        }
    }

    int out_c = l->out_c;
    if (l->NPU_on) 
        out_c = (l->out_c % 4 == 0) ? l->out_c : ((l->out_c / 4) + 1) * 4;

    if (l_current != get_model_output_layer(net))
        l->output_i8 = (fixed_point_t*)BLAI_MALLOC(l->out_w * l->out_h * out_c * sizeof(int));
    else
        l->output_i8 = net->output_i8;
    
    bool MID_ROUTE_CHECK = (l->type == ROUTE_CONV || l->type == ROUTE_MAX || l->type == ROUTE_UPSAMPLE);

    int input_c = l->c;
    if (MID_ROUTE_CHECK)
        for (int i = 0; i < l->n - 1; i++)
            input_c += l->cn[i];
    if (l->mid_out == 0) {
        l->mid_output_i8 = NULL;
    } else {
        if (MID_ROUTE_CHECK)
            l->mid_output_i8 = (fixed_point_t*)BLAI_MALLOC(l->w * l->h * input_c * sizeof(fixed_point_t));
        else
            l->mid_output_i8 = (fixed_point_t*)BLAI_MALLOC(l->w * l->h * l->out_c * sizeof(fixed_point_t));
    }
    
}

void release_dsp_tensor(struct blai_net_info_t* net, struct cpu_inst_layer_t *l, int l_current) {
    int cache_layer = get_model_output_layer(net);
    for (int i = 0; i < l->release_num; i++) {
        //printf("release_dsp_tensor for 0x%x\r\n", (uint32_t)net->layers[l->release_layers[i]].output_i8);    
        if (cache_layer != l->release_layers[i])
            BLAI_FREE(net->layers[l->release_layers[i]].output_i8);            
    }

    for (int i = 0; i < l->release_mid_num; i++) {
        //printf("release_dsp_tensor mid for 0x%x\r\n", (uint32_t)net->layers[l->release_mid_layers[i]].mid_output_i8);    
        BLAI_FREE(net->layers[l->release_mid_layers[i]].mid_output_i8);        
    }
}

fixed_point_t* blai_get_output_buffer(blai_model_hdl_t hdl) {
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    return model->net->output_i8;
}

static void assign_release_layer(struct blai_net_info_t* net) {
    int* release_layer = (int*)BLAI_MALLOC(net->layer_cnt * sizeof(int));
    int* release_layer_mid = (int*)BLAI_MALLOC(net->layer_cnt * sizeof(int));
    net->graph_layer_to_layer = (int*)BLAI_MALLOC(2 * net->layer_cnt * sizeof(int));

    memset(release_layer, 0, net->layer_cnt * sizeof(int));
    memset(release_layer_mid, 0, net->layer_cnt * sizeof(int));

    // search release layer
    bool jump = false;
    for (int i = 0; i < net->layer_cnt; i++) {
        struct cpu_inst_layer_t* l = &net->layers[i];
        jump = false;
        bool combine_layer = check_combine_layer(l);
        if (i == net->layer_cnt - 1) release_layer[i] = i;
        for (int j = net->layer_cnt - 1; j > i; j--) {
            struct cpu_inst_layer_t* cur_l = &net->layers[j];
            if (check_MultiInput_layer(cur_l)) {
                for (int k = 0; k < cur_l->input_num; k++) {
                    if (cur_l->input_layers[k] == l->graph_layer[0]) {
                        release_layer[i] = j;                    
                        jump = true;
                        break;
                    }
                }
            }
            else  {
                if (cur_l->input_layers[0] == l->graph_layer[0]) {
                    release_layer[i] = j;
                    break;
                }            
            }
            if(j == i + 1) release_layer[i] = j;
            if (jump) break;
        }
        jump = false;
        if (combine_layer) {
            for (int j = net->layer_cnt - 1; j > i; j--) {
                struct cpu_inst_layer_t* cur_l = &net->layers[j];
                if (check_MultiInput_layer(cur_l)) {
                    for (int k = 0; k < cur_l->input_num; k++) {
                        if (cur_l->input_layers[k] == l->graph_layer[1]) {
                            release_layer_mid[i] = j;
                            l->mid_out = 1;
                            jump = true;
                            break;
                        }
                    }
                }
                else {
                    if (cur_l->input_layers[0] == l->graph_layer[1]) {
                        release_layer_mid[i] = j;
                        l->mid_out = 1;
                        break;
                    }
                }        
                if (jump) break;
            }
        }    
    }
    
    // convert graph_layer to layer
    for (int i = 0; i < net->layer_cnt; i++) {
        struct cpu_inst_layer_t* l = &net->layers[i];
        net->graph_layer_to_layer[l->graph_layer[0]] = i;
        if(l->mid_out)
            net->graph_layer_to_layer[l->graph_layer[1]] = i;
    }

    // push back release layers
    for (int i = 0; i < net->layer_cnt; i++) {
        
        struct cpu_inst_layer_t *l = &net->layers[release_layer[i]];
        l->release_layers[l->release_num] = i;
        l->release_num += 1;

        if (release_layer_mid[i] != 0) {
            struct cpu_inst_layer_t* ml = &net->layers[release_layer_mid[i]];
            ml->release_mid_layers[ml->release_mid_num] = i;
            ml->release_mid_num += 1;
        }
    }
    BLAI_FREE(release_layer);
    BLAI_FREE(release_layer_mid);
}

BLAI_ProcStatus_e blai_cpu_inference(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    struct blai_net_info_t* net_info = (struct blai_net_info_t*) model->net;
    fixed_point_t *data_buf = (fixed_point_t *) model->buffer;
    TickType_t tick_now;

    if (model->net->cur_layer >= net_info->layer_cnt)
        return BLAI_PROCESS_DONE;

    for (int i = model->net->cur_layer; i < net_info->layer_cnt; i++) {
        struct cpu_inst_layer_t *l = &net_info->layers[i];
        model->net->cur_layer = i;
        if (net_info->use_npu_accel)
            allocate_dsp_tensor(net_info, &net_info->layers[i], data_buf, i);
        
        if (l->NPU_on == 1  && net_info->use_npu_accel == 0) {
#ifdef BLAI_NPU_HALT_EACH_LAYER
            model->net->cur_layer = i+1;
#else
            while (++i < net_info->layer_cnt) {
                if (net_info->layers[i].DSP_on == 1)
                    break;
            }
            model->net->cur_layer = i;
#ifdef BLAI_DEBUG
            BL_LOGI("Switch to NPU, Next DSP layer = %d\r\n", model->net->cur_layer);
#endif
#endif
            if (net_info->use_npu_accel)
                release_dsp_tensor(net_info, &net_info->layers[i], i);
            return BLAI_PROCESS_NPU;
        }
#ifdef BLAI_DEBUG
        BL_LOGI("Processing layer %d/%d, type %d\r\n", i, net_info->layer_cnt-1, l->type);
#endif
        tick_now = xTaskGetTickCount();
#ifdef BLAI_MEMALLOC_DEBUG
        size_t heap_start = xPortGetFreeHeapSize();
#endif
        bool nmsis_depthwise_conv = (l->groups > 1 && l->groups == l->c && l->groups == l->out_c && l->dilation <= 1);
        bool nmsis_conv = (l->groups <= 1 && l->dilation <= 1);
        bool NMSISI_api = false;
        switch (l->type) {
            case CONVOLUTIONAL:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }

                if(net_info->use_tflite && nmsis_conv)
                    forward_CONVOLUTIONAL_tflite_nmsis(net_info, l, data_buf, i);
                else if(net_info->use_tflite && nmsis_depthwise_conv)
                    forward_DEPTHWISE_CONVOLUTIONAL_tflite_nmsis(net_info, l, data_buf, i);
                else if(net_info->use_tflite)
                    forward_CONVOLUTIONAL_tflite(net_info, l, data_buf, i);
                else
                    forward_CONVOLUTIONAL(net_info, l, data_buf, i);
                break;
            case CONV_MAX:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_CONV_MAX_tflite(net_info, l, data_buf, i);
                else
                    forward_CONV_MAX(net_info, l, data_buf, i);
                break;
            case MAXPOOL:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_MAXPOOL_tflite_nmsis(net_info, l, data_buf, i);
                    //forward_MAXPOOL_tflite(net_info, l, data_buf, i);
                else
                    forward_MAXPOOL(net_info, l, data_buf, i);
                break;
            case ROUTE_CONV:
                if (net_info->use_npu_accel && l->NPU_on)  {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                forward_ROUTE_CONV(net_info, l, data_buf, i);
                break;
            case UPSAMPLE:
                if (net_info->use_npu_accel && l->NPU_on)  {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                forward_UPSAMPLE(net_info, l, data_buf, i);
                break;
            case ROUTE_UPSAMPLE:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                forward_ROUTE_UPSAMPLE(net_info, l, data_buf, i);
                break;
            case AVGPOOL:
                if (net_info->use_tflite)
                    forward_AVGPOOL_tflite(net_info, l, data_buf, i);
                break;
            case SHORTCUT:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_SHORTCUT_tflite(net_info, l, data_buf, i);
                else
                    forward_SHORTCUT(net_info, l, data_buf, i);
                break;
            case ROUTE:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_ROUTE_tflite(net_info, l, data_buf, i);
                else
                    forward_ROUTE(net_info, l, data_buf, i);
                break;
            case ROUTE_W:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_ROUTE_W_tflite(net_info, l, data_buf, i);
                break;
            case ROUTE_MAX:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_ROUTE_MAX_tflite(net_info, l, data_buf, i);
                else 
                    forward_ROUTE_MAX(net_info, l, data_buf, i);
                break;
            case MATMUL:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                forward_MATMUL(net_info, l, data_buf, i);
                break;
            case RESHAPE:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_RESHAPE_tflite(net_info, l, data_buf, i);
                break;
             case PRE_TRANSCONV:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_PRE_TRANSCONV_tflite(net_info, l, data_buf, i);
                break;
            case SOFTMAX:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_SOFTMAX_tflite(net_info, l, data_buf, i);
                break;
            case LOGISTIC_L:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                forward_LOGISTIC_tflite(net_info, l, data_buf, i);
                break;
            case TRANSPOSE:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_TRANSPOSE_tflite(net_info, l, data_buf, i);
                break;
            case TRANSPOSE_LK:
                if (net_info->use_tflite) {
                    if (l->tf_input1_offset == 1 && l->tf_input2_offset == 1)
                        forward_TRANSPOSELK_V2_tflite(net_info, l, data_buf, i);
                    else
                        forward_TRANSPOSELK_tflite(net_info, l, data_buf, i);

                }
                break;
            case PAD:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_PAD_tflite(net_info, l, data_buf, i);
                break;
            case MEAN:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if (net_info->use_tflite)
                    forward_MEAN_tflite(net_info, l, data_buf, i);
                break;

            case SSD: {
                struct BLAI_data_t BL_data = { 0 };
                BL_data.image_width = model->in.width;
                BL_data.image_height = model->in.height;
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                else if (net_info->use_tflite)
                    forward_SSD_tflite(net_info, l, data_buf, i, &BL_data, model->post_info.classification.classes_name, model->result_cb);
                break;
             }
            case YOLO:
                if (net_info->use_npu_accel && l->NPU_on) {
                    if (forward_NPU(net_info, data_buf, i))
                        break;
                }
                if(net_info->app_type == OBJECT_DETECTION)
                    forward_YOLO(net_info, l, data_buf, i);
                else if(net_info->app_type == FACE_LANDMARK)
                    forward_YOLO_lm(net_info, l, data_buf, i);
                break;
            case DEQUANTIZE:
                    forward_DEQUANTIZE_tflite(net_info, l, data_buf, i);
                break;
            case CUSTOM_L:
                    printf("[WARNING] CUSTOM LAYER [%d - %s], customize it here\n", i, tflite_230_names[l->builtin_code]);
                break;
            default:
                    printf("unknown layer\r\n");
                break;
        }

        csi_dcache_clean_range((uintptr_t *)(model->buffer + l->out_layer_mem*net_info->patch_size), (int32_t)model->net->patch_size);

#ifdef BLAI_PROFILING_EACH_LAYER
        if (l->NPU_on)
            printf("[NPU]Layer %d process takes %ld ms\n", i, xTaskGetTickCount() - tick_now);
        else
            printf("[CPU]Layer %d process takes %ld ms\n", i, xTaskGetTickCount() - tick_now);
#endif
#ifdef BLAI_MEMALLOC_DEBUG
        size_t heap_end = xPortGetFreeHeapSize();
        if (heap_start != heap_end)
            printf("[MEM][ERROR] memory leak in layer %d, before: %lu, after: %lu\r\n", i, heap_start, heap_end);
        else
            printf("[MEM][OK] layer %d, before: %lu, after: %lu\r\n", i, heap_start, heap_end);
#endif

        if (net_info->use_npu_accel)
            release_dsp_tensor(net_info, l, i);
    }

    return BLAI_PROCESS_DONE;
}

