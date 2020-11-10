/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <string.h>
#include <stdio.h>
#include <device/vfs_spi.h>
#include <vfs_err.h>
#include <vfs_register.h>
#include <hal/soc/spi.h>
#include <aos/kernel.h>

#include <bl_dma.h>
#include <bl_gpio.h>
#include <bl602_spi.h>
#include <bl602_gpio.h>
#include <bl602_glb.h>
#include <bl602_dma.h>
#include <bl_irq.h>
#include <bl_dma.h>

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <event_groups.h>

#include <libfdt.h>
#include <utils_log.h>
#include <blog.h>

#define HAL_SPI_DEBUG       (0)
#define HAL_SPI_HARDCS      (1)

#define SPI_NUM_MAX         1 /* only support spi0 */
#define LLI_BUFF_SIZE       2048

#define EVT_GROUP_SPI_DMA_TX    (1<<0)
#define EVT_GROUP_SPI_DMA_RX    (1<<1)
#define EVT_GROUP_SPI_DMA_TR    (EVT_GROUP_SPI_DMA_TX | EVT_GROUP_SPI_DMA_RX)

typedef struct _spi_hw {
    uint8_t used;
    SPI_ID_Type ssp_id;
    uint8_t mode;
    uint32_t freq;
    uint8_t polar_phase;
    uint8_t tx_dma_ch;
    uint8_t rx_dma_ch;
    uint8_t pin_clk;
    uint8_t pin_cs;
    uint8_t pin_mosi;
    uint8_t pin_miso;
    EventGroupHandle_t spi_dma_event_group;
} spi_hw_t;

typedef struct spi_priv_data {
    spi_hw_t hwspi[SPI_NUM_MAX];
} spi_priv_data_t;

spi_priv_data_t *g_hal_buf = NULL;

void bl_spi0_dma_int_handler_tx(void);
void bl_spi0_dma_int_handler_rx(void);

static void hal_gpio_init(spi_hw_t *arg)
{
    uint8_t gpiopins[4];

    if (!arg) {
        blog_error("arg err.\r\n");
        return;
    }

    gpiopins[0] = arg->pin_cs;
    gpiopins[1] = arg->pin_clk;
    gpiopins[2] = arg->pin_mosi;
    gpiopins[3] = arg->pin_miso;

    GLB_GPIO_Func_Init(GPIO_FUN_SPI,gpiopins,sizeof(gpiopins)/sizeof(gpiopins[0]));

    if (arg->mode == 0) {
        GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);
    } else {
        GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_SLAVE);
    }

    return;
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
    dmactrl.Prot = 0;
    dmactrl.SLargerD = 0;

    *pptxlli = pvPortMalloc(sizeof(DMA_LLI_Ctrl_Type) * count);
    if (*pptxlli == NULL) {
        blog_error("malloc lli failed. \r\n");

        return -1;
    }

    *pprxlli = pvPortMalloc(sizeof(DMA_LLI_Ctrl_Type) * count);
    if (*pprxlli == NULL) {
        blog_error("malloc lli failed.");
        vPortFree(*pptxlli);

        return -1;
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

        dmactrl.SI = DMA_MINC_ENABLE;
        dmactrl.DI = DMA_MINC_DISABLE;

        if (i == count - 1) {
            dmactrl.I = 1;
        } else {
            dmactrl.I = 0;
        }

        (*pptxlli)[i].srcDmaAddr = (uint32_t)(ptx_data + i * LLI_BUFF_SIZE);
        (*pptxlli)[i].destDmaAddr = (uint32_t)(SPI_BASE+SPI_FIFO_WDATA_OFFSET);
        (*pptxlli)[i].dmaCtrl = dmactrl;

        dmactrl.SI = DMA_MINC_DISABLE;
        dmactrl.DI = DMA_MINC_ENABLE;
        (*pprxlli)[i].srcDmaAddr = (uint32_t)(SPI_BASE+SPI_FIFO_RDATA_OFFSET);
        (*pprxlli)[i].destDmaAddr = (uint32_t)(prx_data + i * LLI_BUFF_SIZE);
        (*pprxlli)[i].dmaCtrl = dmactrl;

        if (i != 0) {
            (*pptxlli)[i-1].nextLLI = (uint32_t)&(*pptxlli)[i];
            (*pprxlli)[i-1].nextLLI = (uint32_t)&(*pprxlli)[i];
        }

        (*pptxlli)[i].nextLLI = 0;
        (*pprxlli)[i].nextLLI = 0;
    }

    return 0;
}

