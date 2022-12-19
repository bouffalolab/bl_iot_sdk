#include <stdio.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <aos/kernel.h>
#include <math.h>
#include "bl808.h"
#include "bl808_common.h"
#include "bl_npu.h"
#include "blai_core.h"
#include "blai_def_internal.h"


static SemaphoreHandle_t blai_npu_intr_sem;
static SemaphoreHandle_t blai_npu_exec_sem;
static uint8_t g_bInited = 0;

void blai_npu_init(void)
{
    if (g_bInited == 0) {
        blai_npu_intr_sem = xSemaphoreCreateCounting(1, 0);
        blai_npu_exec_sem = xSemaphoreCreateMutex();
        bl_npu_clk_en(0);
        g_bInited = 1;
    }
}

void blai_npu_destroy(void)
{
    if (g_bInited) {
        vSemaphoreDelete(blai_npu_intr_sem);
        vSemaphoreDelete(blai_npu_exec_sem);
        g_bInited = 0;
    }
}

void blai_npu_exec_lock_required(void)
{
    while (xSemaphoreTake(blai_npu_exec_sem, portMAX_DELAY) != pdTRUE);
}

void blai_npu_exec_lock_release(bool in_isr)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (in_isr)
        xSemaphoreGiveFromISR(blai_npu_exec_sem, &xHigherPriorityTaskWoken);
    else
        xSemaphoreGive(blai_npu_exec_sem);

}


static void blai_halt_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    bl_npu_ack_irq();
    xSemaphoreGiveFromISR(blai_npu_intr_sem, &xHigherPriorityTaskWoken);
}


