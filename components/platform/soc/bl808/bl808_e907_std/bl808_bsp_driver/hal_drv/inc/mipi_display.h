/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#ifndef MIPI_DISPLAY_H
#define MIPI_DISPLAY_H

/**
 * struct drm_panel - DRM panel object
 */
struct drm_panel {
    /**
	 * @dev:
	 *
	 * Parent device of the panel.
	 */
    struct device *dev;

    /**
	 * @backlight:
	 *
	 * Backlight device, used to turn on backlight after the call
	 * to enable(), and to turn off backlight before the call to
	 * disable().
	 * backlight is set by drm_panel_of_backlight() and drivers
	 * shall not assign it.
	 */
    struct backlight_device *backlight;

    /**
	 * @funcs:
	 *
	 * Operations that can be performed on the panel.
	 */
    const struct drm_panel_funcs *funcs;

    /**
	 * @connector_type:
	 *
	 * Type of the panel as a DRM_MODE_CONNECTOR_* value. This is used to
	 * initialise the drm_connector corresponding to the panel with the
	 * correct connector type.
	 */
    int connector_type;

    /**
	 * @list:
	 *
	 * Panel entry in registry.
	 */
    //struct list_head list;
};

/* MIPI DSI Processor-to-Peripheral transaction types */
enum {
    MIPI_DSI_V_SYNC_START = 0x01,
    MIPI_DSI_V_SYNC_END = 0x11,
    MIPI_DSI_H_SYNC_START = 0x21,
    MIPI_DSI_H_SYNC_END = 0x31,

    MIPI_DSI_COMPRESSION_MODE = 0x07,
    MIPI_DSI_END_OF_TRANSMISSION = 0x08,

    MIPI_DSI_COLOR_MODE_OFF = 0x02,
    MIPI_DSI_COLOR_MODE_ON = 0x12,
    MIPI_DSI_SHUTDOWN_PERIPHERAL = 0x22,
    MIPI_DSI_TURN_ON_PERIPHERAL = 0x32,

    MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM = 0x03,
    MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM = 0x13,
    MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM = 0x23,

    MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM = 0x04,
    MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM = 0x14,
    MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM = 0x24,

    MIPI_DSI_DCS_SHORT_WRITE = 0x05,
    MIPI_DSI_DCS_SHORT_WRITE_PARAM = 0x15,

    MIPI_DSI_DCS_READ = 0x06,
    MIPI_DSI_EXECUTE_QUEUE = 0x16,

    MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE = 0x37,

    MIPI_DSI_NULL_PACKET = 0x09,
    MIPI_DSI_BLANKING_PACKET = 0x19,
    MIPI_DSI_GENERIC_LONG_WRITE = 0x29,
    MIPI_DSI_DCS_LONG_WRITE = 0x39,

    MIPI_DSI_PICTURE_PARAMETER_SET = 0x0a,
    MIPI_DSI_COMPRESSED_PIXEL_STREAM = 0x0b,

    MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20 = 0x0c,
    MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24 = 0x1c,
    MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16 = 0x2c,

    MIPI_DSI_PACKED_PIXEL_STREAM_30 = 0x0d,
    MIPI_DSI_PACKED_PIXEL_STREAM_36 = 0x1d,
    MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12 = 0x3d,

    MIPI_DSI_PACKED_PIXEL_STREAM_16 = 0x0e,
    MIPI_DSI_PACKED_PIXEL_STREAM_18 = 0x1e,
    MIPI_DSI_PIXEL_STREAM_3BYTE_18 = 0x2e,
    MIPI_DSI_PACKED_PIXEL_STREAM_24 = 0x3e,
};

/* MIPI DSI Peripheral-to-Processor transaction types */
enum {
    MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT = 0x02,
    MIPI_DSI_RX_END_OF_TRANSMISSION = 0x08,
    MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE = 0x11,
    MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE = 0x12,
    MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE = 0x1a,
    MIPI_DSI_RX_DCS_LONG_READ_RESPONSE = 0x1c,
    MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE = 0x21,
    MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE = 0x22,
};

