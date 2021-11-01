/**
 * *****************************************************************************
 * @file lhal_bl702_dma.h
 * @version 0.1
 * @date 2020-06-15
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

#include <stdint.h>
#include <stdbool.h>
#include "hal_dma.h"
#include "bl702_dma.h"

#define BL702_MAX_DMA_NUM 10

 /*!
 *  @brief      DMABLXXX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct {
    /* DMA control variables */
    bool                opened;         /*!< Has the obj been opened */

    DMA_Chan_Type       dma_ch;
    
    uint32_t            dma_trans_task_num;

    bool                dma_trans_is_loop;

    uint32_t            dma_trans_task_index;

    DMA_Trans_Task *    first_task_pointer;

    DMA_Trans_Task *    previous_task_pointer;  

} DMABLXXX_Object, *DMABLXXX_Handle;


typedef void (*DMABLXXX_ErrorCallback) (void);


typedef struct DMABLXXX_HWAttrsV2 {
    DMABLXXX_ErrorCallback errorFxn;
} DMABLXXX_HWAttrsV2;