BLAI_Status_e blai_npu_initCfg(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    bl_npu_layer_setup(model->inst.npu.inst_buf, model->inst.npu.weights_buf, model->inst.npu.bias_buf);
    bl_npu_set_input_buffer(model->buffer, model->net->patch_size);
    bl_npu_set_net_param(model->net->unsign_input, model->net->relu_n, model->net->use_tflite);

    Interrupt_Handler_Register(CNN_IRQn, blai_halt_IRQHandler);
    System_NVIC_SetPriority(CNN_IRQn, 7, 1);
    CPU_Interrupt_Enable(CNN_IRQn);

    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_npu_layer_config(uint8_t *inst_buf, uint8_t *weights_buf, uint8_t *bias_buf, 
    uint8_t *input_buf, int patch_size, uint8_t b_isFirstLayer)
{
    bl_npu_layer_setup((uint8_t *)inst_buf, (uint8_t *)weights_buf, (uint8_t *)bias_buf);
    bl_npu_set_input_buffer((uint8_t *)input_buf, patch_size);
    if (b_isFirstLayer == 0)
        bl_npu_reset_unsign();

    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_npu_release(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;

    for (int i = 0; i < model->net->npu_layer_cnt; i++) {
        if (model->net->npu_layers[i].cn)
            BLAI_FREE(model->net->npu_layers[i].cn);
    }
    if (model->net->npu_layers)
        BLAI_FREE(model->net->npu_layers);

    return BLAI_STATUS_NO_ERROR;
}

static BLAI_Status_e blai_npu_get_header(BLAI_Model_t *model)
{
    int count = 0;
    int layer_cnt = 0;
    ///////////////calculate layer num////////////////////
    while (count < model->inst.npu.inst_buf_size) {
        if ((*(model->inst.npu.inst_buf + count)) % 2 == 0) {
            layer_cnt++;
            if ((*(model->inst.npu.inst_buf + count + 15) >> 7) % 2 == 1)
                break;
        }
        count+=16;
    }
    model->net->npu_layers = BLAI_MALLOC(layer_cnt*sizeof(struct cpu_inst_layer_t));
    return BLAI_STATUS_NO_ERROR;
}

BLAI_Status_e blai_npu_inst_decode_layer(blai_model_hdl_t hdl)
{
    BLAI_Model_t *model = (BLAI_Model_t *) hdl;
    struct cpu_inst_layer_t *layer_info;

    if (model->inst.npu.inst_buf_size == 0)
        return BLAI_STATUS_NO_ERROR;

    blai_npu_get_header(model);
    layer_info = model->net->npu_layers;

    int count = 0;
    int layer_cnt = 0;
    int extern_instr = 0;
    while (count < model->inst.npu.inst_buf_size) {
        if ((*(model->inst.npu.inst_buf + count)) % 2 == 1 && (*(model->inst.npu.inst_buf + count + 15) >> 7) % 2 == 0) {
            layer_info[layer_cnt].stride = fetch_info(model->inst.npu.inst_buf + count, 85, 3) + 1;
            layer_info[layer_cnt].dilation = fetch_info(model->inst.npu.inst_buf + count, 88, 3) + 1;
            layer_info[layer_cnt].groups = fetch_info(model->inst.npu.inst_buf + count, 37, 12);
            extern_instr = 1;
        }
        else if ((*(model->inst.npu.inst_buf + count)) % 2 == 0) {
            // stride, dilation, groups initial
            if(extern_instr == 0){
                layer_info[layer_cnt].stride =1;
                layer_info[layer_cnt].dilation = 1;
                layer_info[layer_cnt].groups = 1; 
            }
            //cout << "YOLO" << endl;
            //cal out_w
            layer_info[layer_cnt].w = fetch_info(model->inst.npu.inst_buf + count, 1, 12);
            layer_info[layer_cnt].h = fetch_info(model->inst.npu.inst_buf + count, 13, 12);
            layer_info[layer_cnt].c = fetch_info(model->inst.npu.inst_buf + count, 25, 12);
//            layer_info[layer_cnt].cn = (int*)BLAI_MALLOC(sizeof(int));
            layer_info[layer_cnt].cn[0] = fetch_info(model->inst.npu.inst_buf + count, 37, 12);
            layer_info[layer_cnt].out_c = fetch_info(model->inst.npu.inst_buf + count, 49, 12);
            layer_info[layer_cnt].in_layer1_mem = fetch_info(model->inst.npu.inst_buf + count, 102, 5);
            layer_info[layer_cnt].in_layer2_mem = fetch_info(model->inst.npu.inst_buf + count, 107, 5);
            layer_info[layer_cnt].out_layer_mem = fetch_info(model->inst.npu.inst_buf + count, 112, 5);
            layer_info[layer_cnt].fdata = fetch_info(model->inst.npu.inst_buf + count, 61, 5);
            layer_info[layer_cnt].fweight = fetch_info(model->inst.npu.inst_buf + count, 66, 5);
            layer_info[layer_cnt].fbias = fetch_info(model->inst.npu.inst_buf + count, 71, 5);
            layer_info[layer_cnt].froute1 = fetch_info(model->inst.npu.inst_buf + count, 76, 5);
            layer_info[layer_cnt].froute2 = fetch_info(model->inst.npu.inst_buf + count, 81, 5);
            layer_info[layer_cnt].fout = fetch_info(model->inst.npu.inst_buf + count, 86, 5);
            layer_info[layer_cnt].size = fetch_info(model->inst.npu.inst_buf + count, 91, 3);
            layer_info[layer_cnt].activation = fetch_info(model->inst.npu.inst_buf + count, 94, 5);
            layer_info[layer_cnt].tf_output_offset = fetch_info(model->inst.npu.inst_buf + count, 77, 8);
            //layer_info[layer_cnt].type = (fetch_info(model->inst.npu.inst_buf + count, 100, 2) > 0) ? fetch_info(instruction + count, 100, 2) : (fetch_info(instruction + count, 99, 1) == 1) ? 5 : (fetch_info(instruction + count, 98, 1) == 1) ? 4 : 0;
            layer_info[layer_cnt].type =
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 1 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 0 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 0) ? CONVOLUTIONAL :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 1 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 1 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 0) ? ROUTE_CONV :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 1 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 0 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 1) ? CONV_MAX :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 0 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 0 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 1) ? MAXPOOL :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 0 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 1 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 0 && fetch_info(model->inst.npu.inst_buf + count, 125, 1) == 0) ? ROUTE :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 0 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 1 && fetch_info(model->inst.npu.inst_buf + count, 98, 1) == 1) ? ROUTE_MAX :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 2) ? SHORTCUT : (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 3) ? MATMUL :
                (fetch_info(model->inst.npu.inst_buf + count, 125, 1) == 1 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 0) ? UPSAMPLE :
                (fetch_info(model->inst.npu.inst_buf + count, 100, 2) == 0 && fetch_info(model->inst.npu.inst_buf + count, 126, 1) == 1) ? MAXPOOL :
                (fetch_info(model->inst.npu.inst_buf + count, 125, 1) == 1 && fetch_info(model->inst.npu.inst_buf + count, 99, 1) == 1) ? ROUTE_UPSAMPLE : UNKNOWN;

            layer_info[layer_cnt].halt = fetch_info(model->inst.npu.inst_buf + count, 127, 1);
            layer_info[layer_cnt].groups = (layer_info[layer_cnt].groups == 0) ? 1 : layer_info[layer_cnt].c / layer_info[layer_cnt].groups;
            set_npu_output_wh(model->net, layer_cnt);
            //printf("layer:%d w:%d h:%d c:%d\n", layer_cnt,  layer_info[layer_cnt].w, layer_info[layer_cnt].h, layer_info[layer_cnt].c);
            layer_cnt++;
            extern_instr = 0;
            if ((*(model->inst.npu.inst_buf + count + 15) >> 7) % 2 == 1) {
                //break;
            }
        }
        count += 16;
    }
    model->net->npu_layer_cnt = layer_cnt;

    return BLAI_STATUS_NO_ERROR;
}

BLAI_ProcStatus_e blai_npu_inference(void)
{
    bl_npu_clk_en(1);
    bl_npu_start();
    while (xSemaphoreTake(blai_npu_intr_sem, portMAX_DELAY) != pdTRUE);
    bl_npu_clk_en(0);

    return BLAI_PROCESS_CPU;
}

BLAI_Status_e blai_npu_stop(void)
{
    bl_npu_stop();
    return BLAI_STATUS_NO_ERROR;
}

