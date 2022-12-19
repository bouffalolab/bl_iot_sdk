/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

#ifndef __BL808_SPP_MISC_H__
#define __BL808_SPP_MISC_H__

#include <bl808_comm_mm.h>


typedef void(intCallback_Type)(void);

typedef enum {
    DVP_TSRC_PIX_FROM_SPP       = 0,
    DVP_TSRC_PIX_FROM_SENSOR    = 1,
} SPP_DVP_TSRC_PIX_SEL_E;

typedef enum {
    DVP_TSRC_SRC_DVP         = 0,
    DVP_TSRC_SRC_MIPI_CSI    = 1,
} SPP_DTSRC_SRC_E;

typedef enum {
    DVP2AXI_ID_BAYER   = 0,
    DVP2AXI_ID_YUV     = 1,
} DVP2AXI_ID_E;

typedef enum {
    DVP2AXI_SRC_SPP_INPUT              = 0,
    DVP2AXI_SRC_RESERVE0               = 0x1,
    DVP2AXI_SRC_SCALER_FOR_CODEC       = 0x2,
    DVP2AXI_SRC_CODEC_YUV420           = 0x3,
    DVP2AXI_SRC_RESERVE1_OUT           = 0x8,
    DVP2AXI_SRC_RESERVE2               = 0x9,
    DVP2AXI_SRC_RESERVE3               = 0xa,
    DVP2AXI_SRC_RESERVE4_R             = 0xb,
    DVP2AXI_SRC_RESERVE4_G             = 0xc,
    DVP2AXI_SRC_RESERVE4_B             = 0xd,
    DVP2AXI_SRC_RESERVE5_R             = 0xe,
    DVP2AXI_SRC_RESERVE5_G             = 0xf,
    DVP2AXI_SRC_RESERVE5_B             = 0x10,
    DVP2AXI_SRC_RESERVE6_GR            = 0x11,
    DVP2AXI_SRC_RESERVE6_BG            = 0x12,
    DVP2AXI_SRC_RESERVE7_OUT           = 0x19,
    DVP2AXI_SRC_YUV_CONTROL_CB_Y       = 0x1a,
    DVP2AXI_SRC_YUV_CONTROL_CR_CB      = 0x1b,
    DVP2AXI_SRC_RESERVE7               = 0x1d,
    DVP2AXI_SRC_SPP_OUTPUT             = 0x1e,
    DVP2AXI_SRC_SCALER_FOR_HDMI        = 0x1f,
    DVP2AXI_SRC_OFF                    = 0x20,
} DVP2AXI_Src_Type;


/**
 *  @brief Input V/H sync active level type definition
 */
typedef enum {
    SPP_MISC_ACTIVE_HIGH, /*!< Input is active-high */
    SPP_MISC_ACTIVE_LOW,  /*!< Input is active-low */
}SPP_MISC_Active_Level_Type;

/**
 *  @brief DVP 2X input data order type definition
 */
typedef enum {
    SPP_MISC_2X_DATA_BYTE_LOWER,  /*!< The first data is lower-byte */
    SPP_MISC_2X_DATA_BYTE_HIGHER, /*!< The first data is higher-byte */
}SPP_MISC_2X_Data_Order_Type;

/**
 *  @brief DVP input V/H sync active level type definition
 */
typedef enum {
    DVP_ACTIVE_HIGH,                         /*!< Input is active-high */
    DVP_ACTIVE_LOW,                          /*!< Input is active-low */
}DVP_Active_Level_Type;

/**
 *  @brief DVP input data order type definition
 */
typedef enum {
    DVP_DATA_BYTE_LOWER,                     /*!< The first data is lower-byte */
    DVP_DATA_BYTE_HIGHER,                    /*!< The first data is higher-byte */
}DVP_Data_Order_Type;

/**
 *  @brief DVP as 2x configuration strcut definition
 */
typedef struct {
    SPP_MISC_Active_Level_Type hSyncLevel;        /*!< Input H-Sync active level */
    SPP_MISC_Active_Level_Type vSyncLevel;        /*!< Input V-Sync active level */
    SPP_MISC_2X_Data_Order_Type dataOrder;        /*!< Input data order */
    uint16_t fifoThreshold;                       /*!< Fifo threshold for each DVP line to start to
                                                  output,((Width-Fifo_th)*T_in*2)<(Width*T_out)<((Width-Fifo_th)*T_in*2+Blank*T_in) */
}DVP_2x_Cfg_Type;

/*
    SEOF number
 */
typedef enum {
    SPP_SEOF0 = 0,
    SPP_SEOF1,
    SPP_SEOF2,
    SPP_SEOF3,
    SPP_SEOF4,
    SPP_SEOF_NUM,
}SPP_SEOF_E;

typedef enum {
    SEOF_INTR_SRC_SENSOR_VSYNC = 0,
    SEOF_INTR_SRC_SPP_ACT_VSYNC = 1,
    SEOF_INTR_SRC_SPP_OUT_VSYNC = 2,
    SEOF_INTR_SRC_DTSRC_VSYNC = 3,
    SEOF_INTR_SRC_INVALID,
} SPP_Seof_Intr_Src_Type;

typedef enum {
    SPP_DVP_10_BIT = 0,
    SPP_DVP_12_BIT = 1,
} SPP_DVP_BIT_DEPTH_E;

typedef enum {
    SPP_SCALER_A,
    SPP_SCALER_B,
    SPP_SCALER_C,
    SPP_SCALER_D,
} SPP_Scaler_Type;

typedef enum {
    SPP_YUV_ADJUST_A,
    SPP_YUV_ADJUST_B,
    SPP_YUV_ADJUST_C,
    SPP_YUV_ADJUST_D,
} SPP_YUV_Adjust_Type;

