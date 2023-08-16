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

#include "image_sensor.h"
#include "bf2013.h"
#include "gc0308.h"
#include "gc0328.h"
#include "gc2053.h"

/** @addtogroup  Image_Sensor_Driver
 *  @{
 */

/** @addtogroup  IMAGE_SENSOR
 *  @{
 */

/** @defgroup  IMAGE_SENSOR_Private_Macros
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Private_Macros */

/** @defgroup  IMAGE_SENSOR_Private_Types
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Private_Types */

/** @defgroup  IMAGE_SENSOR_Private_Variables
 *  @{
 */

static image_sensor_configure_t* sensor_list[] = {
    &bf2013_config, &gc0308_config, &gc0328_config, &gc2053_config
};

/*@} end of group IMAGE_SENSOR_Private_Variables */

/** @defgroup  IMAGE_SENSOR_Global_Variables
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Global_Variables */

/** @defgroup  IMAGE_SENSOR_Private_Fun_Declaration
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Private_Fun_Declaration */

/** @defgroup  IMAGE_SENSOR_Private_Functions
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Private_Functions */

/** @defgroup  IMAGE_SENSOR_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Scan image sensor model
 *
 * @param  dev: Pointer of device
 *
 * @return 0:SUCCESS -1:FAIL
 *
*******************************************************************************/
int image_sensor_scan(image_sensor_device_t *dev)
{
    uint32_t i,j;
    uint32_t sensor_match_flag = 0, ret = -1;
    image_sensor_command_t read_id = {0, 0};
    
    for(i=0;i<sizeof(sensor_list)/sizeof(sensor_list[0]);i++){
        for(j=0;j<sensor_list[i]->id_size;j++){
            read_id.address = sensor_list[i]->id_addr>>(8*j)&0xff;
            dev->slave_addr = sensor_list[i]->slave_addr;
            dev->read(dev, &read_id, 1);
            if(read_id.paramete != (sensor_list[i]->id_value>>(8*j)&0xff)){
                sensor_match_flag = 0;
                break;
            }
            sensor_match_flag = 1;
        }
        
        if(sensor_match_flag == 1){
            dev->index = i;
            strcpy(dev->name, sensor_list[i]->name);
            ret = 0;
            break;
        }
    }
    
    return ret;
}

/****************************************************************************/ /**
 * @brief  Image sensor config
 *
 * @param  dev: Pointer of device
 *
 * @return 0:SUCCESS -1:FAIL
 *
*******************************************************************************/
int image_sensor_config(image_sensor_device_t *dev)
{
    dev->write(dev, sensor_list[dev->index]->init_list, sensor_list[dev->index]->init_list_size);
    if(dev->callback != NULL){
        dev->callback(dev);
    }
    
    return 0;
}

/*@} end of group IMAGE_SENSOR_Public_Functions */

/*@} end of group IMAGE_SENSOR */

/*@} end of group Image_Sensor_Driver */
