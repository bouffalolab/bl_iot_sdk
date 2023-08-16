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
#ifndef __XRAM_API_H__
#define __XRAM_API_H__
#include <stdint.h>

#define XRAM_SIZE (16 * 1024)
#define XRAM_META_RING_LENGTH (512 + 1)

#if 0
#define xram_log(M, ...) printf(M, ##__VA_ARGS__)
#else
#define xram_log(M, ...) \
    do {                 \
    } while (0);
#endif

struct xram_head {
    uint32_t ver; /* version */
    uint32_t cnt; /* discard log counter */
};

enum xram_ring_id {
    XRAM_RING_ID_LOG_C906,       /* Log Ring */
    XRAM_RING_ID_LOG_E902,       /* Log Ring */
    XRAM_RING_ID_NET,            /* Ethernet Ring */
    XRAM_RING_ID_PERIPHERAL,     /* Peripherals Ring */
    XRAM_RING_ID_RPC,            /* RPC Ring */
    XRAM_RING_ID_AIn1_C906_E902, /* C906 and E902 All In One Ring */
    XRAM_RING_ID_AIn1_E907_E902, /* E907 and E902 All In One Ring */
    XRAM_RING_ID_MAX             /* total Queue size*/
};

void XRAMHeadCntClear(void);
void XRAMHeadCntIncrease(void);
void XRAMHeadCntSet(uint32_t val);
int XRAMHeadCntGet(void);

/*
 * Function: int XRAMHeadInit(void)
 * Description: The XRAMHeadInit() is used for XRAM head init.like version.
 * Param:  void
 * Return: If sucessful, the return value is 0, otherwise,-1 indicating the err.
 * Others:
 */
int XRAMHeadInit(void);

/*
 * Function: int XRAMRingInit(void)
 * Description: The XRAMRingInit() is used for meta ring init.
 * Param:  void
 * Return: If sucessful, the return value is 0, otherwise,-1 indicating the err.
 * Others:
 */
int XRAMRingInit(void);

/*
 * Function: int XRAMRingReset(void)
 * Description: The XRAMRingInit() is used for meta ring init.
 * Param: ringid is ring id.
 * Return: If sucessful, the return value is 0, otherwise,-1 indicating the err.
 * Others:
 */
int XRAMRingReset(uint32_t ringid);

/*
 * Function: int XRAMRingWrite(uint32_t ringid, void *const buffer, uint32_t size);
 * Description: The XRAMRingWrite() function copies size bytes string pointed to by buffer,
 * to the ring buffer which id is ringid.
 * Param:
 *  ringid: rang id, is from 0 to 2.
 *  buffer: is a ptr which point to xram address.
 *  size: buffer size.
 * The size indicate buffer length which you will write to ring buffer.
 * Return: These calls return the number of bytes sent. If ring buffer is full, return 0.
 * Others:
 */
int XRAMRingWrite(uint32_t ringid, void *const buffer, uint32_t size);

/*
 * Function: int XRAMRingWriteTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout);
 * Description: The XRAMRingWriteTimeout() function copies size bytes string pointed to by buffer,
 * to the ring buffer pointed to by ringid. If ring is full, wait for timeout usec microseconds.
 * Param:
 *  ringid: rang id is from 0 to 2.
 *  buffer: a ptr which point to xram address.
 *  size: buffer size.
 *  timeout: waiting time,usec microseconds.
 * Return: These calls return the number of bytes sent. If ring buffer is full, return 0.
 * Others:
 */
int XRAMRingWriteTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout);

/*
 * Function: int XRAMRingRead(uint32_t ringid, void *const buffer, uint32_t size);
 * Description: The XRAMRingRead() function attempts to read up to size bytes from ring buffer
 * which id is ringid into the buffer.
 * Param:
 *  ringid: rang id is from 0 to 2.
 *  buffer: a ptr which point to xram address.
 *  size: buffer size.
 * Return: These calls return the number of bytes read. If ring buffer is empty, return 0.
 * Others:
 */
int XRAMRingRead(uint32_t ringid, void *const buffer, uint32_t size);

/*
 * Function: int XRAMRingReadTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout);
 * Description: The XRAMRingReadTimeout() function attempts to read up to size bytes from ring buffer
 * which id is ringid into the buffer.If ring is empty, wait for timeout usec mocroseconds.
 * Param:
 *  ringid: rang id, is from 0 to 2.
 *  buffer: a ptr, which point to xram address.
 *  size: buffer size.
 *  timeout: waiting time, usec microsecond.
 * Return: These calls return the number of bytes read. If ring buffer is empty, return 0.
 * Others:
 */
int XRAMRingReadTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout);
#endif
