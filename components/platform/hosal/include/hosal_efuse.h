
#ifndef __HOSAL_EFUSE_H__
#define __HOSAL_EFUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read data from efuse
 *
 * @param[in]   addr     efuse address
 * @param[in]   data     store data
 * @param[in]   len      data length 
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_efuse_read(uint32_t addr, uint32_t *data, uint32_t len);

/**
 * @brief Write data to efuse
 *
 * @param[in]   addr     efuse address
 * @param[in]   data     store data
 * @param[in]   len      data length 
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_efuse_write(uint32_t addr, uint32_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_EFUSE_H__ */

/* end of file */