typedef enum {
    SPP_YUV_ADJUST_INPUT_SPP_OUTPUT ,
    SPP_YUV_ADJUST_INPUT_SPP_INPUT,
    SPP_YUV_ADJUST_INPUT_OSD_A,
    SPP_YUV_ADJUST_INPUT_OSD_B,
    SPP_YUV_ADJUST_INPUT_OSD_C,
    SPP_YUV_ADJUST_INPUT_OSD_D,
    SPP_YUV_ADJUST_INPUT_SCALER_A,
    SPP_YUV_ADJUST_INPUT_SCALER_B,
    SPP_YUV_ADJUST_INPUT_SCALER_C,
    SPP_YUV_ADJUST_INPUT_SCALER_D,
    SPP_YUV_ADJUST_INPUT_DVP_2x,
} SPP_YUV_Adjust_Input;

/**
 *  @brief OSD id type definition
 */
typedef enum {
    SPP_MISC_OSD_0_ID,                       /*!< OSD 0 port define */
    SPP_MISC_OSD_1_ID,                       /*!< OSD 1 port define */
    SPP_MISC_OSD_2_ID,                       /*!< OSD 2 port define */
    SPP_MISC_OSD_3_ID,                       /*!< OSD 3 port define */
    SPP_MISC_OSD_ID_MAX,                     /*!< OSD max ID define */
}SPP_MISC_OSD_ID_Type;

/**
 *  @brief OSD input type definition
 */
typedef enum {
    SPP_MISC_OSD_SPP_OUTPUT,                 /*!< Use SPP output as OSD input */
    SPP_MISC_OSD_SPP_INPUT,                  /*!< Use SPP input as OSD input */
    SPP_MISC_OSD_SCALER_0_OUTPUT,            /*!< Use scaler 0 as OSD input */
    SPP_MISC_OSD_SCALER_1_OUTPUT,            /*!< Use scaler 1 as OSD input */
    SPP_MISC_OSD_SCALER_2_OUTPUT,            /*!< Use scaler 2 as OSD input */
    SPP_MISC_OSD_SCALER_3_OUTPUT,            /*!< Use scaler 3 as OSD input */
    SPP_MISC_OSD_OSD_0_OUTPUT,               /*!< Use osd 0 as OSD input, only osd 1/osd 3 support */
    SPP_MISC_OSD_DVP_2X_OUTPUT,              /*!< Use dvp 2x as OSD input */
    SPP_MISC_OSD_INPUT_MAX,                  /*!< OSD input max ID define */
}SPP_MISC_OSD_Input_Type;
/**
 *  @brief OSD Pb input type definition
 */
typedef enum {
    SPP_MISC_OSD_PB_SPP_OUTPUT,                 /*!< Use SPP output as OSD input */
    SPP_MISC_OSD_PB_SPP_INPUT,                  /*!< Use SPP input as OSD input */
    SPP_MISC_OSD_PB_MAX,                        /*!< OSD PB max ID define */
}SPP_MISC_OSD_PB_Input_Type;

typedef enum {
    SPP_OSD_A,
    SPP_OSD_B,
    SPP_OSD_C,
    SPP_OSD_D,
} SPP_OSD_Type;

typedef enum {
    SPP_YUV2RGB_A,
} SPP_YUV2RGB_Type;

typedef enum {
    SPP_SCALER_INPUT_SPP_OUTPUT ,
    SPP_SCALER_INPUT_SPP_INPUT,
    SPP_SCALER_INPUT_OSD_A,
    SPP_SCALER_INPUT_OSD_B,
    SPP_SCALER_INPUT_OSD_C,
    SPP_SCALER_INPUT_OSD_D,
    SPP_SCALER_DVP_2X,
} SPP_Scaler_Input;

/**
 *  @brief Crop configuration strcut definition
 */
typedef struct {
    uint16_t hsyncStart;                     /*!< Hsync valid start */
    uint16_t hsyncEnd;                       /*!< Hsync valid end */
    uint16_t vsyncStart;                     /*!< Vsync valid start */
    uint16_t vsyncEnd;                       /*!< Vsync valid end */
}SPP_MISC_Crop_Cfg_Type;

typedef enum {
    SPP_OSD_INPUT_SPP_OUTPUT ,
    SPP_OSD_INPUT_SPP_INPUT,
    SPP_OSD_INPUT_SCALER_A,
    SPP_OSD_INPUT_SCALER_B,
    SPP_OSD_INPUT_SCALER_C,
    SPP_OSD_INPUT_SCALER_D,
    SPP_OSD_INPUT_OSD_A,
    SPP_OSD_INPUT_OSD_C,
} SPP_OSD_Input;

typedef enum {
    SPP_YUV2RGB_INPUT_SPP_OUTPUT,
    SPP_YUV2RGB_INPUT_SPP_INPUT,
    SPP_YUV2RGB_INPUT_OSD_A,
    SPP_YUV2RGB_INPUT_OSD_B,
    SPP_YUV2RGB_INPUT_OSD_C,
    SPP_YUV2RGB_INPUT_OSD_D,
    SPP_YUV2RGB_INPUT_SCALER_A,
    SPP_YUV2RGB_INPUT_SCALER_B,
    SPP_YUV2RGB_INPUT_SCALER_C,
    SPP_YUV2RGB_INPUT_SCALER_D,
    SPP_YUV2RGB_INPUT_DVP_2X,
    SPP_YUV2RGB_INPUT_DISABLED,
} SPP_YUV2RGB_Input;

typedef enum {
    SPP_YUV2RGB_PARAM_8BIT_BT601 = 0,
    SPP_YUV2RGB_PARAM_MAX,
} SPP_YUV2RGB_Param;

typedef struct blSPP_DVP2AXI_SRC_SEL_S {
    DVP2AXI_Src_Type data[DVP2AXI_NUM];
} SPP_DVP2AXI_SRC_SEL_S;

typedef struct blSPP_SCALER_CONFIG_S {
    BL_Img_Size_T input;
    BL_Img_Size_T output;
} SPP_SCALER_CONFIG_S;

typedef struct blSPP_FRAME_M_TO_N_S {
    BL_Fun_Type enb;
    int m;
    int n;
    int intv;
} SPP_FRAME_M_TO_N_S;

