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
#ifndef __IMAGE_SENSOR_H__
#define __IMAGE_SENSOR_H__

#include "bflb_platform.h"

/** @addtogroup  Image_Sensor_Driver
 *  @{
 */

/** @addtogroup  IMAGE_SENSOR
 *  @{
 */

/** @defgroup  IMAGE_SENSOR_Public_Types
 *  @{
 */

/**
 *  @brief CAM configuration strcut definition
 */

typedef struct
{
    uint8_t address;  /*!< Address of command */
    uint8_t paramete; /*!< paramete of command */
} image_sensor_command_t;

typedef struct
{
    char name[10];                      /*!< Name of sensor */
    uint8_t slave_addr;                 /*!< Slave address of sensor */
    uint8_t id_size;                    /*!< Size of sensor ID */
    uint32_t id_addr;                   /*!< ID address of sensor */
    uint32_t id_value;                  /*!< ID value of sensor */
    uint32_t init_list_size;            /*!< Size of init list */
    image_sensor_command_t *init_list;  /*!< Pointer of init list */
} image_sensor_configure_t;

typedef struct image_sensor_device
{
    uint32_t index;                                                                                         /*!< Index of sensor */
    char name[10];                                                                                          /*!< Name of sensor */
    uint8_t slave_addr;                                                                                     /*!< Slave address of sensor */
    int (*read)(struct image_sensor_device *dev, image_sensor_command_t *read_list, uint32_t list_size);    /*!< Read function */
    int (*write)(struct image_sensor_device *dev, image_sensor_command_t *write_list, uint32_t list_size);  /*!< Write function */
    int (*callback)(struct image_sensor_device *dev);                                                       /*!< Callback function */
} image_sensor_device_t;

/*@} end of group IMAGE_SENSOR_Public_Types */

/** @defgroup  IMAGE_SENSOR_Public_Constants
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Public_Constants */

/** @defgroup  IMAGE_SENSOR_Public_Macros
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Public_Macros */

/** @defgroup  IMAGE_SENSOR_Public_Functions
 *  @{
 */
int image_sensor_scan(image_sensor_device_t *dev);
int image_sensor_config(image_sensor_device_t *dev);

/*@} end of group IMAGE_SENSOR_Public_Functions */

/*@} end of group IMAGE_SENSOR */

/*@} end of group Image_Sensor_Driver */

#endif /* __IMAGE_SENSOR_H__ */
