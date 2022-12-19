#include <stdio.h>
#include <stdlib.h>
#include "bl808_common.h"
#include "blai_core.h"
#include "blai_def_internal.h"
#include "blai_inst_postprocess.h"
#include <string.h>
#include <getopt.h>
#include <aos/kernel.h>

#define EVA                 (-1)

#if (EVA >= 0)
   #include <output_layer_data.h>

static void eva_golden_offset(blai_model_hdl_t hdl, int offset) {
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    fixed_point_t* DATA_buf = (fixed_point_t *)model->buffer;

    int l_offset = offset;
    int input_size = model->net->layers[model->net->cur_layer + l_offset].w * model->net->layers[model->net->cur_layer + l_offset].h * model->net->layers[model->net->cur_layer + l_offset].c;
    int output_size = model->net->layers[model->net->cur_layer + l_offset].out_w * model->net->layers[model->net->cur_layer + l_offset].out_h * model->net->layers[model->net->cur_layer + l_offset].out_c;
    uint8_t *file_pos = golden;
    uint8_t *golden_data = NULL;
    vTaskDelay(200);
    if (output_size > 0) {
        golden_data = (uint8_t *) BLAI_MALLOC(output_size);
        memcpy(golden_data, file_pos, output_size);
        int error_cnt = 0;
        BL_LOGI("layer_cnt:%d out_layer_mem:%d output_size = %d output_scale:%f output_offset: %d\r\n",
            model->net->cur_layer + l_offset, model->net->layers[model->net->cur_layer + l_offset].out_layer_mem, output_size,
            model->net->layers[model->net->cur_layer + l_offset].output_scale, model->net->layers[model->net->cur_layer + l_offset].tf_output_offset);
        for (int i = 0; i < output_size; i++) {
            fixed_point_t pass_data = MEM_RW(0, i, 0, model->net->layers[model->net->cur_layer + l_offset].out_layer_mem, DATA_buf, model->net->patch_size);
            //fixed_point_t pass_data = MEM_RW(0, i, 0, 0, DATA_buf, model->net->patch_size);
            fixed_point_t golden_i8 = (fixed_point_t)golden_data[i];
            if(abs(golden_i8 - pass_data) > 0 && error_cnt < 10){
                BL_LOGI("\r\nOUTPUT RESULT ERROR\r\n");
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n\r\n", i, golden_i8, pass_data);
                error_cnt++;
            }
            else if(i < 10){
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n", i, golden_i8, pass_data);
            }
        }
        if(error_cnt == 0){
            BL_LOGI("EVA SUCCESS\r\n");
        }
        BLAI_FREE(golden_data);
    }
}


static void eva_golden(blai_model_hdl_t hdl) {
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    fixed_point_t* DATA_buf = (fixed_point_t *)model->buffer;

    int l_offset = -1;
    int input_size = model->net->layers[model->net->cur_layer + l_offset].w * model->net->layers[model->net->cur_layer + l_offset].h * model->net->layers[model->net->cur_layer + l_offset].c;
    int output_size = model->net->layers[model->net->cur_layer + l_offset].out_w * model->net->layers[model->net->cur_layer + l_offset].out_h * model->net->layers[model->net->cur_layer + l_offset].out_c;
    uint8_t *file_pos = golden;
    uint8_t *golden_data = NULL;
    vTaskDelay(200);
    if (output_size > 0) {
        golden_data = (uint8_t *) BLAI_MALLOC(output_size);
        memcpy(golden_data, file_pos, output_size);
        int error_cnt = 0;
        BL_LOGI("layer_cnt:%d out_layer_mem:%d output_size = %d output_scale:%f output_offset: %d\r\n",
            model->net->cur_layer + l_offset, model->net->layers[model->net->cur_layer + l_offset].out_layer_mem, output_size,
            model->net->layers[model->net->cur_layer + l_offset].output_scale, model->net->layers[model->net->cur_layer + l_offset].tf_output_offset);
        for (int i = 0; i < output_size; i++) {
            fixed_point_t pass_data = MEM_RW(0, i, 0, model->net->layers[model->net->cur_layer + l_offset].out_layer_mem, DATA_buf, model->net->patch_size);
            //fixed_point_t pass_data = MEM_RW(0, i, 0, 0, DATA_buf, model->net->patch_size);
            fixed_point_t golden_i8 = (fixed_point_t)golden_data[i];
            if(abs(golden_i8 - pass_data) > 0 && error_cnt < 10){
                BL_LOGI("\r\nOUTPUT RESULT ERROR\r\n");
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n\r\n", i, golden_i8, pass_data);
                error_cnt++;
            }
            else if(i < 10){
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n", i, golden_i8, pass_data);
            }
        }
        if(error_cnt == 0){
            BL_LOGI("EVA SUCCESS\r\n");
        }
        BLAI_FREE(golden_data);
    }
}

