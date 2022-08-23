#ifndef __BL_ADC_H__
#define __BL_ADC_H__

#define ADC_DMA_CHANNEL    1
#define ADC_CHANNEL_MAX    12

typedef void (*bl_adc_cb_t)(int mode, uint32_t *data_ptr, uint32_t data_size);
typedef struct adc_ctx {
    int mode;
    uint32_t *channel_data;
    void *adc_lli;
    int lli_flag;
    uint32_t chan_init_table;
    uint32_t data_size;
    bl_adc_cb_t cb;
}adc_ctx_t;

int test_adc_init(void);
int test_adc_get(int16_t *tmp);
int test_adc_test(void);
int bl_tsen_adc_get(int16_t *temp, uint8_t log_flag);

//int bl_adc_clock_init(int sampling_ms);
int bl_adc_init(int mode, int gpio_num);
int bl_adc_dma_init(int mode, uint32_t data_num);
int bl_adc_start(void);
int bl_adc_gpio_init(int gpio_num);
int bl_adc_get_channel_by_gpio(int gpio_num);
int bl_adc_freq_init(int mode, uint32_t freq);
int32_t bl_adc_parse_data(uint32_t *parr, int data_size, int channel, int raw_flag);

#endif
