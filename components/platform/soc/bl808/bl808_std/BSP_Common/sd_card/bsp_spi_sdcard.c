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
#include "bflb_platform.h"
#include "hal_spi.h"
#include "hal_gpio.h"
#include "hal_dma.h"
#include "bsp_spi_sdcard.h"

static struct device *sd_spi;

#if SPI_SD_DMA_USING

#define SD_SPI_DMA_TX_INDEX DMA0_CH2_INDEX
#define SD_SPI_DMA_RX_INDEX DMA0_CH3_INDEX

static struct device *sd_spi_dma_tx;
static struct device *sd_spi_dma_rx;

static uint32_t sd_idle_tx_data = 0xFFFFFFFF;
#endif

SD_CardInfoTypedef SD_CardInfo = { 0 };

/* SPI Init */
uint8_t SD_SPI_Init(void)
{
    gpio_set_mode(SPI_PIN_CS, GPIO_OUTPUT_MODE);
    gpio_write(SPI_PIN_CS, 1);

    sd_spi = device_find("sd_spi");

    if (sd_spi) {
        device_close(sd_spi);
    } else {
        spi_register(SPI0_INDEX, "sd_spi");
        sd_spi = device_find("sd_spi");
    }

    if (sd_spi) {
        SPI_DEV(sd_spi)->mode = SPI_MASTER_MODE;
        SPI_DEV(sd_spi)->direction = SPI_MSB_BYTE0_DIRECTION_FIRST;
        SPI_DEV(sd_spi)->datasize = SPI_DATASIZE_8BIT;
        SPI_DEV(sd_spi)->clk_polaraity = SPI_POLARITY_LOW;
        SPI_DEV(sd_spi)->clk_phase = SPI_PHASE_1EDGE;
        SPI_DEV(sd_spi)->clk = SD_SPI_SPEED_IDEL;
        SPI_DEV(sd_spi)->fifo_threshold = 3;

        device_open(sd_spi, DEVICE_OFLAG_STREAM_TX | DEVICE_OFLAG_STREAM_RX);
    }

#if SPI_SD_DMA_USING

    sd_spi_dma_tx = device_find("sd_spi_dma_tx");

    if (sd_spi_dma_tx) {
        device_close(sd_spi_dma_tx);
    } else {
        dma_register(SD_SPI_DMA_TX_INDEX, "sd_spi_dma_tx");
        sd_spi_dma_tx = device_find("sd_spi_dma_tx");
    }

    if (sd_spi_dma_tx) {
        DMA_DEV(sd_spi_dma_tx)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(sd_spi_dma_tx)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(sd_spi_dma_tx)->src_req = DMA_REQUEST_NONE;
        DMA_DEV(sd_spi_dma_tx)->dst_req = DMA_REQUEST_SPI0_TX;
        DMA_DEV(sd_spi_dma_tx)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(sd_spi_dma_tx)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(sd_spi_dma_tx)->src_burst_size = DMA_BURST_INCR4;
        DMA_DEV(sd_spi_dma_tx)->dst_burst_size = DMA_BURST_INCR4;
        DMA_DEV(sd_spi_dma_tx)->src_width = DMA_TRANSFER_WIDTH_8BIT;
        DMA_DEV(sd_spi_dma_tx)->dst_width = DMA_TRANSFER_WIDTH_8BIT;

        device_open(sd_spi_dma_tx, 0);
        device_control(sd_spi_dma_tx, DEVICE_CTRL_CLR_INT, NULL);

        device_control(sd_spi, DEVICE_CTRL_ATTACH_TX_DMA, sd_spi_dma_tx);
        device_control(sd_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);
    }

    sd_spi_dma_rx = device_find("sd_spi_dma_rx");

    if (sd_spi_dma_rx) {
        device_close(sd_spi_dma_rx);
    } else {
        dma_register(SD_SPI_DMA_RX_INDEX, "sd_spi_dma_rx");
        sd_spi_dma_rx = device_find("sd_spi_dma_rx");
    }

    if (sd_spi_dma_rx) {
        DMA_DEV(sd_spi_dma_rx)->direction = DMA_PERIPH_TO_MEMORY;
        DMA_DEV(sd_spi_dma_rx)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(sd_spi_dma_rx)->src_req = DMA_REQUEST_SPI0_RX;
        DMA_DEV(sd_spi_dma_rx)->dst_req = DMA_REQUEST_NONE;
        DMA_DEV(sd_spi_dma_rx)->src_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(sd_spi_dma_rx)->dst_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(sd_spi_dma_rx)->src_burst_size = DMA_BURST_INCR4;
        DMA_DEV(sd_spi_dma_rx)->dst_burst_size = DMA_BURST_INCR4;
        DMA_DEV(sd_spi_dma_rx)->src_width = DMA_TRANSFER_WIDTH_8BIT;
        DMA_DEV(sd_spi_dma_rx)->dst_width = DMA_TRANSFER_WIDTH_8BIT;

        device_open(sd_spi_dma_rx, 0);
        device_control(sd_spi_dma_rx, DEVICE_CTRL_CLR_INT, NULL);

        device_control(sd_spi, DEVICE_CTRL_ATTACH_RX_DMA, sd_spi_dma_rx);
        device_control(sd_spi, DEVICE_CTRL_RX_DMA_SUSPEND, NULL);
    }

    L1C_DCache_Clean_By_Addr((uintptr_t)(&sd_idle_tx_data), sizeof(sd_idle_tx_data));
#endif

    return SUCCESS;
}