static void eva_net_output_golden(blai_model_hdl_t hdl) {
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    fixed_point_t* DATA_buf = (fixed_point_t *)model->buffer;

    int l_offset = -1;
    int input_size = model->net->layers[model->net->layer_cnt + l_offset].w * model->net->layers[model->net->layer_cnt + l_offset].h * model->net->layers[model->net->layer_cnt + l_offset].c;
    int output_size = model->net->layers[model->net->layer_cnt + l_offset].out_w * model->net->layers[model->net->layer_cnt + l_offset].out_h * model->net->layers[model->net->layer_cnt + l_offset].out_c;
    uint8_t *file_pos = golden;
    uint8_t *golden_data = NULL;
    vTaskDelay(1000);
    if (output_size > 0) {
        golden_data = (uint8_t *) BLAI_MALLOC(output_size);
        memcpy(golden_data, file_pos, output_size);
        int error_cnt = 0;
        BL_LOGI("layer_cnt:%d out_layer_mem:%d output_size = %d output_scale:%f output_offset: %d\r\n",
            model->net->layer_cnt + l_offset, model->net->layers[model->net->layer_cnt + l_offset].out_layer_mem, output_size,
            model->net->layers[model->net->cur_layer + l_offset].output_scale, model->net->layers[model->net->layer_cnt + l_offset].tf_output_offset);
        for (int i = 0; i < output_size; i++) {
            fixed_point_t pass_data = MEM_RW(0, i, 0, model->net->layers[model->net->layer_cnt + l_offset].out_layer_mem, DATA_buf, model->net->patch_size);
            //fixed_point_t pass_data = MEM_RW(0, i, 0, 0, DATA_buf, model->net->patch_size);
            fixed_point_t golden_i8 = (fixed_point_t)golden_data[i];
            if(abs(golden_i8 - pass_data) > 1 && error_cnt < 10){
                BL_LOGI("\r\nOUTPUT RESULT ERROR\r\n");
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n\r\n", i, golden_i8, pass_data);
                error_cnt++;
            }
            else if(i < 10){
                BL_LOGI("COUNT:%d SW:%hhx HW:%hhx\r\n", i, golden_i8, pass_data);
            }
        }
        if(error_cnt == 0){
            BL_LOGI("EVA SUCCESS\r\n");
        }
        BLAI_FREE(golden_data);
    }
}
#endif

BLAI_Status_e blai_inst_decode_layer(blai_model_hdl_t hdl)
{
    BLAI_Status_e ret = blai_cpu_inst_decode_layer(hdl);
    if (ret != BLAI_STATUS_NO_ERROR)
        return ret;
    return blai_npu_initCfg(hdl);
}

