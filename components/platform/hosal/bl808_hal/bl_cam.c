/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef CONF_USER_YUV_CAM
#include <string.h>
#include <stdio.h>

#include <sensor.h>
#include <bl808_cam_misc.h>
#include <bl808_cam.h>
#include <bl808_clkrst.h>
#include <bl808_mjpeg.h>
#include <bl808_csi.h>
#include <bl808_glb.h>
#include <bl808_hbn.h>
#include <bl808_dvp_tsrc.h>
#include <jpeg_head.h>

#include "bl_cam.h"
#define img_width               640
#define img_height              480
#define mjpeg_width             480
#define mjpeg_height            320
#define img_num                 2
#define fifo_th_gc0308          600
#define CAM_USE_ID              CAM6_ID
#define MJPEG_CAM_ID            CAM4_ID
#define RGB888_SIZE_PER_PIX     3
#define RGB0_SIZE_PER_PIX       4
#define mjpeg_buf_size          1 * 1024 * 1024
#define MJPEG_QUALITY           75
#define JPEG_HEADER             0x30021800
#define VRAM_ADDR               0x3F000000

static uint8_t *pic_buf = NULL;
static uint8_t *line_buf = NULL;
static uint8_t *mjpeg_buf = NULL;
static int dvp2x_enable_flag = 0;

static int bl_dvp2x_init(void)
{
    DVP_2x_Cfg_Type dvpCfg =
    {
        .hSyncLevel = ISP_MISC_ACTIVE_HIGH,
        .vSyncLevel = ISP_MISC_ACTIVE_HIGH,
        .dataOrder = ISP_MISC_2X_DATA_BYTE_LOWER,
        .fifoThreshold = fifo_th_gc0308,
    };

    if (dvp2x_enable_flag == 0) {
        ISP_Clk_Sel(ISP_CLK_160MHz, ENABLE, 1);
        yuvsensor_init();

        ISP_MSIC_DVP_2x_Init(&dvpCfg);
        ISP_MSIC_DVP_2x_Enable();
        dvp2x_enable_flag = 1;
        printf("dvp2x init\r\n");
    }
    return 0;
}

int bl_cam_yuv_init(void)
{
    int ret = 0;

    CAM_CFG_Type cameraCfg =
    {
        .swMode = CAM_SW_MODE_MANUAL,
        .swIntCnt = 0,
        .pixWidth = CAM_PIX_DATA_BIT_24TO32,
        .dropMode = CAM_DROP_NONE,
        .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
        .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
        .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
        .burstType = CAM_BURST_TYPE_INCR64,
        .waitCount = 0x40,
        .frameSize = img_width * img_height * RGB0_SIZE_PER_PIX, //RGB0 one pixcel 3 bytes
    };
    if (pic_buf == NULL) {
        pic_buf = pvPortMalloc(img_width * img_height * RGB0_SIZE_PER_PIX * img_num);
        if (pic_buf == NULL) {
            printf("malloc pic buf fail\r\n");
            ret = -1;
            goto exit;
        }
    }

    ISP_Scaler_Set_Input(ISP_SCALER_D, ISP_SCALER_DVP_2X);
    /* Setting 8bit BT.601 YUV to RGB */
    ISP_YUV2RGB_Init(ISP_YUV2RGB_PARAM_8BIT_BT601);
    ISP_YUV2RGB_Set_Input(ISP_YUV2RGB_A, ISP_YUV2RGB_INPUT_SCALER_D);
    ISP_MISC_CAM_Input_Select(ISP_MISC_CAM_6_ID, ISP_MISC_CAM_YUV2RGB_OUTPUT);
 
    cameraCfg.memStart = (uint32_t)(uintptr_t)pic_buf;
    cameraCfg.memSize = img_width * img_height * RGB0_SIZE_PER_PIX * img_num;
 
    CAM_Init(CAM_USE_ID, &cameraCfg);
    CAM_Enable(CAM_USE_ID);
    bl_dvp2x_init();
exit:
    return ret;
}

void bl_cam_yuv_cb_register(cam_callback_type *cb)
{
    CAM_Int_Callback_Install(CAM_USE_ID, CAM_INT_NORMAL, cb);
    CAM_IntMask(CAM_USE_ID, CAM_INT_NORMAL, UNMASK);
    CAM_IntMask(CAM_USE_ID, CAM_INT_MEMORY_OVERWRITE, UNMASK);
    CAM_IntMask(CAM_USE_ID, CAM_INT_FRAME_OVERWRITE, UNMASK);
    CAM_IntMask(CAM_USE_ID, CAM_INT_FIFO_OVERWRITE, UNMASK);

    CPU_Interrupt_Enable(DVP2AXI_G_IRQn);
}

