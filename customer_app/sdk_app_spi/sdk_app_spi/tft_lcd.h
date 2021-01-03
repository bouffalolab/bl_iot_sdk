/**
  ******************************************************************************
  * @file    tft_lcd.h
  * @version V1.0
  * @date
  * @brief   This file is the peripheral case header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
  *
  ******************************************************************************
  */
#ifndef __TFT_LCD_H__
#define __TFT_LCD_H__

#include "bl602_common.h"
#include "bl602_uart.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TFT_LCD
 *  @{
 */

/** @defgroup  TFT_LCD_Public_Types
 *  @{
 */

/*@} end of group TFT_LCD_Public_Types */

/** @defgroup  TFT_LCD_Public_Constants
 *  @{
 */

/*@} end of group TFT_LCD_Public_Constants */

/** @defgroup  TFT_LCD_Public_Macros
 *  @{
 */
#define SPI_ID                        SPI_ID_0
#define CS1                           GLB_GPIO_PIN_2
#define CLK                           GLB_GPIO_PIN_11
#define MOSI                          GLB_GPIO_PIN_0
#define MISO                          GLB_GPIO_PIN_1
#define RES                           GLB_GPIO_PIN_4
#define DC                            GLB_GPIO_PIN_12
#define CS2                           GLB_GPIO_PIN_15
#define CS1_HIGH                      GLB_GPIO_Write(CS1,1)
#define CS1_LOW                       GLB_GPIO_Write(CS1,0)
#define RES_HIGH                      GLB_GPIO_Write(RES,1)
#define RES_LOW                       GLB_GPIO_Write(RES,0)
#define DC_HIGH                       GLB_GPIO_Write(DC,1)
#define DC_LOW                        GLB_GPIO_Write(DC,0)
#define CS2_HIGH                      GLB_GPIO_Write(CS2,1)
#define CS2_LOW                       GLB_GPIO_Write(CS2,0)
#define LCD_W 240                     /* LCD width */
#define LCD_H 320                     /* LCD height */
/* Turn 24-bit RGB color to 16-bit */
#define RGB(r,g,b)   (((r>>3)<<3|(g>>5)|(g>>2)<<13|(b>>3)<<8)&0xffff)
/* Calculate 32-bit or 16-bit absolute value */
#define ABS32(value)                  ((value^(value>>31))-(value>>31))
#define ABS16(value)                  ((value^(value>>15))-(value>>15))

/*@} end of group TFT_LCD_Public_Macros */

/** @defgroup  TFT_LCD_Public_Functions
 *  @{
 */

/**
 *  @brief Tft_lcd Functions
 */
void LCD_WR_Cmd(uint8_t command);
void LCD_WR_Byte(uint8_t data);
void LCD_WR_HalfWord(uint16_t data);
void LCD_WR_Word(uint32_t data);
void LCD_Set_Addr(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2);
void LCD_Init(void);
void LCD_Clear(uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawCircle(uint16_t x,uint16_t y,uint16_t r,uint16_t color);
void LCD_DrawArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t* picture);
void LCD_UartDrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,UART_ID_Type uartId);
void LCD_DrawChinese(uint16_t x,uint16_t y,uint8_t* character,uint16_t bColor,uint16_t cColor);

/*@} end of group TFT_LCD_Public_Functions */

/*@} end of group TFT_LCD */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __TFT_LCD_H__ */
