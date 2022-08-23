
#ifndef __HOSAL_I2C_H_
#define __HOSAL_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_i2c I2C
 *  HOSAL I2C API
 *
 *  @{
 */

#include <stdint.h>

#define HOSAL_WAIT_FOREVER 0xFFFFFFFFU /**< @brief i2c wait time */

#define HOSAL_I2C_MODE_MASTER 1     /**< @brief i2c communication is master mode */
#define HOSAL_I2C_MODE_SLAVE  2     /**< @brief i2c communication is slave mode */

#define HOSAL_I2C_MEM_ADDR_SIZE_8BIT  1 /**< @brief i2c memory address size 8bit */
#define HOSAL_I2C_MEM_ADDR_SIZE_16BIT 2 /**< @brief i2c memory address size 16bit */
#define HOSAL_I2C_MEM_ADDR_SIZE_24BIT 3 /**< @brief i2c memory address size 24bit */
#define HOSAL_I2C_MEM_ADDR_SIZE_32BIT 4 /**< @brief i2c memory address size 32bit */

#define HOSAL_I2C_ADDRESS_WIDTH_7BIT  0   /**< @brief 7 bit mode */
#define HOSAL_I2C_ADDRESS_WIDTH_10BIT 1   /**< @brief 10 bit mode */

/**
 * @brief I2C configuration
 */
typedef struct {
    uint32_t address_width; /**< @brief Addressing mode: 7 bit or 10 bit */
    uint32_t freq;          /**< @brief CLK freq */
    uint8_t  scl;           /**< @brief i2c clk pin */
    uint8_t  sda;           /**< @brief i2c data pin */
    uint8_t  mode;          /**< @brief master or slave mode */
} hosal_i2c_config_t;

/**
 * @brief I2C device type
 */
typedef struct {
    uint8_t       port;             /**< @brief i2c port */
    hosal_i2c_config_t  config;     /**< @brief i2c config */
    void         *priv;             /**< @brief priv data */
} hosal_i2c_dev_t;

/**
 * @brief Initialises an I2C interface
 *
 * @param[in]  i2c  the device for which the i2c port should be initialised
 *
 * @return  
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_init(hosal_i2c_dev_t *i2c);

/**
 * @brief I2c master send
 *
 * @param[in]  i2c       the i2c device
 * @param[in]  dev_addr  device address
 * @param[in]  data      i2c send data
 * @param[in]  size      i2c send data size
 * @param[in]  timeout   timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                       if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_master_send(hosal_i2c_dev_t *i2c, uint16_t dev_addr, const uint8_t *data,
                            uint16_t size, uint32_t timeout);

/**
 * @brief I2c master recv
 *
 * @param[in]   i2c       the i2c device
 * @param[in]   dev_addr  device address
 * @param[out]  data      i2c receive data
 * @param[in]   size      i2c receive data size
 * @param[in]   timeout   timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                        if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_master_recv(hosal_i2c_dev_t *i2c, uint16_t dev_addr, uint8_t *data,
                            uint16_t size, uint32_t timeout);
/**
 * @brief I2c slave send
 *
 * @param[in]  i2c      the i2c device
 * @param[in]  data     i2c slave send data
 * @param[in]  size     i2c slave send data size
 * @param[in]  timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                      if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_slave_send(hosal_i2c_dev_t *i2c, const uint8_t *data, uint16_t size, uint32_t timeout);

/**
 * @brief I2c slave receive
 *
 * @param[in]   i2c      tthe i2c device
 * @param[out]  data     i2c slave receive data
 * @param[in]   size     i2c slave receive data size
 * @param[in]  timeout   timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                       if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_slave_recv(hosal_i2c_dev_t *i2c, uint8_t *data, uint16_t size, uint32_t timeout);

/**
 * @brief I2c mem write
 *
 * @param[in]  i2c            the i2c device
 * @param[in]  dev_addr       device address
 * @param[in]  mem_addr       mem address
 * @param[in]  mem_addr_size  mem address
 * @param[in]  data           i2c master send data
 * @param[in]  size           i2c master send data size
 * @param[in]  timeout        timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                            if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_mem_write(hosal_i2c_dev_t *i2c, uint16_t dev_addr, uint32_t mem_addr,
                          uint16_t mem_addr_size, const uint8_t *data, uint16_t size,
                          uint32_t timeout);

/**
 * @brief I2c master mem read
 *
 * @param[in]   i2c            the i2c device
 * @param[in]   dev_addr       device address
 * @param[in]   mem_addr       mem address
 * @param[in]   mem_addr_size  mem address
 * @param[out]  data           i2c master send data
 * @param[in]   size           i2c master send data size
 * @param[in]  timeout         timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                             if you want to wait forever
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_mem_read(hosal_i2c_dev_t *i2c, uint16_t dev_addr, uint32_t mem_addr,
                         uint16_t mem_addr_size, uint8_t *data, uint16_t size,
                         uint32_t timeout);

/**
 * @brief Deinitialises an I2C device
 *
 * @param[in]  i2c  the i2c device
 *
 * @return
 *  - 0  on success
 *  - EIO  if an error occurred with any step
 */
int hosal_i2c_finalize(hosal_i2c_dev_t *i2c);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_I2C_H_ */

/* end of file */
