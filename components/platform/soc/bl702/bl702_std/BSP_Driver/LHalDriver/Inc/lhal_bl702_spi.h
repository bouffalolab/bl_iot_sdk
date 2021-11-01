/**
 * *****************************************************************************
 * @file lhal_bl702_spi.h
 * @version 0.1
 * @date 2020-07-14
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
#include <stdbool.h>
#include "hal_spi.h"


typedef struct SPIBLXXX_HWAttrsV2 {

    uint8_t spi_sclk_pin;
    uint8_t spi_miso_pin;
    uint8_t spi_mosi_pin;
    /*
     * SPI_CS_PIN signal is not recommed generate form hardware spi module.
     * beacuse different spi device has different cs timing , hardware spi module cannot cover all.
     * lt is recommand that using software cs pin for spi device application. 
     */ 
    uint8_t spi_cs_pin;

    uint8_t spi_index;


    /*
     * dma requset happend when spi fifo upper/lower than thr
     * only used in dma mode
     */
    uint8_t spi_tx_dma_thr;
    uint8_t spi_rx_dma_thr;

} SPIBLXXX_HWAttrsV2;

 /*!
 *  @brief      SPIBLXXX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct {
    bool opened;
    SPI_Work_Mode spi_work_mode;
    uint8_t spi_clock_div;
    SPI_CPOL spi_cpol;
    SPI_CPHA spi_cpha;
    SPI_Data_First spi_data_first;
    SPI_Data_Size spi_data_size;
    uint32_t spi_block_timeout;
} SPIBLXXX_Object, *SPIBLXXX_Handle;

uint_fast8_t         SPIBLXXX_close(SPI_Handle handle);
int_fast16_t         SPIBLXXX_control(SPI_Handle handle, uint_fast16_t cmd,void *arg);
void                 SPIBLXXX_init(SPI_Handle handle);
SPI_Handle           SPIBLXXX_open(SPI_Handle handle, SPI_Params *params);
uint_fast32_t SPIBLXXX_getDMAAddrFxn(SPI_Handle handle);
uint_fast8_t  SPIBLXXX_getDmaReqFxn(SPI_Handle handle);
