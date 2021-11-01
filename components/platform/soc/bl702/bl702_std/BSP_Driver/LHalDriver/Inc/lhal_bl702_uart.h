/**
 * *****************************************************************************
 * @file lhal_bl702_uart.h
 * @version 0.1
 * @date 2020-06-03
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


#ifndef __LHAL_BL702_UART__
#define __LHAL_BL702_UART__

#include <stdint.h>
#include <stdbool.h>
#include "hal_uart.h"
#include "ring_buffer.h"

/**
 *  @addtogroup UART_STATUS
 *  UARTBLXXX_STATUS_* macros are command codes only defined in the
 *  UARTBLXXX.h driver implementation and need to:
 *  @code
 *  #include <ti/drivers/uart/UARTBLXXX.h>
 *  @endcode
 *  @{
 */

/* Add UARTBXXX_STATUS_* macros here */

/** @}*/


/*!
 * @brief Command used by UART_control to flush the RX FIFO
 *
 * This control command flushes any contents in the RX FIFO. With this command
 * @b arg is @a don't @a care and it returns UART_STATUS_SUCCESS.
 */
#define UARTBLXXX_CMD_RX_FIFO_FLUSH                  (UART_CMD_RESERVED + 0)
#define UARTBLXXX_CMD_TX_FREE_INT_ENABLE             (UART_CMD_RESERVED + 1)
#define UARTBLXXX_CMD_TX_FREE_INT_DISABLE            (UART_CMD_RESERVED + 2)
#define UARTBLXXX_CMD_RX_INT_ENABLE                  (UART_CMD_RESERVED + 3)
#define UARTBLXXX_CMD_RX_INT_DISABLE                 (UART_CMD_RESERVED + 4)

/** @}*/

/*! Size of the TX and RX FIFOs is 16 items */
#define UARTBLXXX_FIFO_SIZE 16
#define UARTBLXXX_MAX_UART_NUM 2
/* END BACKWARDS COMPATIBILITY */

/*!
 *  @brief      The definition of an optional callback function used by the
 *              UART driver to notify the application when a receive error
 *              (FIFO overrun, parity error, etc) occurs.
 *
 *  @param      UART_Handle             UART_Handle
 *
 *  @param      error                   The current value of the receive
 *                                      status register.
 */
typedef void (*UARTBLXXX_ErrorCallback) (UART_Handle handle, uint32_t error);

/*!
 *  @brief      UARTBLXXX Hardware attributes
 *
 *  These fields, with the exception of intPriority, txIntFifoThr and
 *  rxIntFifoThr, are used by driverlib APIs and therefore must be populated
 *  by driverlib macro definitions.
 *  For BLXXXWare these definitions are found in:
 *      - inc/hw_memmap.h
 *      - inc/hw_ints.h
 *UART_Handle
 *  intPriority is the UART peripheral's interrupt priority, as defined by the
 *  underlying OS.  It is passed unmodified to the underlying OS's interrupt
 *  handler creation code, so you need to refer to the OS documentation
 *  for usage.  For example, for SYS/BIOS applications, refer to the
 *  ti.sysbios.family.arm.m3.Hwi documentation for SYS/BIOS usage of
 *  interrupt priorities.  If the driver uses the ti.dpl interface
 *  instead of making OS calls directly, then the HwiP port handles the
 *  interrupt priority in an OS specific way.  In the case of the SYS/BIOS
 *  port, intPriority is passed unmodified to Hwi_create().
 *
 *  A sample structure is shown below:
 *  @code
 *  const UARTBLXXX_HWAttrsV2 uartBLXXXHWAttrs[] = {
 *      {
 *          .deviceIndex    = UART0_BASE,
 *          .powerMngrId = PERIPH_UART0,
 *          .intNum      = INT_UART0,
 *          .intPriority = ~0,
 *          .swiPriority = 0,
 *          .txPin       = Board_UART_TX,
 *          .rxPin       = Board_UART_RX,
 *          .ctsPin      = PIN_UNASSIGNED,
 *          .rtsPin      = PIN_UNASSIGNED,
 *          .ringBufPtr  = uartBLXXXRingBuffer[0],
 *          .ringBufSize = sizeof(uartBLXXXRingBuffer[0]),
 *          .txIntFifoThr= UARTBLXXX_FIFO_THRESHOLD_1_8,
 *          .rxIntFifoThr= UARTBLXXX_FIFO_THRESHOLD_4_8
 *      }
 *  };
 *  @endcode
 *
 *  The .ctsPin and .rtsPin must be assigned to enable flow control.
 */