static void hal_spi_dma_init(spi_hw_t *arg)
{
    spi_hw_t *hw_arg = arg;
    SPI_CFG_Type spicfg;
    SPI_ClockCfg_Type clockcfg;
    SPI_FifoCfg_Type fifocfg;
    SPI_ID_Type spi_id;
    uint8_t clk_div;

    spi_id = hw_arg->ssp_id;

    /* clock */
    /*1  --->  40 Mhz
     *2  --->  20 Mhz
     *5  --->  8  Mhz
     *6  --->  6.66 Mhz
     *10 --->  4 Mhz
     * */
    clk_div = (uint8_t)(40000000 / hw_arg->freq);
    GLB_Set_SPI_CLK(ENABLE,0);
    clockcfg.startLen = clk_div;
    clockcfg.stopLen = clk_div;
    clockcfg.dataPhase0Len = clk_div;
    clockcfg.dataPhase1Len = clk_div;
    clockcfg.intervalLen = clk_div;
    SPI_ClockConfig(spi_id, &clockcfg);

    /* spi config */
    spicfg.deglitchEnable = DISABLE;
    spicfg.continuousEnable = ENABLE;
    spicfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST,
    spicfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST,
    spicfg.frameSize = SPI_FRAME_SIZE_8;

    if (hw_arg->polar_phase == 0) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->polar_phase == 1) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_LOW;
    } else if (hw_arg->polar_phase == 2) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_0;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else if (hw_arg->polar_phase == 3) {
        spicfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
        spicfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    } else {
        blog_error("node support polar_phase \r\n");
    }
    SPI_Init(0,&spicfg);

    if (hw_arg->mode == 0)
    {
        SPI_Disable(spi_id, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Disable(spi_id, SPI_WORK_MODE_SLAVE);
    }

    SPI_IntMask(spi_id,SPI_INT_ALL,MASK);

    /* fifo */
    fifocfg.txFifoThreshold = 1;
    fifocfg.rxFifoThreshold = 1;
    fifocfg.txFifoDmaEnable = ENABLE;
    fifocfg.rxFifoDmaEnable = ENABLE;
    SPI_FifoConfig(spi_id,&fifocfg);

    DMA_Disable();
    DMA_IntMask(hw_arg->tx_dma_ch, DMA_INT_ALL, MASK);
    DMA_IntMask(hw_arg->tx_dma_ch, DMA_INT_TCOMPLETED, UNMASK);
    DMA_IntMask(hw_arg->tx_dma_ch, DMA_INT_ERR, UNMASK);

    DMA_IntMask(hw_arg->rx_dma_ch, DMA_INT_ALL, MASK);
    DMA_IntMask(hw_arg->rx_dma_ch, DMA_INT_TCOMPLETED, UNMASK);
    DMA_IntMask(hw_arg->rx_dma_ch, DMA_INT_ERR, UNMASK);

    bl_irq_enable(DMA_ALL_IRQn);
    bl_dma_irq_register(hw_arg->tx_dma_ch, bl_spi0_dma_int_handler_tx, NULL, NULL);
    bl_dma_irq_register(hw_arg->rx_dma_ch, bl_spi0_dma_int_handler_rx, NULL, NULL);

    return;
}