struct yuv2rgb_param_t {
    int pre_offset_0;
    int pre_offset_1;
    int pre_offset_2;
    int post_offset_0;
    int post_offset_1;
    int post_offset_2;
    int matrix_00;
    int matrix_01;
    int matrix_02;
    int matrix_10;
    int matrix_11;
    int matrix_12;
    int matrix_20;
    int matrix_21;
    int matrix_22;
};

/**
 *  @brief Bayer data shift direction type definition
 */
typedef enum {
    SPP_MISC_BAYER_SHIFT_LEFT,               /*!< Bayer data shift left */
    SPP_MISC_BAYER_SHIFT_RIGHT,              /*!< Bayer data shift right */
}SPP_MISC_Bayer_Shift_Type;

/**
 *  @brief Display input type definition
 */
typedef enum {
    SPP_MISC_DISPLAY_YUV2RGB_OUTPUT,         /*!< Use yuv2rgb output as display input */
    SPP_MISC_DISPLAY_OSD_DP_OUTPUT,          /*!< Use OSD_DP output as display input */
    SPP_MISC_DISPLAY_TSRC_RGB_OUTPUT,        /*!< Use dvp tsrc rgb output as display input */
    SPP_MISC_DISPLAY_TSRC_YUV422_OUTPUT,     /*!< Use dvp tsrc yuv422 output as display input */
}SPP_MISC_Display_Input_Type;

/**
 *  @brief Display OSD input type definition
 */
typedef enum {
    SPP_MISC_DISPLAY_OSD_YUV420TO422_OUTPUT, /*!< Use yuv420to422 output as display OSD input */
    SPP_MISC_DISPLAY_OSD_RGB2YUV422_OUTPUT,  /*!< Use rgb2yuv422 output as display OSD input */
    SPP_MISC_DISPLAY_OSD_TSRCYUV422_OUTPUT,  /*!< Use dvp tsrc yuv422 output as display OSD input */
}SPP_MISC_Display_OSD_Input_Type;

/**
 *  @brief Display configuration structure type definition
 */
typedef struct {
    BL_Fun_Type dpiEnable;                   /*!< Enable or disable dpi function */
    BL_Fun_Type hdmiEnable;                  /*!< Enable or disable hdmi function */
    BL_Fun_Type bt1120Enable;                /*!< Enable or disable BT1120 function, BT1120 and BT656 should not be enabled at the same time */
    BL_Fun_Type bt656Enable;                 /*!< Enable or disable BT656 function, BT1120 and BT656 should not be enabled at the same time */
    SPP_MISC_Display_Input_Type inputType;   /*!< Select display input */
    SPP_MISC_Display_OSD_Input_Type osdType; /*!< Select display OSD input */
    uint8_t hsyncWidth;                      /*!< Horizontal synchronization width */
    uint8_t hfpWidth;                        /*!< Horizontal front porch width */
    uint8_t vsyncWidth;                      /*!< Vertical synchronization width */
    uint8_t vfpWidth;                        /*!< Vertical front porch width */
}SPP_MISC_Display_Cfg_Type;

/**
 *  @brief Display gamma configuration structure type definition
 */
typedef struct {
    BL_Fun_Type ch0Enable;                   /*!< Enable or disable display gamma channel 0 */
    BL_Fun_Type ch1Enable;                   /*!< Enable or disable display gamma channel 1 */
    BL_Fun_Type ch2Enable;                   /*!< Enable or disable display gamma channel 2 */
    uint8_t* gammaCurve;                     /*!< Gamma curve */
}SPP_MISC_Display_Gamma_Cfg_Type;

typedef struct {
    uint16_t y_luma;
    uint16_t y_mul0;
    uint16_t y_mul1;
    uint8_t y_min;
    uint8_t y_max;
    uint16_t uv_mul0;
    uint16_t uv_mul1;
    uint8_t uv_min;
    uint8_t uv_max;
}SPP_YUV_Adjust_Cfg_Type;

/**
 *  @brief YUV2RGB configuration strcut definition
 */
typedef struct {
    BL_Fun_Type enable;                      /*!< Enable or disable yuv2rgb function */
    uint16_t preOffset0;                     /*!< YUV2RGB pre offset 0 */
    uint16_t preOffset1;                     /*!< YUV2RGB pre offset 1 */
    uint16_t preOffset2;                     /*!< YUV2RGB pre offset 2 */
    uint16_t postOffset0;                    /*!< YUV2RGB post offset 0 */
    uint16_t postOffset1;                    /*!< YUV2RGB post offset 1 */
    uint16_t postOffset2;                    /*!< YUV2RGB post offset 2 */
    uint16_t matrix00;                       /*!< YUV2RGB matrix 00 */
    uint16_t matrix01;                       /*!< YUV2RGB matrix 01 */
    uint16_t matrix02;                       /*!< YUV2RGB matrix 02 */
    uint16_t matrix10;                       /*!< YUV2RGB matrix 10 */
    uint16_t matrix11;                       /*!< YUV2RGB matrix 11 */
    uint16_t matrix12;                       /*!< YUV2RGB matrix 12 */
    uint16_t matrix20;                       /*!< YUV2RGB matrix 20 */
    uint16_t matrix21;                       /*!< YUV2RGB matrix 21 */
    uint16_t matrix22;                       /*!< YUV2RGB matrix 22 */
}SPP_MISC_YUV2RGB_Cfg_Type;

/**
 *  @brief RGB2YUV configuration strcut definition
 */
