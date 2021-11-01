/**
 * *****************************************************************************
 * @file lhal_bl702_i2c.h
 * @version 0.1
 * @date 2020-07-30
 * @brief 
 * *****************************************************************************
 * @attention
 * 
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * *****************************************************************************
 */
#ifndef __LHAL_BL702_I2C__
#define __LAHL_BL702_I2C__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hal_i2c.h"
/**
 *  @addtogroup I2C_STATUS
 *  I2CBLXXX_STATUS_* macros are command codes only defined in the
 *  I2CBLXXX.h driver implementation and need to:
 *  @endcode
 *  @{
 */

/* Add I2CBLXXX_STATUS_* macros here */

/** @}*/

/**
 *  @addtogroup I2C_CMD
 *  I2CBLXXX_CMD_* macros are command codes only defined in the
 *  I2CBLXXX.h driver implementation and need to:
 *  @endcode
 *  @{
 */

/* Add I2CBLXXX_CMD_* macros here */

/** @}*/

/* \cond */
typedef unsigned long   I2CDataType;
/* \endcond */

/*! @internal @brief I2C function table pointer */
extern const I2C_FxnTable I2CBLXXX_fxnTable;

/*!
 *  @cond NODOC
 *  I2CBLXXX mode
 *
 *  This enum defines the state of the I2C driver's state-machine. Do not
 *  modify.
 */
typedef enum I2CBLXXX_Mode {
    I2CBLXXX_IDLE_MODE = 0,  /* I2C is not performing a transaction */
    I2CBLXXX_WRITE_MODE,     /* I2C is currently performing write operations */
    I2CBLXXX_READ_MODE,      /* I2C is currently performing read operations */
    I2CBLXXX_BUSBUSY_MODE,   /* I2C Bus is currently busy */
    I2CBLXXX_ERROR = 0xFF    /* I2C error has occurred, exit gracefully */
} I2CBLXXX_Mode;
/*! @endcond */


typedef struct{
    /*! I2C peripheral's base address */
    unsigned char       deviceIndex;
    /*! I2C SDA pin mapping */
    uint8_t             sdaPin;
    /*! I2C SCL pin mapping */
    uint8_t             sclPin;
} I2CBLXXX_HWAttrsV2;

/*!
 *  @cond NODOC
 *  I2CBLXXX Object.  The application must not access any member variables
 *  of this structure!
 */
typedef struct I2CBLXXX_Object {
    /* I2C control variables */
    I2C_TransferMode    transferMode;        /*!< Blocking or Callback mode */
    I2C_CallbackFxn     transferCallbackFxn; /*!< Callback function pointer */
    volatile I2CBLXXX_Mode mode;            /*!< Stores the I2C state */
    I2C_BitRate            bitRate;             /*!< Bitrate of the I2C module */

    bool                opened;             /*!< flag to indicate module is open */
} I2CBLXXX_Object;

/*! @endcond */

#ifdef __cplusplus
}
#endif

#endif