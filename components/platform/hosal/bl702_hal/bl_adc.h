#ifndef __BL_ADC_H__
#define __BL_ADC_H__

#include <stdint.h>

typedef void(*bl_adc_tsen_callback_t)(int16_t tsen_val);

typedef struct bl_adc_tsen_cfg
{
    uint8_t tsen_dma_ch;
    bl_adc_tsen_callback_t tsen_event;
}bl_adc_tsen_cfg_t;

typedef void(*bl_adc_voice_callback_t)(int buf_idx);

typedef struct bl_adc_voice_cfg
{
    uint8_t adc_pos_pin;
    uint8_t adc_neg_pin;
    uint8_t adc_dma_ch;
    uint16_t pcm_frame_size;
    int16_t *pcm_frame_buf[2];
    bl_adc_voice_callback_t pcm_frame_event;
}bl_adc_voice_cfg_t;

int bl_adc_tsen_init(void);
int16_t bl_adc_tsen_get_val(void);

int bl_adc_tsen_dma_init(bl_adc_tsen_cfg_t *cfg);
int bl_adc_tsen_dma_trigger(void);
int bl_adc_tsen_dma_is_busy(void);

int bl_adc_voice_init(bl_adc_voice_cfg_t *cfg);
int bl_adc_voice_start(void);
int bl_adc_voice_stop(void);

#endif
