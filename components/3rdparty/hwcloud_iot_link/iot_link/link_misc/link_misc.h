/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#ifndef LITEOS_LAB_IOT_LINK_LINK_MISC_LINK_MISC_H_
#define LITEOS_LAB_IOT_LINK_LINK_MISC_LINK_MISC_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief:use this function to make a string to argc and args mode
 *
 * @param[in/out]:argc, how many buffer in the argc
 *
 * @param[in/out]:argv, the buffer for the args
 *
 * @param[in]:string, the string to be format
 *
 *
 * @return:how many parameters in the string
 *
 * */
int string_buffer_to_arg(int *argc, const char *argv[],char *string);

/**
 *
 * @brief: use this function to clone a string
 *
 * @param[in]: source string
 *
 * @return: the clone string
 *
 * */

char *osal_strdup(const char *ch);



/**
 *
 *                       dataoff
 * ring buffer map:       |  ----datalen-------
 *                        | /                   \
 *                        |/                     \
 *   ----------------------------------------------------------
 *   |     empty space    |//////valid data///////|           |
 *   ----------------------------------------------------------
 *   | \                                                      /
 *   |  \                                                    /
 *   |   \                                                  /
 *   |     ---------------buflen--------------------------
 *  buf
 *
 *  attention that do dump read or write means no data will really write or read,
 *  it only changed the dataoff or datalen, and you make sure that the dump read
 *  or write length  is legal
 *
 * */

/**
 * @brief: this is the ring buffer data structure, implement as the common function
 *
 * */
typedef struct
{
    unsigned char   *buf;      ///< which means the buffer
    int              buflen;   ///< which means the buffer limit
    int              datalen;  ///< which means how many data in the buffer
    int              dataoff;  ///< which means the valid data offset in the buffer
}tag_ring_buffer_t;

typedef tag_ring_buffer_t  ring_buffer_t;

/**
 * @brief:use this function to make a new ring handle
 *
 * @param[in]:ring,which will be initialized
 *
 * @param[in]:buf, which will be used as the cache for the ring
 *
 * @param[in]:buflen, the length of buf
 *
 * @param[in]:offset, the initialize data offset
 *
 * @param[in]:datalen, the initialize data length
 *
 * @return: 0 success while -1 failed
 *
 * */


int ring_buffer_init(tag_ring_buffer_t *ring,unsigned char *buf, int buflen,int offset,int datalen);



/**
 * @brief:use this function to write data to the ring buffer
 *
 * @param[in]:ring,which will be written
 *
 * @param[in]:buf, the data buffer
 *
 * @param[in]:len, the buffer length
 *
 * @return: how many bytes has been written while -1 means failed
 *
 * */
int ring_buffer_write(tag_ring_buffer_t *ring,unsigned char *buf, int len);

/**
 * @brief:use this function to read data from the ring buffer
 *
 * @param[in]:ring,which will be read
 *
 * @param[in]:buf, the data buffer
 *
 * @param[in]:len, the buffer length
 *
 * @return: how many bytes has been read while -1 failed
 *
 * */

int ring_buffer_read(tag_ring_buffer_t *ring,unsigned char *buf, int len);

#define ring_buffer_buf(x)          (x->buf)
#define ring_buffer_buflen(x)       (x->buflen)
#define ring_buffer_data(x)         (x->buf + x->dataoff)
//#define ring_buffer_datalen(x)      (x->datalen)
//#define ring_buffer_freespace(x)    (x->buflen - x->datalen)

#define ring_buffer_dataoff(x)      (x->dataoff)
#define ring_buffer_dumpread(x,y)   do{x->dataoff = (x->dataoff + y)%x->buflen; x->datalen -= y;}while(0)
#define ring_buffer_dumpwrite(x,y)  do{x->datalen += y;)while(0)

/**
 * @brief:use this function check out how many data in the ring buffer
 *
 * @param[in]:ring,which will be checked

 * @return: how many data bytes while -1 failed
 *
 * */
int ring_buffer_datalen(tag_ring_buffer_t *ring);

/**
 * @brief:use this function check out how many free space in the ring buffer
 *
 * @param[in]:ring,which will be checked

 * @return: how many free space  bytes while -1 failed
 *
 * */
int ring_buffer_freespace(tag_ring_buffer_t *ring);

/**
 * @brief:use this function to reset the ring buffer
 *
 * @param[in]:ring,which will be reset

 * @return: 0 success while -1 failed
 *
 * */
int ring_buffer_reset(tag_ring_buffer_t *ring);

/**
 * @brief:use this function to deinit the ring buffer
 *
 * @param[in]:ring,which will be deinit

 * @return: 0 success while -1 failed
 *
 * */
int ring_buffer_deinit(tag_ring_buffer_t *ring);


///< random
/**
 * @brief: use this function to generate the random ,could be reprogramed by yourelf
 *
 * @param[in]:output, this is the random data storage buffer
 * @param[in]:len, the output buffer length
 *
 * @retrun:0 success while -1 failed
 *
 * */
int link_random(void* output, int len);


/**
 * @brief: use this function to translate the string to argv mode
 *
 * @param[in]:string , the string to translate
 * @param[inout]:argc, the sizeof argv and how many prarameters has been splited
 * @param[inout]:argv, used to storage the parameters splited
 *
 * @retrun:how many parameters geted
 *
 * */
int string_to_arg(int *argc, const char *argv[],char *string);

/**
 * @brief: use this function to add the string list to one string
 *
 * @param[in]:str[] the array to add, end with NULL
 *
 * @retrun:the str added, NULL if failed
 *
 * */

char *osal_strcat(char *str[]);

int hexstr2byte(const char *bufin, int len, char *bufout);

int byte2hexstr(uint8_t *bufin, int len, char *bufout);





#endif /* LITEOS_LAB_IOT_LINK_LINK_MISC_LINK_MISC_H_ */
