/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int params_filter(char** params,uint32_t *r)
{
    char *p ;
    uint32_t result=0;
    uint8_t base=0;

    p = *params;

    if((*p == '0') && ((*(p+1) == 'x') || (*(p+1) == 'X')) ){
        p = p + 2;
        base = 16;

    }else{
        base = 10;
    }

    while(*p){
        result *= base;
        if(*p >= '0' && *p<='9')
            result += *p-'0';
        else if(base==10)
            return -1;

        if(base==16){
            if(*p >= 'a' && *p<='f')
                result += *p-'a' + 10;
            else if(*p >= 'A' && *p<='F')
                result += *p-'A' + 10;

        }
        p++;
    }

    *r = result;
    return 0;

}


void get_bytearray_from_string(char** params, uint8_t *result,int array_size)
{

    int i = 0;
    char rand[3];

    for(i=0; i < array_size; i++){
        strncpy(rand, (const char*)*params, 2);
        rand[2]='\0';
        result[i] = strtol(rand, NULL, 16);
        *params = *params + 2;
    }
}

void get_uint8_from_string(char** params, uint8_t *result)
{
    uint32_t p = 0;
    int state=0;

    state = params_filter(params,&p);
    if(!state){
        *result = p & 0xff;
    }else
        *result = 0;
}

void get_uint16_from_string(char** params, uint16_t *result)
{
    uint32_t p = 0;
    int state=0;

    state = params_filter(params,&p);
    if(!state){
        *result = p & 0xffff;
    }else
        *result = 0;
}

void get_uint32_from_string(char** params, uint32_t *result)
{
    uint32_t p = 0;
    int state=0;

    state = params_filter(params,&p);
    if(!state){
        *result = p;
    }else
        *result = 0;
}