void bl_cam_yuv_deinit(void)
{
    CAM_Disable(CAM_USE_ID);
    vPortFree(pic_buf);
    pic_buf = NULL;
}

int bl_cam_rgb_frame_get(uint8_t **pic, uint32_t *len)
{
    int ret = 0;
    CAM_Frame_Info info;
    memset(&info, 0, sizeof(info));

    CAM_Get_Frame_Info(CAM_USE_ID, &info);

    if (info.validFrames == 0) {
        ret = -1;
        goto exit;
    }

    *pic = (uint8_t *)(uintptr_t)(info.curFrameAddr);
    *len = info.curFrameBytes;
exit:
    return ret;
}

void bl_cam_yuv_frame_pop(void)
{
    CAM_Pop_Frame(CAM_USE_ID);
}

static uint16_t Q_Table_50_Y[64] = {
    16,  11,  10,  16,  24,  40,  51,  61,
    12,  12,  14,  19,  26,  58,  60,  55,
    14,  13,  16,  24,  40,  57,  69,  56,
    14,  17,  22,  29,  51,  87,  80,  62,
    18,  22,  37,  56,  68, 109, 103,  77,
    24,  35,  55,  64,  81, 104, 113,  92,
    49,  64,  78,  87, 103, 121, 120, 101,
    72,  92,  95,  98, 112, 100, 103,  99,
};

static uint16_t Q_Table_50_UV[64] = {
    17,  18,  24,  47,  99,  99,  99,  99,
    18,  21,  26,  66,  99,  99,  99,  99,
    24,  26,  56,  99,  99,  99,  99,  99,
    47,  66,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
};

static uint8_t jpgHeadBuf[768];

int bl_cam_mjpeg_init(void)
{
    int ret = 0;
    uint16_t tmpTableY[64] = {0};
    uint16_t tmpTableUV[64] = {0};
    uint32_t jpgHeadLength;

    CAM_CFG_Type cameraCfg =
    {
        .swMode = CAM_SW_MODE_AUTO,
        .swIntCnt = 0,
        .pixWidth = CAM_PIX_DATA_BIT_16,
        .dropMode = CAM_DROP_NONE,
        .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
        .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
        .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
        .burstType = CAM_BURST_TYPE_INCR16,
        .waitCount = 0x40,
        .memStart = NULL,
        .memSize = mjpeg_width * 8 * 2 * 2,
        .frameSize = mjpeg_width * mjpeg_height * 2,
    };

    MJPEG_CFG_Type mjpegCfg = 
    {
        .burst = MJPEG_BURST_INCR16,
        .yuv = MJPEG_YUV422_INTERLEAVE,
        .frameCount = 0,
        .waitCount = 0x100,
        .bufferMjpeg = NULL,
        .sizeMjpeg = mjpeg_buf_size,
        .bufferCamYY = NULL,
        .sizeCamYY = 2,
        .bufferCamUV = 0,
        .sizeCamUV = 0,
        .resolutionX = mjpeg_width,
        .resolutionY = mjpeg_height,
        .bitOrderEnable = ENABLE,
        .evenOrderEnable = ENABLE,
        .swapModeEnable = DISABLE,
        .readStartEnable = ENABLE,
        .reflectDmy = DISABLE,
        .verticalDmy = DISABLE,
        .horizationalDmy = DISABLE,
    };

    ISP_MISC_Scaler_Cfg_Type scaler_cfg = 
    {
        .inputWidth = img_width,
        .inputHeight = img_height,
        .outputWidth = mjpeg_width,
        .outputHeight = mjpeg_height,
    };

    if (line_buf == NULL) {
        line_buf = pvPortMalloc(mjpeg_width * 8 * 2 * 2);
        if (line_buf == NULL) {
            ret = -1;
            goto exit;
        }
    }

    if (mjpeg_buf == NULL) {
        mjpeg_buf = pvPortMalloc(mjpeg_buf_size);
        if (mjpeg_buf == NULL) {
            vPortFree(line_buf);
            line_buf = NULL;
            ret = -1;
            goto exit;
        }
    }
    cameraCfg.memStart = (uint32_t)(uintptr_t)line_buf;
    mjpegCfg.bufferCamYY = (uint32_t)(uintptr_t)line_buf;
    mjpegCfg.bufferMjpeg = (uint32_t)(uintptr_t)mjpeg_buf;

    MJPEG_Set_YUYV_Order_Interleave(0,1,2,3);
 
    MJPEG_Calculate_Quantize_Table(Q_Table_50_Y,tmpTableY,MJPEG_QUALITY);
    MJPEG_Calculate_Quantize_Table(Q_Table_50_UV,tmpTableUV,MJPEG_QUALITY);
    MJPEG_Set_Quantize_Table_Y(tmpTableY);
    MJPEG_Set_Quantize_Table_UV(tmpTableUV);
    MJPEG_Quantize_SRAM_Switch();
 
    jpgHeadLength = JpegHeadCreate(YUV_MODE_422, MJPEG_QUALITY, mjpeg_width, mjpeg_height, jpgHeadBuf);
    printf("jpeg head addr %p length %d\r\n",jpgHeadBuf, jpgHeadLength);
    uint8_t *jpeg_head = (uint8_t *)JPEG_HEADER;
    for (int i = 0; i < jpgHeadLength; i++) {
        jpeg_head[i] = jpgHeadBuf[i];
    }
    //memcpy((uint8_t *)JPEG_HEADER, jpgHeadBuf, jpgHeadLength); //cpy jpeg header to refernce sram 0x30021800
    printf("cpy finish\r\n");
    csi_dcache_clean_range((void *)JPEG_HEADER, jpgHeadLength);
    MJPEG_Frame_Head_Set_Size(jpgHeadLength);
    MJPEG_Frame_Tail_Auto_Fill(ENABLE);
    /* enable scaler for 480x320*/ 
    ISP_MISC_Scaler_Input_Select(ISP_MISC_SCALER_2_ID, ISP_MISC_SCALER_DVP_2X_OUTPUT);
    ISP_MISC_Scaler_Init(ISP_MISC_SCALER_2_ID, &scaler_cfg);
    ISP_MISC_Scaler_Enable(ISP_MISC_SCALER_2_ID);
 
    ISP_MISC_CAM_Input_Select(MJPEG_CAM_ID, ISP_MISC_CAM_SCALER_2_OUTPUT);
    CAM_Init(MJPEG_CAM_ID, &cameraCfg);
    MJPEG_Init(&mjpegCfg);
    MJPEG_Set_Planar_Y_UV_Input(4, 5);
    MJPEG_Enable();

    CAM_Enable(MJPEG_CAM_ID);
    bl_dvp2x_init();
exit:
    return ret;
}

