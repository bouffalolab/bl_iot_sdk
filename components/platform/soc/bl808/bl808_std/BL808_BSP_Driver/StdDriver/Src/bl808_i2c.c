/*
 * Copyright (c) 2016-2023 Bouffalolab.
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
#include <bl808.h>

#include "bl808_i2c.h"
#include "bl808_clock.h"
#undef  DEBUG_MODULE
#define DEBUG_MODULE 0
//#define MMI2C_DEBUG_MSG

#define I2C_SPEED_STANDARD_CLK  100000
#define I2C_SPEED_FAST_CLK      400000
#define I2C_SPEED_HIGH_CLK      1000000


static const uint32_t  i2cAddr[2] = {I2C0_BASE,I2C1_BASE};


/****************************************************************************//**
 * @brief  I2C interrupt handle
 *
 * @param  intPeriph: Select the peripheral, such as INT_I2C0,INT_I2C1,INT_I2C2
 * @param  i2cNo: Select the I2C port
 *
 * @return None
 *
*******************************************************************************/
void I2C_IntHandler(IRQn_Type intPeriph, I2C_ID_Type i2cNo)
{

}


/****************************************************************************//**
 * @brief  Initializes the I2C to Master
 *
 * @param  i2cNo: I2C ID Type
 * @param  i2cCfgStruct: Pointer to I2C CFG Type
 *
 * @return None
 *
*******************************************************************************/

void I2C_MasterInit(I2C_ID_Type i2cNo, I2C_CFG_Type* i2cCfgStruct)
{
	uint32_t I2Cx;
	uint32_t tmpVal;
    uint32_t phase_cycles;

	/* Check the parameters */
	CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
	CHECK_PARAM(IS_I2C_SPEEDMODE_TYPE(i2cCfgStruct->speedMode));

	I2Cx = i2cAddr[i2cNo];

    /* Configure I2C speed mode */
    switch(i2cCfgStruct->speedMode)
    {
        case I2C_SPEED_STANDARD:
            /* evenly spread the cycles to 4 phases */
            phase_cycles = i2cCfgStruct->srcClk / I2C_SPEED_STANDARD_CLK / 4;
            break;
        case I2C_SPEED_FAST:
            /* evenly spread the cycles to 4 phases */
            phase_cycles = i2cCfgStruct->srcClk / I2C_SPEED_FAST_CLK / 4;
            break;
        case I2C_SPEED_HIGH:
            /* evenly spread the cycles to 4 phases */
            phase_cycles = i2cCfgStruct->srcClk / I2C_SPEED_HIGH_CLK / 4;
            break;
		default:
            /* evenly spread the cycles to 4 phases */
            phase_cycles = i2cCfgStruct->srcClk / I2C_SPEED_STANDARD_CLK / 4;
            break;
    }

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_START);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_0, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_1, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_START, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_STOP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_0, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_1, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_STOP, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_DATA);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_0, phase_cycles - 1);
    /* Compensate i2c clk for lantency by prd_d_ph_1 */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_1, phase_cycles - 16);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_DATA, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_DEG_EN);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
#if (BL80X_HW_VER <= BL80X_HW_A0)
    /* enable i2c interrupt */
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_INT_EN);
#else
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_RXF_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_TXF_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_CLR);
#endif
    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_RX_FIFO_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_TX_FIFO_CLR);
    BL_WR_REG(I2Cx, I2C_FIFO_CONFIG_0, tmpVal);
#if (BL80X_HW_VER <= BL80X_HW_A0)
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_RX_FIFO_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_TX_FIFO_CLR);
    BL_WR_REG(I2Cx, I2C_FIFO_CONFIG_0, tmpVal);
#endif
}

