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


#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <osal.h>
//this function is used to format the char string to the argc mode
//this function will changed the original string, used it carefully
//return how many arguments has been
int string_to_arg(int *argc, const char *argv[],char *string)
{
    int argvlen = 0;
    int paramnum = 0;
    char *tmp = NULL;
    char bak;
    int len;

    argvlen = *argc;
    *argc = paramnum;
    if(NULL == string)
    {
        return paramnum;
    }

    //use the '\0' to replace the ' '
    len = strlen(string);
    tmp = string;
    while(tmp < (string + len))
    {
        if(*tmp == ' ')
        {
            *tmp = '\0';
        }
        tmp++;
    }
    bak = '\0';
    tmp = string;
    while(tmp < (string + len))
    {
        if((*tmp != '\0')&&(bak =='\0'))
        {
            if(paramnum < argvlen)
            {
                argv[paramnum] = tmp;
                paramnum++;
            }
        }
        bak = *tmp;
        tmp++;
    }
    *argc = paramnum;

    return paramnum;
}


char *osal_strdup(const char *ch)
{
    char *copy;
    size_t length;

    if(NULL == ch)
        return NULL;

    length = strlen(ch);
    copy = (char *)osal_malloc(length + 1);
    if(NULL == copy)
        return NULL;
    (void) strncpy(copy, ch, length);
    copy[length] = '\0';

    return copy;
}

char *osal_strcat(char *str[])
{
    char *ret = NULL;
    int str_tnum = 0;
    int str_tlen = 0;
    int str_off = 0;
    int i = 0;

    if(NULL == str)
    {
        return ret;
    }

    while(NULL != str[i])
    {
        str_tlen += strlen(str[i]);
        str_tnum++;
        i++;
    }

    ret = osal_malloc(str_tlen);
    if(NULL != ret)
    {
        for(i =0;i< str_tnum;i++)
        {

            (void) memcpy(ret + str_off,str[i],strlen(str[i]));
            str_off += strlen(str[i]);
        }
        ret[str_off] = '\0';
    }

    return ret;
}

/*
int hexstr2byte(const char *bufin, int len, char *bufout)
{
    int i = 0;
    unsigned char tmp2 = 0x0;
    unsigned int tmp = 0;
    char cc;

    if (NULL == bufin || len <= 0 || NULL == bufout)
    {
        return -1;
    }
    for(i = 0; i < len; i = i+2)
    {
        tmp2 =  (unsigned char )bufin[i];
        tmp2 =  tmp2 <= '9'?(unsigned char)(unsigned int)(tmp2-0x30):(unsigned char)(unsigned int)(tmp2-0x37);
        cc = bufin[i+1];
        tmp =  (unsigned int)(unsigned char)cc;
        tmp =  tmp <= '9'?(unsigned int)(tmp-0x30):(unsigned int)(tmp-0x37);
        bufout[i/2] =(tmp2<<4)|(tmp&0x0F);
    }
    return 0;
}

*/

int hexstr2byte(const char *buf, int len, char *bufout)
{
    int ret = -1;
    int i = 0;
    uint8_t low;
    uint8_t high;

    if (NULL == buf || len <= 0 || NULL == bufout)
    {
        return ret;
    }

    ret = 0;
    for(i = 0; i < len; i = i+2)
    {
        if(((buf[i]) >= '0') && (buf[i] <= '9'))
        {
            high = (uint8_t)( buf[i] - '0');
        }
        else if((buf[i] >= 'A') && (buf[i] <= 'F'))
        {
            high = (uint8_t)( buf[i] - 'A') + 10;
        }
        else if((buf[i] >= 'a') && (buf[i] <= 'f'))
        {
            high = (uint8_t)( buf[i] - 'a') + 10;
        }
        else
        {
            ret = -1;
            break;
        }

        if(((buf[i+1]) >= '0') && (buf[i+1] <= '9'))
        {
            low = (uint8_t)( buf[i+1] - '0');
        }
        else if((buf[i+1] >= 'A') && (buf[i+1] <= 'F'))
        {
            low = (uint8_t)( buf[i+1] - 'A') + 10;
        }
        else if((buf[i+1] >= 'a') && (buf[i+1] <= 'f'))
        {
            low = (uint8_t)( buf[i+1] - 'a') + 10;
        }
        else
        {
            ret = -1;
            break;
        }

        bufout[i/2] = (char)((high<<4)|(low&0x0F));
    }
    return ret;
}



//make a byte to 2 ascii hex
int byte2hexstr(uint8_t *bufin, int len, char *bufout)
{
    int i = 0;
    uint8_t tmp_l = 0x0;
    uint8_t tmp_h = 0;
    if ((NULL == bufin )|| (len <= 0 )||( NULL == bufout))
    {
        return -1;
    }
    for(i = 0; i < len; i++)
    {
        tmp_h = (bufin[i]>>4)&0X0F;
        tmp_l = bufin[i] &0x0F;
        bufout[2*i] = (tmp_h > 9)? (tmp_h - 10 + 'a'):(tmp_h +'0');
        bufout[2*i + 1] = (tmp_l > 9)? (tmp_l - 10 + 'a'):(tmp_l +'0');
    }
    bufout[2*len] = '\0';

    return 0;
}






