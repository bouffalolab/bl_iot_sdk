/**
 * Copyright (c) 2016-2021 Bouffalolab Co., Ltd.
 *
 * Contact information:
 * web site:    https://www.bouffalolab.com/
 */

#ifndef __HOSAL_DMA_H__
#define __HOSAL_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_dma DMA
 *  HOSAL DMA API
 *
 *  @{
 */

#include <stdint.h>
#include <stdio.h>

/**
 * @brief DMA irq callback function flag
 */
#define HOSAL_DMA_INT_TRANS_COMPLETE      0
#define HOSAL_DMA_INT_TRANS_ERROR         1

/**
 * @brief DMA irq callback function
 */
typedef void (*hosal_dma_irq_t)(void *p_arg, uint32_t flag);

/**
 * @brief DMA channel describe
 */
struct hosal_dma_chan {
    uint8_t used;
    hosal_dma_irq_t callback;
    void *p_arg;
};

/**
 * @brief DMA device type
 */
typedef struct hosal_dma_dev {
    int max_chans;
    struct hosal_dma_chan *used_chan;
    void *priv;
} hosal_dma_dev_t;

/**
 * @brief DMA channel
 */
typedef int hosal_dma_chan_t;

/**
 * @brief Initialises a DMA interface
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_init(void);

/**
 * @brief Request a DMA channel
 *
 * @param[in] flag : DMA CHAN REQUEST FLAG
 *
 * @return  < 0 : an error occurred with any step, otherwise is DMA channel number
 */
hosal_dma_chan_t hosal_dma_chan_request(int flag);

/**
 * @brief Release a DMA channel
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_release(hosal_dma_chan_t chan);

/**
 * @brief DMA channel trans start
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_start(hosal_dma_chan_t chan);

/**
 * @brief DMA channel trans stop
 *
 * @param[in]  chan  DMA channel number
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_chan_stop(hosal_dma_chan_t chan);

/**
 * @brief DMA irq callback set
 *
 * @param[in] chan : DMA channel number
 * @param[in] pfn : callback function
 * @param[in] arg : callback function parameter
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_irq_callback_set(hosal_dma_chan_t chan, hosal_dma_irq_t pfn, void *p_arg);

/**
 * @brief Deinitialises a DMA interface
 *
 * @param[in]  DMA the interface which should be deinitialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_dma_finalize(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_DMA_H__ */

/* end of file */