/* SPI Write Data */
static BL_Err_Type SPI_WriteByte(uint8_t *txBuff, uint32_t length)
{
#if SPI_SD_DMA_USING
    if (length >= 64 && length % 4 == 0) {
        /* clean cache */
        L1C_DCache_Clean_By_Addr((uintptr_t)(txBuff), length);
        /* config and start dma */
        device_control(sd_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
        device_write(sd_spi, 0, txBuff, length);
        /* wait for tx dma finish */
        while (dma_channel_check_busy(sd_spi_dma_tx)) {
            __asm volatile("nop");
        }
        /* Wait for tx FIFO to be empty */
        while (device_control(sd_spi, DEVICE_CTRL_SPI_GET_TX_FIFO, NULL) < SPI_FIFO_LEN) {
            __asm volatile("nop");
        }
        /* Wait for the SPI bus to be idle */
        while (device_control(sd_spi, DEVICE_CTRL_SPI_GET_BUS_BUSY_STATUS, NULL) != 0) {
            __asm volatile("nop");
        }
        /* Switch the SPI to non-DMA mode */
        device_control(sd_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);

        device_control(sd_spi, DEVICE_CTRL_SPI_CLEAR_RX_FIFO, NULL);
    } else
#endif
    {
        device_write(sd_spi, 0, txBuff, length);
    }

    return SUCCESS;
}

/* SPI Read Data */
static BL_Err_Type SPI_ReadByte(uint8_t *rxBuff, uint32_t length)
{
#if SPI_SD_DMA_USING
    if (length >= 64 && length % 4 == 0) {
        /* invalid cache */
        L1C_DCache_Clean_By_Addr((uintptr_t)(rxBuff), 0);
        L1C_DCache_Clean_By_Addr((uintptr_t)(rxBuff) + length, 0);
        L1C_DCache_Invalid_By_Addr((uintptr_t)(rxBuff), length);
        /* config and start dma */
        device_control(sd_spi_dma_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)DISABLE);
        device_control(sd_spi, DEVICE_CTRL_RX_DMA_RESUME, NULL);
        device_control(sd_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
        device_read(sd_spi, 0, rxBuff, length);
        device_write(sd_spi, 0, &sd_idle_tx_data, length);
        /*  wait for dma finish  */
        while (dma_channel_check_busy(sd_spi_dma_rx) || dma_channel_check_busy(sd_spi_dma_tx)) {
            __asm volatile("nop");
        }
        /* Switch the SPI to non-DMA mode */
        device_control(sd_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);
        device_control(sd_spi, DEVICE_CTRL_RX_DMA_SUSPEND, NULL);
        device_control(sd_spi, DEVICE_CTRL_SPI_CLEAR_RX_FIFO, NULL);
        device_control(sd_spi_dma_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)ENABLE);
    } else
#endif
    {
        device_read(sd_spi, 0, rxBuff, length);
    }

    return SUCCESS;
}

