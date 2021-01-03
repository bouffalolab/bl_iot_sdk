/**
  ******************************************************************************
  * @file    tft_lcd.c
  * @version V1.0
  * @date
  * @brief   This file is the peripheral case c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 Bouffalo Lab</center></h2>
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

#include "tft_lcd.h"
#include "bl602_glb.h"
#include "bl602_spi.h"

/** @addtogroup  BL602_Peripheral_Case
 *  @{
 */

/** @addtogroup  TFT_LCD
 *  @{
 */

/** @defgroup  TFT_LCD_Private_Macros
 *  @{
 */

/*@} end of group TFT_LCD_Private_Macros */

/** @defgroup  TFT_LCD_Private_Types
 *  @{
 */

/*@} end of group TFT_LCD_Private_Types */

/** @defgroup  TFT_LCD_Private_Variables
 *  @{
 */

/*@} end of group TFT_LCD_Private_Variables */

/** @defgroup  TFT_LCD_Global_Variables
 *  @{
 */

/*@} end of group TFT_LCD_Global_Variables */

/** @defgroup  TFT_LCD_Private_Fun_Declaration
 *  @{
 */

/*@} end of group TFT_LCD_Private_Fun_Declaration */

/** @defgroup  TFT_LCD_Private_Functions
 *  @{
 */

/*@} end of group TFT_LCD_Private_Functions */

/** @defgroup  TFT_LCD_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  LCD write command
 *
 * @param  command: Command to write
 *
 * @return None
 *
*******************************************************************************/
void LCD_WR_Cmd(uint8_t command)
{
    CS1_LOW;
    DC_LOW;
    SPI_Enable(SPI_ID,SPI_WORK_MODE_MASTER);
    SPI_Send_8bits(SPI_ID,&command,1,SPI_TIMEOUT_DISABLE);
    SPI_Disable(SPI_ID,SPI_WORK_MODE_MASTER);
    CS1_HIGH;
}


/****************************************************************************//**
 * @brief  LCD write 8-bit data
 *
 * @param  data: 8-bit data to write
 *
 * @return None
 *
*******************************************************************************/
void LCD_WR_Byte(uint8_t data)
{
    CS1_LOW;
    DC_HIGH;
    SPI_Enable(SPI_ID,SPI_WORK_MODE_MASTER);
    SPI_Send_8bits(SPI_ID,&data,1,SPI_TIMEOUT_DISABLE);
    SPI_Disable(SPI_ID,SPI_WORK_MODE_MASTER);
    CS1_HIGH;
}


/****************************************************************************//**
 * @brief  LCD write 16-bit data
 *
 * @param  data: 16-bit data to write
 *
 * @return None
 *
*******************************************************************************/
void LCD_WR_HalfWord(uint16_t data)
{
    CS1_LOW;
    DC_HIGH;
    SPI_Enable(SPI_ID,SPI_WORK_MODE_MASTER);
    SPI_Send_16bits(SPI_ID,&data,1,SPI_TIMEOUT_DISABLE);
    SPI_Disable(SPI_ID,SPI_WORK_MODE_MASTER);
    CS1_HIGH;
}


/****************************************************************************//**
 * @brief  LCD write 32-bit data
 *
 * @param  data: 32-bit data to write
 *
 * @return None
 *
*******************************************************************************/
void LCD_WR_Word(uint32_t data)
{
    CS1_LOW;
    DC_HIGH;
    SPI_Enable(SPI_ID,SPI_WORK_MODE_MASTER);
    SPI_Send_32bits(SPI_ID,&data,1,SPI_TIMEOUT_DISABLE);
    SPI_Disable(SPI_ID,SPI_WORK_MODE_MASTER);
    CS1_HIGH;
}


/****************************************************************************//**
 * @brief  LCD set address
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 *
 * @return None
 *
*******************************************************************************/
void LCD_Set_Addr(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2)
{ 
   LCD_WR_Cmd(0x2a);
   LCD_WR_Word(x2<<24 | (x2<<8&0xff0000) | (x1<<8&0xff00) | (x1>>8&0xff));

   LCD_WR_Cmd(0x2b);
   LCD_WR_Word(y2<<24 | (y2<<8&0xff0000) | (y1<<8&0xff00) | (y1>>8&0xff));

   LCD_WR_Cmd(0x2C);
}


