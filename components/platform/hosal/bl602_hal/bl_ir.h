#ifndef __BL_IR_H__
#define __BL_IR_H__
#include <stdint.h>

#define BL_IR_CHECK_NONE           (0)
#define BL_IR_CHECK_CMD            (1 << 0)
#define BL_IR_CHECK_ADDR           (1 << 1)
#define CHIP_WS2812B               0
#define CHIP_UCS1903               1
#define IR_DMA_CHANNEL             2


typedef struct _spi_ir_hw {
    uint8_t used;
    uint8_t ssp_id;
    uint8_t mode;
    uint32_t freq;
    uint8_t polar_phase;
    uint8_t tx_dma_ch;
    uint8_t rx_dma_ch;
    uint8_t pin_clk;
    uint8_t pin_cs;
    uint8_t pin_mosi;
    uint8_t pin_miso;
    void *spi_dma_ir_event_group;
} spi_ir_hw_t;

typedef struct _private_ir_data {
    uint8_t *pp_buf0;
    uint8_t *pp_buf1;
    uint32_t left_size;
    uint32_t reset_size;
    int chip_type;
    int end_flag;
    int buf_flag;
    uint32_t data_idx;
    uint32_t chip_coe;
    uint32_t *p_data;
    void *ptxlli;
    spi_ir_hw_t dev_spi;
} private_ir_data_t;

uint32_t bl_receivedata(void);
uint32_t bl_getbitcount(void);
void bl_enable_rx_int(void);
int bl_ir_init(int pin, int ctrltype, int data_check);
int bl_ir_data_check_config(uint32_t data_check);
void bl_irmask(int mask);

void bl_spi_dma_init(private_ir_data_t *pstctx);
int bl_spi_hw_init(private_ir_data_t *pstctx);
int bl_spi_dma_trans(private_ir_data_t *pstctx, uint32_t *TxData, uint32_t Len);

static inline int bl_ir_get_addr(unsigned int val)
{
    return (val & 0xFF);
}

static inline int bl_ir_get_cmd(unsigned int val)
{
    return ((val & 0xFF0000) >> 16);
}

#endif