void SPI_CS_WriteBit(uint8_t bit)
{
    gpio_write(SPI_PIN_CS, bit);
}
/****************************************************************************
 * @brief  SPI_SetSpeed
 *
 *
*******************************************************************************/
static void SD_SPI_SetSpeed(uint32_t spi_freq)
{
    device_control(sd_spi, DEVICE_CTRL_SPI_CONFIG_CLOCK, (void *)(spi_freq));
}

/****************************************************************************/ /**
 * @brief  SD_GetResponse
 *
 *
*******************************************************************************/
static BL_Err_Type SD_GetResponse(uint8_t Response)
{
    uint8_t rx;
    uint32_t time_node;

    time_node = (uint32_t)bflb_platform_get_time_ms();

    do {
        SPI_ReadByte(&rx, 1);
        if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
            SD_SPI_MSG("Get Response 0x%02X time out\r\n", Response);
            break;
        }
    } while (rx != Response);

    if (rx != Response) {
        return ERROR;
    } else {
        return SUCCESS;
    }
}

/****************************************************************************
 * @brief  SD_SendCommand
 *
 *
*******************************************************************************/
static uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t rx;
    uint8_t txbuff[6];
    uint32_t time_node;

    SD_SPI_MSG("SD SPI Send CMD%d\r\n", cmd);

    SPI_CS_WriteBit(0);
    SD_GetResponse(0xFF);

    txbuff[0] = cmd | 0x40;
    txbuff[1] = (uint8_t)(arg >> 24);
    txbuff[2] = (uint8_t)(arg >> 16);
    txbuff[3] = (uint8_t)(arg >> 8);
    txbuff[4] = (uint8_t)(arg);
    txbuff[5] = (uint8_t)(crc) | 0x01;

    SPI_WriteByte(txbuff, 6);

    time_node = (uint32_t)bflb_platform_get_time_ms();
    do {
        SPI_ReadByte(&rx, 1);
        if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
            SD_SPI_MSG("SD SPI send CMD%d, get Resp timeout\r\n", cmd);
            SPI_CS_WriteBit(1);
            return MSD_RESPONSE_FAILURE;
        }

    } while (rx == 0xFF);

    SPI_CS_WriteBit(1);

    SD_SPI_MSG("SD SPI Send CMD%d success, Resp:0x%X\r\n", cmd, rx);

    return rx;
}

/****************************************************************************
 * @brief  SD_SendCommand_NoDeassert
 *
 *
*******************************************************************************/
static uint8_t SD_SendCommand_NoDeassert(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t rx;
    uint8_t txbuff[6];
    uint32_t time_node;

    SD_SPI_MSG("SD SPI Send CMD%d NoDeassert\r\n", cmd);

    SPI_CS_WriteBit(0);
    SD_GetResponse(0xFF);

    txbuff[0] = cmd | 0x40;
    txbuff[1] = (uint8_t)(arg >> 24);
    txbuff[2] = (uint8_t)(arg >> 16);
    txbuff[3] = (uint8_t)(arg >> 8);
    txbuff[4] = (uint8_t)(arg);
    txbuff[5] = (uint8_t)(crc);

    SPI_WriteByte(txbuff, 6);

    time_node = (uint32_t)bflb_platform_get_time_ms();
    do {
        SPI_ReadByte(&rx, 1);
        if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
            SD_SPI_MSG("SD SPI send CMD%d NoDeassert, get Resp timeout\r\n", cmd);
            break;
        }

    } while (rx == 0xFF);

    SD_SPI_MSG("SD SPI Send CMD%d NoDeassert success, Resp:0x%X\r\n", cmd, rx);

    return rx;
}

/****************************************************************************
 * @brief  SD_Idle_Sta
 *
 *
*******************************************************************************/
static BL_Err_Type SD_Idle_Sta(void)
{
    uint16_t i;
    uint8_t rx = 0;
    uint8_t retry = 0;

    SPI_CS_WriteBit(1);

    for (i = 0; i < 10; i++) {
        SPI_ReadByte(&rx, 1);
    }

    do {
        rx = SD_SendCommand(CMD0, 0, 0x95);
        retry++;
    } while (rx != MSD_IN_IDLE_STATE && retry < 3);

    if (rx != MSD_IN_IDLE_STATE) {
        SD_SPI_MSG("SD IDLE err:%d\r\n", rx);
        return ERROR;
    } else {
        SD_SPI_MSG("SD IDLE success\r\n");
        return SUCCESS;
    }
}