/****************************************************************************//**
 * @brief  SPI LCD init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void LCD_Init(void)
{
    /* Reset */
    RES_LOW;
    BL602_Delay_MS(20);
    RES_HIGH;
    BL602_Delay_MS(20);
    
    LCD_WR_Cmd(0x11);                 /* Exit sleep */
    BL602_Delay_MS(60);
    
    LCD_WR_Cmd(0xcf);
    LCD_WR_HalfWord(0xd900);
    LCD_WR_Byte(0X30);
    
    LCD_WR_Cmd(0xed);
    LCD_WR_Word(0x81120364);
    
    LCD_WR_Cmd(0xe8);
    LCD_WR_HalfWord(0x1085);
    LCD_WR_Byte(0x78);
    
    LCD_WR_Cmd(0xcb);
    LCD_WR_Word(0x34002c39);
    LCD_WR_Byte(0x02);
    
    LCD_WR_Cmd(0xf7);
    LCD_WR_Byte(0x20);
    
    LCD_WR_Cmd(0xea);
    LCD_WR_HalfWord(0x0000);
    
    LCD_WR_Cmd(0xc0);                 /* Power control */
    LCD_WR_Byte(0x23);                /* VRH[5:0] */
    LCD_WR_Cmd(0xc1);                 /* Power control */
    LCD_WR_Byte(0x12);                /* SAP[2:0];BT[3:0] */
    LCD_WR_Cmd(0xc2);
    LCD_WR_Byte(0x11);
    LCD_WR_Cmd(0xC5);                 /* VCM control */
    LCD_WR_HalfWord(0x3040);
    LCD_WR_Cmd(0xc7);                 /* VCM control2 */
    LCD_WR_Byte(0xa9);
    LCD_WR_Cmd(0x3a); 
    LCD_WR_Byte(0x55);
    LCD_WR_Cmd(0x36);                 /* Memory Access Control */
    LCD_WR_Byte(0x08);
    LCD_WR_Cmd(0xb1);                 /* Frame Rate Control */
    LCD_WR_HalfWord(0x1800);
    LCD_WR_Cmd(0xb6);                 /* Display Function Control */
    LCD_WR_HalfWord(0xa20a);
    LCD_WR_Cmd(0xf2);                 /* 3Gamma Function Disable */
    LCD_WR_Byte(0x00);
    LCD_WR_Cmd(0xf7);
    LCD_WR_Byte(0x20);
    LCD_WR_Cmd(0x26);                 /* Gamma curve selected */
    LCD_WR_Byte(0x01);
    LCD_WR_Cmd(0xe0);                 /* Set Gamma */
    LCD_WR_Word(0x0b23241f);
    LCD_WR_Word(0xd850080f);
    LCD_WR_Word(0x000a083b);
    LCD_WR_HalfWord(0x0000);
    LCD_WR_Byte(0x00);
    LCD_WR_Cmd(0Xe1);                 /* Set Gamma */
    LCD_WR_Word(0x041c1b00);
    LCD_WR_Word(0x272f0710);
    LCD_WR_Word(0x0f150744);
    LCD_WR_HalfWord(0x3f3f);
    LCD_WR_Byte(0x1f);
    LCD_WR_Cmd(0x29);                 /* Display on */
}


/****************************************************************************//**
 * @brief  LCD clear display
 *
 * @param  color: Color to fill
 *
 * @return None
 *
*******************************************************************************/
void LCD_Clear(uint16_t color)
{
    uint16_t i,j;
    LCD_Set_Addr(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++){
        for (j=0;j<LCD_H;j++){
            LCD_WR_HalfWord(color);
        }
    }
}