#ifdef A0_AUDIO_TEST
/****************************************************************************//**
 * @brief  Initializes the I2C to Master for a0 board 8311 chip only
 *
 * @param  i2cNo: I2C ID Type
 * @param  i2cCfgStruct: Pointer to I2C CFG Type
 *
 * @return None
 *
*******************************************************************************/
void I2C_MasterInit_For_8311(I2C_ID_Type i2cNo, I2C_CFG_Type* i2cCfgStruct)
{
	uint32_t I2Cx;
	uint32_t tmpVal;
    uint32_t phase_cycles;

	/* Check the parameters */
	CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
	CHECK_PARAM(IS_I2C_SPEEDMODE_TYPE(i2cCfgStruct->speedMode));

	I2Cx = i2cAddr[i2cNo];

    /* Configure I2C speed mode */
    phase_cycles = 0x0a;

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_START);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_0, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_1, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_START, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_STOP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_0, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_1, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_STOP, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_DATA);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_0, phase_cycles - 1);
    /* Compensate i2c clk for lantency by prd_d_ph_1 */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_1, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_2, phase_cycles - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_3, phase_cycles - 1);
    BL_WR_REG(I2Cx, I2C_PRD_DATA, tmpVal);
}
#endif

/****************************************************************************//**
 * @brief  Initializes the I2C config struct
 *
 * @param  cfg: Pointer to I2C CFG Type
 *
 * @return None
 *
*******************************************************************************/
extern uint32_t SystemCoreClock;
void I2C_SetDefaultConfig(I2C_CFG_Type* cfg)
{
#if (BL80X_HW_VER <= BL80X_HW_A0)
    cfg->srcClk = 80 * 1000 * 1000;         /* clk source from bclk, which is 80M by default */
#else
    cfg->srcClk = 40 * 1000 * 1000;         /* clk on asic using xtal by default */
#endif

	cfg->speedMode = I2C_SPEED_STANDARD;
	cfg->interrupt = 0;
	cfg->fifoEnable = (BL_Fun_Type)0;
	cfg->DMAEnable = (BL_Fun_Type)0;
	cfg->slaveAddress = 0;
	cfg->transferDirection = I2C_WRITE;
	cfg->subAddressSize = 0;
	cfg->subAddress = 0;
	cfg->data = 0;
	cfg->dataSize = 0;
}

/****************************************************************************//**
 * @brief      Enable the I2C
 *
 * @param[in]  i2cNo:  Select the I2C port, should be I2C0_PORT, I2C1_PORT.
 *
 * @return none
 *
 *******************************************************************************/
void I2C_Enable(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_M_EN);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);
}

/****************************************************************************//**
 * @brief      Disable the I2C
 *
 * @param[in]  i2cNo:  Select the I2C port, should be I2C0_PORT, I2C1_PORT.
 *
 * @return none
 *
 *******************************************************************************/
void I2C_Disable(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_M_EN);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    /* clear i2c interrupt status */
#if (BL80X_HW_VER <= BL80X_HW_A0)
    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_INT_EN);
    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_INT_EN);
    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);
#else
    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_END_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_NAK_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_ARB_CLR);
    BL_WR_REG(I2Cx, I2C_INT_STS, tmpVal);
#endif

    tmpVal = BL_RD_REG(I2Cx, I2C_FIFO_CONFIG_0);
#ifndef A0_AUDIO_TEST
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_TX_FIFO_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_RX_FIFO_CLR);
    BL_WR_REG(I2Cx, I2C_FIFO_CONFIG_0, tmpVal);
#endif

#if (BL80X_HW_VER <= BL80X_HW_A0)
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_TX_FIFO_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_RX_FIFO_CLR);
    BL_WR_REG(I2Cx, I2C_FIFO_CONFIG_0, tmpVal);
#endif
}

BL_Sts_Type I2C_Is_Busy(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

#if (BL80X_HW_VER <= BL80X_HW_A0)
    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);
#else
    tmpVal = BL_RD_REG(I2Cx, I2C_BUS_BUSY);
#endif
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_STS_I2C_BUS_BUSY)) ? SET: RESET);
}

BL_Sts_Type I2C_Is_Intr_Set(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);

    return ((tmpVal & 0x3F) ? SET: RESET);
}

BL_Sts_Type I2C_Is_Nack_Set(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);

#if (BL80X_HW_VER <= BL80X_HW_A0)
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_STS_I2C_GOT_NACK)) ? SET: RESET);
#else
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_NAK_INT)) ? SET: RESET);
#endif
}

BL_Sts_Type I2C_Is_Trans_End_int_Set(I2C_ID_Type i2cNo)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_INT_STS);

