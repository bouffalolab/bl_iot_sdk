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
#ifndef __BL808_DVP2BUS_H__
#define __BL808_DVP2BUS_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BL808_DVP2BUS_SW_MODE_AUTO = 0,
    BL808_DVP2BUS_SW_MODE_MANUAL,
} BL808_DVP2BUS_SW_MODE;

typedef enum {
    BL808_DVP2BUS_AHB_BURST_SINGLE = 0,//3'b000
    BL808_DVP2BUS_AHB_BURST_INCR4 = 0x3,//3'b011
    BL808_DVP2BUS_AHB_BURST_INCR8 = 0x5,//3'b101
    BL808_DVP2BUS_AHB_BURST_INCR16 = 0x7,//3'b111
} BL808_DVP2BUS_AHB_BURST;

typedef enum {
    BL808_DVP2BUS_LINE_ACTIVE_POLARITY_LOW,
    BL808_DVP2BUS_LINE_ACTIVE_POLARITY_HIGH,
} BL808_DVP2BUS_LINE_ACTIVE_POLARITY;

typedef enum {
    BL808_DVP2BUS_FRAME_ACTIVE_POLARITY_LOW,
    BL808_DVP2BUS_FRAME_ACTIVE_POLARITY_HIGH,
} BL808_DVP2BUS_FRAME_ACTIVE_POLARITY;

typedef enum {
    BL808_DVP2BUS_SENSOR_MODE_V_AND_H = 0,
    BL808_DVP2BUS_SENSOR_MODE_V_OR_H,
    BL808_DVP2BUS_SENSOR_MODE_V,
    BL808_DVP2BUS_SENSOR_MODE_H
} BL808_DVP2BUS_SENSOR_MODE;

typedef enum {
    BL808_DVP2BUS_16_BIT = 0,
    BL808_DVP2BUS_8_BIT,
} BL808_DVP2BUS_BITWIDTH;

typedef enum {
    BL808_DVP2BUS_A = 0,
    BL808_DVP2BUS_B,
    BL808_DVP2BUS_C,
    BL808_DVP2BUS_NUM,
} BL808_DVP2BUS_TYPE;

typedef struct _bl808_dvp2bus_mode {
    bool swap_mode_en;
    BL808_DVP2BUS_FRAME_ACTIVE_POLARITY frame_valid;
    BL808_DVP2BUS_LINE_ACTIVE_POLARITY line_valid;
} bl808_dvp2bus_mode_t;

#define BL808_DVP2BUS_CONFIG_FSM_WAIT 0x40
#define BL808_DVP2BUS_INT_INDEX_NORMAL 0
#define BL808_DVP2BUS_INT_INDEX_MEMORY 1
#define BL808_DVP2BUS_INT_INDEX_FRAME  2
#define BL808_DVP2BUS_INT_INDEX_FIFO   3

typedef struct _bl808_dvp2bus {
    BL808_DVP2BUS_TYPE type;
    bl808_dvp2bus_mode_t mode;
    BL808_DVP2BUS_SW_MODE sw_mode;
    BL808_DVP2BUS_SENSOR_MODE sensor_mode;
    BL808_DVP2BUS_AHB_BURST burst;
    uint8_t *buffer;
    uint32_t size;
    int isbusy;
    bool is_8bit;
    bool is_upper_byte;
    uint32_t swap_frame0_addr;
    uint32_t swap_frame1_addr;
    void (*int_rx)(struct _bl808_dvp2bus *dvp2bus, uint8_t *frame_ptr, uint32_t fram_size, uint32_t frames_total, uint32_t error);
} bl808_dvp2bus_t;

int bl808_dvp2bus_init(bl808_dvp2bus_t *dvp2bus);
int bl808_dvp2bus_deinit(BL808_DVP2BUS_TYPE type);
int bl808_dvp2bus_enable(BL808_DVP2BUS_TYPE type);
int bl808_dvp2bus_disable(BL808_DVP2BUS_TYPE type);
int bl808_dvp2bus_set_mode(BL808_DVP2BUS_TYPE type, bl808_dvp2bus_mode_t *mode);
int bl808_dvp2bus_set_bitwidth(BL808_DVP2BUS_TYPE type, BL808_DVP2BUS_BITWIDTH bitwidth);

/*the max value of frame is 32:0x1F*/
int bl808_dvp2bus_frame_interval_configure(bl808_dvp2bus_t *dvp2bus, int frame);
int bl808_dvp2bus_frame_complete(bl808_dvp2bus_t *dvp2bus, uint8_t **frame, uint32_t *size, uint32_t *frames, uint32_t *status);
int bl808_dvp2bus_frame_wait(bl808_dvp2bus_t *dvp2bus, uint8_t **frame, uint32_t *size, uint32_t *frames, uint32_t *status);
int bl808_dvp2bus_frame_try(bl808_dvp2bus_t *dvp2bus, uint8_t **frame, uint32_t *size, uint32_t *frames, uint32_t *status);
int bl808_dvp2bus_frame_pop(BL808_DVP2BUS_TYPE type);
int bl808_dvp2bus_frame_status(bl808_dvp2bus_t *dvp2bus, uint32_t *status);
void bl808_dvp2bus_frame_auto_pop_enable(int enable);

#endif
