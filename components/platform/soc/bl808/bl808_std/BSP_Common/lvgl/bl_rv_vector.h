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

#ifndef _BL_RV_VECTOR_H_
#define _BL_RV_VECTOR_H_

#include "lvgl.h"

/* copy */
#ifndef LV_CPU_RV_VECTOR_COPY_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_SIZE_LIMIT 64
#endif

/* copy with opa */
#ifndef LV_CPU_RV_VECTOR_COPY_OPA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_OPA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_OPA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_OPA_SIZE_LIMIT 64
#endif

/* copy with alpha */
#ifndef LV_CPU_RV_VECTOR_COPY_ALPHA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_COPY_ALPHA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_COPY_ALPHA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_COPY_ALPHA_SIZE_LIMIT 64
#endif

/* fill */
#ifndef LV_CPU_RV_VECTOR_FILL_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_FILL_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_FILL_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_FILL_SIZE_LIMIT 128
#endif

/* fill with opa */
#ifndef LV_CPU_RV_VECTOR_FILL_OPA_WIDTH_LIMIT
#define LV_CPU_RV_VECTOR_FILL_OPA_WIDTH_LIMIT 16
#endif

#ifndef LV_CPU_RV_VECTOR_FILL_OPA_SIZE_LIMIT
#define LV_CPU_RV_VECTOR_FILL_OPA_SIZE_LIMIT 128
#endif


lv_res_t bl_rv_vector_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color);
lv_res_t bl_rv_vector_fill_with_opa(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color, lv_opa_t opa);

lv_res_t bl_rv_vector_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height);
lv_res_t bl_rv_vector_blit_with_opa(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height, lv_opa_t opa);

lv_res_t bl_rv_vector_blit_with_alpha(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height);

#endif