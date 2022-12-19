
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "blai_def.h"
#include "blai_inst_cpu_ops.h"
#include "blai_inst_util.h"
#include "blai_riscv_nnfunctions.h"
#include <string.h>


//#include "riscv_nnfunctions.h"
#ifndef   __ASM
  #define __ASM                     __asm
#endif

#define LEFT_SHIFT(_shift) (_shift > 0 ? _shift : 0)
#define RIGHT_SHIFT(_shift) (_shift > 0 ? 0 : -_shift)
#define MASK_IF_ZERO(x) (x) == 0 ? ~0 : 0
#define MASK_IF_NON_ZERO(x) (x) != 0 ? ~0 : 0
#define SELECT_USING_MASK(mask, a, b) ((mask) & (a)) ^ (~(mask) & (b))

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define CLAMP(x, h, l) MAX(MIN((x), (h)), (l))

#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline

/**
 * @brief           Doubling high multiply without saturation. This is intended
 *                  for requantization where the scale is a positive integer
 *
 * @param[in]       m1        Multiplicand. Range: {Q31_MIN, Q31_MAX}
 * @param[in]       m2        Multiplier Range: {Q31_MIN, Q31_MAX}
 * @return          Result of multiplication.
 * @note            The result of this matches that of neon instruction
 *                  VQRDMULH for m1 in range {Q31_MIN, Q31_MAX} and m2 in
 *                  range {Q31_MIN + 1, Q31_MAX}. Saturation occurs when
 *                  m1 equals m2 equals Q31_MIN and that is not handled by
 *                  this function.
 *
 */
inline q31_t riscv_nn_doubling_high_mult_no_sat(const q31_t m1, const q31_t m2)
{
    q31_t result = 0;
    union riscv_nn_long_long mult;

    // Rounding offset to add for a right shift of 31
    mult.word.low = 1 << 30;
    mult.word.high = 0;

    // Gets resolved as a SMLAL instruction
    mult.long_long = mult.long_long + (q63_t)m1 * m2;

    // Utilize all of the upper 32 bits. This is the doubling step
    // as well.
    result = (int32_t)(mult.long_long >> 31);

    return result;
}


/**
 * @brief           Rounding divide by power of two.
 * @param[in]       dividend - Dividend
 * @param[in]       exponent - Divisor = power(2, exponent)
 *                             Range: [0, 31]
 * @return          Rounded result of division. Midpoint is rounded away from zero.
 *
 */
__STATIC_FORCEINLINE q31_t riscv_nn_divide_by_power_of_two(const q31_t dividend, const q31_t exponent)
{
    q31_t result = 0;
    const q31_t remainder_mask = (1 << exponent) - 1;
    int32_t remainder = remainder_mask & dividend;

    // Basic division
    result = dividend >> exponent;

    // Adjust 'result' for rounding (mid point away from zero)
    q31_t threshold = remainder_mask >> 1;
    if (result < 0)
    {
        threshold++;
    }
    if (remainder > threshold)
    {
        result++;
    }

    return result;
}

/**
 * @brief           Requantize a given value.
 * @param[in]       val         Value to be requantized
 * @param[in]       multiplier  multiplier. Range {Q31_MIN + 1, Q32_MAX}
 * @param[in]       shift       left or right shift for 'val * multiplier'
 *
 * @return          Returns (val * multiplier)/(2 ^ shift)
 *
 */
__STATIC_FORCEINLINE q31_t riscv_nn_requantize(const q31_t val, const q31_t multiplier, const q31_t shift)
{
    return riscv_nn_divide_by_power_of_two(riscv_nn_doubling_high_mult_no_sat(val * (1 << LEFT_SHIFT(shift)), multiplier),
                                         RIGHT_SHIFT(shift));
}



int32_t riscv_convolve_s8_get_buffer_size(const nmsis_nn_dims *input_dims, const nmsis_nn_dims *filter_dims)
{
#if defined(RISCV_MATH_DSP)
    return (2 * input_dims->c * filter_dims->w * filter_dims->h) * (int32_t)sizeof(int16_t);
#else
    (void)input_dims;
    (void)filter_dims;
    return 0;
#endif
}

