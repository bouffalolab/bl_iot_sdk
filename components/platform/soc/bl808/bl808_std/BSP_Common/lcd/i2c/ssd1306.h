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
#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "stdint.h"

#define SSD1306_CMD 0
#define SSD1306_DAT 1

#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64

#define OLED_CS_PIN  GPIO_PIN_10
#define OLED_DC_PIN  GPIO_PIN_22
#define OLED_RES_PIN GPIO_PIN_11

#define CS1_HIGH gpio_write(OLED_CS_PIN, 1)
#define CS1_LOW  gpio_write(OLED_CS_PIN, 0)
#define DC_HIGH  gpio_write(OLED_DC_PIN, 1)
#define DC_LOW   gpio_write(OLED_DC_PIN, 0)
#define RES_HIGH gpio_write(OLED_RES_PIN, 1)
#define RES_LOW  gpio_write(OLED_RES_PIN, 0)

void ssd1306_init(void);
void ssd1306_display_on(void);
void ssd1306_display_off(void);
void ssd1306_refresh_gram(void);
void ssd1306_clear_screen(uint8_t fill);
void ssd1306_draw_point(uint8_t x, uint8_t y, uint8_t mode);
void ssd1306_display_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void ssd1306_display_string(uint8_t x, uint8_t y, const char *string, uint8_t size, uint8_t mode);
void ssd1306_display_chinese(uint8_t x, uint8_t y, uint8_t no, uint8_t mode);
void ssd1306_draw_bmp(uint8_t x, uint8_t y, const unsigned char *image, uint8_t index, uint8_t mode);
void ssd1306_draw_alpha(uint8_t x, uint8_t y, const unsigned char *image, uint8_t index, uint8_t mode);
#endif