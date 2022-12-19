/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <FreeRTOS.h>
#include <event_groups.h>
#include <bl808_spi.h>
#include <bl808_glb.h>

#include <bl808_glb_gpio.h>
#include <bl808_dma.h>
#include <hosal_dma.h>
#include "hosal_spi.h"
#include "bl_irq.h"
#include "blog.h"

#define LLI_BUFF_SIZE       2048

#define EVT_GROUP_SPI_TX    (1<<0)
#define EVT_GROUP_SPI_RX    (1<<1)
#define EVT_GROUP_SPI_TR    (EVT_GROUP_SPI_TX | EVT_GROUP_SPI_RX)

static void hosal_spi_int_handler_tx(void *arg, uint32_t flag);
static void hosal_spi_int_handler_rx(void *arg, uint32_t flag);
static void spi_tx_handler(void)
{
    SPI_ClrIntStatus(SPI1_ID, SPI_INT_END);
    printf("tx\r\n");
}
typedef struct {
    uint8_t *tx_data;
    uint8_t *rx_data;
    uint32_t length;
    uint32_t tx_index;
    uint32_t rx_index;
    EventGroupHandle_t spi_event_group;
} spi_priv_t;

typedef struct {
    int8_t tx_dma_ch;
    int8_t rx_dma_ch;
    uint8_t rx_enable;
    EventGroupHandle_t spi_event_group;
} spi_dma_priv_t;

static void spi_basic_init(hosal_spi_dev_t *arg)
{
    hosal_spi_dev_t *hw_arg = arg;
    SPI_CFG_Type spicfg;
    SPI_FifoCfg_Type fifocfg;
    SPI_ID_Type spi_id;

    spi_id = hw_arg->port;

    /* clock config */
    SPI_SetClock(spi_id, hw_arg->config.freq);

    /* spi config */
    spicfg.deglitchEnable = DISABLE;
    spicfg.slavePin = SPI_SLAVE_PIN_4;
    spicfg.continuousEnable = ENABLE;
    spicfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST;
    spicfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST;
    if (hw_arg->config.polar_phase == 0) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->config.polar_phase == 1) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->config.polar_phase == 2) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else if (hw_arg->config.polar_phase == 3) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else {
        blog_error("node support polar_phase \r\n");
    }
    spicfg.frameSize = SPI_FRAME_SIZE_8;
    SPI_Init(spi_id, &spicfg);

    if (hw_arg->config.mode == HOSAL_SPI_MODE_MASTER) {
        SPI_Disable(spi_id, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Disable(spi_id, SPI_WORK_MODE_SLAVE);
    }
    SPI_IntMask(spi_id, SPI_INT_ALL, MASK);

    /* fifo */
    fifocfg.txFifoThreshold = 0;
    fifocfg.rxFifoThreshold = 0;
    if (hw_arg->config.dma_enable) {
        fifocfg.txFifoDmaEnable = ENABLE;
        fifocfg.rxFifoDmaEnable = ENABLE;
        SPI_FifoConfig(spi_id,&fifocfg);
    } else {
        fifocfg.txFifoDmaEnable = DISABLE;
        fifocfg.rxFifoDmaEnable = DISABLE;
        SPI_FifoConfig(spi_id,&fifocfg);
        blog_info("spi no dma mode\r\n");
    }
}