static void hal_spi_dma_trans(spi_hw_t *arg, uint8_t *TxData, uint8_t *RxData, uint32_t Len)
{
    EventBits_t uxBits;
    DMA_LLI_Cfg_Type txllicfg;
    DMA_LLI_Cfg_Type rxllicfg;
    DMA_LLI_Ctrl_Type *ptxlli;
    DMA_LLI_Ctrl_Type *prxlli;
    int ret;

    if (!arg) {
        blog_error("arg err.\r\n");
        return;
    }

    txllicfg.dir = DMA_TRNS_M2P;
    txllicfg.srcPeriph = DMA_REQ_NONE;
    txllicfg.dstPeriph = DMA_REQ_SPI_TX;

    rxllicfg.dir = DMA_TRNS_P2M;
    rxllicfg.srcPeriph = DMA_REQ_SPI_RX;
    rxllicfg.dstPeriph = DMA_REQ_NONE;


    xEventGroupClearBits(arg->spi_dma_event_group, EVT_GROUP_SPI_DMA_TR);

    DMA_Channel_Disable(arg->tx_dma_ch);
    DMA_Channel_Disable(arg->rx_dma_ch);
    bl_dma_int_clear(arg->tx_dma_ch);
    bl_dma_int_clear(arg->rx_dma_ch);
    DMA_Enable();

    if (arg->mode == 0) {
        SPI_Enable(arg->ssp_id, SPI_WORK_MODE_MASTER);
    } else {
        SPI_Enable(arg->ssp_id, SPI_WORK_MODE_SLAVE);
    }

    ret = lli_list_init(&ptxlli, &prxlli, TxData, RxData, Len);
    if (ret < 0) {
        blog_error("init lli failed. \r\n");

        return;
    }

    DMA_LLI_Init(arg->tx_dma_ch, &txllicfg);
    DMA_LLI_Init(arg->rx_dma_ch, &rxllicfg);
    DMA_LLI_Update(arg->tx_dma_ch,(uint32_t)ptxlli);
    DMA_LLI_Update(arg->rx_dma_ch,(uint32_t)prxlli);
    DMA_Channel_Enable(arg->tx_dma_ch);
    DMA_Channel_Enable(arg->rx_dma_ch);

    uxBits = xEventGroupWaitBits(arg->spi_dma_event_group,
                                     EVT_GROUP_SPI_DMA_TR,
                                     pdTRUE,
                                     pdTRUE,
                                     portMAX_DELAY);

    if ((uxBits & EVT_GROUP_SPI_DMA_TR) == EVT_GROUP_SPI_DMA_TR) {
        blog_info("recv all event group.\r\n");
    }

    vPortFree(ptxlli);
    vPortFree(prxlli);
}

int32_t hal_spi_init(spi_dev_t *spi)
{
    int i;
    spi_priv_data_t *data;

    if (!spi) {
        blog_error("arg err.\r\n");
    }

    data = (spi_priv_data_t *)spi->priv;
    if (data == NULL) {
        return -1;
    }

    for (i = 0; i < SPI_NUM_MAX; i++) {
        hal_gpio_init(&data->hwspi[i]);
        hal_spi_dma_init(&data->hwspi[i]);
    }

#if (HAL_SPI_DEBUG)
    blog_info("hal_spi_init.\r\n");
#endif

    return 0;
}

int32_t hal_spi_finalize(spi_dev_t *spi)
{
    blog_info("not support. hal_spi_finalize.\r\n");
    return 0;
}

int32_t hal_spi_send(spi_dev_t *spi, const uint8_t *data, uint16_t size, uint32_t timeout)
{
    blog_info("not support. hal_spi_send.\r\n");
    return 0;
}

int32_t hal_spi_recv(spi_dev_t *spi, uint8_t *data, uint16_t size, uint32_t timeout)
{
    blog_info("not support. hal_spi_recv.\r\n");
    return 0;
}

int32_t hal_spi_send_recv(spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint16_t size, uint32_t timeout)
{
    blog_info("not support. hal_spi_send_recv.\r\n");
    return 0;
}

int hal_spi_set_rwmode(spi_dev_t *spi_dev, int mode)
{
    spi_priv_data_t *data;

#if (HAL_SPI_DEBUG)
    blog_info("set rwmode = %d\r\n", mode);
#endif
    if ((mode < 0) || (mode > 3)) {
        blog_error("mode is err.\r\n");
        return -1;
    }

    data = (spi_priv_data_t *)spi_dev->priv;
    data->hwspi[spi_dev->port].mode = mode;
    spi_dev->config.mode = mode;

    hal_spi_init(spi_dev);
    return 0;
}