int bl_cam_mjpeg_get(uint8_t **ptr, uint32_t *len)
{
    int ret = 0;
    MJPEG_Frame_Info mjpeg_info;
    MJPEG_Get_Frame_Info(&mjpeg_info);

    if (mjpeg_info.validFrames > 0) {
        if ((mjpeg_info.curFrameAddr + mjpeg_info.curFrameBytes) < ((uint32_t)(uintptr_t)mjpeg_buf + mjpeg_buf_size)) {
            *ptr = (uint8_t *)(uintptr_t)mjpeg_info.curFrameAddr;
            *len = mjpeg_info.curFrameBytes;
        } else {
            bl_cam_mjpeg_pop();
            ret = -1;
        }
    } else {
        ret = -1;
    }
    return ret;
}

int bl_cam_mjpeg_pop(void)
{
    MJPEG_Pop_Frame();
    return 0;
}

int bl_cam_mjpeg_deinit(void)
{
    MJPEG_Disable();
    CAM_Disable(MJPEG_CAM_ID);

    if (line_buf != NULL) {
        vPortFree(line_buf);
        line_buf = NULL;
    }

    if (mjpeg_buf != NULL) {
        vPortFree(mjpeg_buf);
        mjpeg_buf = NULL;
    }

    return 0;
}

#define MIPI_CAM_USE_ID                     CAM7_ID
#define RGB565_CAM_USE_ID                   CAM5_ID

#define MIPI_WIDTH                     1600
#define MIPI_HEIGHT                    1200
#define SCALER_WIDTH                   800
#define SCALER_HEIGHT                  600
#define YUV422_FRAME_SIZE              (MIPI_WIDTH * MIPI_HEIGHT * 2)
#define RGB0_FRAME_SIZE                (MIPI_WIDTH * MIPI_HEIGHT * 4)
#define RGB565_FRAME_SIZE              (MIPI_WIDTH * MIPI_HEIGHT * 2)
#define FRAME_COUNT                    2 