#if (BL80X_HW_VER <= BL80X_HW_A0)
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_STS_I2C_INT)) ? SET: RESET);
#else
    return ((BL_IS_REG_BIT_SET(tmpVal, I2C_END_INT)) ? SET: RESET);
#endif
}

#if (BL80X_HW_VER <= BL80X_HW_A0)
BL_Err_Type I2C_MasterSendBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    BL_Err_Type ret = SUCCESS;
	uint32_t cnt;
    uint32_t pkt_data = 0;
    uint8_t *pkt_ptr = (uint8_t*)&pkt_data;
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
	CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
	CHECK_PARAM(cfg->subAddressSize + cfg->dataSize <= 4);  /* fit into one packet */

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SLV_ADDR, cfg->slaveAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_NUM, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_DIR, 0x0E);     /* write dir for packet 0 */
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    /* write packet len = subAddr size + data size */
    tmpVal = BL_RD_REG(I2Cx, I2C_PKT_LEN_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_0_LEN, cfg->subAddressSize + cfg->dataSize - 1);
    BL_WR_REG(I2Cx, I2C_PKT_LEN_0, tmpVal);

#ifdef A0_AUDIO_TEST
    I2C_Enable(i2cNo);
#endif

    cnt = 0;
    while (cnt < cfg->subAddressSize) {
	    *pkt_ptr++ = *(cfg->subAddress + cnt);
        cnt++;
    }

    cnt = 0;
    while (cnt < cfg->dataSize) {
	    *pkt_ptr++ = *(cfg->data + cnt);
        cnt++;
    }

    /* write out packet */
    BL_WR_REG(I2Cx, I2C_FIFO_WDATA, pkt_data);

#ifdef A0_AUDIO_TEST
    while(I2C_Is_Busy(i2cNo));
#else
    /* kick off command */
    I2C_Enable(i2cNo);

    while (!I2C_Is_Trans_End_int_Set(i2cNo));
#endif

    if(I2C_Is_Nack_Set(i2cNo) == SET) {
        ret =  ERROR;
    }

    I2C_Disable(i2cNo);
    return ret;
}

BL_Err_Type I2C_MasterReceiveBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    BL_Err_Type ret = SUCCESS;
    uint32_t cnt;
    uint32_t pkt_data;
    uint8_t *pkt_ptr;
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));
    CHECK_PARAM(cfg->subAddressSize <= 4);  /* fit into one packet */
    CHECK_PARAM(cfg->dataSize <= 4);        /* fit into one packet */

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SLV_ADDR, cfg->slaveAddr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_NUM, 1);    /* two packets */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_DIR, 0x0E); /* write dir for packet 0, read dir for packet 1 */
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    tmpVal = BL_RD_REG(I2Cx, I2C_PKT_LEN_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_0_LEN, cfg->subAddressSize - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_1_LEN, cfg->dataSize - 1);
    BL_WR_REG(I2Cx, I2C_PKT_LEN_0, tmpVal);

    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;
    while (cnt < cfg->subAddressSize) {
        *pkt_ptr++ = *(uint8_t*)(cfg->subAddress + cnt);
        cnt++;
    }

    /* write out packet */
    BL_WR_REG(I2Cx, I2C_FIFO_WDATA, pkt_data);

    /* kick off command */
    I2C_Enable(i2cNo);

    while (!I2C_Is_Trans_End_int_Set(i2cNo));

    if(I2C_Is_Nack_Set(i2cNo) == SET) {
        ret = ERROR;
    }

    /* read the packet */
    pkt_data = BL_RD_REG(I2Cx, I2C_FIFO_RDATA);

    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;

    while (cnt < cfg->dataSize) {
		*(cfg->data+cnt) = *pkt_ptr++;
        cnt++;
    }

    I2C_Disable(i2cNo);
    return ret;
}