static int lli_list_init(DMA_LLI_Ctrl_Type **pptxlli, DMA_LLI_Ctrl_Type **pprxlli, uint8_t *ptx_data, uint8_t *prx_data, uint32_t length)
{
    uint32_t i = 0;
    uint32_t count;
    uint32_t remainder;
    struct DMA_Control_Reg dmactrl;

    count = length / LLI_BUFF_SIZE;
    remainder = length % LLI_BUFF_SIZE;

    if (remainder != 0) {
        count = count + 1;
    }

    dmactrl.SBSize = DMA_BURST_SIZE_1;
    dmactrl.DBSize = DMA_BURST_SIZE_1;
    dmactrl.SWidth = DMA_TRNS_WIDTH_8BITS;
    dmactrl.DWidth = DMA_TRNS_WIDTH_8BITS;
    dmactrl.dst_min_mode = DISABLE;
    dmactrl.dst_add_mode = DISABLE;
    dmactrl.fix_cnt = 0;
    dmactrl.Prot = 0;
    dmactrl.reserved_20 = 0;

    *pptxlli = pvPortMalloc(sizeof(DMA_LLI_Ctrl_Type) * count);
    if (*pptxlli == NULL) {
        blog_error("malloc lli failed. \r\n");

        return -1;
    }

    if (NULL != prx_data) {
        *pprxlli = pvPortMalloc(sizeof(DMA_LLI_Ctrl_Type) * count);
        if (*pprxlli == NULL) {
            blog_error("malloc lli failed.");
            vPortFree(*pptxlli);
            return -1;
        }
    }

    for (i = 0; i < count; i++) {
        if (remainder == 0) {
            dmactrl.TransferSize = LLI_BUFF_SIZE;
        } else {
            if (i == count - 1) {
                dmactrl.TransferSize = remainder;
            } else {
                dmactrl.TransferSize = LLI_BUFF_SIZE;
            }
        }

        if (i == count - 1) {
            dmactrl.I = 1;
        } else {
            dmactrl.I = 0;
        }

        if (NULL != ptx_data) {
            dmactrl.SI = DMA_MINC_ENABLE;
            dmactrl.DI = DMA_MINC_DISABLE;
            (*pptxlli)[i].srcDmaAddr = (uint32_t)(uintptr_t)(ptx_data + i * LLI_BUFF_SIZE);
            (*pptxlli)[i].destDmaAddr = (uint32_t)(SPI1_BASE + SPI_FIFO_WDATA_OFFSET);
            (*pptxlli)[i].dmaCtrl = dmactrl;
            if (i != 0) {
                (*pptxlli)[i-1].nextLLI = (uint32_t)(uintptr_t)&(*pptxlli)[i];
            }
            (*pptxlli)[i].nextLLI = 0;
        }

        if (NULL != prx_data) {
            dmactrl.SI = DMA_MINC_DISABLE;
            dmactrl.DI = DMA_MINC_ENABLE;
            (*pprxlli)[i].srcDmaAddr = (uint32_t)(SPI1_BASE + SPI_FIFO_RDATA_OFFSET);
            (*pprxlli)[i].destDmaAddr = (uint32_t)(uintptr_t)(prx_data + i * LLI_BUFF_SIZE);
            (*pprxlli)[i].dmaCtrl = dmactrl;
            if (i != 0) {
                (*pprxlli)[i-1].nextLLI = (uint32_t)(uintptr_t)&(*pprxlli)[i];
            }
            (*pprxlli)[i].nextLLI = 0;
        }
    }

    if (NULL != pptxlli) {
        L1C_DCache_Clean_By_Addr((uintptr_t)pptxlli ,count * sizeof(DMA_LLI_Ctrl_Type));
    }

    if (NULL != pprxlli) {
        L1C_DCache_Clean_By_Addr((uintptr_t)pprxlli ,count * sizeof(DMA_LLI_Ctrl_Type));
    }

    if (NULL != ptx_data) {
        L1C_DCache_Clean_By_Addr((uintptr_t)ptx_data ,length);
    }

    return 0;
}

