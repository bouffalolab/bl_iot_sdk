#ifndef __BL_DAC_AUDIO_H__
#define __BL_DAC_AUDIO_H__

#include <stdint.h>
#include <bl602_dma.h>
#include <bl_dma.h>
#include "bl602_dac.h"

typedef int (*audio_callback_rx_ready_t)(void *usrdata, uint8_t *audiodata, int len, int is_overflow);
typedef int (*audio_callback_tx_ready_t)(void *uerdata, uint8_t *audiodata, int len, int is_underrun);

typedef struct {
    uint8_t pingpang;
    DMA_LLI_Ctrl_Type lli_list[2];
    uint8_t *lli_tx_buffer;
    uint32_t lli_tx_buffer_size;

    int is_underrun;
    audio_callback_tx_ready_t usr_cb;
    void *p_usr_arg;

} bl_audio_dac_dev_t;

int bl_audio_dac_init (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_deinit (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_start (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_stop (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_tx_buffer_config (bl_audio_dac_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_dac_rx_buffer_config (bl_audio_dac_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_dac_tx_ready_config(bl_audio_dac_dev_t *p_dev,
                                 audio_callback_tx_ready_t cb,
                                 void *p_arg);

int bl_audio_dac_rx_ready_config(bl_audio_dac_dev_t *p_dev,
                                 audio_callback_rx_ready_t cb,
                                 void *p_arg);

int bl_audio_dac_samplerate_set (bl_audio_dac_dev_t *p_dev,
                                 GPIP_DAC_MOD_Type samplerate);

#endif