#define ISP_USE_CLK                    (80000000)
#define PIX_USE_CLK                    (66000000)

#define SENSOR_REF_CLK_MHZ             24
#define SENSOR_HS_CLK_MHZ              520

static uint8_t *mipi_pic_buf = NULL;
static uint8_t *rgb565_pic_buf = NULL;
static int mipi_csi_enable_flag = 0;

static CSI_CFG_Type csiCfg = 
{
    .dvp0VirtualChan = 0,
    .laneNum = CSI_LANE_NUMBER_2,
    .dataUnpackEn = ENABLE,
    .syncShortPacketEn = ENABLE,
    .dataBitInverseEn = DISABLE,
    .laneInverseEn = DISABLE,
};

static int bl_yuv2rgb_init(void)
{
    ISP_YUV2RGB_Init(ISP_YUV2RGB_PARAM_8BIT_BT601);
    ISP_YUV2RGB_Set_Input(ISP_YUV2RGB_A, ISP_YUV2RGB_INPUT_ISP_INPUT);
    return 0;
}

static int bl_cam_mipi_csi_init(void)
{
    uint32_t fifoThreshold = 0;
    HBN_AON_PAD_CFG_Type aonPadCfg = {
        DISABLE,
        DISABLE,
        DISABLE,
        HBN_GPIO_PAD_PULL_NONE,
    };

    if (0 == mipi_csi_enable_flag) {
        HBN_Aon_Pad_Cfg(DISABLE, HBN_AON_PAD_GPIO40, &aonPadCfg);
        HBN_Aon_Pad_Cfg(DISABLE, HBN_AON_PAD_GPIO41, &aonPadCfg);
        DVP_TSRC_Disable(DVP_TSRC0_ID);

        GLB_Set_Ldo15cis_Vout(GLB_LDO15CIS_LEVEL_1P20V);
        GLB_CSI_Config_MIPIPLL(2, 0x21000);
        GLB_CSI_Power_Up_MIPIPLL();

        ISP_Clk_Sel(ISP_CLK_160MHz, ENABLE, 1);
        fifoThreshold = (ISP_USE_CLK-PIX_USE_CLK)/1000*MIPI_WIDTH/(ISP_USE_CLK/1000)+10;
        DVP_TSRC_Sensor_Input_Set(DVP_TSRC0_ID,fifoThreshold,DISABLE,DISABLE);

        ISP_MISC_TSRC_Source_Select(ISP_MISC_TSRC_SOURCE_CSI);
        CSI_Disable(CSI0_ID);
        CSI_PHY_Disable_Lanes(CSI0_ID);
        CSI_PHY_Reset(CSI0_ID);
        CSI_Init_Yuv_Sensor(CSI0_ID, &csiCfg);
        CSI_PHY_Config(CSI0_ID, SENSOR_REF_CLK_MHZ, SENSOR_HS_CLK_MHZ);
        CSI_Enable(CSI0_ID);
        CSI_PHY_Enable_Lanes(CSI0_ID, CSI_LANE_NUMBER_2);
        DVP_TSRC_Enable(DVP_TSRC0_ID);

        bl_yuv2rgb_init();
        /*init sensor */
        mipi_sensor_init();

        mipi_csi_enable_flag = 1;
    }
    return 0;
}

int bl_cam_mipi_yuv_init(void)
{
    int ret = 0;
    CAM_CFG_Type camcfg =
    {
        .swMode = CAM_SW_MODE_MANUAL,
        .swIntCnt = 0,
        .pixWidth = CAM_PIX_DATA_BIT_24TO32,
        .dropMode = CAM_DROP_NONE,
        .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
        .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
        .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
        .burstType = CAM_BURST_TYPE_INCR64,
        .waitCount = 0x40,
        .memStart = NULL, //need init 
        .memSize = 0,
        .frameSize = RGB0_FRAME_SIZE,
    };

    if (mipi_pic_buf == NULL) {
        mipi_pic_buf = pvPortMalloc(RGB0_FRAME_SIZE * FRAME_COUNT);
        if (NULL == mipi_pic_buf) {
            printf("malloc mipi pic buf fail\r\n");
            ret = -1;
            goto exit;
        }
    }

    bl_cam_mipi_csi_init();
    ISP_MISC_CAM_Input_Select(ISP_MISC_CAM_7_ID, ISP_MISC_CAM_YUV2RGB_OUTPUT);
    camcfg.memStart = (uint32_t)(uintptr_t)mipi_pic_buf;
    camcfg.memSize = RGB0_FRAME_SIZE * FRAME_COUNT;
    CAM_Init(MIPI_CAM_USE_ID, &camcfg);
    CAM_Enable(MIPI_CAM_USE_ID);
exit:
    return ret;
}