typedef struct {
    BL_Fun_Type enable;                      /*!< Enable or disable rgb2yuv function */
    uint16_t preOffset0;                     /*!< RGB2YUV pre offset 0 */
    uint16_t preOffset1;                     /*!< RGB2YUV pre offset 1 */
    uint16_t preOffset2;                     /*!< RGB2YUV pre offset 2 */
    uint16_t postOffset0;                    /*!< RGB2YUV post offset 0 */
    uint16_t postOffset1;                    /*!< RGB2YUV post offset 1 */
    uint16_t postOffset2;                    /*!< RGB2YUV post offset 2 */
    uint16_t matrix00;                       /*!< RGB2YUV matrix 00 */
    uint16_t matrix01;                       /*!< RGB2YUV matrix 01 */
    uint16_t matrix02;                       /*!< RGB2YUV matrix 02 */
    uint16_t matrix10;                       /*!< RGB2YUV matrix 10 */
    uint16_t matrix11;                       /*!< RGB2YUV matrix 11 */
    uint16_t matrix12;                       /*!< RGB2YUV matrix 12 */
    uint16_t matrix20;                       /*!< RGB2YUV matrix 20 */
    uint16_t matrix21;                       /*!< RGB2YUV matrix 21 */
    uint16_t matrix22;                       /*!< RGB2YUV matrix 22 */
}SPP_MISC_RGB2YUV_Cfg_Type;

/**
 *  @brief Scaler configuration strcut definition
 */
typedef struct {
    uint16_t inputWidth;                     /*!< Width of input frame */
    uint16_t inputHeight;                    /*!< Height of input frame */
    uint16_t outputWidth;                    /*!< Width of output frame */
    uint16_t outputHeight;                   /*!< Height of output frame */
}SPP_MISC_Scaler_Cfg_Type;

/**
 *  @brief Scaler input type definition
 */
typedef enum {
    SPP_MISC_SCALER_SPP_OUTPUT,              /*!< Use SPP output as scaler input */
    SPP_MISC_SCALER_SPP_INPUT,               /*!< Use SPP input as scaler input */
    SPP_MISC_SCALER_OSD_0_OUTPUT,            /*!< Use OSD 0 as scaler input */
    SPP_MISC_SCALER_OSD_1_OUTPUT,            /*!< Use OSD 1 as scaler input */
    SPP_MISC_SCALER_OSD_2_OUTPUT,            /*!< Use OSD 2 as scaler input */
    SPP_MISC_SCALER_OSD_3_OUTPUT,            /*!< Use OSD 3 as scaler input */
    SPP_MISC_SCALER_DVP_2X_OUTPUT,           /*!< Use DVP 2X as scaler input */
}SPP_MISC_Scaler_Input_Type;


/**
 *  @brief DVP TSRC data source type definition
 */
typedef enum {
    SPP_MISC_TSRC_SOURCE_DVP, /*!< DVP TSRC data source is DVP */
    SPP_MISC_TSRC_SOURCE_CSI, /*!< DVP TSRC data source is MIPI CSI */
}SPP_MISC_TSRC_Source_Type;


/**
 *  @brief Scaler id type definition
 */
typedef enum {
    SPP_MISC_SCALER_0_ID,                    /*!< Scaler 0 port define */
    SPP_MISC_SCALER_1_ID,                    /*!< Scaler 1 port define */
    SPP_MISC_SCALER_2_ID,                    /*!< Scaler 2 port define */
    SPP_MISC_SCALER_3_ID,                    /*!< Scaler 3 port define */
    SPP_MISC_SCALER_ID_MAX,                  /*!< Scaler max ID define */
}SPP_MISC_Scaler_ID_Type;

/**
 *  @brief Crop id type definition
 */
typedef enum {
    SPP_MISC_CROP_0_ID,                      /*!< Crop 0 port define */
    SPP_MISC_CROP_1_ID,                      /*!< Crop 1 port define */
    SPP_MISC_CROP_2_ID,                      /*!< Crop 2 port define */
    SPP_MISC_CROP_3_ID,                      /*!< Crop 3 port define */
    SPP_MISC_CROP_ID_MAX,                    /*!< Crop max ID define */
}SPP_MISC_Crop_ID_Type;

/**
 *  @brief CAM id type definition
 */
typedef enum {
    SPP_MISC_CAM_0_ID,                       /*!< CAM 0 port define */
    SPP_MISC_CAM_1_ID,                       /*!< CAM 1 port define */
    SPP_MISC_CAM_2_ID,                       /*!< CAM 2 port define */
    SPP_MISC_CAM_3_ID,                       /*!< CAM 3 port define */
    SPP_MISC_CAM_4_ID,                       /*!< CAM 4 port define */
    SPP_MISC_CAM_5_ID,                       /*!< CAM 5 port define */
    SPP_MISC_CAM_6_ID,                       /*!< CAM 6 port define */
    SPP_MISC_CAM_7_ID,                       /*!< CAM 7 port define */
    SPP_MISC_CAM_ID_MAX,                     /*!< CAM max ID define */
}SPP_MISC_CAM_ID_Type;

/**
 *  @brief CAM input type definition
 */
