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
#ifndef __BL60X_I2C_H__
#define __BL60X_I2C_H__

#include "bl808_common.h"

#if (BL80X_HW_VER <= BL80X_HW_A0)
#include "i2c_reg_a0.h"
#else
#include "i2c_reg.h"
#endif

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2C
 *  @{
 */

/** @defgroup  I2C_Public_Types
 *  @{
 */

/**
 *  @brief I2C No. type definition
 */
typedef enum {
    I2C0_ID = 0, /*!< I2C0 define */
    I2C1_ID = 1, /*!< I2C1 define */
    I2C2_ID = 2, /*!< I2C2 define */
    I2C3_ID = 3, /*!< I2C3 define */
    I2C_ID_MAX,  /*!< I2C max define */
} I2C_ID_Type;

/**
 *  @brief I2C speed mode type definition
 */
typedef enum {
    I2C_SPEED_STANDARD = 0,                  /*!< I2C standard speed mode define */
    I2C_SPEED_FAST,                          /*!< I2C fast speed mode define */
    I2C_SPEED_HIGH,                          /*!< I2C high speed mode define */
}I2C_SpeedMode_Type;

/**
 *  @brief I2C read/write type definition
 */
typedef enum {
    I2C_WRITE = 0,                           /*!< I2C write direction */
    I2C_READ,                                /*!< I2C read direction */
}I2C_Direction_Type;

/**
 *  @brief I2C interrupt type definition
 */
typedef enum {
    I2C_INT_STATUS,                          /*!< I2C interrupt status */
    I2C_INT_ALL,                             /*!< I2C interrupt all type */
}I2C_INT_Type;

/**
 *  @brief I2C enable start or stop definition
 */
typedef struct {
    uint8_t len0;                            /*!< Length of START condition phase 0 */
    uint8_t len1;                            /*!< Length of START condition phase 1 */
    uint8_t len2;                            /*!< Length of START condition phase 2 */
    uint8_t len3;                            /*!< Length of START condition phase 3 */
}I2C_Start_Condition_Phase_Type;

/**
 *  @brief I2C Configuration Structure type definition
 */
typedef struct {
    uint32_t srcClk;                         /*!< I2C module src clock */
    I2C_SpeedMode_Type speedMode;            /*!< Specifies the I2C speed mode. */
    uint32_t interrupt;                      /*!< Specifies the interrupts to be enabled */
    BL_Fun_Type fifoEnable;                  /*!< Determines whether enable I2C FIFO. */
    BL_Fun_Type DMAEnable;                   /*!< Determines whether enable I2C DMA. */
    uint32_t slaveAddress;                   /*!< Specifies the I2C slave address. */
    I2C_Direction_Type transferDirection;           /*!< Specifies the I2C transfer direction. */
    uint32_t subAddressSize;                 /*!< Specifies the size of I2C sub address section. */
    uint8_t* subAddress;                     /*!< Specifies the pointer of I2C sub address. */
    uint32_t dataSize;                       /*!< Specifies the size of I2C data section. */
    uint8_t* data;                           /*!< Specifies the pointer of I2C R/W data. */
}I2C_CFG_Type;

/**
 *  @brief I2S transfer structure type definition
 */
typedef struct {
    uint8_t slaveAddr;                       /*!< I2C slave address */
    BL_Fun_Type slaveAddr10Bit;              /*!< Enable or disable slave address 10-bit mode */
    BL_Fun_Type stopEveryByte;               /*!< I2C all data byte with stop bit */
    uint8_t subAddressSize;                  /*!< Specifies the size of I2C sub address section */
    uint8_t* subAddress;                     /*!< I2C sub address */
    uint8_t dataSize;                       /*!< Specifies the size of I2C data section */
    uint8_t* data;                           /*!< Specifies the pointer of I2C R/W data */
}I2C_Transfer_Cfg;

/*@} end of group I2C_Public_Types */

/** @defgroup  I2C_Public_Constants
 *  @{
 */

/** @defgroup  I2C_ID_TYPE
 *  @{
 */
#define IS_I2C_ID_TYPE(type)                             (((type) == I2C0_ID ) || \
                                                          ((type) == I2C1_ID))