void bl_cam_mipi_yuv_deinit(void)
{
    CAM_Disable(MIPI_CAM_USE_ID);
    vPortFree(mipi_pic_buf);
    mipi_pic_buf = NULL;
}

int bl_cam_mipi_rgb_frame_get(uint8_t **pic, uint32_t *len)
{
    int ret = 0;
    CAM_Frame_Info info;
    memset(&info, 0, sizeof(info));

    CAM_Get_Frame_Info(MIPI_CAM_USE_ID, &info);

    if (info.validFrames == 0) {
        ret = -1;
        goto exit;
    }

    *pic = (uint8_t *)(uintptr_t)(info.curFrameAddr);
    *len = info.curFrameBytes;
exit:
    return ret;
}

void bl_cam_mipi_frame_pop(void)
{
    CAM_Pop_Frame(MIPI_CAM_USE_ID);
}

int bl_cam_mipi_rgb565_init(void)
{
    int ret = 0;
    CAM_CFG_Type camcfg =
    {
        .swMode = CAM_SW_MODE_MANUAL,
        .swIntCnt = 0,
        .pixWidth = CAM_PIX_DATA_BIT_24TO16,
        .dropMode = CAM_DROP_NONE,
        .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
        .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
        .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
        .burstType = CAM_BURST_TYPE_INCR64,
        .waitCount = 0x40,
        .memStart = NULL, //need init 
        .memSize = 0,
        .frameSize = RGB565_FRAME_SIZE,
    };

    if (rgb565_pic_buf == NULL) {
        rgb565_pic_buf = pvPortMalloc(RGB565_FRAME_SIZE * FRAME_COUNT);
        if (NULL == rgb565_pic_buf) {
            printf("malloc rgb565 pic buf fail\r\n");
            ret = -1;
            goto exit;
        }
    }

    bl_cam_mipi_csi_init();
    ISP_MISC_CAM_Input_Select(ISP_MISC_CAM_5_ID, ISP_MISC_CAM_YUV2RGB_OUTPUT);
    camcfg.memStart = (uint32_t)(uintptr_t)rgb565_pic_buf;
    camcfg.memSize = RGB565_FRAME_SIZE * FRAME_COUNT;
    CAM_Init(RGB565_CAM_USE_ID, &camcfg);
    CAM_16_Bit_RGB_order(RGB565_CAM_USE_ID, CAM_16_BIT_BGR);
    CAM_Enable(RGB565_CAM_USE_ID);
exit:
    return ret;
}

void bl_cam_mipi_rgb565_deinit(void)
{
    CAM_Disable(RGB565_CAM_USE_ID);
    vPortFree(mipi_pic_buf);
    mipi_pic_buf = NULL;
}

int bl_cam_mipi_rgb565_frame_get(uint8_t **pic, uint32_t *len)
{
    int ret = 0;
    CAM_Frame_Info info;
    memset(&info, 0, sizeof(info));

    CAM_Get_Frame_Info(RGB565_CAM_USE_ID, &info);

    if (info.validFrames == 0) {
        ret = -1;
        goto exit;
    }

    *pic = (uint8_t *)(uintptr_t)(info.curFrameAddr);
    *len = info.curFrameBytes;
exit:
    return ret;
}

void bl_cam_mipi_rgb565_frame_pop(void)
{
    CAM_Pop_Frame(RGB565_CAM_USE_ID);
}