typedef enum {
    SPP_MISC_CAM_SPP_INPUT,                  /*!< Use SPP input as CAM input */
    SPP_MISC_CAM_ACTIVE_DVP_OUTPUT,          /*!< Use active DVP(TG) as CAM input */
    SPP_MISC_CAM_DEFECT_CORRECT_OUTPUT,      /*!< Use defect correct as CAM input */
    SPP_MISC_CAM_RESERVE0_R_OUTPUT,          /*!< Use RESERVE0 R as CAM input */
    SPP_MISC_CAM_RESERVE0_G_OUTPUT,          /*!< Use RESERVE0 G as CAM input */
    SPP_MISC_CAM_RESERVE0_B_OUTPUT,          /*!< Use RESERVE0 B as CAM input */
    SPP_MISC_CAM_RESERVE1_R_OUTPUT,          /*!< Use RESERVE1 R as CAM input */
    SPP_MISC_CAM_RESERVE1_G_OUTPUT,          /*!< Use RESERVE1 G as CAM input */
    SPP_MISC_CAM_NONE_OUTPUT,                /*!< Don't use */
    SPP_MISC_CAM_RESERVE2_OUTPUT,            /*!< Use RESERVE2 as CAM input */
    SPP_MISC_CAM_RESERVE3_OUTPUT,            /*!< Use RESERVE3 as CAM input */
    SPP_MISC_CAM_RESERVE4_OUTPUT,            /*!< Use RESERVE4 as CAM input */
    SPP_MISC_CAM_SPP_OUTPUT,                 /*!< Use SPP output as CAM input */
    SPP_MISC_CAM_OSD_0_OUTPUT,               /*!< Use OSD 0 as CAM input */
    SPP_MISC_CAM_OSD_1_OUTPUT,               /*!< Use OSD 1 as CAM input */
    SPP_MISC_CAM_OSD_2_OUTPUT,               /*!< Use OSD 2 as CAM input */
    SPP_MISC_CAM_OSD_3_OUTPUT,               /*!< Use OSD 3 as CAM input */
    SPP_MISC_CAM_SCALER_0_OUTPUT,            /*!< Use scaler 0 as CAM input */
    SPP_MISC_CAM_SCALER_1_OUTPUT,            /*!< Use scaler 1 as CAM input */
    SPP_MISC_CAM_SCALER_2_OUTPUT,            /*!< Use scaler 2 as CAM input */
    SPP_MISC_CAM_SCALER_3_OUTPUT,            /*!< Use scaler 3 as CAM input */
    SPP_MISC_CAM_ADJUST_0_OUTPUT,            /*!< Use adjust 0 as CAM input */
    SPP_MISC_CAM_ADJUST_1_OUTPUT,            /*!< Use adjust 1 as CAM input */
    SPP_MISC_CAM_ADJUST_2_OUTPUT,            /*!< Use adjust 2 as CAM input */
    SPP_MISC_CAM_ADJUST_3_OUTPUT,            /*!< Use adjust 3 as CAM input */
    SPP_MISC_CAM_YUV420_0_OUTPUT,            /*!< Use YUV420 0 as CAM input */
    SPP_MISC_CAM_YUV420_1_OUTPUT,            /*!< Use YUV420 1 as CAM input */
    SPP_MISC_CAM_YUV420_2_OUTPUT,            /*!< Use YUV420 2 as CAM input */
    SPP_MISC_CAM_YUV420_3_OUTPUT,            /*!< Use YUV420 3 as CAM input */
    SPP_MISC_CAM_RESERVE5_B_OUTPUT,          /*!< Use RESERVE5 B as CAM input */
    SPP_MISC_CAM_RESERVE6_Y_OUTPUT,          /*!< Use RESERVE6 Y as CAM input */
    SPP_MISC_CAM_RESERVE6_U_OUTPUT,          /*!< Use RESERVE6 U as CAM input */
    SPP_MISC_CAM_RESERVE6_V_OUTPUT,          /*!< Use RESERVE6 V as CAM input */
    SPP_MISC_CAM_RESERVE7_OUTPUT,            /*!< Use RESERVE7 as CAM input */
    SPP_MISC_CAM_YUV2RGB_OUTPUT = 35,        /*!< Use YUV2RGB as CAM input */
    SPP_MISC_CAM_DVP2X_OUTPUT = 36,          /*!< Use DVP2X as CAM input */
}SPP_MISC_CAM_Input_Type;


/**
 *  @brief SPP MISC interrupt type definition
 */
typedef enum {
    SPP_MISC_INT_OSD_PB,  /*!< OSD probe interrupt */
    SPP_MISC_INT_SEOF0,   /*!< S/E-oF 0 interrupt */
    SPP_MISC_INT_SEOF1,   /*!< S/E-oF 1 interrupt */
    SPP_MISC_INT_SEOF2,   /*!< S/E-oF 2 interrupt */
    SPP_MISC_INT_DISPLAY, /*!< Display S/E-oF 0 interrupt */
    SPP_MISC_INT_SEOF3,   /*!< S/E-oF 3 interrupt */
    SPP_MISC_INT_ALL,     /*!< All the interrupt */
} SPP_MISC_INT_Type;

/**
 *  @brief SEOF interrupt vsync source type definition
 */
typedef enum {
    SPP_MISC_SEOF_VSYNC_SENSOR = 0,     /*!< Use sensor vsync as SEOF vsync source */
    SPP_MISC_SEOF_VSYNC_SPP_ACT = 1,    /*!< Use isp active vsync as SEOF vsync source */
    SPP_MISC_SEOF_VSYNC_SPP_OUT = 2,    /*!< Use isp out vsync as SEOF vsync source */
    SPP_MISC_SEOF_VSYNC_DVP_TSRC = 3,   /*!< Use dvp tsrc vsync as SEOF vsync source */
    SPP_MISC_SEOF_DISPLAY_TEST_SRC = 0, /*!< Use display test source as display SEOF vsync source */
    SPP_MISC_SEOF_DISPLAY_OUTPUT = 1,   /*!< Use display output as display SEOF vsync source */
} SPP_MISC_SEOF_Source_Type;

/**
 *  @brief SEOF interrupt trigger vsync edge type definition
 */
typedef enum {
    SPP_MISC_SEOF_VSYNC_NEGEDGE, /*!< Vsync negedge will trigger interrupt */
    SPP_MISC_SEOF_VSYNC_POSEDGE, /*!< Vsync posedge will trigger interrupt */
} SPP_MISC_SEOF_Edge_Type;

/**
 *  @brief YUV2RGB id type definition
 */
typedef enum {
    SPP_MISC_YUV2RGB_DISPLAY_ID,             /*!< Display YUV2RGB port define, disp_y2r*/
    SPP_MISC_YUV2RGB_NORMAL_ID,              /*!< Normal YUV2RGB port define, y2rA */
    SPP_MISC_YUV2RGB_ID_MAX,                 /*!< YUV2RGB max ID define */
}SPP_MISC_YUV2RGB_ID_Type;