/****************************************************************************//**
 * @brief  LCD draw a point
 *
 * @param  x: Coordinate x
 * @param  y: Coordinate y
 * @param  color: Color of the point
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_Set_Addr(x,y,x,y);
    LCD_WR_HalfWord(color);
}


/****************************************************************************//**
 * @brief  LCD draw line
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color of the line
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    int xVariation,yVariation,temp;
    int absX,absY,i;
    xVariation = x2-x1;
    yVariation = y2-y1;
    absX = ABS32(xVariation);
    absY = ABS32(yVariation);
    
    if(absX > absY){
        for(i=0;i<absX+1;i++){
            temp = yVariation*100/absX*i/100;
            if(xVariation>0){
                LCD_DrawPoint(x1+i,y1+temp,color);
            }else{
                LCD_DrawPoint(x1-i,y1+temp,color);
            }
        }
    }
    else{
        for(i=0;i<absY+1;i++){
            temp = xVariation*100/absY*i/100;
            if(yVariation>0){
                LCD_DrawPoint(x1+temp,y1+i,color);
            }else{
                LCD_DrawPoint(x1+temp,y1-i,color);
            }
        }
    }
}


/****************************************************************************//**
 * @brief  LCD draw rectangle
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color of the rectangle
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
    LCD_DrawLine(x2,y2,x1,y2,color);
    LCD_DrawLine(x1,y2,x1,y1,color);
}


/****************************************************************************//**
 * @brief  LCD draw circle
 *
 * @param  x: Center coordinate x
 * @param  y: Center coordinate y
 * @param  r: Radius
 * @param  color: Color of the circle
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawCircle(uint16_t x,uint16_t y,uint16_t r,uint16_t color)
{
    int a = 0,b;
    int di;
    b = r;
    di = 3-(r<<1);
    while(a <= b)
    {
        LCD_DrawPoint(x-b,y-a,color);
        LCD_DrawPoint(x+b,y-a,color);
        LCD_DrawPoint(x-a,y+b,color);
        LCD_DrawPoint(x-b,y-a,color);
        LCD_DrawPoint(x-a,y-b,color);
        LCD_DrawPoint(x+b,y+a,color);
        LCD_DrawPoint(x+a,y-b,color);
        LCD_DrawPoint(x+a,y+b,color);
        LCD_DrawPoint(x-b,y+a,color);
        a++;
        if(di<0){
            di += 4*a+6;
        }else{
            di += 10+4*(a-b);
            b--;
        }
        LCD_DrawPoint(x+a,y+b,color);
    }
}


/****************************************************************************//**
 * @brief  LCD fill the area with color
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  color: Color to fill
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawArea(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    uint16_t i,j;
    LCD_Set_Addr(x1,y1,x2,y2); 
    for(i=y1;i<=y2;i++)
    {
        for(j=x1;j<=x2;j++)LCD_WR_HalfWord(color);
    }
}


/****************************************************************************//**
 * @brief  LCD draw picture
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  picture: Color array of the picture
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t* picture)
{
    uint32_t i;
    LCD_Set_Addr(x1,y1,x2,y2);
    for(i=0;i<ABS16((x2-x1+1)*(y2-y1+1));i++)
    {
        LCD_WR_HalfWord(picture[i]);
    }
}


/****************************************************************************//**
 * @brief  LCD use uart to receive picture data and send to display
 *
 * @param  x1: Coordinate x start
 * @param  y1: Coordinate y start
 * @param  x2: Coordinate x end
 * @param  y2: Coordinate y end
 * @param  uartId: Color array of the picture
 *
 * @return None
 *
*******************************************************************************/
void LCD_UartDrawPicture(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,UART_ID_Type uartId)
{
    uint32_t rxLen = 0,i;
    uint32_t recvCnt = 0;
    uint8_t uartRxBuf[UART_RX_FIFO_SIZE] = {0};
    LCD_Set_Addr(x1,y1,x2,y2);
    
    UART_Enable(uartId,UART_RX);
    
    while(rxLen < 2*(x2-x1+1)*(y2-y1+1)){
        while((recvCnt=UART_GetRxFifoCount(uartId)) == 0){}
        rxLen += UART_ReceiveData(uartId,uartRxBuf,recvCnt);
        for(i=0;i<recvCnt;i++){
            LCD_WR_Byte(uartRxBuf[i]);
        }
    }
    
    UART_Disable(uartId,UART_RX);
}


/****************************************************************************//**
 * @brief  LCD draw a 32*32 chinese character in lattice mode
 *
 * @param  x: Coordinate x
 * @param  y: Coordinate y
 * @param  character: Array of the character
 * @param  bColor: Color of the background
 * @param  cColor: Color of the character
 *
 * @return None
 *
*******************************************************************************/
void LCD_DrawChinese(uint16_t x,uint16_t y,uint8_t* character,uint16_t bColor,uint16_t cColor)
{
    uint8_t i,j;
    LCD_Set_Addr(x,y,x+31,y+31);
    for(j=0;j<128;j++)
    {
        for(i=0;i<8;i++)
        {
            if((*character&(1<<i)) != 0)
            {
                LCD_WR_HalfWord(cColor);
            } 
            else
            {
                LCD_WR_HalfWord(bColor);
            }
        }
        character++;
     }
}


/*@} end of group TFT_LCD_Public_Functions */

/*@} end of group TFT_LCD */

/*@} end of group BL602_Peripheral_Case */
