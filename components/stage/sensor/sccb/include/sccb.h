/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * SCCB (I2C like) driver.
 *
 */
#ifndef __SCCB_H__
#define __SCCB_H__

#include "stdint.h"

int SCCB_Init(void);
int SCCB_Init_GPIO(uint8_t scl, uint8_t sda);
int SCCB_Scan(int first, int last);
int SCCB_Read(uint8_t slave_addr, uint8_t reg_addr, uint8_t* rdata);
int SCCB_Read_Reg16(uint8_t slv_addr, uint16_t reg, uint8_t* rdata);
int SCCB_Write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);
int SCCB_Write_Reg16(uint8_t slv_addr, uint16_t reg, uint8_t data);
uint8_t SCCB_Read_Dbg(uint8_t slv_addr, uint8_t reg_addr);
uint8_t SCCB_Read_Reg16_Dbg(uint8_t slv_addr, uint16_t reg);

#endif // __SCCB_H__
