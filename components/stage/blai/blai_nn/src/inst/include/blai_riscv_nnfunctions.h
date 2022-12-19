
#include "riscv_nn_types.h"

/**
 * @brief Union for SIMD access of q31/q15/q7 types
 */
 
/**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7_t;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15_t;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31_t;

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63_t;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double float64_t;


 
union riscv_nnword
{
    q31_t word;
    /**< q31 type */
    q15_t half_words[2];
    /**< q15 type */
    q7_t bytes[4];
    /**< q7 type */
};

union riscv_nnword_u
{
    uint32_t word;
    /**< q31 type */
    uint16_t half_words[2];
    /**< q15 type */
    uint8_t bytes[4];
    /**< q7 type */
};

/**
 * @brief Union for data type long long
 */
struct riscv_nn_double
{
    uint32_t low;
    int32_t high;
};

union riscv_nn_long_long
{
    int64_t long_long;
    struct riscv_nn_double word;
};

#define F64_MAX   ((float64_t)DBL_MAX)
#define F32_MAX   ((float32_t)FLT_MAX)



#define F64_MIN   (-DBL_MAX)
#define F32_MIN   (-FLT_MAX)



#define F64_ABSMAX   ((float64_t)DBL_MAX)
#define F32_ABSMAX   ((float32_t)FLT_MAX)



#define F64_ABSMIN   ((float64_t)0.0)
#define F32_ABSMIN   ((float32_t)0.0)


#define Q31_MAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_MAX   ((q15_t)(0x7FFF))
#define Q7_MAX    ((q7_t)(0x7F))
#define Q31_MIN   ((q31_t)(0x80000000L))
#define Q15_MIN   ((q15_t)(0x8000))
#define Q7_MIN    ((q7_t)(0x80))

#define Q31_ABSMAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_ABSMAX   ((q15_t)(0x7FFF))
#define Q7_ABSMAX    ((q7_t)(0x7F))
#define Q31_ABSMIN   ((q31_t)0)
#define Q15_ABSMIN   ((q15_t)0)
#define Q7_ABSMIN    ((q7_t)0)

  /* Dimension C vector space */
  #define CMPLX_DIM 2

  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    RISCV_MATH_SUCCESS                 =  0,        /**< No error */
    RISCV_MATH_ARGUMENT_ERROR          = -1,        /**< One or more arguments are incorrect */
    RISCV_MATH_LENGTH_ERROR            = -2,        /**< Length of data buffer is incorrect */
    RISCV_MATH_SIZE_MISMATCH           = -3,        /**< Size of matrices is not compatible with the operation */
    RISCV_MATH_NANINF                  = -4,        /**< Not-a-number (NaN) or infinity is generated */
    RISCV_MATH_SINGULAR                = -5,        /**< Input matrix is singular and cannot be inverted */
    RISCV_MATH_TEST_FAILURE            = -6,        /**< Test Failed */
    RISCV_MATH_DECOMPOSITION_FAILURE   = -7         /**< Decomposition Failed */
  } riscv_status;


int32_t riscv_convolve_s8_get_buffer_size(const nmsis_nn_dims *input_dims, const nmsis_nn_dims *filter_dims);

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
    uint8_t* output_data);

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
                           q7_t *output_data);

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
    uint8_t* output);

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
                                 q7_t *output);

riscv_status riscv_max_pool_u8(const nmsis_nn_context* ctx,
    const nmsis_nn_pool_params* pool_params,
    const nmsis_nn_dims* input_dims,
    const uint8_t* src,
    const nmsis_nn_dims* filter_dims,
    const nmsis_nn_dims* output_dims,
    uint8_t* dst);