typedef struct UARTBLXXX_HWAttrsV2 {
    uint32_t     deviceIndex;    /*!< UART Peripheral's base address */
    uint8_t                  txPin;        /*!< UART TX pin */
    uint8_t                  rxPin;        /*!< UART RX pin */
    uint8_t                  ctsPin;       /*!< UART CTS pin */
    uint8_t                  rtsPin;       /*!< UART RTS pin */
    unsigned char           *ringBufPtr;   /*!< Pointer to an application ring buffer */
    uint32_t                 ringBufSize;  /*!< Size of ringBufPtr */
    void *                   ringBufferLockFnx;  /*!< Size of ringBufPtr */
    void *                   ringBufferUnlockFnx;/*!< Size of ringBufPtr */
    uint8_t  dmaTxIntFifoThr; /*!< UART TX interrupt FIFO threshold select */
    uint8_t  dmaRxIntFifoThr; /*!< UART RX interrupt FIFO threshold select */
    /*! Application error function to be called on receive errors */
    UARTBLXXX_ErrorCallback errorFxn;
} UARTBLXXX_HWAttrsV2;

/*!
 *  @brief    UART status
 *
 *  The UART Status is used to flag the different Receive Errors.
 */
typedef enum UART_Status {
    UART_TIMED_OUT     = 0x10,                 /*!< UART timed out */
    UART_PARITY_ERROR  = 0x11,                 /*!< UART Parity error */
    UART_BRAKE_ERROR   = 0x12,                 /*!< UART Break error */
    UART_OVERRUN_ERROR = 0x13,                 /*!< UART overrun error */
    UART_FRAMING_ERROR = 0x14,                 /*!< UART Framing error */
    UART_OK            = 0x0                   /*!< UART OK */
} UART_Status;

 /*!
 *  @brief      UARTBLXXX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct {
    /* UART control variables */
    bool                opened;         /*!< Has the obj been opened */
    UART_Mode           readMode;       /*!< Mode for all read calls */
    UART_Mode           writeMode;      /*!< Mode for all write calls */
    unsigned int        readTimeout;    /*!< Timeout for read semaphore in BLOCKING mode*/
    unsigned int        writeTimeout;   /*!< Timeout for write semaphore in BLOCKING mode*/
    UART_Callback       readCallback;   /*!< Pointer to read callback */
    UART_Callback       writeCallback;  /*!< Pointer to write callback */
    UART_ReturnMode     readReturnMode; /*!< Receive return mode */
    UART_DataMode       readDataMode;   /*!< Type of data being read */
    UART_DataMode       writeDataMode;  /*!< Type of data being written */
    /*! @brief Baud rate for BLXXX UART
     *
     *  The BLXXX driver supports baud rates up to 3Mbaud.
     *  However, when receiving more than 32 bytes back-to-back the baud
     *  rate is limited to approx. 2Mbaud.
     *  The throughput is also dependent on the user application.
     */
    uint32_t            baudRate;
    UART_LEN            dataLength;     /*!< Data length for UART */
    UART_STOP           stopBits;       /*!< Stop bits for UART */
    UART_PAR            parityType;     /*!< Parity bit type for UART */
    UART_Status         status;         /*!< Status variable */

    /* UART write variables */
    const void         *writeBuf;       /*!< Buffer data pointer */
    uint32_t            writeCount;     /*!< Number of Chars sent */
    uint32_t            writeSize;      /*!< Chars remaining in buffer */
    bool                writeCR;        /*!< Write a return character */

    /* UART receive variables */
    Ring_Buffer_Type      *ringBuffer;        /*!< local circular buffer object */
    void                  *readBuf;           /*!< Buffer data pointer */
    uint32_t              readCount;          /*!< Number of Chars read */
    uint32_t              readSize;           /*!< Chars remaining in buffer */
    
    
    /*! UART post-notification function pointer */
    void             *uartPostFxn;
} UARTBLXXX_Object, *UARTBLXXX_Handle;

#endif