int I2C_Write_Byte(I2C_ID_Type i2cNo, uint8_t slv_addr, uint8_t val)
{
    int ret = 0;

	/* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

	i2c_reg_t *i2c_reg = (i2c_reg_t *)(i2cAddr[i2cNo]);

    CHECK_CONDITION(i2c_reg->i2c_fifo_config_1.BF.tx_fifo_cnt == 16);
    CHECK_CONDITION(i2c_reg->i2c_fifo_config_1.BF.rx_fifo_cnt == 0);

    i2c_reg->i2c_config.BF.cr_i2c_slv_addr = slv_addr;      /* slave address */
    i2c_reg->i2c_config.BF.cr_i2c_pkt_num = 0;              /* one packet */
    i2c_reg->i2c_config.BF.cr_i2c_pkt_dir = 0xE;            /* write packet */

    i2c_reg->i2c_pkt_len_0.BF.cr_i2c_pkt_0_len = 0;         /* write 1 bytes */

    i2c_reg->i2c_fifo_wdata.WORD = (uint32_t)val;

    /* kick off command */
    i2c_reg->i2c_config.BF.cr_i2c_m_en = 1;

    //while(I2C_Is_Busy(i2cNo));
    while (i2c_reg->i2c_int_sts.BF.sts_i2c_int == 0);

    if (i2c_reg->i2c_int_sts.BF.sts_i2c_got_nack) {
        BL_LOGE("I2C[%d] write ACKNAK Error!\r\n", i2cNo);
        ret = -1;
    }

    if (i2c_reg->i2c_int_sts.BF.sts_i2c_arb_lost) {
        BL_LOGE("I2C[%d] write Arbitration Error!\r\n", i2cNo);
        ret = -1;
    }

    /* disable I2C */
    i2c_reg->i2c_config.BF.cr_i2c_m_en = 0;

    /* clear i2c interrupt status */
    i2c_reg->i2c_int_sts.BF.cr_i2c_int_en = 0;
    i2c_reg->i2c_int_sts.BF.cr_i2c_int_en = 1;

    /* clear tx/rx fifo */
    i2c_reg->i2c_fifo_config_0.BF.tx_fifo_clr = 1;
    i2c_reg->i2c_fifo_config_0.BF.tx_fifo_clr = 0;
    i2c_reg->i2c_fifo_config_0.BF.rx_fifo_clr = 1;
    i2c_reg->i2c_fifo_config_0.BF.rx_fifo_clr = 0;

    return ret;
}
#else
BL_Err_Type I2C_MasterSendBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    BL_Err_Type ret = SUCCESS;
	uint32_t cnt;
    uint32_t pkt_data = 0;
    uint8_t *pkt_ptr;
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;
#ifdef MMI2C_DEBUG_MSG
    printf("I2C_MasterSendBlocking \r\n");
#endif
    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SLV_ADDR, cfg->slaveAddr);
    if (cfg->subAddressSize > 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_SUB_ADDR_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SUB_ADDR_BC, cfg->subAddressSize - 1);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_SUB_ADDR_EN);
    }
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2C_CR_I2C_PKT_DIR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_LEN, cfg->dataSize - 1);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);
#ifdef MMI2C_DEBUG_MSG
    printf("I2C_CONFIG \r\n");
#endif
    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;
    while (cnt < cfg->subAddressSize) {
	    *pkt_ptr++ = *(cfg->subAddress + cnt);
        cnt++;
    }
    BL_WR_REG(I2Cx, I2C_SUB_ADDR, pkt_data);

    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;
    while (cnt < cfg->dataSize) {
	    *pkt_ptr++ = *(cfg->data + cnt);
        cnt++;
    }
    BL_WR_REG(I2Cx, I2C_FIFO_WDATA, pkt_data);
#ifdef MMI2C_DEBUG_MSG
    printf("I2C_FIFO_WDATA \r\n");
#endif
    /* kick off command */
    I2C_Enable(i2cNo);
#ifdef MMI2C_DEBUG_MSG
    printf("I2C_Enable \r\n");
#endif
    while (!I2C_Is_Trans_End_int_Set(i2cNo));
#ifdef MMI2C_DEBUG_MSG
    printf("I2C_Is_Trans_End_int_Set \r\n");
#endif
    //BL808_Delay_US(100);    /* TODO: temp workaround for delayed NACK signal */
    if(I2C_Is_Nack_Set(i2cNo)) {
        ret = ERROR;
    }

    I2C_Disable(i2cNo);
    return ret;
}

