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

#if LV_USE_RV_VECTOR_EXT

#if (defined(BL808) || defined(BL606P)) && defined(CPU_D0)

#include"bl_rv_vector.h"
#include <riscv_vector.h>

#if (LV_COLOR_DEPTH == 32)

lv_res_t bl_rv_vector_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color)
{
    register size_t vl;
    vuint32m4_t v4;
    register size_t line_len;
    register uint32_t *p_dest;
    dest_buf += dest_width * fill_area->y1 + fill_area->x1;

    /* fill  */
    vl = vsetvlmax_e32m4();
    v4 = vmv_v_x_u32m4(color.full, vl);

    for(uint32_t i = 0; i <= (fill_area->y2 - fill_area->y1); i++){

        line_len = fill_area->x2 - fill_area->x1 + 1;
        p_dest = (uint32_t *)(dest_buf + dest_width * i);

        do {
            vl = vsetvl_e32m4(line_len);

            /* stores dest */
            vse32_v_u32m4(p_dest, v4, vl);

            line_len -= vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_fill_with_opa(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color, lv_opa_t opa)
{
    register size_t vl;
    vuint8m4_t v4;
    vuint8m4_t v8;
    vuint8m4_t v12;
    vuint8m4_t v16;

    vuint32m4_t v32;

    uint8_t v_buff[128/8*4];

    register size_t line_len;
    register uint8_t *p_dest;

    /* fill  */
    vl = vsetvlmax_e32m4();
    v32 = vmv_v_x_u32m4(color.full, vl);
    vse32_v_u32m4((uint32_t *)v_buff, v32, vl);

    /* get foreground */
    vl = vsetvlmax_e8m4();
    v4 = vle8_v_u8m4((const uint8_t *)v_buff, vl);
    v8 = vmulhu_vx_u8m4(v4, 255 - opa, vl);

    dest_buf += dest_width * fill_area->y1 + fill_area->x1;

    for(uint32_t i = 0; i <= (fill_area->y2 - fill_area->y1); i++){

        line_len = (fill_area->x2 - fill_area->x1 + 1) * sizeof(lv_color_t);
        p_dest = (uint8_t *)(dest_buf + dest_width * i);

        do {
            vl = vsetvl_e8m4(line_len);

            /* load dst */
            v4 = vle8_v_u8m4((const uint8_t *)p_dest, vl);
            /* background */
            v12  = vmulhu_vx_u8m4(v4, 255 - opa, vl);
            /* foreground = background */
            v16 = vsaddu_vv_u8m4(v8, v12, vl);
            /* stores dest */
            vse8_v_u8m4(p_dest, v16, vl);

            line_len -= vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    register size_t vl;
    vuint32m4_t v4;

    register size_t line_len;
    register uint32_t *p_src, *p_dest;

    for (uint32_t i = 0; i < copy_height; i++)
    {
        line_len = copy_width;
        p_src = (uint32_t *)(src + src_width * i);
        p_dest = (uint32_t *)(dest + dest_width * i);

        do {
            vl = vsetvl_e32m4(line_len);

            /* load src */
            v4 = vle32_v_u32m4((const uint32_t *)p_src, vl);

            /* stores dest */
            vse32_v_u32m4(p_dest, v4, vl);

            line_len -= vl;
            p_dest += vl;
            p_src += vl;

        } while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_blit_with_opa(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height, lv_opa_t opa)
{
    register size_t vl;
    vuint8m4_t v0;
    vuint8m4_t v4;
    vuint8m4_t v8;
    vuint8m4_t v10;
    vuint8m4_t v28;

    register size_t line_len;
    register uint8_t *p_src, *p_dest;

    for(uint32_t i = 0; i < copy_height; i++){

        line_len = copy_width * sizeof(lv_color_t);
        p_src = (uint8_t *)(src + src_width * i);
        p_dest = (uint8_t *)(dest + dest_width * i);

        do{
            vl = vsetvl_e8m4(line_len);

            /* load src */
            v0 = vle8_v_u8m4((const uint8_t *)p_src, vl);
            /* load dst */
            v4 = vle8_v_u8m4((const uint8_t *)p_dest, vl);

            /* foreground */
            v8  = vmulhu_vx_u8m4(v0, 255 - opa, vl);
            /* background */
            v10 = vmulhu_vx_u8m4(v4, opa, vl);

            /* add */
            v28 = vsaddu_vv_u8m4(v8, v10, vl);

            /* stores dest */
            vse8_v_u8m4(p_dest, v28, vl);

            line_len -= vl;
            p_src += vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

/* source data format : ARGB8888, 4byte/pixel */
/* destin data format : NRGB8888, 4byte/pixel */
lv_res_t bl_rv_vector_blit_with_alpha(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    size_t vl;
    vuint8m4_t v0;
    vuint8m4_t v4;
    vuint8m4_t v8;
    vuint8m4_t v12;
    vuint8m4_t v16;
    vuint8m4_t v20;

    vuint8m4_t v24;
    vuint8m4_t v28;

    size_t line_len = copy_width * sizeof(lv_color_t);
    uint8_t *p_src, *p_dest;

    const uint8_t alpha_indexe[128/8*4] = {3,3,3,3, 7,7,7,7, 11,11,11,11, 15,15,15,15, 19,19,19,19, 23,23,23,23, 27,27,27,27, 31,31,31,31,
                                            35,35,35,35, 39,39,39,39, 43,43,43,43, 47,47,47,47, 51,51,51,51, 55,55,55,55, 59,59,59,59, 63,63,63,63};

    const uint8_t alpha_mask[128/8*4] = {0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF,
                                          0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF, 0,0,0,0xFF};

    vl = vsetvl_e8m4(line_len);
    /* load alpha indexe */
    v24 = vle8_v_u8m4(alpha_indexe, vl);
    /* load alpha mask */
    v28 = vle8_v_u8m4(alpha_mask, vl);

    for(uint32_t i = 0; i < copy_height; i++){

        line_len = copy_width * sizeof(lv_color_t);
        p_src = (uint8_t *)(src + src_width * i);
        p_dest = (uint8_t *)(dest + dest_width * i);

        do{
            vl = vsetvl_e8m4(line_len);

            /* load src */
            v0 = vle8_v_u8m4((const uint8_t *)p_src, vl);
            /* load dst */
            v4 = vle8_v_u8m4((const uint8_t *)p_dest, vl);

            /* get src alpha */
            v8 = vrgather_vv_u8m4(v0, v24, vl);
            /* get alpha */
            v12 = vrsub_vx_u8m4(v8, 255, vl);

            /* foreground */
            v16  = vmulhu_vv_u8m4(v0, v8, vl);
            /* background */
            v20  = vmulhu_vv_u8m4(v4, v12, vl);

            /* add */;
            v0 = vsaddu_vv_u8m4(v16, v20, vl);
            /* set alpah */
            v4 = vor_vv_u8m4(v0, v28, vl);

            /* stores dest */
            vse8_v_u8m4(p_dest, v0, vl);

            line_len -= vl;
            p_src += vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

#elif (LV_COLOR_DEPTH == 16)

lv_res_t bl_rv_vector_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color)
{
    size_t vl;
    vuint16m4_t v4;
    size_t line_len;
    uint16_t *p_dest;
    dest_buf += dest_width * fill_area->y1 + fill_area->x1;

    /* fill  */
    vl = vsetvlmax_e16m4();
    v4 = vmv_v_x_u16m4(color.full, vl);

    for(uint32_t i = 0; i <= (fill_area->y2 - fill_area->y1); i++){

        line_len = fill_area->x2 - fill_area->x1 + 1;
        p_dest = (uint16_t *)(dest_buf + dest_width * i);

        do {
            vl = vsetvl_e16m4(line_len);

            /* stores dest */
            vse16_v_u16m4(p_dest, v4, vl);

            line_len -= vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_fill_with_opa(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color, lv_opa_t opa)
{
    register size_t vl;
    vuint16m4_t v4;
    vuint16m4_t v8;
    vuint16m4_t v12;
    vuint16m4_t v16;
    vuint16m4_t v20;
    vuint16m4_t v24;

    register size_t line_len;
    register uint16_t *p_dest;
    uint16_t background_r = ((color.full >> 8) & 0xF8) * opa;
    uint16_t background_g = ((color.full >> 3) & 0xFC) * opa;
    uint16_t background_b = ((color.full << 3) & 0xF8) * opa;

    dest_buf += dest_width * fill_area->y1 + fill_area->x1;

    for(uint32_t i = 0; i <= (fill_area->y2 - fill_area->y1); i++){

        line_len = fill_area->x2 - fill_area->x1 + 1;
        p_dest = (uint16_t *)(dest_buf + dest_width * i);

        do {
            vl = vsetvl_e16m4(line_len);

            /* load dst */
            v4 = vle16_v_u16m4((const uint16_t *)p_dest, vl);

            /* Blue */
            v8 = vsll_vx_u16m4(v4, 11, vl);
            v12 = vsrl_vx_u16m4(v8, 8, vl);
            /* foreground */
            v8  = vmul_vx_u16m4(v12, 255 - opa, vl);
            /* foreground + background */
            v12 = vsaddu_vx_u16m4(v8, background_b, vl);
            /* save */
            v16 = vsrl_vx_u16m4(v12, 11, vl);

            /* Green */
            v8 = vsrl_vx_u16m4(v4, 5, vl);
            v12 = vsll_vx_u16m4(v8, 10, vl);
            v8 = vsrl_vx_u16m4(v12, 8, vl);
            /* foreground */
            v12  = vmul_vx_u16m4(v8, 255 - opa, vl);
            /* foreground + background */
            v8 = vsaddu_vx_u16m4(v12, background_g, vl);
            /* save */
            v12 = vsrl_vx_u16m4(v8, 10, vl);
            v20 = vsll_vx_u16m4(v12, 5, vl);

            /* Red */
            v8 = vsrl_vx_u16m4(v4, 11, vl);
            v12 = vsll_vx_u16m4(v8, 3, vl);
            /* foreground */
            v8  = vmul_vx_u16m4(v12, 255 - opa, vl);
            /* foreground + background */
            v12 = vsaddu_vx_u16m4(v8, background_r, vl);
            /* save */
            v8 = vsrl_vx_u16m4(v12, 11, vl);
            v24 = vsll_vx_u16m4(v8, 11, vl);

            /* the new RGB565 */
            v8 = vor_vv_u16m4(v16, v20, vl);
            v12 = vor_vv_u16m4(v8, v24, vl);

            /* stores dest */
            vse16_v_u16m4(p_dest, v12, vl);

            line_len -= vl;
            p_dest += vl;
        }while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    register size_t vl;
    vuint16m4_t v4;

    register size_t line_len;
    register uint16_t *p_src, *p_dest;

    for (uint32_t i = 0; i < copy_height; i++)
    {
        line_len = copy_width;
        p_src = (uint16_t *)(src + src_width * i);
        p_dest = (uint16_t *)(dest + dest_width * i);

        do {
            vl = vsetvl_e16m4(line_len);

            /* load src */
            v4 = vle16_v_u16m4((const uint16_t *)p_src, vl);

            /* stores dest */
            vse16_v_u16m4(p_dest, v4, vl);

            line_len -= vl;
            p_dest += vl;
            p_src += vl;

        } while(line_len);
    }
    return LV_RES_OK;
}

lv_res_t bl_rv_vector_blit_with_opa(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height, lv_opa_t opa)
{
    size_t vl;
    vuint16m4_t v0;
    vuint16m4_t v4;
    vuint16m4_t v8;
    vuint16m4_t v12;
    vuint16m4_t v16;
    vuint16m4_t v20;
    vuint16m4_t v24;
    vuint16m4_t v28;

    size_t line_len;
    uint16_t *p_src, *p_dest;

    uint16_t opa_e = opa << 8;

    for (uint32_t i = 0; i < copy_height; i++){
        line_len = copy_width;
        p_src = (uint16_t *)(src + src_width * i);
        p_dest = (uint16_t *)(dest + dest_width * i);

        do {
            vl = vsetvl_e16m4(line_len);

            /* load src */
            v0 = vle16_v_u16m4((const uint16_t *)p_src, vl);
            /* load dst */
            v4 = vle16_v_u16m4((const uint16_t *)p_dest, vl);

            /* Red */
            /* foreground */
            v8 = vmulhu_vx_u16m4(v0, opa_e, vl);
            /* background */
            v12 = vmulhu_vx_u16m4(v4, 0xFF00 - opa_e, vl);
            /* add */
            v16 = vsaddu_vv_u16m4(v8, v12, vl);
            /* mask red */
            v20 = vand_vx_u16m4(v16, 0xF800, vl);

            /* Green */
            v0 = vsll_vx_u16m4(v0, 5, vl);
            v4 = vsll_vx_u16m4(v4, 5, vl);
            /* foreground */
            v8 = vmulhu_vx_u16m4(v0, opa_e, vl);
            /* background */
            v12 = vmulhu_vx_u16m4(v4, 0xFF00 - opa_e, vl);
            /* add */
            v16 = vsaddu_vv_u16m4(v8, v12, vl);
            /* mask Green */
            v8 = vand_vx_u16m4(v16, 0xFC00, vl);
            /* move */
            v24 = vsrl_vx_u16m4(v8, 5, vl);


            /* blue */
            v0 = vsll_vx_u16m4(v0, 6, vl);
            v4 = vsll_vx_u16m4(v4, 6, vl);
            /* foreground */
            v8 = vmulhu_vx_u16m4(v0, opa_e, vl);
            /* background */
            v12 = vmulhu_vx_u16m4(v4, 0xFF00 - opa_e, vl);
            /* add */
            v16 = vsaddu_vv_u16m4(v8, v12, vl);
            /* move */
            v28 = vsrl_vx_u16m4(v16, 11, vl);

            /* the new RGB565 */
            v8 = vor_vv_u16m4(v20, v24, vl);
            v12 = vor_vv_u16m4(v8, v28, vl);

            /* stores dest */
            vse16_v_u16m4(p_dest, v12, vl);

            line_len -= vl;
            p_dest += vl;
            p_src += vl;
        } while(line_len);
    }
    return LV_RES_OK;
}

/* source data format : ARGB8565, 3byte/pixel */
/* destin data format : RGB565,   2byte/pixel */
lv_res_t bl_rv_vector_blit_with_alpha(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    size_t vl;
    vuint16m4_t v0;
    vuint16m4_t v4;
    vuint16m4_t v8;
    vuint16m4_t v12;
    vuint16m4_t v16;
    vuint16m4_t v20;
    vuint16m4_t v24;
    vuint16m4_t v28;

    size_t line_len;
    uint8_t *p_src;
    uint16_t *p_dest,*p_src_rgb, *p_src_a;

    uint16_t *line_alpha_buff = _lv_mem_buf_get(copy_width * sizeof(lv_color_t));
    uint16_t *line_rgb_buff = _lv_mem_buf_get(copy_width * sizeof(lv_color_t));

    for (uint32_t i = 0; i < copy_height; i++){

        line_len = copy_width;
        p_dest = (uint16_t *)(dest + dest_width * i);
        p_src = (uint8_t *)src + (src_width * i * LV_IMG_PX_SIZE_ALPHA_BYTE);

        /* Separate a from rgb */
        for(uint32_t j=0; j < line_len; j++){
            line_rgb_buff[j] = *(uint16_t *)p_src;
            line_alpha_buff[j] = *(uint16_t *)(p_src+1);
            p_src += LV_IMG_PX_SIZE_ALPHA_BYTE;
        }

        p_src_rgb = line_rgb_buff;
        p_src_a = line_alpha_buff;

        do {
            vl = vsetvl_e16m4(line_len);

            /* load src argb */
            v0 = vle16_v_u16m4((const uint16_t *)p_src_rgb, vl);
            /* load  alpha indexe */
            v4 = vle16_v_u16m4((const uint16_t *)p_src_a, vl);

            /* load dst rgb*/
            v8 = vle16_v_u16m4((const uint16_t *)p_dest, vl);
            /* get dst alpha */
            v12 = vrsub_vx_u16m4(v4, 0xFFFF, vl);

            /* Red */
            /* foreground */
            v16 = vmulhu_vv_u16m4(v0, v4, vl);
            /* background */
            v20 = vmulhu_vv_u16m4(v8, v12, vl);
            /* add */
            v16 = vsaddu_vv_u16m4(v16, v20, vl);
            /* mask red */
            v16 = vand_vx_u16m4(v16, 0xF800, vl);

            /* Green */
            v0 = vsll_vx_u16m4(v0, 5, vl);
            v8 = vsll_vx_u16m4(v8, 5, vl);
            /* foreground */
            v20 = vmulhu_vv_u16m4(v0, v4, vl);
            /* background */
            v24 = vmulhu_vv_u16m4(v8, v12, vl);
            /* add */
            v20 = vsaddu_vv_u16m4(v20, v24, vl);
            /* mask Green */
            v20 = vand_vx_u16m4(v16, 0xFC00, vl);
            /* move */
            v20 = vsrl_vx_u16m4(v16, 5, vl);


            /* blue */
            v0 = vsll_vx_u16m4(v0, 6, vl);
            v8 = vsll_vx_u16m4(v8, 6, vl);
            /* foreground */
            v24 = vmulhu_vv_u16m4(v0, v4, vl);
            /* background */
            v28 = vmulhu_vv_u16m4(v8, v12, vl);
            /* add */
            v24 = vsaddu_vv_u16m4(v24, v28, vl);
            /* move */
            v24 = vsrl_vx_u16m4(v16, 11, vl);

            /* the new RGB565 */
            v28 = vor_vv_u16m4(v16, v20, vl);
            v28 = vor_vv_u16m4(v24, v28, vl);

            /* stores dest */
            vse16_v_u16m4(p_dest, v28, vl);

            line_len -= vl;
            p_src_rgb += vl;
            p_src_a += vl;
            p_dest += vl;
        } while(line_len);
    }
    _lv_mem_buf_release(line_rgb_buff);
    _lv_mem_buf_release(line_alpha_buff);
    return LV_RES_OK;

}

#else

lv_res_t bl_rv_vector_fill(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color)
{
    return LV_RES_INV;
}

lv_res_t bl_rv_vector_fill_with_opa(lv_color_t *dest_buf, lv_coord_t dest_width, const lv_area_t *fill_area, lv_color_t color, lv_opa_t opa)
{
    return LV_RES_INV;
}

lv_res_t bl_rv_vector_copy(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    return LV_RES_INV;
}

lv_res_t bl_rv_vector_blit_with_opa(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height, lv_opa_t opa)
{
    return LV_RES_INV;
}

lv_res_t bl_rv_vector_blit_with_alpha(lv_color_t *dest, lv_coord_t dest_width, const lv_color_t *src, lv_coord_t src_width, lv_coord_t copy_width, lv_coord_t copy_height)
{
    return LV_RES_INV;
}

#endif

#else
    #error CPU core that do not support Vector Extensions !
#endif

#endif
