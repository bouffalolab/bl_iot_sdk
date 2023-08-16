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

#ifndef _BL_GPU_DMA2D_H_
#define _BL_GPU_DMA2D_H_

#include "lvgl.h"

#ifndef LV_GPU_BL808_DMA2D_COPY_SIZE_LIMIT
/** Minimum area (in pixels) for image copy with 100% opacity to be handled by PXP */
#define LV_GPU_BL808_DMA2D_COPY_SIZE_LIMIT 64
#endif

#ifndef LV_GPU_BL808_DMA2D_COPY_OPA_SIZE_LIMIT
/** Minimum area (in pixels) for image copy with transparency to be handled by PXP */
#define LV_GPU_BL808_DMA2D_COPY_OPA_SIZE_LIMIT 32
#endif

#ifndef LV_GPU_BL808_DMA2D_FILL_SIZE_LIMIT
/** Minimum area (in pixels) to be filled by PXP with 100% opacity */
#define LV_GPU_BL808_DMA2D_FILL_SIZE_LIMIT 64
#endif

#ifndef LV_GPU_BL808_DMA2D_FILL_OPA_SIZE_LIMIT
/** Minimum area (in pixels) to be filled by PXP with transparency */
#define LV_GPU_BL808_DMA2D_FILL_OPA_SIZE_LIMIT 32
#endif

/**
 * Reset and initialize DMA2D device. This function should be called as a part
 * of display init sequence.
 *
 * @return LV_RES_OK: PXP init ok; LV_RES_INV: init error. See error log for more information.
 */
lv_res_t bl_gpu_dma2d_init(void);

/**
 * Disable DMA2D device. Should be called during display deinit sequence.
 */
void bl_gpu_dma2d_deinit(void);

/**
 * Fill area, with optional opacity.
 *
 * @param[in/out] dest_buf destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] fill_area area to fill
 * @param[in] color color
 */
lv_res_t bl_gpu_dma2d_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color);

/**
 * @brief BLock Image Transfer - copy rectangular image from src buffer to dst buffer with effects.
 *
 * By default, image is copied directly, with optional opacity configured by \p opa.
 * Color keying can be enabled by calling lv_gpu_nxp_pxp_enable_color_key() before calling this function.
 * Recoloring can be enabled by calling lv_gpu_nxp_pxp_enable_recolor() before calling this function.
 * Note that color keying and recoloring at the same time is not supported and black rectangle is rendered.
 *
 * @param[in/out] dest destination buffer
 * @param[in] dest_width width (stride) of destination buffer in pixels
 * @param[in] src source buffer
 * @param[in] src_with width (stride) of source buffer in pixels
 * @param[in] copy_w width of area to be copied from src to dest
 * @param[in] copy_h height of area to be copied from src to dest
 */
lv_res_t bl_gpu_dma2d_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width,
                         lv_coord_t copy_width, lv_coord_t copy_height);

/**
 * @brief Enable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 * Color key is defined by LV_COLOR_TRANSP symbol in lv_conf.h
 */
void bl_gpu_dma2d_enable_color_key(void);

/**
 * @brief Disable color keying for subsequent calls to lv_gpu_nxp_pxp_blit()
 *
 */
void bl_gpu_dma2d_disable_color_key(void);

#endif