/** @defgroup  I2C_SPEEDMODE_TYPE
 *  @{
 */
#define IS_I2C_SPEEDMODE_TYPE(type)                      (((type) == I2C_SPEED_STANDARD ) || \
                                                          ((type) == I2C_SPEED_FAST) || \
                                                          ((type) == I2C_SPEED_HIGH))

/** @defgroup  I2C_DIRECTION_TYPE
 *  @{
 */
#define IS_I2C_DIRECTION_TYPE(type)                      (((type) == I2C_WRITE ) || \
                                                          ((type) == I2C_READ))

/** @defgroup  I2C_INT_TYPE
 *  @{
 */
#define IS_I2C_INT_TYPE(type)                            (((type) == I2C_INT_STATUS) || \
                                                          ((type) == I2C_INT_ALL))

/*@} end of group I2C_Public_Constants */

/** @defgroup  I2C_Public_Macros
 *  @{
 */
#define I2C_INTTERUPT_BUFFER_FULL     					 0x01
#define I2C_INTTERUPT_BUFFER_EMPTY     					 0x02
#define I2C_INTTERUPT_SLAVEADDR_DETECTED				 0x04
#define I2C_INTTERUPT_BUS_ERROR     					 0x08
#define I2C_INTTERUPT_TRANSACTION_DONE   				 0x10
#define I2C_INTTERUPT_RFIFO_HALFFULL     				 0x20
#define I2C_INTTERUPT_TFIFO_EMPTY     					 0x40
#define I2C_INTTERUPT_RFIFO_FULL   	  					 0x80
#define I2C_INTTERUPT_RFIFO_OVERRUN     				 0x100
#define I2C_TIMEOUT_CNT                                  1024
#define I2C_TX_FIFO_MAX_SIZE                             8
#define I2C_FIFO_CTRL_WORD_ACK                           0x0000
#define I2C_FIFO_CTRL_WORD_START                         0x0100
#define I2C_FIFO_CTRL_WORD_STOP                          0x0200
#define I2C_FIFO_CTRL_WORD_NAK                           0x0400
#define I2C_FIFO_CTRL_WORD_TB                            0x0800

/*@} end of group I2C_Public_Macros */

/** @defgroup  I2C_Public_Functions
 *  @{
 */

/**
 *  @brief I2C Functions
 */
#ifndef BL60X_USE_HAL_DRIVER
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
#endif
void I2C_Disable(I2C_ID_Type i2cNo);
void I2C_Enable(I2C_ID_Type i2cNo);
BL_Err_Type I2C_MasterReceiveBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg);
BL_Err_Type I2C_MasterSendBlocking(I2C_ID_Type i2cNo, I2C_Transfer_Cfg *cfg);
int I2C_Write_Byte(I2C_ID_Type i2cNo, uint8_t slv_addr, uint8_t val);
int I2C_Read_Reg8(I2C_ID_Type i2cNo, uint8_t slv_addr, uint8_t reg, uint8_t *val);
int I2C_Write_Reg8(I2C_ID_Type i2cNo, uint8_t slv_addr, uint8_t reg, uint8_t val);
int I2C_Read_Reg16(I2C_ID_Type i2cNo, uint8_t slv_addr, uint16_t reg, uint8_t *val);
int I2C_Write_Reg16(I2C_ID_Type i2cNo, uint8_t slv_addr, uint16_t reg, uint8_t val);

void I2C_SetPrd(I2C_ID_Type i2cNo, uint8_t phase);
void I2C_DSP0_ClockSet(I2C_ID_Type i2cNo, uint32_t clk);
void I2C_SetDefaultConfig(I2C_CFG_Type* i2cCfgStruct);
void I2C_MasterInit(I2C_ID_Type i2cNo, I2C_CFG_Type* i2cCfgStruct);
BL_Err_Type I2C_MasterFIFOWirte(I2C_ID_Type i2cNo, I2C_CFG_Type *Cfg);

int I2C_Write_Byte(I2C_ID_Type i2cNo, uint8_t slv_addr, uint8_t val);

/*@} end of group I2C_Public_Functions */

/*@} end of group I2C */

/*@} end of group BL60x_Peripheral_Driver */

#endif /* __BL808_I2C_H__ */