int hal_spi_set_rwspeed(spi_dev_t *spi_dev, uint32_t speed)
{
    spi_priv_data_t *data;
    int i;
    uint8_t real_flag = 0;
    uint32_t real_speed = 0;

#if (HAL_SPI_DEBUG)
    blog_info("set rwspeed = %ld\r\n", speed);
#endif
    if (spi_dev->config.freq == speed) {
        blog_info("speed not change.\r\n");
        return 0;
    }

    for (i = 0; i < 256; i++) {
        if (speed == (40000000/(i+1))) {
            real_speed = speed;
            real_flag = 1;
        } else if (speed < (40000000/(i+1))) {
            continue;
        } else {
            break;
        }
    }

    if (real_flag != 1) {
        if (i == 0) {
            blog_error("The max speed is 40000000 Hz, please set it smaller.");
            return -1;
        } else if (i == 256) {
            blog_error("The min speed is 156250 Hz, please set it bigger.");
            return -1;
        } else {
            if ( ((40000000/(i+1)) - speed) > (speed - (40000000/i)) ) {
                real_speed = (40000000/(i+1));
                blog_info("not support speed: %ld, change real_speed = %ld\r\n", speed, real_speed);
            } else {
                real_speed = (40000000/i);
                blog_info("not support speed: %ld, change real_speed = %ld\r\n", speed, real_speed);
            }
        }
    }

    data = (spi_priv_data_t *)spi_dev->priv;
    data->hwspi[spi_dev->port].freq = real_speed;
    spi_dev->config.freq = real_speed;

    hal_spi_init(spi_dev);
    return 0;
}

int hal_spi_transfer(spi_dev_t *spi_dev, void *xfer, uint8_t size)
{
    uint16_t i;
    spi_ioc_transfer_t * s_xfer;
    spi_priv_data_t *priv_data;

    if ((!spi_dev) || (!xfer)) {
        blog_error("arg err.\r\n");
        return -1;
    }

    priv_data = (spi_priv_data_t *)spi_dev->priv;
    if (priv_data == NULL) {
        blog_error("priv_data NULL.\r\n");
        return -1;
    }

    s_xfer = (spi_ioc_transfer_t *)xfer;

#if (HAL_SPI_DEBUG)
    blog_info("hal_spi_transfer = %d\r\n", size);
#endif

#if (0 == HAL_SPI_HARDCS)
    bl_gpio_output_set(priv_data->hwspi[spi_dev->port].pin_cs, 0);
#endif
    for (i = 0; i < size; i++) {
#if (HAL_SPI_DEBUG)
        blog_info("transfer xfer[%d].len = %ld\r\n", i, s_xfer[i].len);
#endif
        hal_spi_dma_trans(&priv_data->hwspi[spi_dev->port],
                (uint8_t *)s_xfer[i].tx_buf, (uint8_t *)s_xfer[i].rx_buf, s_xfer[i].len);
    }
#if (0 == HAL_SPI_HARDCS)
    bl_gpio_output_set(priv_data->hwspi[spi_dev->port].pin_cs, 1);
#endif

    return 0;
}

int vfs_spi_init_fullname(const char *fullname, uint8_t port,
                            uint8_t mode, uint8_t polar_phase, uint32_t freq, uint8_t tx_dma_ch, uint8_t rx_dma_ch,
                            uint8_t pin_clk, uint8_t pin_cs, uint8_t pin_mosi, uint8_t pin_miso)
{
    int ret, len;
    spi_dev_t *spi;

    len = strlen(fullname);
    if (len + 1 > 32) {
        blog_error("arg err.\r\n");
        return -EINVAL;
    }

    //TODO use one bigger mem for these two small struct
    if (NULL == g_hal_buf) {
        g_hal_buf = (spi_priv_data_t*)aos_malloc(sizeof(spi_priv_data_t));
        if (NULL == g_hal_buf) {
            blog_error("mem err.\r\n");
            return -ENOMEM;
        }
        memset(g_hal_buf, 0, sizeof(spi_priv_data_t));
    }

    g_hal_buf->hwspi[port].spi_dma_event_group = xEventGroupCreate();
    blog_info("port%d eventloop init = %08lx\r\n", port,
        (uint32_t)g_hal_buf->hwspi[port].spi_dma_event_group);
    if (NULL == g_hal_buf->hwspi[port].spi_dma_event_group) {
        aos_free(g_hal_buf);
        return -ENOMEM;
    }

    spi = (spi_dev_t*)aos_malloc(sizeof(spi_dev_t));
    if (NULL == spi) {
        blog_error("mem err.\r\n");
        vEventGroupDelete(g_hal_buf->hwspi[port].spi_dma_event_group);
        aos_free(g_hal_buf);
        return -ENOMEM;
    }

    memset(spi, 0, sizeof(spi_dev_t));
    spi->port = port;
    spi->config.mode = mode;
    spi->config.freq = freq;
    g_hal_buf->hwspi[port].ssp_id = port;
    g_hal_buf->hwspi[port].mode = mode;
    g_hal_buf->hwspi[port].polar_phase = polar_phase;
    g_hal_buf->hwspi[port].freq = freq;
    g_hal_buf->hwspi[port].tx_dma_ch = tx_dma_ch;
    g_hal_buf->hwspi[port].rx_dma_ch = rx_dma_ch;
    g_hal_buf->hwspi[port].pin_clk = pin_clk;
    g_hal_buf->hwspi[port].pin_cs = pin_cs;
    g_hal_buf->hwspi[port].pin_mosi = pin_mosi;
    g_hal_buf->hwspi[port].pin_miso = pin_miso;
    spi->priv = g_hal_buf;

    blog_info("[HAL] [SPI] Register Under %s for :\r\nport=%d, mode=%d, polar_phase = %d, freq=%ld, tx_dma_ch=%d, rx_dma_ch=%d, pin_clk=%d, pin_cs=%d, pin_mosi=%d, pin_miso=%d\r\n",
        fullname, port, mode, polar_phase, freq, tx_dma_ch, rx_dma_ch, pin_clk, pin_cs, pin_mosi, pin_miso);

    ret = aos_register_driver(fullname, &spi_ops, spi);
    if (ret != VFS_SUCCESS) {
        aos_free(spi);
        vEventGroupDelete(g_hal_buf->hwspi[port].spi_dma_event_group);
        aos_free(g_hal_buf);
        return ret;
    }

    return VFS_SUCCESS;
}

