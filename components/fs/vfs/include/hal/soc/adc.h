/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef HAL_ADC_H
#define HAL_ADC_H

typedef struct {
    uint32_t sampling_cycle;  /* sampling period in number of ADC clock cycles */
} adc_config_t;

typedef struct {
    uint8_t      port;   /* adc port */
    adc_config_t config; /* adc config */
    void        *priv;   /* priv data */
    void         *mutex;
    void         *fd;
    void         *poll_cb;
    void         *poll_data;
} adc_dev_t;

/**
 * Initialises an ADC interface, Prepares an ADC hardware interface for sampling
 *
 * @param[in]  adc  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_adc_init(adc_dev_t *adc);

/**
 * Takes a single sample from an ADC interface
 *
 * @param[in]   adc      the interface which should be sampled
 * @param[out]  output   pointer to a variable which will receive the sample
 * @param[in]   timeout  ms timeout
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_adc_value_get(adc_dev_t *adc, uint32_t *output, uint32_t timeout);

/**
 * De-initialises an ADC interface, Turns off an ADC hardware interface
 *
 * @param[in]  adc  the interface which should be de-initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_adc_finalize(adc_dev_t *adc);

/**
 * Register notify on a ADC device
 *
 * @param[in]  adc  the adc device which notify should be noticed
 * @param[in]  cb    call back function
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register(adc_dev_t *adc, void (*cb)(void *arg));

/**
 * Disable notify source. It's usually disable low level INT
 *
 * @param[in]  adc  the adc device which notify should be noticed
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register_config_disable(adc_dev_t *adc);

/**
 *  Config source to be high level trigger
 *
 * @param[in]  adc  the adc device which notify should be noticed
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register_config_high(adc_dev_t *adc);

/**
 *  Config source to be low level trigger
 *
 * @param[in]  adc  the adc device which notify should be noticed
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register_config_low(adc_dev_t *adc);

/**
 *  Config source to be trigger by voltage higher than specified
 *
 * @param[in]  adc  the adc device which notify should be noticed
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register_config_higher(adc_dev_t *adc, int level);

/**
 *  Config source to be trigger by voltage lower than specified
 *
 * @param[in]  adc  the adc device which notify should be noticed
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_register_config_lower(adc_dev_t *adc, int level);
/**
 * Unregister notify on a ADC device
 *
 * @param[in]  adc  the adc device which notify should be noticed
 * @param[in]  cb    call back function
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hal_adc_notify_unregister(adc_dev_t *adc, void (*cb)(void *arg));
#endif /* HAL_ADC_H */