/** @defgroup  SPP_MISC_CAM_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_CAM_ID_TYPE(type)                    (((type) == SPP_MISC_CAM_0_ID) || \
                                                          ((type) == SPP_MISC_CAM_1_ID) || \
                                                          ((type) == SPP_MISC_CAM_2_ID) || \
                                                          ((type) == SPP_MISC_CAM_3_ID) || \
                                                          ((type) == SPP_MISC_CAM_4_ID) || \
                                                          ((type) == SPP_MISC_CAM_5_ID) || \
                                                          ((type) == SPP_MISC_CAM_6_ID) || \
                                                          ((type) == SPP_MISC_CAM_7_ID) || \
                                                          ((type) == SPP_MISC_CAM_ID_MAX))

/** @defgroup  SPP_MISC_SCALER_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_SCALER_ID_TYPE(type)                 (((type) == SPP_MISC_SCALER_0_ID) || \
                                                          ((type) == SPP_MISC_SCALER_1_ID) || \
                                                          ((type) == SPP_MISC_SCALER_2_ID) || \
                                                          ((type) == SPP_MISC_SCALER_3_ID) || \
                                                          ((type) == SPP_MISC_SCALER_ID_MAX))

/** @defgroup  SPP_MISC_TSRC_SOURCE_TYPE
 *  @{
 */
#define IS_SPP_MISC_TSRC_SOURCE_TYPE(type) (((type) == SPP_MISC_TSRC_SOURCE_DVP) || \
                                            ((type) == SPP_MISC_TSRC_SOURCE_CSI))


/** @defgroup  SPP_MISC_OSD_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_OSD_ID_TYPE(type)                    (((type) == SPP_MISC_OSD_0_ID) || \
                                                          ((type) == SPP_MISC_OSD_1_ID) || \
                                                          ((type) == SPP_MISC_OSD_2_ID) || \
                                                          ((type) == SPP_MISC_OSD_3_ID) || \
                                                          ((type) == SPP_MISC_OSD_ID_MAX))

/** @defgroup  SPP_MISC_ADJUST_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_ADJUST_ID_TYPE(type)                 (((type) == SPP_MISC_ADJUST_0_ID) || \
                                                          ((type) == SPP_MISC_ADJUST_1_ID) || \
                                                          ((type) == SPP_MISC_ADJUST_2_ID) || \
                                                          ((type) == SPP_MISC_ADJUST_3_ID) || \
                                                          ((type) == SPP_MISC_ADJUST_ID_MAX))

/** @defgroup  SPP_MISC_YUV2RGB_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_YUV2RGB_ID_TYPE(type)                (((type) == SPP_MISC_YUV2RGB_DISPLAY_ID) || \
                                                          ((type) == SPP_MISC_YUV2RGB_NORMAL_ID) || \
                                                          ((type) == SPP_MISC_YUV2RGB_ID_MAX))

/** @defgroup  SPP_MISC_CAM_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_CAM_INPUT_TYPE(type)                 (((type) == SPP_MISC_CAM_SPP_INPUT) || \
                                                          ((type) == SPP_MISC_CAM_ACTIVE_DVP_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_DEFECT_CORRECT_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE0_R_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE0_G_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE0_B_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE1_R_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE1_G_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_NONE_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE2_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE3_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE4_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_SPP_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_OSD_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_OSD_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_OSD_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_OSD_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_SCALER_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_SCALER_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_SCALER_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_SCALER_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_ADJUST_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_ADJUST_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_ADJUST_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_ADJUST_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_YUV420_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_YUV420_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_YUV420_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_YUV420_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE5_B_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE6_Y_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE6_U_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE6_V_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_YUV2RGB_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_DVP2X_OUTPUT) || \
                                                          ((type) == SPP_MISC_CAM_RESERVE7_OUTPUT))

/** @defgroup  SPP_MISC_SCALER_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_SCALER_INPUT_TYPE(type)              (((type) == SPP_MISC_SCALER_SPP_OUTPUT) || \
                                                          ((type) == SPP_MISC_SCALER_SPP_INPUT) || \
                                                          ((type) == SPP_MISC_SCALER_OSD_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_SCALER_OSD_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_SCALER_OSD_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_SCALER_OSD_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_SCALER_DVP_2X_OUTPUT))

/** @defgroup  SPP_MISC_OSD_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_OSD_INPUT_TYPE(type)                 (((type) == SPP_MISC_OSD_SPP_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_SPP_INPUT) || \
                                                          ((type) == SPP_MISC_OSD_SCALER_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_SCALER_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_SCALER_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_SCALER_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_OSD_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_DVP_2X_OUTPUT))
/** @defgroup  SPP_MISC_OSD_PB_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_OSD_PB_INPUT_TYPE(type)              (((type) == SPP_MISC_OSD_PB_SPP_OUTPUT) || \
                                                          ((type) == SPP_MISC_OSD_PB_SPP_INPUT))

/** @defgroup  SPP_MISC_YUV2RGB_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_YUV2RGB_INPUT_TYPE(type)             (((type) == SPP_MISC_YUV2RGB_SPP_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_SPP_INPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_OSD_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_OSD_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_OSD_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_OSD_3_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_SCALER_0_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_SCALER_1_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_SCALER_2_OUTPUT) || \
                                                          ((type) == SPP_MISC_YUV2RGB_SCALER_3_OUTPUT))

/** @defgroup  SPP_MISC_BAYER_SHIFT_TYPE
 *  @{
 */
#define IS_SPP_MISC_BAYER_SHIFT_TYPE(type)               (((type) == SPP_MISC_BAYER_SHIFT_LEFT) || \
                                                          ((type) == SPP_MISC_BAYER_SHIFT_RIGHT))

/** @defgroup  SPP_MISC_INT_TYPE
 *  @{
 */
#define IS_SPP_MISC_INT_TYPE(type) (((type) == SPP_MISC_INT_OSD_PB) ||  \
                                    ((type) == SPP_MISC_INT_SEOF0) ||   \
                                    ((type) == SPP_MISC_INT_SEOF1) ||   \
                                    ((type) == SPP_MISC_INT_SEOF2) ||   \
                                    ((type) == SPP_MISC_INT_DISPLAY) || \
                                    ((type) == SPP_MISC_INT_SEOF3) ||   \
                                    ((type) == SPP_MISC_INT_ALL))
/** @defgroup  SPP_MISC_SEOF_SOURCE_TYPE
 *  @{
 */