#define BL_FDT32_TO_U8(addr, byte_offset)   ((uint8_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U16(addr, byte_offset)  ((uint16_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))
#define BL_FDT32_TO_U32(addr, byte_offset)  ((uint32_t)fdt32_to_cpu(*(uint32_t *)((uint8_t *)addr + byte_offset)))

int spi_arg_set_fdt2(const void * fdt, uint32_t dtb_spi_offset)
{
    #define SPI_MODULE_MAX 1
    uint8_t port;
    uint8_t mode;
    uint8_t polar_phase;
    uint32_t freq;
    uint8_t tx_dma_ch;
    uint8_t rx_dma_ch;
    uint8_t pin_clk;
    uint8_t pin_cs;
    uint8_t pin_mosi;
    uint8_t pin_miso;
    char *path = NULL;

    int offset1 = 0;
    int offset2 = 0;
    const uint32_t *addr_prop = 0;
    int lentmp = 0;
    const char *result = 0;
    int countindex = 0;

    int i;
    int ret;

    const char *spi_node[SPI_MODULE_MAX] = {
        "spi@4000F000"
    };

    /* spi */
    for (i = 0; i < SPI_MODULE_MAX; i++) {
        /* get spi0 ? spi1 ? spi2 offset1 */
        offset1 = fdt_subnode_offset(fdt, dtb_spi_offset, spi_node[i]);
        if (0 >= offset1) {
            continue;
        }

        result = fdt_stringlist_get(fdt, offset1, "status", 0, &lentmp);
        if ((lentmp != 4) || (memcmp("okay", result, 4) != 0)) {
            blog_info("spi[%d] status != okay\r\n", i);
            continue;
        }

        result = fdt_stringlist_get(fdt, offset1, "mode", 0, &lentmp);
        if ((lentmp != 6 && lentmp != 5) || ((memcmp("master", result, 6) != 0) && (memcmp("slave", result, 5)))) {
            blog_info("spi[%d] mode != master or slave\r\n", i);
            continue;
        }

        if (memcmp("master", result, 6) == 0) {
            mode = 0;
        } else {
            mode = 1;
        }

        /* set path */
        countindex = fdt_stringlist_count(fdt, offset1, "path");
        if (countindex != 1) {
            blog_info("spi[%d] path_countindex = %d NULL.\r\n", i, countindex);
            continue;
        }
        result = fdt_stringlist_get(fdt, offset1, "path", 0, &lentmp);
        if ((lentmp < 0) || (lentmp > 32)) {
            blog_info("spi[%d] path lentmp = %d\r\n", i, lentmp);
        }
        path = (char *)result;

        /* sure port == i */
        addr_prop = fdt_getprop(fdt, offset1, "port", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] port NULL.\r\n", i);
            continue;
        }
        port = BL_FDT32_TO_U8(addr_prop, 0);
        if (port != i) {
            blog_error("fdt err. port[%d] != i[%d].\r\n", port, i);
            continue;
        }

        /* get polar_phase */
        addr_prop = fdt_getprop(fdt, offset1, "polar_phase", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] polar_phase NULL.\r\n", i);
            continue;
        }
        polar_phase = BL_FDT32_TO_U8(addr_prop, 0);

        /* get freq */
        addr_prop = fdt_getprop(fdt, offset1, "freq", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] freq NULL.\r\n", i);
            continue;
        }
        freq = BL_FDT32_TO_U32(addr_prop, 0);

        /* set pin */
        offset2 = fdt_subnode_offset(fdt, offset1, "pin");
        if (0 >= offset1) {
            continue;
        }

        /* get pin_clk */
        addr_prop = fdt_getprop(fdt, offset2, "clk", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] clk NULL.\r\n", i);
            continue;
        }
        pin_clk = BL_FDT32_TO_U8(addr_prop, 0);

        /* get pin_cs */
        addr_prop = fdt_getprop(fdt, offset2, "cs", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] cs NULL.\r\n", i);
            continue;
        }
        pin_cs = BL_FDT32_TO_U8(addr_prop, 0);

        /* get pin_mosi */
        addr_prop = fdt_getprop(fdt, offset2, "mosi", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] mosi NULL.\r\n", i);
            continue;
        }
        pin_mosi = BL_FDT32_TO_U8(addr_prop, 0);

        /* get pin_miso */
        addr_prop = fdt_getprop(fdt, offset2, "miso", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] miso NULL.\r\n", i);
            continue;
        }
        pin_miso = BL_FDT32_TO_U8(addr_prop, 0);

        /* set dma_cfg */
        offset2 = fdt_subnode_offset(fdt, offset1, "dma_cfg");
        if (0 >= offset1) {
            continue;
        }

        /* get tx_dma_ch */
        addr_prop = fdt_getprop(fdt, offset2, "tx_dma_ch", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] tx_dma_ch NULL.\r\n", i);
            continue;
        }
        tx_dma_ch = BL_FDT32_TO_U8(addr_prop, 0);

        /* get rx_dma_ch */
        addr_prop = fdt_getprop(fdt, offset2, "rx_dma_ch", &lentmp);
        if (addr_prop == NULL) {
            blog_info("spi[%d] rx_dma_ch NULL.\r\n", i);
            continue;
        }
        rx_dma_ch = BL_FDT32_TO_U8(addr_prop, 0);

        ret = vfs_spi_init_fullname((const char *)path, port, mode, polar_phase, freq, tx_dma_ch, rx_dma_ch,           pin_clk, pin_cs, pin_mosi, pin_miso);
        if (ret == 0) {
            blog_info("init ok and read %08lx\r\n", (uint32_t)g_hal_buf->hwspi[0].spi_dma_event_group);
        } else {
            blog_info("spi init failed \r\n");
        }
    }
    return 0;
}