BLAI_Status_e blai_inst_release(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    blai_npu_release(hdl);
    blai_cpu_release(hdl);

    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_inst_inference(blai_model_hdl_t hdl)
{
    BLAI_Status_e ret = BLAI_STATUS_NO_ERROR;
    BLAI_ProcStatus_e process_state = BLAI_PROCESS_START;
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    model->net->cur_layer = 0;    
    TickType_t tick_start = xTaskGetTickCount();
    TickType_t tick_process;
    model->inst.cpu.process_time = 0;
    model->inst.npu.process_time = 0;

    while (process_state != BLAI_PROCESS_DONE) {
        switch (process_state) {
            case BLAI_PROCESS_START:
            case BLAI_PROCESS_CPU:
                tick_process = xTaskGetTickCount();
                process_state = blai_cpu_inference(hdl);
                model->inst.cpu.process_time += (xTaskGetTickCount() - tick_process);
                break;
            case BLAI_PROCESS_NPU:
                tick_process = xTaskGetTickCount();
                process_state = blai_npu_inference();
                csi_dcache_invalid_range((uintptr_t *)(model->buffer + model->net->layers[model->net->cur_layer - 1].out_layer_mem*model->net->patch_size), (int32_t)model->net->patch_size);
#ifdef BLAI_PROFILING_EACH_LAYER
                BL_LOGI("[NPU]Layer %d process time: %ld ms\r\n", model->net->cur_layer - 1, xTaskGetTickCount() - tick_process);
#endif
                model->inst.npu.process_time += (xTaskGetTickCount() - tick_process);
#if (EVA >= 0)
                eva_golden(hdl);
#endif
                break;
            case BLAI_PROCESS_DONE:
                break;
            default:
                BL_LOGE("Incorrect state %d\r\n", process_state);
                process_state = BLAI_PROCESS_FAIL;
                break;
        }
    }
    blai_npu_stop();
#if (EVA >= 0)
    eva_net_output_golden(hdl);
#endif
#ifdef BLAI_PROFILING
    if (model->net->use_npu_accel)
        BL_LOGI("[CPU]Total process time: %ld ms\r\n", model->inst.cpu.process_time - model->inst.npu.process_time);
    else
        BL_LOGI("[CPU]Total process time: %ld ms\r\n", model->inst.cpu.process_time);
    BL_LOGI("[NPU]Total process time: %ld ms\r\n", model->inst.npu.process_time);
#endif
    tick_process = xTaskGetTickCount();
    switch (model->net->app_type) {
        case OBJECT_DETECTION:
            yolo_obj_det(model->net, model->post_info.classification.classes_name, model->in.width, model->in.height, model->result_cb);
            break;
        case CLASSIFICATION:
            image_classification(model->net, model->post_info.classification.classes_name, (fixed_point_t *)model->buffer, model->result_cb, model->post_info.classification.classes_num);
            break;
        case FACE_RECONGNITION:
            face_recongnition(model->net, model->post_info.face_recongnition.names, model->post_info.face_recongnition.names_num,
                model->post_info.face_recongnition.features_list, model->post_info.face_recongnition.features_num, (fixed_point_t *)model->buffer, model->result_cb);
            break;
        case FACE_LANDMARK:
            yolo_face_landmark(model->net, model->post_info.classification.classes_name, model->in.width, model->in.height, model->result_cb);
            break;
        case KEYWORD_SPOTTING:
            KWS_classification(model->net, model->post_info.classification.classes_name, (fixed_point_t *)model->buffer, model->result_cb, model->post_info.classification.classes_num);
            break;
        case RETINA_FACE:
            retina_face(model->net, model->post_info.classification.classes_name, (fixed_point_t *)model->buffer, model->in.width, model->in.height, model->result_cb);
           break;
        case RETINA_PERSON:
            retina_person(model->net, model->post_info.classification.classes_name, (fixed_point_t *)model->buffer, model->in.width, model->in.height, model->result_cb);
           break;
        case RETINA:
            retina(model->net, model->post_info.classification.classes_name, model->post_info.classification.classes_num, (fixed_point_t *)model->buffer, model->in.width, model->in.height, model->result_cb);
            break;
        case FR_EVALUATION:
            if(model->net->custom_postprocess == 0)
                face_recognition_evaluation(model->net, model->post_info.classification.classes_name, (fixed_point_t *)model->buffer, model->in.width, model->in.height, model->result_cb);
            break;
        case CUSTOM:
            get_output_data(model->net, (fixed_point_t *)model->buffer, model->net->layer_cnt - 1, 10);
            //model->custom_postproc_cb(model->net, (fixed_point_t *)model->buffer, model->net->layer_cnt - 1, 10);
            break;
        default:
            get_output_data(model->net, (fixed_point_t *)model->buffer, model->net->layer_cnt - 1, 10);
            break;
    }
#ifdef BLAI_PROFILING
    BL_LOGI("[POST]Total process time: %ld ms\r\n", xTaskGetTickCount() - tick_process);
    BL_LOGI("[ALL]Total process time: %ld ms\r\n", xTaskGetTickCount() - tick_start);
#endif
    if (process_state != BLAI_PROCESS_DONE)
        return BLAI_STATUS_OP_FAILED;
    else
        return BLAI_STATUS_NO_ERROR;
}