#define IS_SPP_MISC_SEOF_SOURCE_TYPE(type) (((type) == SPP_MISC_SEOF_VSYNC_SENSOR) ||     \
                                            ((type) == SPP_MISC_SEOF_VSYNC_SPP_ACT) ||    \
                                            ((type) == SPP_MISC_SEOF_VSYNC_SPP_OUT) ||    \
                                            ((type) == SPP_MISC_SEOF_VSYNC_DVP_TSRC) ||    \
                                            ((type) == SPP_MISC_SEOF_DISPLAY_TEST_SRC) || \
                                            ((type) == SPP_MISC_SEOF_DISPLAY_OUTPUT))




/** @defgroup  SPP_MISC_SEOF_EDGE_TYPE
 *  @{
 */
#define IS_SPP_MISC_SEOF_EDGE_TYPE(type)                 (((type) == SPP_MISC_SEOF_VSYNC_NEGEDGE) || \
                                                          ((type) == SPP_MISC_SEOF_VSYNC_POSEDGE))

/** @defgroup  SPP_MISC_DISPLAY_INPUT_TYPE
 *  @{
 */
#define IS_SPP_MISC_DISPLAY_INPUT_TYPE(type)             (((type) == SPP_MISC_DISPLAY_YUV2RGB_OUTPUT) || \
                                                          ((type) == SPP_MISC_DISPLAY_YUV422_OUTPUT))

/*@} end of group SPP_MISC_Public_Constants */

/** @defgroup  SPP_MISC_CROP_ID_TYPE
 *  @{
 */
#define IS_SPP_MISC_CROP_ID_TYPE(type)                   (((type) == SPP_MISC_CROP_0_ID) || \
                                                          ((type) == SPP_MISC_CROP_1_ID) || \
                                                          ((type) == SPP_MISC_CROP_2_ID) || \
                                                          ((type) == SPP_MISC_CROP_3_ID) || \
                                                          ((type) == SPP_MISC_CROP_ID_MAX))

/** @defgroup  DVP_DATA_ORDER_TYPE
 *  @{
 */
#define IS_DVP_DATA_ORDER_TYPE(type)                     (((type) == SPP_MISC_2X_DATA_BYTE_LOWER) || \
                                                          ((type) == SPP_MISC_2X_DATA_BYTE_HIGHER))

/** @defgroup  DVP_ACTIVE_LEVEL_TYPE
 *  @{
 */
#define IS_DVP_ACTIVE_LEVEL_TYPE(type)                   (((type) == SPP_MISC_ACTIVE_HIGH) || \
                                                          ((type) == SPP_MISC_ACTIVE_LOW))
void Display_IRQHandler(void);
void SPP_MISC_Int_Callback_Install(SPP_MISC_INT_Type intType, intCallback_Type *cbFun);
void SPP_MISC_Int_Mask(SPP_MISC_INT_Type intType, BL_Mask_Type intMask);
void SPP_MISC_Int_Clear_1(SPP_MISC_INT_Type intType);
void SPP_MISC_SEOF_Set_Source(SPP_MISC_INT_Type intType, SPP_MISC_SEOF_Source_Type source);
void SPP_MISC_SEOF_Set_Edge(SPP_MISC_INT_Type intType, SPP_MISC_SEOF_Edge_Type edge);
void SPP_Misc_Config(SPP_DVP_BIT_DEPTH_E dvp_bits);
void SPP_DVP2AXI_Set_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type sel);
void SPP_DVP2AXI_Get_Src(DVP2AXI_Port_Type dvp2axi, DVP2AXI_Src_Type *sel);
void SPP_DVP2AXI_Set_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E id);
void SPP_DVP2AXI_Get_Id_Sel(DVP2AXI_Port_Type dvp2axi, DVP2AXI_ID_E *id);

void SPP_MISC_TSRC_Source_Select(SPP_MISC_TSRC_Source_Type sourceType);

void SPP_Intr_Ctrl_Init(void);
void SPP_Intr_Ctrl_Set_Src(SPP_SEOF_E seof,SPP_Seof_Intr_Src_Type selection);
void SPP_Intr_Ctrl_Get_Src(SPP_SEOF_E seof, SPP_Seof_Intr_Src_Type *selection);
void SPP_Scaler_Set_State(SPP_Scaler_Type type, BL_Fun_Type state);
void SPP_Scaler_Set_Cfg(SPP_Scaler_Type scaler, SPP_SCALER_CONFIG_S *scaler_conf);
void SPP_Frame_M_to_N(SPP_FRAME_M_TO_N_S *cfg);
void SPP_Frame_Get_M_to_N(SPP_FRAME_M_TO_N_S *cfg);
void SPP_Enable_BL_SPP_Back(void);

void SPP_YUV_Adjust_Init();
void SPP_YUV_Adjust_Set_Cfg(SPP_YUV_Adjust_Type id, SPP_YUV_Adjust_Cfg_Type *cfg);
void SPP_YUV_Adjust_Get_Cfg(SPP_YUV_Adjust_Type id, SPP_YUV_Adjust_Cfg_Type *cfg);
void SPP_YUV_Adjust_Set_State(SPP_YUV_Adjust_Type type, BL_Fun_Type state);
void SPP_YUV_Adjust_Get_State(SPP_YUV_Adjust_Type type, BL_Fun_Type *state);
void SPP_YUV_Adjust_Set_Input(SPP_YUV_Adjust_Type type, SPP_YUV_Adjust_Input input);
void SPP_YUV_Adjust_Get_Input(SPP_YUV_Adjust_Type type, SPP_YUV_Adjust_Input *input);

void SPP_MISC_OSD_Input_Select(SPP_MISC_OSD_ID_Type osdId,SPP_MISC_OSD_Input_Type inputType);
void SPP_MISC_OSD_Get_Input_Select(SPP_MISC_OSD_ID_Type osdId,SPP_MISC_OSD_Input_Type *inputType);
void SPP_MISC_OSD_Pb_Input_Select(SPP_MISC_OSD_PB_Input_Type inputType);
void SPP_MISC_OSD_Pb_Get_Input_Select(SPP_MISC_OSD_PB_Input_Type *inputType);
void SPP_MISC_Bayer_Shift(uint16_t bitEnable,SPP_MISC_Bayer_Shift_Type shiftType,uint8_t bitShift);