int vfs_spi_fdt_init(uint32_t fdt, uint32_t dtb_spi_offset)
{
    spi_arg_set_fdt2((const void *)fdt, dtb_spi_offset);
    blog_info("vfs_spi_fdt_init ok.\r\n");
    return 0;
}

void bl_spi0_dma_int_handler_tx(void)
{
    BaseType_t xResult = pdFAIL;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (NULL != g_hal_buf) {
        bl_dma_int_clear(g_hal_buf->hwspi[0].tx_dma_ch);

        if (g_hal_buf->hwspi[0].spi_dma_event_group != NULL) {
            xResult = xEventGroupSetBitsFromISR(g_hal_buf->hwspi[0].spi_dma_event_group,
                                                EVT_GROUP_SPI_DMA_TX,
                                                &xHigherPriorityTaskWoken);
        }

        if(xResult != pdFAIL) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    } else {
        blog_error("bl_spi0_dma_int_handler_tx no clear isr.\r\n");
    }

    return;
}

void bl_spi0_dma_int_handler_rx(void)
{
    BaseType_t xResult = pdFAIL;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (NULL != g_hal_buf) {
        bl_dma_int_clear(g_hal_buf->hwspi[0].rx_dma_ch);

        if (g_hal_buf->hwspi[0].spi_dma_event_group != NULL) {
            xResult = xEventGroupSetBitsFromISR(g_hal_buf->hwspi[0].spi_dma_event_group,
                                                EVT_GROUP_SPI_DMA_RX,
                                                &xHigherPriorityTaskWoken);
        }

        if(xResult != pdFAIL) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    } else {
        blog_error("bl_spi0_dma_int_handler_rx no clear isr.\r\n");
    }
    return;
}
