#ifndef HAL_RNG_H
#define HAL_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_rng RNG
 *  HOSAL RNG API
 *
 *  @{
 */

#include <stdint.h>

/**
 * @brief init rng
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_rng_init(void);

/**
 * @brief Fill in a memory buffer with random data
 *
 * @param[out]  buf          Point to a valid memory buffer, this function will fill
 *                           in this memory with random numbers after executed
 * @param[in]   bytes        Length of the memory buffer (bytes)
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_random_num_read(void *buf, uint32_t bytes);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_RNG_H */