void SPP_MISC_Scaler_Init(SPP_MISC_Scaler_ID_Type scalerId,SPP_MISC_Scaler_Cfg_Type* scalerCfg);
void SPP_MISC_Scaler_Get_Cfg(SPP_MISC_Scaler_ID_Type scalerId,SPP_MISC_Scaler_Cfg_Type* scalerCfg);
void SPP_MISC_Scaler_Input_Select(SPP_MISC_Scaler_ID_Type scalerId,SPP_MISC_Scaler_Input_Type inputType);
void SPP_MISC_Scaler_Get_Input_Select(SPP_MISC_Scaler_ID_Type scalerId,SPP_MISC_Scaler_Input_Type *inputType);
void SPP_MISC_Scaler_Enable(SPP_MISC_Scaler_ID_Type scalerId);
void SPP_MISC_Scaler_Disable(SPP_MISC_Scaler_ID_Type scalerId);
void SPP_MISC_Scaler_Get_State(SPP_MISC_Scaler_ID_Type scalerId, BL_Fun_Type *state);
void SPP_MISC_Scaler_Sh_Enable(SPP_MISC_Scaler_ID_Type scalerId);
void SPP_MISC_Scaler_Sh_Disable(SPP_MISC_Scaler_ID_Type scalerId);

void SPP_MISC_YUV2RGB_Init(SPP_MISC_YUV2RGB_ID_Type yuv2rgbId,SPP_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg);
void SPP_MISC_YUV2RGB_Get_Cfg(SPP_MISC_YUV2RGB_ID_Type yuv2rgbId,SPP_MISC_YUV2RGB_Cfg_Type* yuv2rgbCfg);

void SPP_MISC_CAM_Input_Select(SPP_MISC_CAM_ID_Type camId,SPP_MISC_CAM_Input_Type inputType);

void SPP_MISC_Display_Init(SPP_MISC_Display_Cfg_Type* displayCfg);
void SPP_MISC_Display_Get_Cfg(SPP_MISC_Display_Cfg_Type* displayCfg);
void SPP_MISC_Display_Set_Clk_Output_Inv(int value);
void SPP_MISC_Display_Get_Clk_Output_Inv(int *value);
void SPP_MISC_Display_RGB2YUV_Set_Cfg(SPP_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg);
void SPP_MISC_Display_RGB2YUV_Get_Cfg(SPP_MISC_RGB2YUV_Cfg_Type* rgb2yuvCfg);

void SPP_Scaler_Set_Input(SPP_Scaler_Type type, SPP_Scaler_Input input);
void SPP_Scaler_Get_Input(SPP_Scaler_Type type, SPP_Scaler_Input *input);
void SPP_OSD_Set_Input(SPP_OSD_Type type, SPP_OSD_Input input);
void SPP_OSD_Get_Input(SPP_OSD_Type type, SPP_OSD_Input *input);
void SPP_YUV2RGB_Set_Input(SPP_YUV2RGB_Type type, SPP_YUV2RGB_Input input);
void SPP_YUV2RGB_Get_Input(SPP_YUV2RGB_Type type, SPP_YUV2RGB_Input *input);
void SPP_YUV2RGB_Init(SPP_YUV2RGB_Param type);

void SPP_MISC_Crop_Init(SPP_MISC_Crop_ID_Type cropId,SPP_MISC_Crop_Cfg_Type* cropCfg);
void SPP_MISC_Crop_Get_Cfg(SPP_MISC_Crop_ID_Type cropId, SPP_MISC_Crop_Cfg_Type* cropCfg);
void SPP_MISC_Crop_Enable(SPP_MISC_Crop_ID_Type cropId);
void SPP_MISC_Crop_Disable(SPP_MISC_Crop_ID_Type cropId);
void SPP_MISC_Crop_Get_State(SPP_MISC_Crop_ID_Type cropId, BL_Fun_Type *state);
void SPP_MSIC_DVP_2x_Init(DVP_2x_Cfg_Type* dvp2xCfg);
void SPP_MSIC_DVP_2x_Get_Cfg(DVP_2x_Cfg_Type* dvp2xCfg);
void SPP_MSIC_DVP_2x_Enable(void);
void SPP_MSIC_DVP_2x_Disable(void);
void SPP_MSIC_DVP_2x_Get_State(BL_Fun_Type *state);
void SPP_MSIC_Pclk_Force_Set_State(BL_Fun_Type state);
void SPP_MSIC_Pclk_Force_Get_State(BL_Fun_Type *state);
void SPP_MSIC_Cr_De_As_Hsync_Set_State(BL_Fun_Type state);
void SPP_MSIC_Cr_De_As_Hsync_Get_State(BL_Fun_Type *state);
void SPP_MSIC_Dtsrc_Set_Mode(SPP_DTSRC_SRC_E mode);
void SPP_MSIC_Dtsrc_Get_Mode(SPP_DTSRC_SRC_E *mode);

/* DVP reshape */
void SPP_MISC_Reshape_Set_State(BL_Fun_Type state);
void SPP_MISC_Reshape_Get_State(BL_Fun_Type *state);
void SPP_MISC_Reshape_Counter_Clear();
void SPP_MISC_Reshape_Set_Counter(int value);
void SPP_MISC_Reshape_Get_Counter(int *value);
void SPP_MISC_Reshape_Set_HSync_Inv(BL_Fun_Type state);
void SPP_MISC_Reshape_Get_HSync_Inv(BL_Fun_Type *state);
void SPP_MISC_Reshape_Set_VSync_Inv(BL_Fun_Type state);
void SPP_MISC_Reshape_Get_VSync_Inv(BL_Fun_Type *state);

#endif //__BL808_SPP_MISC_H__