riscv_status riscv_convolve_u8(const nmsis_nn_context* ctx,
    const nmsis_nn_conv_params* conv_params,
    const nmsis_nn_per_channel_quant_params* quant_params,
    const nmsis_nn_dims* input_dims,
    const uint8_t* input_data,
    const nmsis_nn_dims* filter_dims,
    const uint8_t* filter_data,
    const nmsis_nn_dims* bias_dims,
    const int32_t* bias_data,
    const nmsis_nn_dims* output_dims,
    uint8_t* output_data)
{
    (void)bias_dims;
    q15_t* buffer_a = (q15_t*)ctx->buf;

    const uint16_t input_batches = input_dims->n;
    const uint16_t input_x = input_dims->w;
    const uint16_t input_y = input_dims->h;
    const uint16_t input_ch = input_dims->c;
    const uint16_t kernel_x = filter_dims->w;
    const uint16_t kernel_y = filter_dims->h;
    const uint16_t output_x = output_dims->w;
    const uint16_t output_y = output_dims->h;
    const uint16_t output_ch = output_dims->c;

    const uint16_t pad_x = conv_params->padding.w;
    const uint16_t pad_y = conv_params->padding.h;
    const uint16_t stride_x = conv_params->stride.w;
    const uint16_t stride_y = conv_params->stride.h;

    const int32_t input_offset = conv_params->input_offset;
    const int32_t filter_offset = conv_params->filter_offset;
    const int32_t out_offset = conv_params->output_offset;
    const int32_t out_activation_min = conv_params->activation.min;
    const int32_t out_activation_max = conv_params->activation.max;
    int32_t* output_mult = quant_params->multiplier;
    int32_t* output_shift = quant_params->shift;

    int i_batch;
    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
        /* Run the following code as reference implementation for RISC-V Core without DSP */
        (void)buffer_a;
        int32_t i_out_ch, i_out_y, i_out_x, i_input_ch, i_ker_y, i_ker_x;
        int32_t conv_out;

        for (i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
        {
            for (i_out_y = 0; i_out_y < output_y; i_out_y++)
            {
                for (i_out_x = 0; i_out_x < output_x; i_out_x++)
                {
                    conv_out = 0;

                    const int32_t base_idx_y = stride_y * i_out_y - pad_y;
                    const int32_t base_idx_x = stride_x * i_out_x - pad_x;

                    const int32_t ker_y_start = MAX(0, -base_idx_y);
                    const int32_t ker_x_start = MAX(0, -base_idx_x);

                    const int32_t ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                    const int32_t ker_x_end = MIN(kernel_x, input_x - base_idx_x);

                    for (i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                    {
                        for (i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                        {
                            const int32_t in_row = base_idx_y + i_ker_y;
                            const int32_t in_col = base_idx_x + i_ker_x;
                            for (i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                            {
                                conv_out +=
                                    (input_data[(in_row * input_x + in_col) * input_ch + i_input_ch] + input_offset) *
                                    (filter_data[i_out_ch * input_ch * kernel_y * kernel_x +
                                    (i_ker_y * kernel_x + i_ker_x) * input_ch + i_input_ch] + filter_offset);
                            }
                        }
                    }

                    if (bias_data)
                    {
                        conv_out += bias_data[i_out_ch];
                    }

                    conv_out = riscv_nn_requantize(conv_out, output_mult[i_out_ch], output_shift[i_out_ch]);
               
                    conv_out += out_offset;
                    conv_out = MAX(conv_out, out_activation_min);
                    conv_out = MIN(conv_out, out_activation_max);
          
                    output_data[i_out_ch + (i_out_y * output_x + i_out_x) * output_ch] = (int8_t)conv_out;
                }
            }
        }
        /* Advance to the next batch */
        input_data += (input_x * input_y * input_ch);
        output_data += (output_x * output_y * output_ch);
    }

    /* Return to application */
    return RISCV_MATH_SUCCESS;
}


riscv_status riscv_convolve_s8(const nmsis_nn_context *ctx,
                           const nmsis_nn_conv_params *conv_params,
                           const nmsis_nn_per_channel_quant_params *quant_params,
                           const nmsis_nn_dims *input_dims,
                           const q7_t *input_data,
                           const nmsis_nn_dims *filter_dims,
                           const q7_t *filter_data,
                           const nmsis_nn_dims *bias_dims,
                           const int32_t *bias_data,
                           const nmsis_nn_dims *output_dims,
                           q7_t *output_data)
{
    (void)bias_dims;
    q15_t *buffer_a = (q15_t *)ctx->buf;

    const uint16_t input_batches = input_dims->n;
    const uint16_t input_x = input_dims->w;
    const uint16_t input_y = input_dims->h;
    const uint16_t input_ch = input_dims->c;
    const uint16_t kernel_x = filter_dims->w;
    const uint16_t kernel_y = filter_dims->h;
    const uint16_t output_x = output_dims->w;
    const uint16_t output_y = output_dims->h;
    const uint16_t output_ch = output_dims->c;

    const uint16_t pad_x = conv_params->padding.w;
    const uint16_t pad_y = conv_params->padding.h;
    const uint16_t stride_x = conv_params->stride.w;
    const uint16_t stride_y = conv_params->stride.h;

    const int32_t input_offset = conv_params->input_offset;
    const int32_t out_offset = conv_params->output_offset;
    const int32_t out_activation_min = conv_params->activation.min;
    const int32_t out_activation_max = conv_params->activation.max;
    int32_t *output_mult = quant_params->multiplier;
    int32_t *output_shift = quant_params->shift;

    int i_batch;
    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
#if   defined(RISCV_MATH_DSP)
        int32_t i_out_y, i_out_x, i_ker_y, i_ker_x;

        /* Generate two columns from the input tensor a GEMM computation */
        q15_t *two_column_buf = buffer_a;
        q7_t *out = output_data;

        /* This part implements the im2col function */
        for (i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            for (i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                for (i_ker_y = i_out_y * stride_y - pad_y; i_ker_y < i_out_y * stride_y - pad_y + kernel_y; i_ker_y++)
                {
                    for (i_ker_x = i_out_x * stride_x - pad_x; i_ker_x < i_out_x * stride_x - pad_x + kernel_x;
                         i_ker_x++)
                    {
                        if (i_ker_y < 0 || i_ker_y >= input_y || i_ker_x < 0 || i_ker_x >= input_x)
                        {
                            /* Filling 0 for out-of-bound paddings */
                            memset(two_column_buf, 0, sizeof(q15_t) * input_ch);
                        }
                        else
                        {
                            /* Copying the pixel data to column */
                            riscv_q7_to_q15_with_offset(input_data + (i_ker_y * input_x + i_ker_x) * input_ch,
                                                      two_column_buf,
                                                      input_ch,
                                                      input_offset);
                        }
                        two_column_buf += input_ch;
                    }
                }

                /* Computation is filed for every 2 columns */
                if (two_column_buf == buffer_a + 2 * input_ch * kernel_y * kernel_x)
                {
                    out = riscv_nn_mat_mult_kernel_s8_s16(filter_data,
                                                        buffer_a,
                                                        output_ch,
                                                        output_shift,
                                                        output_mult,
                                                        out_offset,
                                                        out_activation_min,
                                                        out_activation_max,
                                                        input_ch * kernel_y * kernel_x,
                                                        bias_data,
                                                        out);

                    /* counter reset */
                    two_column_buf = buffer_a;
                }
            }
        }

        /* left-over because odd number of output pixels */
        if (two_column_buf != buffer_a)
        {
            const q7_t *ker_a = filter_data;
            int i;

            for (i = 0; i < output_ch; i++)
            {
                /* Load the accumulator with bias first */
                q31_t sum = 0;
                if (bias_data)
                {
                    sum = bias_data[i];
                }

                /* Point to the beginning of the im2col buffer where the input is available as a rearranged column */
                const q15_t *ip_as_col = buffer_a;

                /* 4 multiply and accumulates are done in one loop. */
                uint16_t col_count = (input_ch * kernel_y * kernel_x) >> 2;

                while (col_count)
                {
                    q31_t ker_a1, ker_a2;
                    q31_t ip_b1, ip_b2;

                    // ker_a = read_and_pad(ker_a, &ker_a1, &ker_a2);
                    q31_t inA = riscv_nn_read_q7x4_ia(&ker_a);
                    ker_a1 = __RV_SUNPKD810(inA);
                    ker_a2 = __RV_SUNPKD832(inA);

                    ip_b1 = riscv_nn_read_q15x2_ia(&ip_as_col);
                    sum = __RV_KMADA(sum, ker_a1, ip_b1);
                    ip_b2 = riscv_nn_read_q15x2_ia(&ip_as_col);
                    sum = __RV_KMADA(sum, ker_a2, ip_b2);

                    col_count--;
                }
                /* Handle left over mac */
                col_count = input_ch * kernel_y * kernel_x & 0x3;
                while (col_count)
                {
                    q7_t ker_a1 = *ker_a++;
                    q15_t ip_b1 = *ip_as_col++;
                    sum += ker_a1 * ip_b1;
                    col_count--;
                }

                sum = riscv_nn_requantize(sum, output_mult[i], output_shift[i]);
                sum += out_offset;
                sum = MAX(sum, out_activation_min);
                sum = MIN(sum, out_activation_max);
                *out++ = (q7_t)sum;
            }
        }
#else
        /* Run the following code as reference implementation for RISC-V Core without DSP */
        (void)buffer_a;
        int32_t i_out_ch, i_out_y, i_out_x, i_input_ch, i_ker_y, i_ker_x;
        int32_t conv_out;

        for (i_out_ch = 0; i_out_ch < output_ch; i_out_ch++)
        {
            for (i_out_y = 0; i_out_y < output_y; i_out_y++)
            {
                for (i_out_x = 0; i_out_x < output_x; i_out_x++)
                {
                    conv_out = 0;

                    const int32_t base_idx_y = stride_y * i_out_y - pad_y;
                    const int32_t base_idx_x = stride_x * i_out_x - pad_x;

                    const int32_t ker_y_start = MAX(0, -base_idx_y);
                    const int32_t ker_x_start = MAX(0, -base_idx_x);

                    const int32_t ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                    const int32_t ker_x_end = MIN(kernel_x, input_x - base_idx_x);

                    for (i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                    {
                        for (i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                        {
                            const int32_t in_row = base_idx_y + i_ker_y;
                            const int32_t in_col = base_idx_x + i_ker_x;
                            for (i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                            {
                                conv_out +=
                                    (input_data[(in_row * input_x + in_col) * input_ch + i_input_ch] + input_offset) *
                                    filter_data[i_out_ch * input_ch * kernel_y * kernel_x +
                                                (i_ker_y * kernel_x + i_ker_x) * input_ch + i_input_ch];
                            }
                        }
                    }
                    if (bias_data)
                    {
                        conv_out += bias_data[i_out_ch];
                    }
                    conv_out = riscv_nn_requantize(conv_out, output_mult[i_out_ch], output_shift[i_out_ch]);
                    conv_out += out_offset;
                    conv_out = MAX(conv_out, out_activation_min);
                    conv_out = MIN(conv_out, out_activation_max);
                    output_data[i_out_ch + (i_out_y * output_x + i_out_x) * output_ch] = (int8_t)conv_out;
                }
            }
        }
#endif
        /* Advance to the next batch */
        input_data += (input_x * input_y * input_ch);
        output_data += (output_x * output_y * output_ch);
    }

    /* Return to application */
    return RISCV_MATH_SUCCESS;
}


static void depthwise_conv_s8_mult_4(const int8_t *input,
                                     const int32_t input_x,
                                     const int32_t input_y,
                                     const int32_t input_ch,
                                     const int8_t *kernel,
                                     const int32_t output_ch,
                                     const int32_t ch_mult,
                                     const int32_t kernel_x,
                                     const int32_t kernel_y,
                                     const int32_t pad_x,
                                     const int32_t pad_y,
                                     const int32_t stride_x,
                                     const int32_t stride_y,
                                     const int32_t *bias,
                                     int8_t *output,
                                     const int32_t *output_shift,
                                     const int32_t *output_mult,
                                     const int32_t output_x,
                                     const int32_t output_y,
                                     const int32_t output_offset,
                                     const int32_t input_offset,
                                     const int32_t output_activation_min,
                                     const int32_t output_activation_max)
{
#if defined(RISCV_VECTOR)
    size_t l;
    uint32_t blkCnt;
    vint8m1_t vkernel;
    vint32m4_t vout_buff;
#endif
    for (int32_t in_h = -pad_y, out_h = 0, out_idx = 0; out_h < output_y; in_h += stride_y, ++out_h)
    {
        for (int32_t in_w = -pad_x, out_w = 0, ker_h_start = MAX(0, -in_h); out_w < output_x; in_w += stride_x, ++out_w)
        {
            for (int32_t in_ch = 0, out_ch = 0, ker_w_start = MAX(0, -in_w); out_ch < output_ch;
                 ++in_ch, out_ch += ch_mult)
            {
                for (int mult_tile = 0; mult_tile < ch_mult; mult_tile += 4)
                {
                    int32_t out_buff[4];
#if defined(RISCV_VECTOR)
                    l = vsetvl_e32m1(4);
                    vout_buff = vle32_v_i32m4(bias + out_ch + mult_tile, l);
#else
                    out_buff[0] = bias[out_ch + 0 + mult_tile];
                    out_buff[1] = bias[out_ch + 1 + mult_tile];
                    out_buff[2] = bias[out_ch + 2 + mult_tile];
                    out_buff[3] = bias[out_ch + 3 + mult_tile];
#endif

                    for (int32_t ker_h = ker_h_start; ker_h < MIN(kernel_y, input_y - in_h); ++ker_h)
                    {
                        int32_t ker_idx = ker_h * (output_ch * kernel_x) + ker_w_start * output_ch + out_ch;
                        int32_t in_idx = (in_h + ker_h) * (input_ch * input_x) + in_w * input_ch + in_ch;

                        for (int32_t ker_w = ker_w_start; ker_w < MIN(kernel_x, input_x - in_w);
                             ++ker_w, ker_idx += output_ch)
                        {
                            int32_t in_val = input[in_idx + ker_w * input_ch] + input_offset;
#if defined(RISCV_VECTOR)
                            l = vsetvl_e8m1(4);
                            vkernel = vle8_v_i8m1(kernel + ker_idx + mult_tile, l);
                            vout_buff = vadd_vv_i32m4(vout_buff, vmul_vx_i32m4(vsext_vf4_i32m4 (vkernel, l),in_val, l), l);
                            vse32_v_i32m4(out_buff,vout_buff, l);
#else
                            out_buff[0] += in_val * kernel[ker_idx + 0 + mult_tile];
                            out_buff[1] += in_val * kernel[ker_idx + 1 + mult_tile];
                            out_buff[2] += in_val * kernel[ker_idx + 2 + mult_tile];
                            out_buff[3] += in_val * kernel[ker_idx + 3 + mult_tile];
#endif
                        }
                    }
                    out_buff[0] = riscv_nn_requantize(out_buff[0], output_mult[out_ch + 0 + mult_tile], output_shift[out_ch + 0 + mult_tile]);
                    out_buff[1] = riscv_nn_requantize(out_buff[1], output_mult[out_ch + 1 + mult_tile], output_shift[out_ch + 1 + mult_tile]);
                    out_buff[2] = riscv_nn_requantize(out_buff[2], output_mult[out_ch + 2 + mult_tile], output_shift[out_ch + 2 + mult_tile]);
                    out_buff[3] = riscv_nn_requantize(out_buff[3], output_mult[out_ch + 3 + mult_tile], output_shift[out_ch + 3 + mult_tile]);
#if defined(RISCV_VECTOR)
                    l = vsetvl_e32m4(4);
                    vout_buff = vle32_v_i32m4(out_buff, l);
                    vout_buff = vadd_vx_i32m4(vout_buff, output_offset, l);
                    vout_buff = vmin_vx_i32m4(vmax_vx_i32m4(vout_buff,output_activation_min, l),output_activation_max, l);
                    vse8_v_i8m1(output+out_idx,vnclip_wx_i8m1(vnclip_wx_i16m2(vout_buff,0, l),0, l), l);
                    out_idx += 4;
                    // vse32_v_i32m4(out_buff,vout_buff);
#else
                    out_buff[0] += output_offset;
                    out_buff[1] += output_offset;
                    out_buff[2] += output_offset;
                    out_buff[3] += output_offset;

                    out_buff[0] = MIN(MAX(out_buff[0], output_activation_min), output_activation_max);
                    out_buff[1] = MIN(MAX(out_buff[1], output_activation_min), output_activation_max);
                    out_buff[2] = MIN(MAX(out_buff[2], output_activation_min), output_activation_max);
                    out_buff[3] = MIN(MAX(out_buff[3], output_activation_min), output_activation_max);

                    output[out_idx++] = (int8_t)out_buff[0];
                    output[out_idx++] = (int8_t)out_buff[1];
                    output[out_idx++] = (int8_t)out_buff[2];
                    output[out_idx++] = (int8_t)out_buff[3];
#endif
                }
            }
        }
    }
}

static void depthwise_conv_s8_generic(const q7_t *input,
                                      const uint16_t input_batches,
                                      const uint16_t input_x,
                                      const uint16_t input_y,
                                      const uint16_t input_ch,
                                      const q7_t *kernel,
                                      const uint16_t output_ch,
                                      const uint16_t ch_mult,
                                      const uint16_t kernel_x,
                                      const uint16_t kernel_y,
                                      const uint16_t pad_x,
                                      const uint16_t pad_y,
                                      const uint16_t stride_x,
                                      const uint16_t stride_y,
                                      const int32_t *bias,
                                      q7_t *output,
                                      const int32_t *output_shift,
                                      const int32_t *output_mult,
                                      const uint16_t output_x,
                                      const uint16_t output_y,
                                      const int32_t output_offset,
                                      const int32_t input_offset,
                                      const int32_t output_activation_min,
                                      const int32_t output_activation_max)
{
    (void)output_ch;
#if defined(RISCV_VECTOR)
    size_t l;
    uint32_t blkCnt_v;
    vint8m2_t vkernel;
    vint32m8_t vout_acc;
#endif
    int i_out = 0;
    int i_batch;

    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
        for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            const int16_t base_idx_y = (i_out_y * stride_y) - pad_y;
            for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;
                for (int i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                {
#if defined(RISCV_VECTOR)
                    blkCnt_v = ch_mult;
                    int idx_out_ch = i_input_ch * ch_mult;
                    /* Condition for kernel start dimension: (base_idx_<x,y> + ker_<x,y>_start) >= 0 */
                    const int ker_y_start = MAX(0, -base_idx_y);
                    const int ker_x_start = MAX(0, -base_idx_x);
                    /* Condition for kernel end dimension: (base_idx_<x,y> + ker_<x,y>_end) < input_<x,y> */
                    const int ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                    const int ker_x_end = MIN(kernel_x, input_x - base_idx_x);
                    for (; (l = vsetvl_e32m8(blkCnt_v)) > 0; blkCnt_v -= l) {
                        vout_acc = vle32_v_i32m8(bias + idx_out_ch, l);
    
                        for (int i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                        {
                            const int32_t idx_y = base_idx_y + i_ker_y;
                            for (int i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                            {
                                const int32_t idx_x = base_idx_x + i_ker_x;
                                int32_t idx_0 = (idx_y * input_x + idx_x) * input_ch + i_input_ch;
                                // bstridea = input_ch;
                                int32_t ker_idx_0 = (i_ker_y * kernel_x + i_ker_x) * (input_ch * ch_mult) + idx_out_ch;
                                // bstrideb = input_ch * ch_mult;
                                int8_t input_data = input[idx_0];
    
                                // vinput = vlse8_v_i8m2(input + idx_0,bstridea, l);
                                vkernel = vle8_v_i8m2(kernel + ker_idx_0, l);
    
                                vout_acc = vadd_vv_i32m8(vout_acc,vmul_vx_i32m8(vsext_vf4_i32m8(vkernel, l), ((int32_t)input_data + input_offset), l), l);
                            }
                        }
    
                        int32_t acc_0;
                        for(size_t i=l;i>0;i--){
                            acc_0 = vmv_x_s_i32m8_i32 (vout_acc);
    
                            /* Requantize and clamp output to provided range */
                            acc_0 = riscv_nn_requantize(acc_0, output_mult[idx_out_ch], output_shift[idx_out_ch]);
                            acc_0 += output_offset;
                            acc_0 = MAX(acc_0, output_activation_min);
                            acc_0 = MIN(acc_0, output_activation_max);
    
                            output[i_out++] = acc_0;
                            l = vsetvl_e32m8(l);
                            vout_acc = vslide1down_vx_i32m8(vout_acc,0, l);
                            idx_out_ch++;
                        }
                    }
                }
#else
                // for (int i_ch_mult = 0; i_ch_mult < ch_mult; i_ch_mult++)
                // const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;
                // for (int i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                // {
                    for (int i_ch_mult = 0; i_ch_mult < ch_mult; i_ch_mult++)
                    {
                        const int idx_out_ch = i_ch_mult + i_input_ch * ch_mult;
                        int32_t acc_0;
                        /* Condition for kernel start dimension: (base_idx_<x,y> + ker_<x,y>_start) >= 0 */
                        const int ker_y_start = MAX(0, -base_idx_y);
                        const int ker_x_start = MAX(0, -base_idx_x);
                        /* Condition for kernel end dimension: (base_idx_<x,y> + ker_<x,y>_end) < input_<x,y> */
                        const int ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                        const int ker_x_end = MIN(kernel_x, input_x - base_idx_x);
                        acc_0 = bias[idx_out_ch];

                        for (int i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                        {
                            const int32_t idx_y = base_idx_y + i_ker_y;
                            for (int i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                            {
                                const int32_t idx_x = base_idx_x + i_ker_x;
                                int32_t idx_0 = (idx_y * input_x + idx_x) * input_ch + i_input_ch;
                                int32_t ker_idx_0 = (i_ker_y * kernel_x + i_ker_x) * (input_ch * ch_mult) + idx_out_ch;

                                acc_0 += (input[idx_0] + input_offset) * kernel[ker_idx_0];
                            }
                        }

                        /* Requantize and clamp output to provided range */
                        acc_0 = riscv_nn_requantize(acc_0, output_mult[idx_out_ch], output_shift[idx_out_ch]);
                        acc_0 += output_offset;
                        acc_0 = MAX(acc_0, output_activation_min);
                        acc_0 = MIN(acc_0, output_activation_max);

                        output[i_out++] = acc_0;
                    }
                }
#endif
            }
        }
        /* Advance to the next batch */
        input += (input_x * input_y * input_ch);
    }
}

/*
 *  Basic s8 depthwise convolution function.
 *
 *  Refer header file for details.
 *  Optimization using DSP extension is not available for the generic case where channel multiplier is > 1.
 *
 */
riscv_status riscv_depthwise_conv_s8(const nmsis_nn_context *ctx,
                                 const nmsis_nn_dw_conv_params *dw_conv_params,
                                 const nmsis_nn_per_channel_quant_params *quant_params,
                                 const nmsis_nn_dims *input_dims,
                                 const q7_t *input,
                                 const nmsis_nn_dims *filter_dims,
                                 const q7_t *kernel,
                                 const nmsis_nn_dims *bias_dims,
                                 const int32_t *bias,
                                 const nmsis_nn_dims *output_dims,
                                 q7_t *output)
{
    (void)dw_conv_params->dilation;
    (void)bias_dims;
    (void)ctx;

    if (dw_conv_params->ch_mult % 4 == 0 && input_dims->n == 1)
    {
        depthwise_conv_s8_mult_4(input,
                                 input_dims->w,
                                 input_dims->h,
                                 input_dims->c,
                                 kernel,
                                 output_dims->c,
                                 dw_conv_params->ch_mult,
                                 filter_dims->w,
                                 filter_dims->h,
                                 dw_conv_params->padding.w,
                                 dw_conv_params->padding.h,
                                 dw_conv_params->stride.w,
                                 dw_conv_params->stride.h,
                                 bias,
                                 output,
                                 quant_params->shift,
                                 quant_params->multiplier,
                                 output_dims->w,
                                 output_dims->h,
                                 dw_conv_params->output_offset,
                                 dw_conv_params->input_offset,
                                 dw_conv_params->activation.min,
                                 dw_conv_params->activation.max);
    }
    else
    {
        depthwise_conv_s8_generic(input,
                                  input_dims->n,
                                  input_dims->w,
                                  input_dims->h,
                                  input_dims->c,
                                  kernel,
                                  output_dims->c,
                                  dw_conv_params->ch_mult,
                                  filter_dims->w,
                                  filter_dims->h,
                                  dw_conv_params->padding.w,
                                  dw_conv_params->padding.h,
                                  dw_conv_params->stride.w,
                                  dw_conv_params->stride.h,
                                  bias,
                                  output,
                                  quant_params->shift,
                                  quant_params->multiplier,
                                  output_dims->w,
                                  output_dims->h,
                                  dw_conv_params->output_offset,
                                  dw_conv_params->input_offset,
                                  dw_conv_params->activation.min,
                                  dw_conv_params->activation.max);
    }

    /* Return to application */
    return RISCV_MATH_SUCCESS;
}


static void depthwise_conv_u8_mult_4(const uint8_t* input,
    const int32_t input_x,
    const int32_t input_y,
    const int32_t input_ch,
    const uint8_t* kernel,
    const int32_t output_ch,
    const int32_t ch_mult,
    const int32_t kernel_x,
    const int32_t kernel_y,
    const int32_t pad_x,
    const int32_t pad_y,
    const int32_t stride_x,
    const int32_t stride_y,
    const int32_t* bias,
    uint8_t* output,
    const int32_t* output_shift,
    const int32_t* output_mult,
    const int32_t output_x,
    const int32_t output_y,
    const int32_t output_offset,
    const int32_t input_offset,
    const int32_t filter_offset,
    const int32_t output_activation_min,
    const int32_t output_activation_max)
{
#if defined(RISCV_VECTOR)
    size_t l;
    uint32_t blkCnt;
    vint8m1_t vkernel;
    vint32m4_t vout_buff;
#endif
    for (int32_t in_h = -pad_y, out_h = 0, out_idx = 0; out_h < output_y; in_h += stride_y, ++out_h)
    {
        for (int32_t in_w = -pad_x, out_w = 0, ker_h_start = MAX(0, -in_h); out_w < output_x; in_w += stride_x, ++out_w)
        {
            for (int32_t in_ch = 0, out_ch = 0, ker_w_start = MAX(0, -in_w); out_ch < output_ch;
                ++in_ch, out_ch += ch_mult)
            {
                for (int mult_tile = 0; mult_tile < ch_mult; mult_tile += 4)
                {
                    int32_t out_buff[4];
#if defined(RISCV_VECTOR)
                    l = vsetvl_e32m1(4);
                    vout_buff = vle32_v_i32m4(bias + out_ch + mult_tile, l);
#else
                    out_buff[0] = bias[out_ch + 0 + mult_tile];
                    out_buff[1] = bias[out_ch + 1 + mult_tile];
                    out_buff[2] = bias[out_ch + 2 + mult_tile];
                    out_buff[3] = bias[out_ch + 3 + mult_tile];
#endif

                    for (int32_t ker_h = ker_h_start; ker_h < MIN(kernel_y, input_y - in_h); ++ker_h)
                    {
                        int32_t ker_idx = ker_h * (output_ch * kernel_x) + ker_w_start * output_ch + out_ch;
                        int32_t in_idx = (in_h + ker_h) * (input_ch * input_x) + in_w * input_ch + in_ch;

                        for (int32_t ker_w = ker_w_start; ker_w < MIN(kernel_x, input_x - in_w);
                            ++ker_w, ker_idx += output_ch)
                        {
                            int32_t in_val = input[in_idx + ker_w * input_ch] + input_offset;
#if defined(RISCV_VECTOR)
                            l = vsetvl_e8m1(4);
                            vkernel = vle8_v_i8m1(kernel + ker_idx + mult_tile, l);
                            vout_buff = vadd_vv_i32m4(vout_buff, vmul_vx_i32m4(vsext_vf4_i32m4(vkernel, l), in_val, l), l);
                            vse32_v_i32m4(out_buff, vout_buff, l);
#else
                            out_buff[0] += in_val * (kernel[ker_idx + 0 + mult_tile] + filter_offset);
                            out_buff[1] += in_val * (kernel[ker_idx + 1 + mult_tile] + filter_offset);
                            out_buff[2] += in_val * (kernel[ker_idx + 2 + mult_tile] + filter_offset);
                            out_buff[3] += in_val * (kernel[ker_idx + 3 + mult_tile] + filter_offset);
#endif
                        }
                    }
                    out_buff[0] = riscv_nn_requantize(out_buff[0], output_mult[out_ch + 0 + mult_tile], output_shift[out_ch + 0 + mult_tile]);
                    out_buff[1] = riscv_nn_requantize(out_buff[1], output_mult[out_ch + 1 + mult_tile], output_shift[out_ch + 1 + mult_tile]);
                    out_buff[2] = riscv_nn_requantize(out_buff[2], output_mult[out_ch + 2 + mult_tile], output_shift[out_ch + 2 + mult_tile]);
                    out_buff[3] = riscv_nn_requantize(out_buff[3], output_mult[out_ch + 3 + mult_tile], output_shift[out_ch + 3 + mult_tile]);
#if defined(RISCV_VECTOR)
                    l = vsetvl_e32m4(4);
                    vout_buff = vle32_v_i32m4(out_buff, l);
                    vout_buff = vadd_vx_i32m4(vout_buff, output_offset, l);
                    vout_buff = vmin_vx_i32m4(vmax_vx_i32m4(vout_buff, output_activation_min, l), output_activation_max, l);
                    vse8_v_i8m1(output + out_idx, vnclip_wx_i8m1(vnclip_wx_i16m2(vout_buff, 0, l), 0, l), l);
                    out_idx += 4;
                    // vse32_v_i32m4(out_buff,vout_buff);
#else
                    out_buff[0] += output_offset;
                    out_buff[1] += output_offset;
                    out_buff[2] += output_offset;
                    out_buff[3] += output_offset;

                    out_buff[0] = MIN(MAX(out_buff[0], output_activation_min), output_activation_max);
                    out_buff[1] = MIN(MAX(out_buff[1], output_activation_min), output_activation_max);
                    out_buff[2] = MIN(MAX(out_buff[2], output_activation_min), output_activation_max);
                    out_buff[3] = MIN(MAX(out_buff[3], output_activation_min), output_activation_max);

                    output[out_idx++] = (int8_t)out_buff[0];
                    output[out_idx++] = (int8_t)out_buff[1];
                    output[out_idx++] = (int8_t)out_buff[2];
                    output[out_idx++] = (int8_t)out_buff[3];
#endif
                }
            }
        }
    }
}

static void depthwise_conv_u8_generic(const uint8_t* input,
    const uint16_t input_batches,
    const uint16_t input_x,
    const uint16_t input_y,
    const uint16_t input_ch,
    const uint8_t* kernel,
    const uint16_t output_ch,
    const uint16_t ch_mult,
    const uint16_t kernel_x,
    const uint16_t kernel_y,
    const uint16_t pad_x,
    const uint16_t pad_y,
    const uint16_t stride_x,
    const uint16_t stride_y,
    const int32_t* bias,
    uint8_t* output,
    const int32_t* output_shift,
    const int32_t* output_mult,
    const uint16_t output_x,
    const uint16_t output_y,
    const int32_t output_offset,
    const int32_t input_offset,
    const int32_t filter_offset,
    const int32_t output_activation_min,
    const int32_t output_activation_max)
{
    (void)output_ch;
#if defined(RISCV_VECTOR)
    size_t l;
    uint32_t blkCnt_v;
    vint8m2_t vkernel;
    vint32m8_t vout_acc;
#endif
    int i_out = 0;
    int i_batch;

    for (i_batch = 0; i_batch < input_batches; i_batch++)
    {
        for (int i_out_y = 0; i_out_y < output_y; i_out_y++)
        {
            const int16_t base_idx_y = (i_out_y * stride_y) - pad_y;
            for (int i_out_x = 0; i_out_x < output_x; i_out_x++)
            {
                const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;
                for (int i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                {
#if defined(RISCV_VECTOR)
                    blkCnt_v = ch_mult;
                    int idx_out_ch = i_input_ch * ch_mult;
                    /* Condition for kernel start dimension: (base_idx_<x,y> + ker_<x,y>_start) >= 0 */
                    const int ker_y_start = MAX(0, -base_idx_y);
                    const int ker_x_start = MAX(0, -base_idx_x);
                    /* Condition for kernel end dimension: (base_idx_<x,y> + ker_<x,y>_end) < input_<x,y> */
                    const int ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                    const int ker_x_end = MIN(kernel_x, input_x - base_idx_x);
                    for (; (l = vsetvl_e32m8(blkCnt_v)) > 0; blkCnt_v -= l) {
                        vout_acc = vle32_v_i32m8(bias + idx_out_ch, l);

                        for (int i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                        {
                            const int32_t idx_y = base_idx_y + i_ker_y;
                            for (int i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                            {
                                const int32_t idx_x = base_idx_x + i_ker_x;
                                int32_t idx_0 = (idx_y * input_x + idx_x) * input_ch + i_input_ch;
                                // bstridea = input_ch;
                                int32_t ker_idx_0 = (i_ker_y * kernel_x + i_ker_x) * (input_ch * ch_mult) + idx_out_ch;
                                // bstrideb = input_ch * ch_mult;
                                int8_t input_data = input[idx_0];

                                // vinput = vlse8_v_i8m2(input + idx_0,bstridea, l);
                                vkernel = vle8_v_i8m2(kernel + ker_idx_0, l);

                                vout_acc = vadd_vv_i32m8(vout_acc, vmul_vx_i32m8(vsext_vf4_i32m8(vkernel, l), ((int32_t)input_data + input_offset), l), l);
                            }
                        }

                        int32_t acc_0;
                        for (size_t i = l; i > 0; i--) {
                            acc_0 = vmv_x_s_i32m8_i32(vout_acc);

                            /* Requantize and clamp output to provided range */
                            acc_0 = riscv_nn_requantize(acc_0, output_mult[idx_out_ch], output_shift[idx_out_ch]);
                            acc_0 += output_offset;
                            acc_0 = MAX(acc_0, output_activation_min);
                            acc_0 = MIN(acc_0, output_activation_max);

                            output[i_out++] = acc_0;
                            l = vsetvl_e32m8(l);
                            vout_acc = vslide1down_vx_i32m8(vout_acc, 0, l);
                            idx_out_ch++;
                        }
                    }
                }
#else
                    // for (int i_ch_mult = 0; i_ch_mult < ch_mult; i_ch_mult++)
                    // const int16_t base_idx_x = (i_out_x * stride_x) - pad_x;
                    // for (int i_input_ch = 0; i_input_ch < input_ch; i_input_ch++)
                    // {
                    
                    for (int i_ch_mult = 0; i_ch_mult < ch_mult; i_ch_mult++)
                    {
                        const int idx_out_ch = i_ch_mult + i_input_ch * ch_mult;
                        int32_t acc_0;
                        /* Condition for kernel start dimension: (base_idx_<x,y> + ker_<x,y>_start) >= 0 */
                        const int ker_y_start = MAX(0, -base_idx_y);
                        const int ker_x_start = MAX(0, -base_idx_x);
                        /* Condition for kernel end dimension: (base_idx_<x,y> + ker_<x,y>_end) < input_<x,y> */
                        const int ker_y_end = MIN(kernel_y, input_y - base_idx_y);
                        const int ker_x_end = MIN(kernel_x, input_x - base_idx_x);
                        acc_0 = bias[idx_out_ch];

                        for (int i_ker_y = ker_y_start; i_ker_y < ker_y_end; i_ker_y++)
                        {
                            const int32_t idx_y = base_idx_y + i_ker_y;
                            for (int i_ker_x = ker_x_start; i_ker_x < ker_x_end; i_ker_x++)
                            {
                                const int32_t idx_x = base_idx_x + i_ker_x;
                                int32_t idx_0 = (idx_y * input_x + idx_x) * input_ch + i_input_ch;
                                int32_t ker_idx_0 = (i_ker_y * kernel_x + i_ker_x) * (input_ch * ch_mult) + idx_out_ch;

                                acc_0 += (input[idx_0] + input_offset) * (kernel[ker_idx_0] + filter_offset);
                            }
                        }

                        /* Requantize and clamp output to provided range */
                        acc_0 = riscv_nn_requantize(acc_0, output_mult[idx_out_ch], output_shift[idx_out_ch]);
                        acc_0 += output_offset;
                        acc_0 = MAX(acc_0, output_activation_min);
                        acc_0 = MIN(acc_0, output_activation_max);
                        output[i_out++] = acc_0;
                    }
            }
#endif
        }
    }
        /* Advance to the next batch */
        input += (input_x * input_y * input_ch);
}
}


/*
 *  Basic s8 depthwise convolution function.
 *
 *  Refer header file for details.
 *  Optimization using DSP extension is not available for the generic case where channel multiplier is > 1.
 *
 */
riscv_status riscv_depthwise_conv_u8(const nmsis_nn_context* ctx,
    const nmsis_nn_dw_conv_params* dw_conv_params,
    const nmsis_nn_per_channel_quant_params* quant_params,
    const nmsis_nn_dims* input_dims,
    const uint8_t* input,
    const nmsis_nn_dims* filter_dims,
    const uint8_t* kernel,
    const nmsis_nn_dims* bias_dims,
    const int32_t* bias,
    const nmsis_nn_dims* output_dims,
    uint8_t* output)
{
    (void)dw_conv_params->dilation;
    (void)bias_dims;
    (void)ctx;

    if (dw_conv_params->ch_mult % 4 == 0 && input_dims->n == 1)
    {
        depthwise_conv_u8_mult_4(input,
            input_dims->w,
            input_dims->h,
            input_dims->c,
            kernel,
            output_dims->c,
            dw_conv_params->ch_mult,
            filter_dims->w,
            filter_dims->h,
            dw_conv_params->padding.w,
            dw_conv_params->padding.h,
            dw_conv_params->stride.w,
            dw_conv_params->stride.h,
            bias,
            output,
            quant_params->shift,
            quant_params->multiplier,
            output_dims->w,
            output_dims->h,
            dw_conv_params->output_offset,
            dw_conv_params->input_offset,
            dw_conv_params->filter_offset,
            dw_conv_params->activation.min,
            dw_conv_params->activation.max);
    }
    else
    {
        depthwise_conv_u8_generic(input,
            input_dims->n,
            input_dims->w,
            input_dims->h,
            input_dims->c,
            kernel,
            output_dims->c,
            dw_conv_params->ch_mult,
            filter_dims->w,
            filter_dims->h,
            dw_conv_params->padding.w,
            dw_conv_params->padding.h,
            dw_conv_params->stride.w,
            dw_conv_params->stride.h,
            bias,
            output,
            quant_params->shift,
            quant_params->multiplier,
            output_dims->w,
            output_dims->h,
            dw_conv_params->output_offset,
            dw_conv_params->input_offset,
            dw_conv_params->filter_offset,
            dw_conv_params->activation.min,
            dw_conv_params->activation.max);
    }

    /* Return to application */
    return RISCV_MATH_SUCCESS;
}

/**
  @brief         Read 4 q7 from q7 pointer and post increment pointer.
  @param[in]     in_q7       Pointer to pointer that holds address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE q31_t riscv_nn_read_q7x4_ia(const q7_t **in_q7)
{
  q31_t val;
#ifdef __RISCV_FEATURE_UNALIGNED
  memcpy (&val, *in_q7, 4);
#else
  __ASM volatile ("lw %0, 0(%1)" : "=r" (val) : "r" (*in_q7));
#endif
  *in_q7 += 4;

    return (val);
}

/**
  @brief         Read 4 q7 values.
  @param[in]     in_q7       pointer to address of input.
  @return        q31 value
 */
__STATIC_FORCEINLINE q31_t riscv_nn_read_q7x4(const q7_t *in_q7)
{
  q31_t val;
#ifdef __RISCV_FEATURE_UNALIGNED
  memcpy (&val, in_q7, 4);
#else
    __ASM volatile ("lw %0, 0(%1)" : "=r" (val) : "r" (in_q7));
#endif

    return (val);
}

/**
  @brief         Write 4 Q7 to Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q7x4_ia (
    q7_t ** pQ7,
    q31_t   value)
{
    q31_t val = value;
    memcpy (*pQ7, &val, 4);
    *pQ7 += 4;
}


static void compare_and_replace_if_larger_u8(uint8_t* base, const uint8_t* target, int32_t length)
{
#if defined (RISCV_VECTOR)
    q7_t* dst = base;
    const q7_t* src = target;
    uint32_t blkCnt = length;                              /* Loop counter */
    size_t l;
    vint8m8_t vx, vy;

    for (; (l = vsetvl_e8m8(blkCnt)) > 0; blkCnt -= l) {
        vse8_v_i8m8(dst, vmax_vv_i8m8(vle8_v_i8m8(src, l), vle8_v_i8m8(dst, l), l), l);
        src += l;
        dst += l;
}
#else
    uint8_t* dst = base;
    const uint8_t* src = target;
    union riscv_nnword_u ref_max;
    union riscv_nnword_u comp_max;
    int32_t cnt = length >> 2;

    while (cnt > 0l)
    {
        ref_max.word = (uint32_t)riscv_nn_read_q7x4((q7_t*)dst);
        comp_max.word = (uint32_t)riscv_nn_read_q7x4_ia(&src);

        if (comp_max.bytes[0] > ref_max.bytes[0])
        {
            ref_max.bytes[0] = comp_max.bytes[0];
        }
        if (comp_max.bytes[1] > ref_max.bytes[1])
        {
            ref_max.bytes[1] = comp_max.bytes[1];
        }
        if (comp_max.bytes[2] > ref_max.bytes[2])
        {
            ref_max.bytes[2] = comp_max.bytes[2];
        }
        if (comp_max.bytes[3] > ref_max.bytes[3])
        {
            ref_max.bytes[3] = comp_max.bytes[3];
        }

        write_q7x4_ia(&dst, ref_max.word);

        cnt--;
    }

    cnt = length & 0x3;
    while (cnt > 0l)
    {
        if (*src > *dst)
        {
            *dst = *src;
        }
        dst++;
        src++;
        cnt--;
    }
#endif /*defined (RISCV_VECTOR)*/
}

static void clamp_output_u8(uint8_t* source, int32_t length, const int32_t act_min, const int32_t act_max)
{
#if defined (RISCV_VECTOR)
    uint32_t blkCnt = length;                              /* Loop counter */
    size_t l;
    vint8m8_t vx, vy;

    for (; (l = vsetvl_e8m8(blkCnt)) > 0; blkCnt -= l) {
        vse8_v_i8m8(source, vmax_vx_i8m8(vmin_vx_i8m8(vle8_v_i8m8(source, l), act_max, l), act_min, l), l);
        source += l;
    }
#else
    union riscv_nnword_u in;
    int32_t cnt = length >> 2;

    while (cnt > 0l)
    {
        in.word = riscv_nn_read_q7x4((q7_t *)source);

        in.bytes[0] = MAX(in.bytes[0], act_min);
        in.bytes[0] = MIN(in.bytes[0], act_max);
        in.bytes[1] = MAX(in.bytes[1], act_min);
        in.bytes[1] = MIN(in.bytes[1], act_max);
        in.bytes[2] = MAX(in.bytes[2], act_min);
        in.bytes[2] = MIN(in.bytes[2], act_max);
        in.bytes[3] = MAX(in.bytes[3], act_min);
        in.bytes[3] = MIN(in.bytes[3], act_max);

        write_q7x4_ia(&source, in.word);
        cnt--;
    }

    cnt = length & 0x3;
    while (cnt > 0l)
    {
        int32_t comp = *source;
        comp = MAX(comp, act_min);
        comp = MIN(comp, act_max);
        *source++ = (uint8_t)comp;
        cnt--;
    }
#endif /*defined (RISCV_VECTOR)*/
}

riscv_status riscv_max_pool_u8(const nmsis_nn_context* ctx,
    const nmsis_nn_pool_params* pool_params,
    const nmsis_nn_dims* input_dims,
    const uint8_t* src,
    const nmsis_nn_dims* filter_dims,
    const nmsis_nn_dims* output_dims,
    uint8_t* dst)
{
    const int32_t input_y = input_dims->h;
    const int32_t input_x = input_dims->w;
    const int32_t output_y = output_dims->h;
    const int32_t output_x = output_dims->w;
    const int32_t stride_y = pool_params->stride.h;
    const int32_t stride_x = pool_params->stride.w;
    const int32_t kernel_y = filter_dims->h;
    const int32_t kernel_x = filter_dims->w;
    const int32_t pad_y = pool_params->padding.h;
    const int32_t pad_x = pool_params->padding.w;
    const int32_t act_min = pool_params->activation.min;
    const int32_t act_max = pool_params->activation.max;
    const int32_t channel_in = input_dims->c;
    (void)ctx;
    uint8_t* dst_base = dst;
   
    for (int i_y = 0, base_idx_y = -pad_y; i_y < output_y; base_idx_y += stride_y, i_y++)
    {
        for (int i_x = 0, base_idx_x = -pad_x; i_x < output_x; base_idx_x += stride_x, i_x++)
        {
            /* Condition for kernel start dimension: (base_idx_<x,y> + kernel_<x,y>_start) >= 0 */
            const int32_t ker_y_start = MAX(0, -base_idx_y);
            const int32_t ker_x_start = MAX(0, -base_idx_x);

            /* Condition for kernel end dimension: (base_idx_<x,y> + kernel_<x,y>_end) < dim_src_<width,height> */
            const int32_t kernel_y_end = MIN(kernel_y, input_y - base_idx_y);
            const int32_t kernel_x_end = MIN(kernel_x, input_x - base_idx_x);

            int count = 0;

            for (int k_y = ker_y_start; k_y < kernel_y_end; k_y++)
            {
                for (int k_x = ker_x_start; k_x < kernel_x_end; k_x++)
                {
                    const uint8_t* start = src + channel_in * (k_x + base_idx_x + (k_y + base_idx_y) * input_x);

                    if (count == 0)
                    {
                        memcpy(dst, start, channel_in);
                        count++;
                    }
                    else
                    {
                        compare_and_replace_if_larger_u8(dst, start, channel_in);
                    }
                }
            }
            /* 'count' is expected to be non-zero here. */
            dst += channel_in;
        }
    }

    clamp_output_u8(dst_base, output_x * output_y * channel_in, act_min, act_max);

    return RISCV_MATH_SUCCESS;
}

/*
void forward_DEPTHWISE_CONVOLUTIONAL_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    const q7_t* Im_in = l->input_i8[0];
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = l->c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    q7_t* Im_out = l->output_i8;
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * l->c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        //for (int cin = 0; cin < l->c; cin++) {
        for (int wt = 0; wt < ksize; wt++) {
            int index = outin * ksize + wt;
            int nm_index = wt * l->out_c + outin;
            nm_weight[nm_index] = l->weights[index];
        }
        //}
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_depthwise_separable_conv_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }

}

void forward_CONVOLUTIONAL_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    const q7_t* Im_in = l->input_i8[0];
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = l->c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    q7_t* Im_out = l->output_i8;
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * l->c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        for (int cin = 0; cin < l->c; cin++) {
            for (int wt = 0; wt < l->size * l->size; wt++) {
                int index = outin * (l->c / l->groups) * ksize + (cin / l->groups) * ksize + wt;
                int nm_index = outin * ksize * (l->c / l->groups) + wt * (l->c / l->groups) + (cin / l->groups);
                nm_weight[nm_index] = l->weights[index];
            }
        }
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }
}

void forward_DEPTHWISE_CONV_MAX_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int conv_output_size = l->out_w * l->out_h * l->out_c;

    const q7_t* Im_in = l->input_i8[0];
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = l->c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    //q7_t* Im_out = l->output_i8;
    q7_t* Im_out = (q7_t*) BLAI_MALLOC(l->out_w * l->out_h * l->out_c * sizeof(q7_t));
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * l->c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        //for (int cin = 0; cin < l->c; cin++) {
        for (int wt = 0; wt < ksize; wt++) {
            int index = outin * ksize + wt;
            int nm_index = wt * l->out_c + outin;
            nm_weight[nm_index] = l->weights[index];
        }
        //}
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_depthwise_separable_conv_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }


    riscv_maxpool_q7_HWC_nonsquare(Im_out, l->out_w, l->out_h, l->out_c, 2, 0, 2, l->out_w / 2, l->out_h / 2, (q7_t*)bufferA, l->output_i8);

    BLAI_FREE(Im_out);
}

void forward_CONV_MAX_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    const q7_t* Im_in = l->input_i8[0];
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = l->c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    //q7_t* Im_out = l->output_i8;
    q7_t* Im_out = (q7_t*)BLAI_MALLOC(l->out_w * l->out_h * l->out_c * sizeof(q7_t));
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * l->c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        for (int cin = 0; cin < l->c; cin++) {
            for (int wt = 0; wt < l->size * l->size; wt++) {
                int index = outin * (l->c / l->groups) * ksize + (cin / l->groups) * ksize + wt;
                int nm_index = outin * ksize * (l->c / l->groups) + wt * (l->c / l->groups) + (cin / l->groups);
                nm_weight[nm_index] = l->weights[index];
            }
        }
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }

    riscv_maxpool_q7_HWC_nonsquare(Im_out, l->out_w, l->out_h, l->out_c, 2, 0, 2, l->out_w / 2, l->out_h / 2, (q7_t*)bufferA, l->output_i8);

    BLAI_FREE(Im_out);
}

void forward_ROUTE_DEPTHWISE_CONVOLUTIONAL_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int accum_c = l->c + l->cn[0];
    q7_t* route_out = NULL;
    if (l->mid_out)
        route_out = l->mid_output_i8;
    else
        route_out = (q7_t*)BLAI_MALLOC(l->w * l->h * accum_c * sizeof(q7_t));

    q7_t* final_output_i8 = l->output_i8;
    int temp_out_c = l->out_c;
    l->output_i8 = route_out;
    l->out_c = accum_c;
    forward_ROUTE(net, l, DATA_buf, l_current);
    l->out_c = temp_out_c;
    l->output_i8 = final_output_i8;

    forward_ROUTE(net, l, DATA_buf, l_current);

    l->output_i8 = final_output_i8;

    const q7_t* Im_in = route_out;
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = accum_c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    q7_t* Im_out = l->output_i8;
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * accum_c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        //for (int cin = 0; cin < l->c; cin++) {
        for (int wt = 0; wt < ksize; wt++) {
            int index = outin * ksize + wt;
            int nm_index = wt * l->out_c + outin;
            nm_weight[nm_index] = l->weights[index];
        }
        //}
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_depthwise_separable_conv_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_depthwise_separable_conv_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }
}

void forward_ROUTE_CONVOLUTIONAL_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {

    int accum_c = l->c + l->cn[0];
    q7_t* route_out = NULL;
    if (l->mid_out) route_out = l->mid_output_i8;
    else route_out = (q7_t*)BLAI_MALLOC(l->w * l->h * accum_c * sizeof(q7_t));
    q7_t* final_output_i8 = l->output_i8;
    int temp_out_c = l->out_c;
    int temp_out_w = l->out_w;
    int temp_out_h = l->out_h;
    l->output_i8 = route_out;
    l->out_c = accum_c;
    l->out_w = l->w;
    l->out_h = l->h;
    forward_ROUTE(net, l, DATA_buf, l_current);
    l->out_c = temp_out_c;
    l->out_w = temp_out_w;
    l->out_h = temp_out_h;
    l->output_i8 = final_output_i8;

    const q7_t* Im_in = route_out;
    const uint16_t dim_im_in = l->w;
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = accum_c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    q7_t* Im_out = l->output_i8;
    const uint16_t dim_im_out = l->out_w;
    const uint16_t dim_im_out_x = l->out_w;
    const uint16_t dim_im_out_y = l->out_h;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));
    q7_t* bufferB = (q7_t*)BLAI_MALLOC(num_B * sizeof(q7_t));
    // weight reshape
    uint16_t ksize = l->size * l->size;
    q7_t* nm_weight = (q7_t*)BLAI_MALLOC((l->out_c * accum_c * ksize / l->groups) * sizeof(q7_t));
    q7_t* nm_bias = (q7_t*)BLAI_MALLOC(l->out_c * sizeof(q7_t));
    for (int outin = 0; outin < l->out_c; outin++) {
        nm_bias[outin] = l->biases[outin];
        for (int cin = 0; cin < accum_c; cin++) {
            for (int wt = 0; wt < l->size * l->size; wt++) {
                int index = outin * (accum_c / l->groups) * ksize + (cin / l->groups) * ksize + wt;
                int nm_index = outin * ksize * (accum_c / l->groups) + wt * (accum_c / l->groups) + (cin / l->groups);
                nm_weight[nm_index] = l->weights[index];
            }
        }
    }

    if (l->w == l->h) {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_acti_u8((uint8_t*)Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_acti(Im_in, dim_im_in, ch_im_in, nm_weight, ch_im_out, dim_kernel, padding,
                stride, nm_bias, bias_shift, out_shift, Im_out, dim_im_out, activation, data_shift, bufferA, bufferB);
    }
    else {
        if (l_current == 0 && net->unsign_input)
            riscv_convolve_HWC_q7_nonsquare_acti_u8((uint8_t*)Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
        else
            riscv_convolve_HWC_q7_nonsquare_acti(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, nm_weight, ch_im_out, dim_kernel_x,
                dim_kernel_y, padding_x, padding_y, stride_x, stride_y, nm_bias, bias_shift, out_shift,
                Im_out, dim_im_out_x, dim_im_out_y, activation, data_shift, bufferA, bufferB);
    }

    if (!l->mid_out)
        BLAI_FREE(route_out);
}

void forward_MAXPOOL_nmsis(struct blai_net_info_t* net, struct cpu_inst_layer_t* l, fixed_point_t* DATA_buf, int l_current) {
    q7_t* Im_in = l->input_i8[0];
    const uint16_t dim_im_in_x = l->w;
    const uint16_t dim_im_in_y = l->h;
    const uint16_t ch_im_in = l->c;
    const uint16_t ch_im_out = l->out_c;
    const uint16_t dim_kernel = l->size;
    const uint16_t dim_kernel_x = l->size;
    const uint16_t dim_kernel_y = l->size;
    const uint16_t padding = (l->size == 2) ? 0 : l->size / 2;
    const uint16_t padding_x = l->size / 2;
    const uint16_t padding_y = l->size / 2;
    const uint16_t stride = l->stride;
    const uint16_t stride_x = l->stride;
    const uint16_t stride_y = l->stride;
    const uint16_t bias_shift = -(l->fbias - (l->fdata + l->fweight));
    const uint16_t out_shift = l->fdata + l->fweight - l->fout;
    const uint16_t data_shift = l->fdata + l->fweight;
    q7_t* Im_out = l->output_i8;
    const uint16_t dim_im_out_x = l->w / l->stride;
    const uint16_t dim_im_out_y = l->h / l->stride;
    const uint8_t activation = l->activation;
    int num_A = 0;
    int num_B = 0;
#if defined (RISCV_MATH_DSP) || defined (RISCV_VECTOR)
    num_A = (l->w == l->h) ? 2 * ch_im_in * dim_kernel * dim_kernel : 2 * ch_im_in * dim_kernel_x * dim_kernel_y;
#endif
    q15_t* bufferA = (q15_t*)BLAI_MALLOC(num_A * sizeof(q15_t));

    riscv_maxpool_q7_HWC_nonsquare(Im_in, dim_im_in_x, dim_im_in_y, ch_im_in, dim_kernel, padding, stride, dim_im_out_x, dim_im_out_y, (q7_t*)bufferA, Im_out);

}
*/
