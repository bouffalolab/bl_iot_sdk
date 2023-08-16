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
#ifndef __BL808_COMMON_H__
#define __BL808_COMMON_H__

#include <FreeRTOS.h>
#include <task.h>
#include "bl808.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  COMMON
 *  @{
 */

/** @defgroup  COMMON_Public_Types
 *  @{
 */

/**
 * @brief Error type definition
 */
typedef enum 
{
  SUCCESS  = 0, 
  ERROR   = 1,
  TIMEOUT = 2,
  INVALID = 3, /* invalid arguments */
  NORESC  = 4  /* no resource or resource temperary unavailable */
}BL_Err_Type;

/**
 * @brief Functional type definition
 */
typedef enum 
{
  DISABLE  = 0, 
  ENABLE   = 1,
}BL_Fun_Type;

/**
 * @brief Status type definition
 */
typedef enum 
{
  RESET  = 0, 
  SET   = 1,
}BL_Sts_Type;

/**
 * @brief Mask type definition
 */
typedef enum 
{
  UNMASK = 0, 
  MASK = 1
}BL_Mask_Type;

/*@} end of group COMMON_Public_Types */

/** @defgroup  COMMON_Public_Constants
 *  @{
 */
 
/** @defgroup DRIVER_INT_PERIPH
 *  @{
 */
#define IS_INT_PERIPH(INT_PERIPH)       ((INT_PERIPH) < IRQn_LAST)

/*@} end of group DRIVER_INT_PERIPH */

/** @defgroup DRIVER_INT_MASK     
 *  @{
 */
#define IS_BL_MASK_TYPE(type)          (((type) == MASK) || ((type) == UNMASK))

/*@} end of group COMMON_Public_Constants */

/** @defgroup  COMMON_Public_Macros
 *  @{
 */

/**
 * @brief Null Type definition
 */
#ifndef NULL
#define NULL   0
#endif

/**
 * @brief Debug definition
 */
#define DEBUG   1

#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line);
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#define BL_ABORT() configASSERT(0)
#else
#define CHECK_PARAM(expr) ((void)0)
#define BL_ABORT() ((void)0)
#endif /* DEBUG */

#define CHECK_CONDITION     CHECK_PARAM
#define CHECK_PARAM_RANGE(value, min, max)  \
    CHECK_PARAM((value) >= min && (value) <= max)
#define CHECK_PARAM_MAX(value, max)  \
    CHECK_PARAM((value) <= max)
#define CHECK_PARAM_MIN(value, min)  \
    CHECK_PARAM((value) >= min)


/**
 * @brief Memory access macro
 */
#define BL_RD_WORD(addr)                             (*((volatile uint32_t*)(addr)))
#define BL_WR_WORD(addr,val)                         ((*(volatile uint32_t*)(addr))=(val))
#define BL_RD_SHORT(addr)                            (*((volatile uint16_t*)(addr)))
#define BL_WR_SHORT(addr,val)                        ((*(volatile uint16_t*)(addr))=(val))
#define BL_RD_BYTE(addr)                             (*((volatile uint8_t*)(addr)))
#define BL_WR_BYTE(addr,val)                         ((*(volatile uint8_t*)(addr))=(val))
#define BL_RDWD_FRM_BYTEP(p)                         ((p[3]<<24)|(p[2]<<16)|(p[1]<<8)|(p[0]))
#define BL_WRWD_TO_BYTEP(p,val)                      {p[0]=val&0xff;p[1]=(val>>8)&0xff;p[2]=(val>>16)&0xff;p[3]=(val>>24)&0xff;}
/**
 * @brief Register access macro
 */
#define BL_RD_REG16(addr,regname)                    BL_RD_SHORT(addr+regname##_OFFSET)
#define BL_WR_REG16(addr,regname,val)                BL_WR_SHORT(addr+regname##_OFFSET,val)
#define BL_RD_REG(addr,regname)                      BL_RD_WORD(addr+regname##_OFFSET)
#define BL_WR_REG(addr,regname,val)                  BL_WR_WORD(addr+regname##_OFFSET,val)
#define BL_SET_REG_BIT(val,bitname)                  ( (val) |(1U<<bitname##_POS))
#define BL_CLR_REG_BIT(val,bitname)                  ( (val) & bitname##_UMSK )
#define BL_GET_REG_BITS_VAL(val,bitname)             ( ((val) & bitname##_MSK) >> bitname##_POS )
/* the bitval should be masked already */
#define BL_SET_REG_BITS_VAL(val,bitname,bitval)      ( ((val)&bitname##_UMSK) | ((uint32_t)(bitval)<<bitname##_POS) )
#define BL_IS_REG_BIT_SET(val,bitname)               ( ((val)&(1U<<(bitname##_POS))) !=0 )

#define BL_WR_REG_SINGLE_VAL(addr,regname,bitname,bitval)  \
    BL_WR_REG(addr,regname,BL_SET_REG_BITS_VAL(0,bitname,bitval))

#define BL_RD_REG_SINGLE_BIT(addr,regname,bitname)  \
    BL_GET_REG_BITS_VAL(BL_RD_REG(addr,regname),bitname)

/* handle bitval that is not properly masked, such as signed value with less than 32bit.
    mask (zero out) the unrelated part */
#define BL_SET_REG_BITS_VAL_2(val,bitname,bitval)   \
    ( ((val)&bitname##_UMSK) | (((uint32_t)(bitval)<<bitname##_POS) & bitname##_MSK))

#define BL_DRV_DUMMY           \
    {                          \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
        __ASM volatile("nop"); \
    }

/**
 *  @brief Interrupt callback function type
 */
typedef void (intCallback_Type)(void);

/** @defgroup Interrupt callback array
 *  @{
 */
extern  intCallback_Type ** intCbfArra[];

/*@} end of group COMMON_Public_Macros */

/** @defgroup  COMMON_Public_Functions
 *  @{
 */

typedef void (*IRQHandler_t) (void);

void Install_Int_Callback(IRQn_Type intPeriph, uint32_t intType, intCallback_Type * cbFun);
void BL808_Delay_US(uint32_t cnt);
void BL808_Delay_MS(uint32_t cnt);
void *BL60X_MemCpy(void *dst, const void *src, uint32_t n);
uint32_t *BL60X_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n);
void *BL60X_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n);
void BL60X_MemCpy_Fastest_DMA_Init(uint8_t dmaCh);
void* BL60X_MemCpy_Fastest(void *pdst, const void *psrc, uint32_t n);
void* BL60X_MemSet(void *s, uint8_t c, uint32_t n);
uint32_t *BL60X_MemSet4(uint32_t *dst, const uint32_t val, uint32_t n);
void* ATTR_TCM_SECTION ARCH_MemCpy_Fast(void *pdst, const void *psrc, uint32_t n);
void ARCH_Delay_US(uint32_t cnt);
void ARCH_Delay_MS(uint32_t cnt);
uint32_t* ARCH_MemCpy4(uint32_t *dst, const uint32_t *src, uint32_t n);

/*@} end of group COMMON_Public_Functions */

/*@} end of group COMMON */

/*@} end of group BL60x_Peripheral_Driver */


/***************************** Common defines ************************************/
#define LINES_PER_MB_ROW_Y      16
#define LINES_PER_MB_ROW_UV     8
#define NS_PER_MS               1000000

void* BL_MallocDMA(uint8_t mem_id, size_t size);

/* TODO: need to zero out the addr which is freed */
#define BL_FreeDMA(addr)   \
    do {    \
        if ((addr) != 0) {    \
            BL_LOGI("[BL_FreeDMA] addr 0x%p\r\n", addr);   \
            vPortFree((void *)addr); \
        }   \
    } while (0)

/***************************** Log utility ************************************/
#include <stdbool.h>
#include <stdarg.h>

#define DEBUG_MODULE 0

/**
 *  BL log type definition
 */
typedef enum
{
    BL_LOG_OFF = 0,
    BL_LOG_ERROR,
    BL_LOG_WARNING,
    BL_LOG_INFO,
    BL_LOG_DEBUG,
    BL_LOG_ALL,
} BL_LOGTYPE;


/**
 * Pre Set BL log Level
 */

extern int bl_log_print_level;

#ifndef BL_LOG_PRINT
#define BL_LOG_PRINT(debug_module, type, ...) \
    (((debug_module && (bl_log_print_level != BL_LOG_OFF)) || (type <= bl_log_print_level))  \
    ? ((void)printf(__VA_ARGS__)) \
    : (void)0)
#endif

/**
*   Simplified macro to print error message .
*/
#define BL_LOGE(...) ((void)BL_LOG_PRINT(DEBUG_MODULE, BL_LOG_ERROR, __VA_ARGS__))


/**
*  Simplified macro to print warning message .
*/

#define BL_LOGW(...) ((void)BL_LOG_PRINT(DEBUG_MODULE, BL_LOG_WARNING, __VA_ARGS__))


/**
*  Simplified macro to print info log message .
*/

#define BL_LOGI(...) ((void)BL_LOG_PRINT(DEBUG_MODULE, BL_LOG_INFO, __VA_ARGS__))


/**
*  Simplified macro to print debug log message .
*/
#define BL_LOGD(...) ((void)BL_LOG_PRINT(DEBUG_MODULE, BL_LOG_DEBUG, __VA_ARGS__))


int BL_DBG_ChgLogPrintLevel(BL_LOGTYPE level);
BL_LOGTYPE BL_DBG_GetLogPrintLevel(void);


#define BL_CHECK_POINTER(ptr)\
do {\
    if (NULL == ptr)\
    {\
        BL_LOGE("Null Pointer!\r\n");\
        return;\
    }\
} while(0)


#endif /* __BL808_COMMON_H__ */

