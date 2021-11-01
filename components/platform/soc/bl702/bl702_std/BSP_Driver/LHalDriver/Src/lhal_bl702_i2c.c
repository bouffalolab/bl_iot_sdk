/**
 * *****************************************************************************
 * @file lhal_bl702_i2c.c
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
#include "hal_i2c.h"
#include "hal_pin.h"
#include "lhal_bl702_i2c.h"
#include "bflb_platform.h"
#include "bl702_i2c.h"
#include "bl702_glb.h"
void                I2CBLXXX_cancel(I2C_Handle handle);
void                I2CBLXXX_close(I2C_Handle handle);
int_fast16_t         I2CBLXXX_control(I2C_Handle handle, uint_fast16_t cmd,void *arg);
void                 I2CBLXXX_init(I2C_Handle handle);
I2C_Handle           I2CBLXXX_open(I2C_Handle handle, I2C_Params *params);
bool                 I2CBLXXX_transfer(I2C_Handle handle, I2C_Transaction *transaction);

static bool          I2CBLXXX_initHw(I2C_Handle handle);
static bool          I2CBLXXX_initIO(I2C_Handle handle);

const I2C_FxnTable I2CBLXXX_fxnTable = {
    I2CBLXXX_cancel,
    I2CBLXXX_close,
    I2CBLXXX_control,
    I2CBLXXX_init,
    I2CBLXXX_open,
    I2CBLXXX_transfer,
};


void         I2CBLXXX_cancel(I2C_Handle handle){

}

void         I2CBLXXX_close(I2C_Handle handle){
    I2CBLXXX_Object               *object;
    I2CBLXXX_HWAttrsV2 const     *hwAttrs;

    object = handle->object;
    hwAttrs = handle->hwAttrs;
    
    I2C_Disable(hwAttrs->deviceIndex);

    object -> opened = false;
}
int_fast16_t         I2CBLXXX_control(I2C_Handle handle, uint_fast16_t cmd,void *arg){
    return 0;
}
void                 I2CBLXXX_init(I2C_Handle handle){
    I2CBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;
}
I2C_Handle           I2CBLXXX_open(I2C_Handle handle, I2C_Params *params){
    I2CBLXXX_Object               *object;

    object = handle->object;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("I2C:(%p) already in use.", handle);
        return (NULL);
    }    

    object->transferMode = params->transferMode;
    object->bitRate = params->bitRate;
    object->transferCallbackFxn = params->transferCallbackFxn;

    if(I2CBLXXX_initIO(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    if(I2CBLXXX_initHw(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    object->opened = true;
    
    return (handle);
}
bool                 I2CBLXXX_transfer(I2C_Handle handle, I2C_Transaction *transaction){
    I2CBLXXX_HWAttrsV2  const     *hwAttrs;
    I2CBLXXX_Object               *object;
    I2C_Transfer_Cfg i2cCfg;

    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    i2cCfg.slaveAddr = transaction->slaveAddr;
    i2cCfg.stopEveryByte = DISABLE;
    i2cCfg.subAddr = transaction->subAddr;
    i2cCfg.subAddrSize = transaction->subAddrSize;
    i2cCfg.data = transaction->data;
    i2cCfg.dataSize =  transaction->dataSize;

    if(object->transferMode == I2C_MODE_BLOCKING){
        if(transaction->transDir == WriteSlaveDir){
            return I2C_MasterSendBlocking(hwAttrs->deviceIndex, &i2cCfg);
        }else{
            return I2C_MasterReceiveBlocking(hwAttrs->deviceIndex, &i2cCfg);
        }
    }

    return ERROR;
}

static bool          I2CBLXXX_initHw(I2C_Handle handle){
    I2CBLXXX_HWAttrsV2  const     *hwAttrs;
    I2CBLXXX_Object               *object;

    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    GLB_Set_I2C_CLK(ENABLE,0);

    switch (object->bitRate)
    {
        case I2C_100kHz:   I2C_SetPrd(hwAttrs->deviceIndex,80);  break;    
        case I2C_400kHz:   I2C_SetPrd(hwAttrs->deviceIndex,20);  break;  
        case I2C_1000kHz:  I2C_SetPrd(hwAttrs->deviceIndex,8);  break;   
        case I2C_2000kHz:  I2C_SetPrd(hwAttrs->deviceIndex,4);  break;    
        default: break;
    }

    if(object->transferMode ==  I2C_MODE_BLOCKING){

    }else{

    }

    return SUCCESS;
}
static bool          I2CBLXXX_initIO(I2C_Handle handle){
    I2CBLXXX_HWAttrsV2  const     *hwAttrs;
    uint8_t i2c_pin[2];

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->sclPin == PIN_UNASSIGNED || hwAttrs->sdaPin == PIN_UNASSIGNED){
        MSG("i2c port can not be set as PIN_UNASSIGNED\r\n");
        return ERROR;
    }

    i2c_pin[0] = hwAttrs->sclPin;
    i2c_pin[1] = hwAttrs->sdaPin;

    GLB_GPIO_Func_Init(GPIO_FUN_I2C,i2c_pin,2);    

    return SUCCESS;
}