int bl_cam_mipi_mjpeg_init(void)
{
    int ret = 0;
    uint16_t tmpTableY[64] = {0};
    uint16_t tmpTableUV[64] = {0};
    uint32_t jpgHeadLength;

    CAM_CFG_Type cameraCfg =
    {
        .swMode = CAM_SW_MODE_AUTO,
        .swIntCnt = 0,
        .pixWidth = CAM_PIX_DATA_BIT_16,
        .dropMode = CAM_DROP_NONE,
        .linePol = CAM_LINE_ACTIVE_POLARITY_HIGH,
        .framePol = CAM_FRAME_ACTIVE_POLARITY_HIGH,
        .camSensorMode = CAM_SENSOR_MODE_V_AND_H,
        .burstType = CAM_BURST_TYPE_INCR64,
        .waitCount = 0x40,
        .memStart = NULL,
        .memSize = SCALER_WIDTH * 8 * 2 * 2,
        .frameSize = SCALER_WIDTH * SCALER_HEIGHT * 2,
    };

    MJPEG_CFG_Type mjpegCfg = 
    {
        .burst = MJPEG_BURST_INCR16,
        .yuv = MJPEG_YUV422_INTERLEAVE,
        .frameCount = 0,
        .waitCount = 0x100,
        .bufferMjpeg = NULL,
        .sizeMjpeg = mjpeg_buf_size,
        .bufferCamYY = NULL,
        .sizeCamYY = 2,
        .bufferCamUV = 0,
        .sizeCamUV = 0,
        .resolutionX = SCALER_WIDTH,
        .resolutionY = SCALER_HEIGHT,
        .bitOrderEnable = ENABLE,
        .evenOrderEnable = ENABLE,
        .swapModeEnable = DISABLE,
        .readStartEnable = ENABLE,
        .reflectDmy = DISABLE,
        .verticalDmy = DISABLE,
        .horizationalDmy = DISABLE,
    };

    if (line_buf == NULL) {
        line_buf = pvPortMalloc(SCALER_WIDTH * 8 * 2 * 2);
        if (line_buf == NULL) {
            ret = -1;
            goto exit;
        }
    }

    if (mjpeg_buf == NULL) {
        mjpeg_buf = pvPortMalloc(mjpeg_buf_size);
        if (mjpeg_buf == NULL) {
            vPortFree(line_buf);
            line_buf = NULL;
            ret = -1;
            goto exit;
        }
    }

    ISP_MISC_Scaler_Cfg_Type scaler_cfg = 
    {
        .inputWidth = MIPI_WIDTH,
        .inputHeight = MIPI_HEIGHT,
        .outputWidth = SCALER_WIDTH,
        .outputHeight = SCALER_HEIGHT,
    };

    cameraCfg.memStart = (uint32_t)(uintptr_t)line_buf;
    mjpegCfg.bufferCamYY = (uint32_t)(uintptr_t)line_buf;
    mjpegCfg.bufferMjpeg = (uint32_t)(uintptr_t)mjpeg_buf;

    MJPEG_Set_YUYV_Order_Interleave(0,1,2,3);
 
    MJPEG_Calculate_Quantize_Table(Q_Table_50_Y,tmpTableY,MJPEG_QUALITY);
    MJPEG_Calculate_Quantize_Table(Q_Table_50_UV,tmpTableUV,MJPEG_QUALITY);
    MJPEG_Set_Quantize_Table_Y(tmpTableY);
    MJPEG_Set_Quantize_Table_UV(tmpTableUV);
    MJPEG_Quantize_SRAM_Switch();
 
    jpgHeadLength = JpegHeadCreate(YUV_MODE_422, MJPEG_QUALITY, SCALER_WIDTH, SCALER_HEIGHT, jpgHeadBuf);
    uint8_t *jpeg_head = (uint8_t *)JPEG_HEADER;
    for (int i = 0; i < jpgHeadLength; i++) {
        jpeg_head[i] = jpgHeadBuf[i];
    }
    //memcpy((uint8_t *)JPEG_HEADER, jpgHeadBuf, jpgHeadLength); //cpy jpeg header to refernce sram 0x30021800
    csi_dcache_clean_range((void *)JPEG_HEADER, jpgHeadLength);
    MJPEG_Frame_Head_Set_Size(jpgHeadLength);
    MJPEG_Frame_Tail_Auto_Fill(ENABLE);
    /* enable scaler for 480x320*/ 
    ISP_MISC_Scaler_Input_Select(ISP_MISC_SCALER_2_ID, ISP_MISC_SCALER_ISP_INPUT);
    ISP_MISC_Scaler_Init(ISP_MISC_SCALER_2_ID, &scaler_cfg);
    ISP_MISC_Scaler_Enable(ISP_MISC_SCALER_2_ID);
 
    ISP_MISC_CAM_Input_Select(MJPEG_CAM_ID, ISP_MISC_CAM_SCALER_2_OUTPUT);
    CAM_Init(MJPEG_CAM_ID, &cameraCfg);
    MJPEG_Init(&mjpegCfg);
    MJPEG_Set_Planar_Y_UV_Input(4, 5);
    MJPEG_Enable();

    CAM_Enable(MJPEG_CAM_ID);
    bl_cam_mipi_csi_init();
exit:
    return ret;
}
#endif
