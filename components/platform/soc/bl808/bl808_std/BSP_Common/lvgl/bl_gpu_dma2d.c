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


#include "../../../components/lvgl/lv_conf_internal.h"

#if LV_USE_GPU_LB_DMA2D

#include "bl_gpu_dma2d.h"

#if defined(BL808) || defined(BL606P)

#if defined (BL808)
#include "bl808_dma2d.h"
#elif defined (BL606P)
#include "bl606p_dma2d.h"
#endif

#define DMA2D_ID  DMA2D0_ID
#define DMA2D_CH  0

#define DMA2D_Get_Channel(id_base, ch) ((id_base) + (ch)*0x100)
static uint32_t dma2dAddr[DMA2D_ID_MAX] = { DMA2D_BASE };

/* Get DMA2D register */
static uint32_t DMA2DChs;

static void wait_finish(void)
{
    while(DMA2D_Channel_Is_Busy(DMA2D_ID, DMA2D_CH)){
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
    }
}

/**
 * Reset and initialize DMA2D device. This function should be called as a part
 * of display init sequence.
 *
 * @return LV_RES_OK: PXP init ok; LV_RES_INV: init error. See error log for more information.
 */
lv_res_t bl_gpu_dma2d_init(void)
{
    DMA2D_Cfg_Type dma2d_init_cfg={0};
    DMA2D_Color_Key_Type key_type;
    uint32_t key_value;

    DMA2DChs = DMA2D_Get_Channel(dma2dAddr[DMA2D_ID], DMA2D_CH);

    DMA2D_DeInit(DMA2D_ID);
    DMA2D_Init(DMA2D_ID, DMA2D_CH, &dma2d_init_cfg);
    DMA2D_Enable(DMA2D_ID);
    union {
        struct DMA2D_Control_Reg dma2d_reg_c0_bus;
        uint32_t word;
    }dma2d_bus_reg = {
        .dma2d_reg_c0_bus={
            .TransferSize = 0,
#if (LV_COLOR_DEPTH == 8)
            .SRC_BURST = 3,
            .DST_BURST = 3,
            .SRC_SIZE = 0,
            .DST_SIZE = 0,
#elif (LV_COLOR_DEPTH == 16)
            .SRC_BURST = 2,
            .DST_BURST = 2,
            .SRC_SIZE = 1,
            .DST_SIZE = 1,
#elif (LV_COLOR_DEPTH == 32)
            .SRC_BURST = 1,
            .DST_BURST = 1,
            .SRC_SIZE = 2,
            .DST_SIZE = 2,
#endif
        }
    };

    BL_WR_REG(DMA2DChs, DMA2D_C0LLI, 0);
    BL_WR_REG(DMA2DChs, DMA2D_C0_BUS, dma2d_bus_reg.word);

#if (LV_COLOR_DEPTH == 8)
    key_type = DMA2D_COLOR_KEY_8BIT;
    key_value = lv_color_to8(LV_COLOR_TRANSP);
#elif (LV_COLOR_DEPTH == 16)
    key_type = DMA2D_COLOR_KEY_16BIT;
    key_value = lv_color_to16(LV_COLOR_TRANSP);
#elif (LV_COLOR_DEPTH == 32)
    key_type = DMA2D_COLOR_KEY_32BIT;
    key_value = lv_color_to32(LV_COLOR_TRANSP);
#endif
    DMA2D_Color_Key_Set(DMA2D_ID, DMA2D_CH, key_type, key_value);
    DMA2D_Color_Key_Disable(DMA2D_ID, DMA2D_CH);
    return LV_RES_OK;
}

/**
 * Fill area, with optional opacity.
 *
 * @param[in/out] dest_buf destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] fill_area area to fill
 * @param[in] color color
 */