static int hosal_spi_dma_trans(hosal_spi_dev_t *arg, uint8_t *TxData, uint8_t *RxData, uint32_t Len, uint32_t timeout)
{
    EventBits_t uxBits = 0;
    DMA_LLI_Cfg_Type txllicfg;
    DMA_LLI_Cfg_Type rxllicfg;
    DMA_LLI_Ctrl_Type *ptxlli = NULL;
    DMA_LLI_Ctrl_Type *prxlli = NULL;
    spi_dma_priv_t *dma_arg = NULL;
    int ret;

    if (!arg) {
        blog_error("arg err.\r\n");
        return -1;
    }

    dma_arg = (spi_dma_priv_t*)arg->priv;

    if (TxData) {
        if (dma_arg->tx_dma_ch == -1) {
            dma_arg->tx_dma_ch = hosal_dma_chan_request(0);
            if (dma_arg->tx_dma_ch < 0) {
                blog_error("SPI TX DMA CHANNEL get failed!\r\n");
                return -1;
            }
        }
    } else {
        dma_arg->tx_dma_ch = -1;
    }
    if (RxData) {
        if (dma_arg->rx_dma_ch == -1) {
            dma_arg->rx_dma_ch = hosal_dma_chan_request(0);
            if (dma_arg->rx_dma_ch < 0) {
                blog_error("SPI RX DMA CHANNEL get failed!\r\n");
                return -1;
            }
        }
    } else {
        dma_arg->rx_dma_ch = -1;
    }

    txllicfg.dir = DMA_TRNS_M2P;
    txllicfg.srcPeriph = DMA_REQ_NONE;
    txllicfg.dstPeriph = DMA_REQ_SPI1_TX;

    rxllicfg.dir = DMA_TRNS_P2M;
    rxllicfg.srcPeriph = DMA_REQ_SPI1_RX;
    rxllicfg.dstPeriph = DMA_REQ_NONE;

    //xEventGroupClearBits(dma_arg->spi_event_group, EVT_GROUP_SPI_TR);

    if (arg->config.mode == HOSAL_SPI_MODE_MASTER) {
        SPI_Enable(arg->port, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Enable(arg->port, SPI_WORK_MODE_SLAVE);
    }

    ret = lli_list_init(&ptxlli, &prxlli, TxData, RxData, Len);
    if (ret < 0) {
        blog_error("init lli failed. \r\n");

        return -1;
    }

    if (NULL != RxData) {
        hosal_dma_irq_callback_set(dma_arg->rx_dma_ch, hosal_spi_int_handler_rx, arg);
        DMA_LLI_Init(DMA2_ID, dma_arg->rx_dma_ch, &rxllicfg);
        DMA_LLI_Update(DMA2_ID, dma_arg->rx_dma_ch,(uint32_t)(uintptr_t)prxlli);
        hosal_dma_chan_start(dma_arg->rx_dma_ch);
    }

    if (NULL != TxData) {
        hosal_dma_irq_callback_set(dma_arg->tx_dma_ch, hosal_spi_int_handler_tx, arg);
        DMA_LLI_Init(DMA2_ID, dma_arg->tx_dma_ch, &txllicfg);
        DMA_LLI_Update(DMA2_ID, dma_arg->tx_dma_ch,(uint32_t)(uintptr_t)ptxlli);
        hosal_dma_chan_start(dma_arg->tx_dma_ch);
    }

    uxBits = xEventGroupWaitBits(dma_arg->spi_event_group,
                                     EVT_GROUP_SPI_TR,
                                     pdFALSE,
                                     pdTRUE,
                                     timeout);

    //printf("group bits %x\r\n", (unsigned int)uxBits);
    if ((uxBits & EVT_GROUP_SPI_TR) == EVT_GROUP_SPI_TR) {
        if (dma_arg->tx_dma_ch >= 0) {
            hosal_dma_chan_stop(dma_arg->tx_dma_ch);
            hosal_dma_chan_release(dma_arg->tx_dma_ch);
            dma_arg->tx_dma_ch = -1;
        }
        if (dma_arg->rx_dma_ch >= 0) {
            hosal_dma_chan_stop(dma_arg->rx_dma_ch);
            hosal_dma_chan_release(dma_arg->rx_dma_ch);
            dma_arg->rx_dma_ch = -1;
        }
        if (arg->cb) {
            arg->cb(arg->p_arg);
        }
    } else {
        blog_error(" trans timeout\r\n");
    }
    xEventGroupClearBits(dma_arg->spi_event_group, EVT_GROUP_SPI_TR);
    //uxBits = xEventGroupGetBits(dma_arg->spi_event_group);
    //printf("after group bits %x\r\n", (unsigned int)uxBits);
    vPortFree(ptxlli);
    if (NULL != RxData) {
        vPortFree(prxlli);
    }
	return 0;
}

static void hosal_spi_int_handler_tx(void *arg, uint32_t flag)
{
    BaseType_t xResult = pdFAIL;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    hosal_spi_dev_t *dev = (hosal_spi_dev_t *)arg;
    if (NULL != dev) {
        if (dev->config.dma_enable) {
            spi_dma_priv_t *priv=  (spi_dma_priv_t *)dev->priv;
            if (priv->spi_event_group != NULL) {
                xResult = xEventGroupSetBitsFromISR(priv->spi_event_group,
                                                    EVT_GROUP_SPI_TX,
                                                    &xHigherPriorityTaskWoken);

                if (priv->rx_dma_ch == -1) {
                    xEventGroupSetBitsFromISR(priv->spi_event_group,
                                                    EVT_GROUP_SPI_RX,
                                                    &xHigherPriorityTaskWoken);
                }

            }

            if(xResult != pdFAIL) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    } else {
        blog_error("hosal_spi_int_handler_tx no clear isr.\r\n");
    }
    return;
}

static void hosal_spi_int_handler_rx(void *arg, uint32_t flag)
{
    BaseType_t xResult = pdFAIL;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    hosal_spi_dev_t *dev = (hosal_spi_dev_t *)arg;
    if (NULL != dev) {
        if (dev->config.dma_enable) {
            spi_dma_priv_t *priv=  (spi_dma_priv_t *)dev->priv;
            if (priv->spi_event_group != NULL) {
                xResult = xEventGroupSetBitsFromISR(priv->spi_event_group, EVT_GROUP_SPI_RX, &xHigherPriorityTaskWoken);

                if (priv->tx_dma_ch == -1) {
                    xEventGroupSetBitsFromISR(priv->spi_event_group, EVT_GROUP_SPI_TX, &xHigherPriorityTaskWoken);
                }

            }

            if(xResult != pdFAIL) {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
    } else {
        blog_error("hosal_spi_int_handler_tx no clear isr.\r\n");
    }
    return;
}

static int hosal_spi_trans(hosal_spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint32_t length, uint32_t timeout)
{
    int ret = -1;

    /* Clear tx and rx fifo */
    SPI_ClrTxFifo(spi->port);
    SPI_ClrRxFifo(spi->port);

    if (spi->config.mode == 0) {
        SPI_Enable(spi->port, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Enable(spi->port, SPI_WORK_MODE_SLAVE);
    }

    if (tx_data && rx_data)
        ret = SPI_SendRecvData(spi->port, tx_data, rx_data, length, SPI_TIMEOUT_DISABLE);
    else if (tx_data)
        ret = SPI_SendData(spi->port, tx_data, length, SPI_TIMEOUT_DISABLE);
    else if (rx_data)
        ret = SPI_ReceiveData(spi->port, rx_data, length, SPI_TIMEOUT_DISABLE);

    if (spi->config.mode == 0) {
        SPI_Disable(spi->port, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Disable(spi->port, SPI_WORK_MODE_SLAVE);
    }
    return ret;
}

static void hosal_spi_gpio_init(hosal_spi_dev_t *arg)
{
    if (!arg) {
        blog_error("arg err.\r\n");
        return;
    }

    GLB_GPIO_Type gpiopins[3];
    gpiopins[0] = arg->config.pin_clk;
    gpiopins[1] = arg->config.pin_mosi;
    gpiopins[2] = arg->config.pin_miso;
    if (arg->port == SPI0_ID)
        GLB_GPIO_Func_Init(GPIO_FUN_SPI0, gpiopins, sizeof(gpiopins)/sizeof(gpiopins[0]));
    else
        GLB_GPIO_Func_Init(GPIO_FUN_SPI1, gpiopins, sizeof(gpiopins)/sizeof(gpiopins[0]));

    if (arg->config.mode == 0) {
        if(arg->port == SPI0_ID) {
            GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);
        } else {
            GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);
        }
    } else {
        if(arg->port == SPI0_ID) {
            GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_SLAVE);
        } else {
            GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_SLAVE);
        }
    }

    return;
}

int hosal_spi_init(hosal_spi_dev_t *spi)
{
    hosal_spi_dev_t *dev = spi;
    if (NULL == spi ) {
        blog_error("arg err.\r\n");
    }

    hosal_spi_gpio_init(dev);
    spi_basic_init(dev);
    if (dev->config.dma_enable) {
        spi_dma_priv_t *priv = (spi_dma_priv_t *)pvPortMalloc(sizeof(spi_dma_priv_t));
        priv->spi_event_group = xEventGroupCreate();
        priv->tx_dma_ch = -1;
        priv->rx_dma_ch = -1;
        dev->priv = priv;
    } else {
        spi_priv_t *priv = (spi_priv_t *)pvPortMalloc(sizeof(spi_priv_t));
        priv->spi_event_group = xEventGroupCreate();
        priv->tx_data = NULL;
        priv->rx_data = NULL;
        priv->length  = 0;
        priv->tx_index = 0;
        priv->rx_index = 0;
        dev->priv = priv;
    }
    return 0;
}

int hosal_spi_set_cs(uint8_t pin, uint8_t value)
{
    GLB_GPIO_Cfg_Type cfg;
    cfg.gpioPin = pin;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.gpioMode = GPIO_MODE_OUTPUT;
    cfg.pullType = GPIO_PULL_UP;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    if (GLB_GPIO_Get_Fun(pin) != GPIO_FUN_GPIO)
        GLB_GPIO_Init(&cfg);
    GLB_GPIO_Write(pin, value);
    return 0;
}

int hosal_spi_irq_callback_set(hosal_spi_dev_t *spi, hosal_spi_irq_t pfn, void *p_arg)
{
    if (NULL == spi ) {
        blog_error("not init.\r\n");
        return -1;
    }

    spi->cb = pfn;
    spi->p_arg = p_arg;
    return 0;
}

int hosal_spi_finalize(hosal_spi_dev_t *spi)
{
    if (NULL == spi ) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        spi_dma_priv_t *spi_priv = (spi_dma_priv_t *)spi->priv;
        if (spi_priv->tx_dma_ch >= 0) {
            hosal_dma_chan_release(spi_priv->tx_dma_ch);
        }
        if (spi_priv->rx_dma_ch >= 0) {
            hosal_dma_chan_release(spi_priv->rx_dma_ch);
        }
        if (spi_priv->spi_event_group != NULL) {
            vEventGroupDelete(spi_priv->spi_event_group);
            spi_priv->spi_event_group = NULL;
        }
        vPortFree(spi_priv);
    } else {
        spi_priv_t *spi_priv = (spi_priv_t *)spi->priv;
        if (spi_priv->spi_event_group != NULL) {
            vEventGroupDelete(spi_priv->spi_event_group);
            spi_priv->spi_event_group = NULL;
        }
        vPortFree(spi_priv);
    }
    spi->priv = NULL;

    SPI_DeInit(spi->port);
    return 0;
}

int hosal_spi_send(hosal_spi_dev_t *spi, const uint8_t *data, uint16_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        ret = hosal_spi_dma_trans(spi, (uint8_t *)data, NULL, size, timeout);
    } else {
        ret = hosal_spi_trans(spi, (uint8_t *)data, NULL, size, timeout);
    }
    return ret;
}

int hosal_spi_recv(hosal_spi_dev_t *spi, uint8_t *data, uint16_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }
    /*FIXME: dcache may effect*/
    if (spi->config.dma_enable) {
        ret = hosal_spi_dma_trans(spi, NULL, data, size, timeout);
    } else {
        ret = hosal_spi_trans(spi, NULL, data, size, timeout);
    }
    return ret;
}

int hosal_spi_send_recv(hosal_spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint16_t size, uint32_t timeout)
{
    int ret;

    if (NULL == spi || tx_data == NULL || rx_data == NULL) {
        blog_error("not init.\r\n");
        return -1;
    }

    if (spi->config.dma_enable) {
        ret = hosal_spi_dma_trans(spi, (uint8_t *)tx_data, (uint8_t *)rx_data, size, timeout);
    } else {
        ret = hosal_spi_trans(spi, tx_data, rx_data, size, timeout);
    }
    return ret;
}