/* MIPI DCS commands */
enum {
    MIPI_DCS_NOP = 0x00,
    MIPI_DCS_SOFT_RESET = 0x01,
    MIPI_DCS_GET_COMPRESSION_MODE = 0x03,
    MIPI_DCS_GET_DISPLAY_ID = 0x04,
    MIPI_DCS_GET_ERROR_COUNT_ON_DSI = 0x05,
    MIPI_DCS_GET_RED_CHANNEL = 0x06,
    MIPI_DCS_GET_GREEN_CHANNEL = 0x07,
    MIPI_DCS_GET_BLUE_CHANNEL = 0x08,
    MIPI_DCS_GET_DISPLAY_STATUS = 0x09,
    MIPI_DCS_GET_POWER_MODE = 0x0A,
    MIPI_DCS_GET_ADDRESS_MODE = 0x0B,
    MIPI_DCS_GET_PIXEL_FORMAT = 0x0C,
    MIPI_DCS_GET_DISPLAY_MODE = 0x0D,
    MIPI_DCS_GET_SIGNAL_MODE = 0x0E,
    MIPI_DCS_GET_DIAGNOSTIC_RESULT = 0x0F,
    MIPI_DCS_ENTER_SLEEP_MODE = 0x10,
    MIPI_DCS_EXIT_SLEEP_MODE = 0x11,
    MIPI_DCS_ENTER_PARTIAL_MODE = 0x12,
    MIPI_DCS_ENTER_NORMAL_MODE = 0x13,
    MIPI_DCS_GET_IMAGE_CHECKSUM_RGB = 0x14,
    MIPI_DCS_GET_IMAGE_CHECKSUM_CT = 0x15,
    MIPI_DCS_EXIT_INVERT_MODE = 0x20,
    MIPI_DCS_ENTER_INVERT_MODE = 0x21,
    MIPI_DCS_SET_GAMMA_CURVE = 0x26,
    MIPI_DCS_SET_DISPLAY_OFF = 0x28,
    MIPI_DCS_SET_DISPLAY_ON = 0x29,
    MIPI_DCS_SET_COLUMN_ADDRESS = 0x2A,
    MIPI_DCS_SET_PAGE_ADDRESS = 0x2B,
    MIPI_DCS_WRITE_MEMORY_START = 0x2C,
    MIPI_DCS_WRITE_LUT = 0x2D,
    MIPI_DCS_READ_MEMORY_START = 0x2E,
    MIPI_DCS_SET_PARTIAL_ROWS = 0x30, /* MIPI DCS 1.02 - MIPI_DCS_SET_PARTIAL_AREA before that */
    MIPI_DCS_SET_PARTIAL_COLUMNS = 0x31,
    MIPI_DCS_SET_SCROLL_AREA = 0x33,
    MIPI_DCS_SET_TEAR_OFF = 0x34,
    MIPI_DCS_SET_TEAR_ON = 0x35,
    MIPI_DCS_SET_ADDRESS_MODE = 0x36,
    MIPI_DCS_SET_SCROLL_START = 0x37,
    MIPI_DCS_EXIT_IDLE_MODE = 0x38,
    MIPI_DCS_ENTER_IDLE_MODE = 0x39,
    MIPI_DCS_SET_PIXEL_FORMAT = 0x3A,
    MIPI_DCS_WRITE_MEMORY_CONTINUE = 0x3C,
    MIPI_DCS_SET_3D_CONTROL = 0x3D,
    MIPI_DCS_READ_MEMORY_CONTINUE = 0x3E,
    MIPI_DCS_GET_3D_CONTROL = 0x3F,
    MIPI_DCS_SET_VSYNC_TIMING = 0x40,
    MIPI_DCS_SET_TEAR_SCANLINE = 0x44,
    MIPI_DCS_GET_SCANLINE = 0x45,
    MIPI_DCS_SET_DISPLAY_BRIGHTNESS = 0x51,  /* MIPI DCS 1.3 */
    MIPI_DCS_GET_DISPLAY_BRIGHTNESS = 0x52,  /* MIPI DCS 1.3 */
    MIPI_DCS_WRITE_CONTROL_DISPLAY = 0x53,   /* MIPI DCS 1.3 */
    MIPI_DCS_GET_CONTROL_DISPLAY = 0x54,     /* MIPI DCS 1.3 */
    MIPI_DCS_WRITE_POWER_SAVE = 0x55,        /* MIPI DCS 1.3 */
    MIPI_DCS_GET_POWER_SAVE = 0x56,          /* MIPI DCS 1.3 */
    MIPI_DCS_SET_CABC_MIN_BRIGHTNESS = 0x5E, /* MIPI DCS 1.3 */
    MIPI_DCS_GET_CABC_MIN_BRIGHTNESS = 0x5F, /* MIPI DCS 1.3 */
    MIPI_DCS_READ_DDB_START = 0xA1,
    MIPI_DCS_READ_PPS_START = 0xA2,
    MIPI_DCS_READ_DDB_CONTINUE = 0xA8,
    MIPI_DCS_READ_PPS_CONTINUE = 0xA9,
};

/* MIPI DCS pixel formats */
#define MIPI_DCS_PIXEL_FMT_24BIT 7
#define MIPI_DCS_PIXEL_FMT_18BIT 6
#define MIPI_DCS_PIXEL_FMT_16BIT 5
#define MIPI_DCS_PIXEL_FMT_12BIT 3
#define MIPI_DCS_PIXEL_FMT_8BIT  2
#define MIPI_DCS_PIXEL_FMT_3BIT  1

#endif