lv_res_t bl_gpu_dma2d_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color)
{
    uint32_t color_source ATTR_EALIGN(64);

    uint16_t src_x_cnt = fill_area->x2 - fill_area->x1 + 1;
    uint16_t src_y_cnt = fill_area->y2 - fill_area->y1 + 1;
    uint32_t src_x_incr = 0;
    uint32_t src_y_incr = 0;

    uint16_t dst_x_cnt = src_x_cnt;
    uint32_t dst_x_incr = sizeof(lv_color_t);
    uint32_t dst_y_incr = sizeof(lv_color_t) * (dest_width - src_x_cnt + 1);

    color_source = color.full;
    dest_buf += (dest_width * fill_area->y1 + fill_area->x1);

    BL_WR_REG(DMA2DChs, DMA2D_C0SRCADDR, (uint32_t)(uintptr_t)(&color_source));
    BL_WR_REG(DMA2DChs, DMA2D_C0DSTADDR, (uint32_t)(uintptr_t)dest_buf);

    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_CNT, (src_y_cnt<<16) | src_x_cnt);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_XIC, src_x_incr);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_YIC, src_y_incr);

    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_CNT, dst_x_cnt);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_XIC, dst_x_incr);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_YIC, dst_y_incr);

    csi_dcache_clean_range((void *)(&color_source), 64);
    csi_dcache_clean_invalid_range((void*)dest_buf, dest_width * (fill_area->y2 - fill_area->y1 + 1) * sizeof(lv_color_t));

    DMA2D_Channel_Enable(DMA2D_ID, DMA2D_CH);
    wait_finish();
    return LV_RES_OK;
}

/**
 * @brief BLock Image Transfer - copy rectangular image from src buffer to dst buffer.
 *
 * Color keying can be enabled by calling bl_gpu_dma2d_enable_color_key() before calling this function.
 *
 * @param[in/out] dest destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] src source buffer
 * @param[in] src_with width (stride) of source buffer in pixels
 * @param[in] copy_w width of area to be copied from src to dest
 * @param[in] copy_h height of area to be copied from src to dest
 */
lv_res_t bl_gpu_dma2d_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width,
                         lv_coord_t copy_width, lv_coord_t copy_height)
{
    /* DMA2D does not support Flash as the source address  */
    uint32_t memmap = ((uint32_t)(uintptr_t)src & 0xFF000000) >> 24;
    if(memmap >= 0x58 && memmap < 0x60){
        return LV_RES_INV;
    }

    uint16_t src_x_cnt = copy_width;
    uint16_t src_y_cnt = copy_height;
    uint32_t src_x_incr = sizeof(lv_color_t);
    uint32_t src_y_incr = sizeof(lv_color_t) * (src_width - copy_width + 1);

    uint16_t dst_x_cnt = copy_width;
    uint32_t dst_x_incr = sizeof(lv_color_t);
    uint32_t dst_y_incr = sizeof(lv_color_t) * (dest_width - copy_width + 1);

    BL_WR_REG(DMA2DChs, DMA2D_C0SRCADDR, (uint32_t)(uintptr_t)(src));
    BL_WR_REG(DMA2DChs, DMA2D_C0DSTADDR, (uint32_t)(uintptr_t)(dest));

    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_CNT, (src_y_cnt<<16) | src_x_cnt);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_XIC, src_x_incr);
    BL_WR_REG(DMA2DChs, DMA2D_C0_SRC_YIC, src_y_incr);

    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_CNT, dst_x_cnt);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_XIC, dst_x_incr);
    BL_WR_REG(DMA2DChs, DMA2D_C0_DST_YIC, dst_y_incr);

    csi_dcache_clean_range((void *)src, src_width * copy_height * sizeof(lv_color_t));
    csi_dcache_clean_invalid_range((void *)dest, dest_width * copy_height * sizeof(lv_color_t));
    DMA2D_Channel_Enable(DMA2D_ID, DMA2D_CH);
    wait_finish();
    return LV_RES_OK;
}

/**
 * @brief Enable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 * Color key is defined by LV_COLOR_TRANSP symbol in lv_conf.h
 */
void bl_gpu_dma2d_enable_color_key(void)
{
    DMA2D_Color_Key_Enable(DMA2D_ID, DMA2D_CH);
}

/**
 * @brief Disable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 */
void bl_gpu_dma2d_disable_color_key(void)
{
    DMA2D_Color_Key_Disable(DMA2D_ID, DMA2D_CH);
}

#else
    #error Devices that do not support DMA2D!
#endif

#endif