/****************************************************************************/ /**
 * @brief  SD_ReceiveData
 *
 *
 *
*******************************************************************************/
uint8_t SD_ReceiveData(uint8_t *data, uint16_t len, uint8_t release)
{
    uint8_t rx;

    SPI_CS_WriteBit(0);

    SD_SPI_MSG("SD SPI read data, len:%d\r\n", len);

    /* get token */
    if (SD_GetResponse(0xFE)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("SD SPI receive err: no token\r\n");
        return ERROR;
    }

    SPI_ReadByte(data, len);

    /* two dummy CRC */
    SPI_ReadByte(&rx, 1);
    SPI_ReadByte(&rx, 1);

    /* */
    if (release) {
        SPI_CS_WriteBit(1);
    }
    SD_SPI_MSG("SD SPI read data success\r\n");
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SD_SendData
 *
 *
 *
*******************************************************************************/
static uint8_t SD_SendData(uint8_t *buf, uint16_t len, uint8_t token)
{
    uint8_t rx;

    /* Waiti for free */
    if (SD_GetResponse(0xFF)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("sd send err: bus busy,timeout\r\n");
        return ERROR;
    }

    /* send token */
    SPI_WriteByte(&token, 1);

    /* non stop token */
    if (token != 0xFD) {
        SD_SPI_MSG("SD SPI write data, len:%d\r\n", len);

        /* send block data */
        SPI_WriteByte(buf, len);

        /* two dummy CRC */
        SPI_ReadByte(&rx, 1);
        SPI_ReadByte(&rx, 1);

        /* get response */
        SPI_ReadByte(&rx, 1);

        /*  */
        if ((rx & 0x1F) != 0x05) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("sd send data err: resp err:0x%X\r\n", rx);
            return rx;
        }

        SD_SPI_MSG("SD SPI write data success\r\n");
    }

    /* wait for free */
    if (SD_GetResponse(0xFF)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("sd send data err: bus busy,timeout\r\n");
        return ERROR;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SD_Get_CardInfo
 *
 *
*******************************************************************************/
uint8_t SD_Get_CardInfo(SD_CardInfoTypedef *pCardInfo)
{
    uint32_t tmp = 0;
    uint8_t rx;

    /* Waiti for free */
    if (SD_GetResponse(0xFF)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("sd send err: bus busy,timeout\r\n");
        return ERROR;
    }

    /* get cid */
    rx = SD_SendCommand(CMD10, 0, 0xFF);

    if (rx) {
        return 1;
    }

    SD_ReceiveData(pCardInfo->SD_cid.CID, 16, RELEASE);
    // SPI_ReadWriteByte(&t_0xFF, &rx, 1);
    SPI_ReadByte(&rx, 1);
    /* get csd */
    rx = SD_SendCommand(CMD9, 0, 0xFF);

    if (rx) {
        return 1;
    }

    SD_ReceiveData(pCardInfo->SD_csd.CSD, 16, RELEASE);

    /* Byte 0 */
    tmp = pCardInfo->SD_csd.CSD[0];
    pCardInfo->SD_csd.CSDStruct = (uint8_t)((tmp & 0xC0) >> 6);
    pCardInfo->SD_csd.SysSpecVersion = (uint8_t)((tmp & 0x3C) >> 2);
    pCardInfo->SD_csd.Reserved1 = tmp & 0x03;
    /* Byte 1 */
    tmp = pCardInfo->SD_csd.CSD[1];
    pCardInfo->SD_csd.TAAC = (uint8_t)tmp;
    /* Byte 2 */
    tmp = pCardInfo->SD_csd.CSD[2];
    pCardInfo->SD_csd.NSAC = (uint8_t)tmp;
    /* Byte 3 */
    tmp = pCardInfo->SD_csd.CSD[3];
    pCardInfo->SD_csd.MaxBusClkFrec = (uint8_t)tmp;
    /* Byte 4 */
    tmp = pCardInfo->SD_csd.CSD[4];
    pCardInfo->SD_csd.CardComdClasses = (uint16_t)(tmp << 4);
    /* Byte 5 */
    tmp = pCardInfo->SD_csd.CSD[5];
    pCardInfo->SD_csd.CardComdClasses |= (uint16_t)((tmp & 0xF0) >> 4);
    pCardInfo->SD_csd.RdBlockLen = (uint8_t)(tmp & 0x0F);
    /* Byte 6 */
    tmp = pCardInfo->SD_csd.CSD[6];
    pCardInfo->SD_csd.PartBlockRead = (uint8_t)((tmp & 0x80) >> 7);
    pCardInfo->SD_csd.WrBlockMisalign = (uint8_t)((tmp & 0x40) >> 6);
    pCardInfo->SD_csd.RdBlockMisalign = (uint8_t)((tmp & 0x20) >> 5);
    pCardInfo->SD_csd.DSRImpl = (uint8_t)((tmp & 0x10) >> 4);
    pCardInfo->SD_csd.Reserved2 = 0; /*!< Reserved */

    if ((pCardInfo->CardType == SD_TYPE_V1) || (pCardInfo->CardType == SD_TYPE_V2)) {
        pCardInfo->SD_csd.DeviceSize = (tmp & 0x03) << 10;
        /* Byte 7 */
        tmp = pCardInfo->SD_csd.CSD[7];
        pCardInfo->SD_csd.DeviceSize |= (tmp) << 2;
        /* Byte 8 */
        tmp = pCardInfo->SD_csd.CSD[8];
        pCardInfo->SD_csd.DeviceSize |= (tmp & 0xC0) >> 6;
        pCardInfo->SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
        pCardInfo->SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);
        /* Byte 9 */
        tmp = pCardInfo->SD_csd.CSD[9];
        pCardInfo->SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
        pCardInfo->SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
        pCardInfo->SD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
        /* Byte 10 */
        tmp = pCardInfo->SD_csd.CSD[10];
        pCardInfo->SD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;

        pCardInfo->CardCapacity = (pCardInfo->SD_csd.DeviceSize + 1);
        pCardInfo->CardCapacity *= (1 << (pCardInfo->SD_csd.DeviceSizeMul + 2));
        pCardInfo->CardBlockSize = 1 << (pCardInfo->SD_csd.RdBlockLen);
        pCardInfo->CardCapacity *= pCardInfo->CardBlockSize;
    } else if (pCardInfo->CardType == SD_TYPE_V2HC) {
        /* Byte 7 */
        tmp = pCardInfo->SD_csd.CSD[7];
        pCardInfo->SD_csd.DeviceSize = (tmp & 0x3F) << 16;
        /* Byte 8 */
        tmp = pCardInfo->SD_csd.CSD[8];
        pCardInfo->SD_csd.DeviceSize |= (tmp << 8);
        /* Byte 9 */
        tmp = pCardInfo->SD_csd.CSD[9];
        pCardInfo->SD_csd.DeviceSize |= (tmp);
        /* Byte 10 */
        tmp = pCardInfo->SD_csd.CSD[10];

        pCardInfo->CardCapacity = (uint64_t)((((uint64_t)pCardInfo->SD_csd.DeviceSize + 1)) * 512 * 1024);
        pCardInfo->CardBlockSize = 512;
    } else {
        /* Not supported card type */
    }

    pCardInfo->SD_csd.EraseGrSize = (tmp & 0x40) >> 6;
    pCardInfo->SD_csd.EraseGrMul = (tmp & 0x3F) << 1;
    /* Byte 11 */
    tmp = pCardInfo->SD_csd.CSD[11];
    pCardInfo->SD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
    pCardInfo->SD_csd.WrProtectGrSize = (tmp & 0x7F);
    /* Byte 12 */
    tmp = pCardInfo->SD_csd.CSD[12];
    pCardInfo->SD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
    pCardInfo->SD_csd.ManDeflECC = (tmp & 0x60) >> 5;
    pCardInfo->SD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
    pCardInfo->SD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;
    /* Byte 13 */
    tmp = pCardInfo->SD_csd.CSD[13];
    pCardInfo->SD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
    pCardInfo->SD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
    pCardInfo->SD_csd.Reserved3 = 0;
    pCardInfo->SD_csd.ContentProtectAppli = (tmp & 0x01);
    /* Byte 14 */
    tmp = pCardInfo->SD_csd.CSD[14];
    pCardInfo->SD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
    pCardInfo->SD_csd.CopyFlag = (tmp & 0x40) >> 6;
    pCardInfo->SD_csd.PermWrProtect = (tmp & 0x20) >> 5;
    pCardInfo->SD_csd.TempWrProtect = (tmp & 0x10) >> 4;
    pCardInfo->SD_csd.FileFormat = (tmp & 0x0C) >> 2;
    pCardInfo->SD_csd.ECC = (tmp & 0x03);
    /* Byte 15 */
    tmp = pCardInfo->SD_csd.CSD[15];
    pCardInfo->SD_csd.CSD_CRC = (tmp & 0xFE) >> 1;
    pCardInfo->SD_csd.Reserved4 = 1;

    /* Byte 0 */
    tmp = pCardInfo->SD_cid.CID[0];
    pCardInfo->SD_cid.ManufacturerID = tmp;
    /* Byte 1 */
    tmp = pCardInfo->SD_cid.CID[1];
    pCardInfo->SD_cid.OEM_AppliID = tmp << 8;
    /* Byte 2 */
    tmp = pCardInfo->SD_cid.CID[2];
    pCardInfo->SD_cid.OEM_AppliID |= tmp;
    /* Byte 3 */
    tmp = pCardInfo->SD_cid.CID[3];
    pCardInfo->SD_cid.ProdName1 = tmp << 24;
    /* Byte 4 */
    tmp = pCardInfo->SD_cid.CID[4];
    pCardInfo->SD_cid.ProdName1 |= tmp << 16;
    /* Byte 5 */
    tmp = pCardInfo->SD_cid.CID[5];
    pCardInfo->SD_cid.ProdName1 |= tmp << 8;
    /* Byte 6 */
    tmp = pCardInfo->SD_cid.CID[6];
    pCardInfo->SD_cid.ProdName1 |= tmp;
    /* Byte 7 */
    tmp = pCardInfo->SD_cid.CID[7];
    pCardInfo->SD_cid.ProdName2 = tmp;
    /* Byte 8 */
    tmp = pCardInfo->SD_cid.CID[8];
    pCardInfo->SD_cid.ProdRev = tmp;
    /* Byte 9 */
    tmp = pCardInfo->SD_cid.CID[9];
    pCardInfo->SD_cid.ProdSN = tmp << 24;
    /* Byte 10 */
    tmp = pCardInfo->SD_cid.CID[10];
    pCardInfo->SD_cid.ProdSN |= tmp << 16;
    /* Byte 11 */
    tmp = pCardInfo->SD_cid.CID[11];
    pCardInfo->SD_cid.ProdSN |= tmp << 8;
    /* Byte 12 */
    tmp = pCardInfo->SD_cid.CID[12];
    pCardInfo->SD_cid.ProdSN |= tmp;
    /* Byte 13 */
    tmp = pCardInfo->SD_cid.CID[13];
    pCardInfo->SD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
    pCardInfo->SD_cid.ManufactDate = (tmp & 0x0F) << 8;
    /* Byte 14 */
    tmp = pCardInfo->SD_cid.CID[14];
    pCardInfo->SD_cid.ManufactDate |= tmp;
    /* Byte 15 */
    tmp = pCardInfo->SD_cid.CID[16];
    pCardInfo->SD_cid.CID_CRC = (tmp & 0xFE) >> 1;
    pCardInfo->SD_cid.Reserved2 = 1;
    return 0;
}

/****************************************************************************/ /**
 * @brief  SD_ReadSingleBlock
 *
 *
*******************************************************************************/
uint8_t SD_ReadBlock(uint32_t sector, uint8_t *buffer, uint32_t num)
{
    uint8_t rx;

    SD_SPI_MSG("SD SPI Read Block Start,sector:%d, num:%d, buff:0x%08X\r\n", sector, num, (uint32_t)(uintptr_t)buffer);

    SPI_CS_WriteBit(0);

    /* Waiti for free */
    if (SD_GetResponse(0xFF)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("sd send err: bus busy,timeout\r\n");
        return ERROR;
    }

    /* sector to byte */
    if (SD_CardInfo.CardType != SD_TYPE_V2HC) {
        sector = sector << 9;
    }

    if (num == 1) {
        rx = SD_SendCommand_NoDeassert(CMD17, sector, 0);

        if (rx) {
            SD_SPI_MSG("SD CMD17 err:0x%02X\r\n", rx);
            return rx;
        }

        rx = SD_ReceiveData(buffer, 512, RELEASE);

        if (rx != 0) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD single read err:0x%02X\r\n", rx);
            return rx;
        }
    } else if (num > 1) {
        rx = SD_SendCommand_NoDeassert(CMD18, sector, 0);

        if (rx) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD CMD18 err:0x%02X\r\n", rx);
            return rx;
        }

        while (num--) {
            rx = SD_ReceiveData(buffer, 512, NO_RELEASE);

            if (rx != 0) {
                SPI_CS_WriteBit(1);
                SD_SPI_MSG("SD multi read err:0x%02X\r\n", rx);
                return rx;
            }

            buffer += 512;
        }

        rx = SD_SendCommand(CMD12, 0, 0);
    }

    SD_SPI_MSG("SD SPI Read Block Succeed!\r\n");
    return SUCCESS;
}
/****************************************************************************/ /**
 * @brief  SD_WriteSingleBlock
 *
 *
*******************************************************************************/
uint8_t SD_WriteBlock(uint32_t sector, uint8_t *data, uint32_t num)
{
    uint8_t rx;

    SD_SPI_MSG("SD SPI Write Block Start,sector:%d, num:%d, buff:0x%08X\r\n", sector, num, (uint32_t)(uintptr_t)data);

    SPI_CS_WriteBit(0);

    /* Waiti for free */
    if (SD_GetResponse(0xFF)) {
        SPI_CS_WriteBit(1);
        SD_SPI_MSG("sd send err: bus busy,timeout\r\n");
        return ERROR;
    }

    /* sector to byte */
    if (SD_CardInfo.CardType != SD_TYPE_V2HC) {
        sector = sector << 9;
    }

    if (num == 1) {
        rx = SD_SendCommand_NoDeassert(CMD24, sector, 0);

        if (rx) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD CMD24 err:%d\r\n", rx);
            return rx;
        }

        rx = SD_SendData(data, 512, 0xFE);

        if (rx) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD single write err:0x%X\r\n", rx);
            return rx;
        }
    } else if (num > 1) {
        if (SD_CardInfo.CardType != SD_TYPE_MMC) {
            rx = SD_SendCommand_NoDeassert(CMD55, 0, 0);

            if (rx == 0) {
                rx = SD_SendCommand_NoDeassert(ACMD23, num, 0);
            }

            if (rx != 0) {
                SD_SPI_MSG("SD ACMD23 err:%d\r\n", rx);
                return rx;
            }
        }

        rx = SD_SendCommand_NoDeassert(CMD25, sector, 0);

        if (rx != 0) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD CMD25 err:%d\r\n", rx);
            return rx;
        }

        do {
            rx = SD_SendData(data, 512, 0xFC);
            data += 512;
        } while (--num && rx == 0);

        SD_SendData(NULL, 0, 0xFD);

        if (rx) {
            SPI_CS_WriteBit(1);
            SD_SPI_MSG("SD multi write err:0x%X\r\n", rx);
            return rx;
        }
    }

    SD_SPI_MSG("SD SPI Write Block Succeed!\r\n");

    SPI_CS_WriteBit(1);
    SPI_ReadByte(&rx, 1);
    return 0;
}
/****************************************************************************/ /**
 * @brief  SD init
 *
 *
 *
 *
*******************************************************************************/
uint8_t SD_Init(SD_CardInfoTypedef *pCardInfo)
{
    uint8_t rx;
    uint8_t rxbuff[6];
    uint16_t i;
    uint32_t time_node;

    SD_SPI_Init();

    SPI_CS_WriteBit(1);
    /* low speed */
    SD_SPI_SetSpeed(SD_SPI_SPEED_IDEL);

    if (SD_Idle_Sta()) {
        return ERROR;
    }

    /* send CMD8 */
    rx = SD_SendCommand_NoDeassert(CMD8, 0x1aa, 0x87);

    /* sd card v1.0 */
    if (rx == 0x05) {
        pCardInfo->CardType = SD_TYPE_V1;
        SPI_CS_WriteBit(1);
        SPI_ReadByte(&rx, 1);

        time_node = (uint32_t)bflb_platform_get_time_ms();
        /* send CMD55+CMD41  sd init */
        do {
            rx = SD_SendCommand(CMD55, 0, 0);
            if (rx != 0x01) {
                SD_SPI_MSG("sdv1 CMD55 err:%d\r\n", rx);
                return rx;
            }
            rx = SD_SendCommand(ACMD41, 0x00000000, 0);

            if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
                break;
            }

        } while (rx != 0x00);

        /* mmc card init */
        if (rx != 0x00) {
            time_node = (uint32_t)bflb_platform_get_time_ms();
            do {
                rx = SD_SendCommand(CMD1, 0, 0);

                if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
                    break;
                }
            } while (rx != 0x00);

            if (rx != 0x00) {
                SD_SPI_MSG("sdv2 CMD1 timeout err:%d\r\n", rx);
                return ERROR;
            } else {
                pCardInfo->CardType = SD_TYPE_MMC;
            }
        }

        /* high speed */
        SD_SPI_SetSpeed(SD_SPI_SPEED_HIGH);
        SPI_ReadByte(&rx, 1);

        /* set sector size */
        rx = SD_SendCommand(CMD16, 512, 0xff);

        if (rx != 0x00) {
            SD_SPI_MSG("sdv1 CMD16 err:%d\r\n", rx);
            return rx;
        }
    }
    /* sd card v2.0 */
    else if (rx == 0x01) {
        SPI_ReadByte(rxbuff, 4);
        SPI_CS_WriteBit(1);

        /* next 8 clocks */
        SPI_ReadByte(&rx, 1);
        SPI_ReadByte(&rx, 1);

        /* 2.7V - 3.6V */
        if (rxbuff[2] == 0x01 && rxbuff[3] == 0xAA) {
            time_node = (uint32_t)bflb_platform_get_time_ms();
            do {
                rx = SD_SendCommand(CMD55, 0, 0);
                if (rx != 0x01) {
                    SD_SPI_MSG("sdv2 CMD55 err:%d\r\n", rx);
                    return rx;
                }
                rx = SD_SendCommand_NoDeassert(ACMD41, 0x40000000, 0);
                SPI_ReadByte(rxbuff, 4);
                SPI_CS_WriteBit(1);

                if ((uint32_t)bflb_platform_get_time_ms() - time_node > SD_SPI_TIMEOUT_MS) {
                    SD_SPI_MSG("sdv2 ACMD41 timeout err:%d\r\n", rx);
                    return rx;
                }
            } while (rx != 0);

            /* send CMD58 */
            rx = SD_SendCommand_NoDeassert(CMD58, 0, 0);

            if (rx != 0x00) {
                SD_SPI_MSG("sdv2 CMD58 err:%d\r\n", rx);
                return rx;
            }

            /* get OCR */
            SPI_ReadByte(rxbuff, 4);
            SPI_CS_WriteBit(1);

            SPI_ReadByte(&rx, 1);

            /* bit32 CCS: 1-SDHC  0-SD2.0 */
            if (rxbuff[0] & 0x40) {
                pCardInfo->CardType = SD_TYPE_V2HC;
                SD_SPI_MSG("SD v2.0 SDHC/SDXC success\r\n");
            } else {
                pCardInfo->CardType = SD_TYPE_V2;
                SD_SPI_MSG("SD v2.0 SDSC success\r\n");
            }

            /* set sector size */
            rx = SD_SendCommand(CMD16, 512, 0xff);

            if (rx != 0x00) {
                SD_SPI_MSG("sdv1 CMD16 err:%d\r\n", rx);
            }

            /* high speed */
            SD_SPI_SetSpeed(SD_SPI_SPEED_HIGH);
            SPI_ReadByte(&rx, 1);
        }
    } else {
        return 1;
    }

    SD_SPI_MSG("sd init success\r\n");

    SD_Get_CardInfo(pCardInfo);

    SD_SPI_MSG(" sd csd:");

    for (i = 0; i < 4; i++) {
        SD_SPI_MSG("0x%02X ", pCardInfo->SD_csd.CSD[i]);
    }
    SD_SPI_MSG("...\r\n");

    SD_SPI_MSG(" sd cid:");
    for (i = 0; i < 4; i++) {
        SD_SPI_MSG("0x%02X ", pCardInfo->SD_cid.CID[i]);
    }
    SD_SPI_MSG("...\r\n");

    SD_SPI_MSG("SD Card Block Size:%d Byte\r\n", (pCardInfo->CardBlockSize));
    SD_SPI_MSG("SD Card Capacity:%lld MByte\r\n", (SD_CardInfo.CardCapacity / 1024 / 1024));

    return 0;
}