BL_Err_Type I2C_MasterReceiveBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg)
{
    BL_Err_Type ret = SUCCESS;
    uint32_t cnt;
    uint32_t pkt_data = 0;
    uint8_t *pkt_ptr;
    uint32_t tmpVal;
    uint32_t I2Cx = i2cNo ? I2C1_BASE: I2C0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    tmpVal = BL_RD_REG(I2Cx, I2C_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SLV_ADDR, cfg->slaveAddr);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_SUB_ADDR_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_SUB_ADDR_BC, cfg->subAddressSize - 1);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2C_CR_I2C_PKT_DIR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PKT_LEN, cfg->dataSize - 1);
    BL_WR_REG(I2Cx, I2C_CONFIG, tmpVal);

    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;
    while (cnt < cfg->subAddressSize) {
        *pkt_ptr++ = *(cfg->subAddress + cnt);
        cnt++;
    }
    BL_WR_REG(I2Cx, I2C_SUB_ADDR, pkt_data);

    /* kick off command */
    I2C_Enable(i2cNo);

    while (!I2C_Is_Trans_End_int_Set(i2cNo));

    if(I2C_Is_Nack_Set(i2cNo)) {
        ret = ERROR;
    }

    /* read the packet */
    pkt_data = BL_RD_REG(I2Cx, I2C_FIFO_RDATA);

    cnt = 0;
    pkt_ptr = (uint8_t*)&pkt_data;
    while (cnt < cfg->dataSize) {
		*(cfg->data+cnt) = *pkt_ptr++;
        cnt++;
    }

    I2C_Disable(i2cNo);
    return ret;
}
#endif

void I2C_SetPrd(I2C_ID_Type i2cNo, uint8_t phase)
{
    uint32_t tmpVal;
    uint32_t I2Cx = i2cAddr[i2cNo];

    /* Check the parameters */
    CHECK_PARAM(IS_I2C_ID_TYPE(i2cNo));

    //phase_cycles = (32000000 / phase / 4) - 1;
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_START);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_S_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_START, tmpVal);
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_STOP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_P_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_STOP, tmpVal);
    tmpVal = BL_RD_REG(I2Cx, I2C_PRD_DATA);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_0, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_1, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_2, phase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2C_CR_I2C_PRD_D_PH_3, phase);
    BL_WR_REG(I2Cx, I2C_PRD_DATA, tmpVal);
}

void I2C_DSP0_ClockSet(I2C_ID_Type i2cNo, uint32_t clk)
{
    uint32_t bclk = 0;

    bclk = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MM_BCLK);
    printf("BL_SYSTEM_CLOCK_MM_BCLK   %d\r\n", bclk);

    if (clk >= 100000) {
        GLB_Set_DSP_I2C0_CLK(1, 1, 1, 0);
        I2C_SetPrd(i2cNo, bclk / (clk * 4) - 1);
    } else if (clk >= 8000) {
        GLB_Set_DSP_I2C0_CLK(1, 1, 1, 9);
        I2C_SetPrd(i2cNo, bclk / 10 / (clk * 4) - 1);
    } else if (clk >= 800) {
        GLB_Set_DSP_I2C0_CLK(1, 1, 1, 99);
        I2C_SetPrd(i2cNo, bclk / 100 / (clk * 4) - 1);
    } else {
        GLB_Set_DSP_I2C0_CLK(1, 1, 1, 255);
        I2C_SetPrd(i2cNo, bclk / 256 / (clk * 4) - 1);
    }
}


/****************************************************************************//**
 * @brief  I2C0 interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BL60X_USE_HAL_DRIVER
void I2C0_IRQHandler(void)
{
   I2C_IntHandler(I2C0_IRQn, I2C0_ID);
}
#endif

/****************************************************************************//**
 * @brief  I2C1 interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BL60X_USE_HAL_DRIVER
void I2C1_IRQHandler(void)
{
   I2C_IntHandler(I2C1_IRQn, I2C1_ID);
}
#endif

/*@} end of group I2C_Public_Functions */

/*@} end of group I2C */

/*@} end of group BL60x_Peripheral_Driver */
