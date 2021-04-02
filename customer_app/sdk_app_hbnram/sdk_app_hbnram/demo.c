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
#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <string.h>
#include <hal_hbnram.h>
#include "demo.h"

#define hbnram_address     0x40010000
#define hbnram_size        4096
#define magic_size         4
#define hash128_size       16
#define version_size       4
#define head_reserve_size  44
#define hbnram_head_size   (hash128_size + version_size + head_reserve_size + magic_size)
#define key_size           4
#define buf_reserve_size   4
#define len_size           4
#define buf_head_size      (key_size + buf_reserve_size + len_size)
#define magic_num          0x12345678

int print_hash128(void)
{
    uint32_t *paddr;
    
    int i = 0;

    paddr = (uint32_t *)(hbnram_address + magic_size); 
    printf("hash128 \r\n");
    for (i = 0; i < 4; i++) {
        printf("%lu-", *paddr);
        paddr++;
    }
    printf("\r\n \r\n");

    return 0;
}

int print_all_data(void)
{
    uint8_t *paddr;
    int i = 0;

    paddr = (uint8_t *)hbnram_address;
    printf("print all data \r\n");

    for (i = 0; i < 4096; i++) {
        printf("%d:%d  ", i, *paddr);
        paddr++;
        if (i % 50 == 0) {
            printf("\r\n");
        }
    }

    return 0;
}

const char test_key[] = "abc";

int test_hbnram1(void)
{
    uint8_t test_arr[100];
    uint8_t recv_buf[100];
    int i = 0;
    int flag = 0;
    int ret;
    int data_size;

    for (i = 0; i < 100; i++) {
        test_arr[i] = i;
    }

    hal_hbnram_init();
    ret = hal_hbnram_alloc(test_key, 100);
    if (ret != 0) {
        printf("test_hbnram1 alloc failed \r\n");
        print_mem_map();
        return -1;
    }        

    data_size = 15;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size); 
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data1 correct \r\n");
    } else {
        printf("data1 not correct \r\n");
    }

    data_size = 20;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data2 correct \r\n");
    } else {
        printf("data2 not correct \r\n");
    }

    data_size = 37;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data3 correct \r\n");
    } else {
        printf("data3 not correct \r\n");
    }


    data_size = 1;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data4 correct \r\n");
    } else {
        printf("data4 not correct \r\n");
    }

    data_size = 3;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data5 correct \r\n");
    } else {
        printf("data5 not correct \r\n");
    }


    data_size = 4;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data5 correct \r\n");
    } else {
        printf("data5 not correct \r\n");
    }


    data_size = 73;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data6 correct \r\n");
    } else {
        printf("data6 not correct \r\n");
    }


    data_size = 100;
    hal_hbnram_buffer_set(test_key, test_arr, data_size);
    hal_hbnram_buffer_get(test_key, recv_buf, data_size);
    
    flag = memcmp(recv_buf, test_arr, data_size);
    if (flag == 0) {
        printf("data7 correct \r\n");
    } else {
        printf("data7 not correct \r\n");
    }

    print_mem_map();

    return 0;

}

const char test2_key[] = "h";
const char test3_key[] = "man";
const char test4_key[] = "na";
const char test5_key[] = "oan";
const char test6_key[] = "pmp";
const char test7_key[] = "qspd";
const char test8_key[] = "rrrzd";
const char test9_key[] = "snp";
hbnram_handle_t test2_handle;
hbnram_handle_t test3_handle;
hbnram_handle_t test4_handle;
hbnram_handle_t test5_handle;
hbnram_handle_t test6_handle;

int test_hbnram2(void)
{
    uint8_t test_buf[1000];
    uint8_t recv_buf[1000];
    int i = 0;
    int flag;

    print_hash128();
    

    for (i = 0; i < 1000; i++) {
        test_buf[i] = i % 255;
    }

    if (*(uint32_t *)hbnram_address != (uint32_t)magic_num) {
        printf("***************************************\r\n");
        printf("power down \r\n");

        hal_hbnram_init();
        print_hash128();
        hal_hbnram_alloc(test2_key, 1000);
        hal_hbnram_handle_get_fromkey(test2_key, &test2_handle);
        hal_hbnram_copy_to_stream(&test2_handle, test_buf, 25);

        for (i = 0; i < 50; i ++) {
            hal_hbnram_copy_to_stream(&test2_handle, test_buf + 25 + i, 1);
        }
        for (i = 0; i < 25; i ++) {
            hal_hbnram_copy_to_stream(&test2_handle, test_buf + 75 + i * 3, 3);
        }
        for (i = 0; i < 17; i ++) {
            hal_hbnram_copy_to_stream(&test2_handle, test_buf + 150 + i * 11, 11);
        }
        for (i = 0; i < 8; i ++) {
            hal_hbnram_copy_to_stream(&test2_handle, test_buf + 337 + i * 8, 8);
        }

        hal_hbnram_copy_to_stream(&test2_handle, test_buf + 401, 147);
        hal_hbnram_copy_to_stream(&test2_handle, test_buf + 548, 1);
        hal_hbnram_copy_to_stream(&test2_handle, test_buf + 549, 100);
        hal_hbnram_copy_to_stream(&test2_handle, test_buf + 649, 351);

        for (i = 0; i < 24; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + i * 1, 1);
        }
        for (i = 0; i < 25; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 24 + i * 2, 2);
        }
        for (i = 0; i < 26; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 74 + i * 1, 1);
        }
        for (i = 0; i < 33; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 100 + i * 3, 3);
        }
        for (i = 0; i < 1; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 199 + i * 1, 1);
        }
        for (i = 0; i < 5; i++) {
            hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 200 + i * 20, 20);
        }

        hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 300, 173);
        hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 473, 400);
        hal_hbnram_copy_from_stream(&test2_handle, recv_buf + 873, 127);

          
        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-02 correct \r\n");
        } else {
            printf("data-02 not correct flag == %d \r\n", flag);
        }
        print_hash128();
        //print_all_data();

        memset(recv_buf, 0, 1000);
        hal_hbnram_alloc(test3_key, 1000);
        hal_hbnram_handle_get_fromkey(test3_key, &test3_handle);
        hal_hbnram_copy_to_stream(&test3_handle, test_buf, 1000);
        hal_hbnram_copy_from_stream(&test3_handle, recv_buf, 1000);

        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-03 correct \r\n");
        } else {
            printf("data-03 not correct flag == %d \r\n", flag);
        }
        print_hash128();
        //print_all_data();

        memset(recv_buf, 0, 1000); 
        hal_hbnram_alloc(test4_key, 1000);
        hal_hbnram_handle_get_fromkey(test4_key, &test4_handle);
        hal_hbnram_copy_to_stream(&test4_handle, test_buf, 1000);
        hal_hbnram_copy_from_stream(&test4_handle, recv_buf, 1000);

        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-04 correct \r\n");
        } else {
            printf("data-04  not correct flag == %d \r\n", flag);
        }
        print_hash128();
        //print_all_data();

        memset(recv_buf, 0, 1000);
        hal_hbnram_alloc(test5_key, 751);
        hal_hbnram_handle_get_fromkey(test5_key, &test5_handle);
        hal_hbnram_copy_to_stream(&test5_handle, test_buf, 751);
        hal_hbnram_copy_from_stream(&test5_handle, recv_buf, 751);

        flag = memcmp(test_buf, recv_buf, 751);
        printf("flag = %d  \r\n", flag);

        if (flag == 0) {
            printf("data-05 correct \r\n");
        } else {
            printf("data-05  not correct flag == %d \r\n", flag);
        }
        print_hash128();
        //print_all_data();
        hal_hbnram_alloc(test6_key, 1);
        hal_hbnram_alloc(test7_key, 29);
        hal_hbnram_alloc(test8_key, 29);
        hal_hbnram_alloc(test7_key, 290);
        print_mem_map();

    } else if (*(uint32_t *)hbnram_address == (uint32_t)magic_num) {
        printf("###############################\r\n");
        printf("not power down, just reboot \r\n");
        
        hal_hbnram_init();
        memset(recv_buf, 0, 1000);
        hal_hbnram_handle_get_fromkey(test2_key, &test2_handle);
        hal_hbnram_copy_from_stream(&test2_handle, recv_buf, 1000);

        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-02 correct \r\n");
        } else {
                printf("data-02  not correct flag == %d \r\n", flag);
        }
        printf("reboot hash\r\n");
        print_hash128();
         
        memset(recv_buf, 0, 1000);
        hal_hbnram_handle_get_fromkey(test3_key, &test3_handle);
        hal_hbnram_copy_from_stream(&test3_handle, recv_buf, 1000);

        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-03 correct \r\n");
        } else {
            printf("data-03  not correct flag == %d \r\n", flag);
        }
        printf("reboot hash\r\n");
        print_hash128();

        memset(recv_buf, 0, 1000);
        hal_hbnram_handle_get_fromkey(test4_key, &test4_handle);
        hal_hbnram_copy_from_stream(&test4_handle, recv_buf, 1000);

        flag = memcmp(test_buf, recv_buf, 1000);
        if (flag == 0) {
            printf("data-04 correct \r\n");
        } else {
                printf("data-04  not correct flag == %d \r\n", flag);
        }
        printf("reboot hash\r\n");
        print_hash128();
                
        memset(recv_buf, 0, 1000);
        hal_hbnram_handle_get_fromkey(test5_key, &test5_handle);
        hal_hbnram_copy_from_stream(&test5_handle, recv_buf, 980);

        flag = memcmp(test_buf, recv_buf, 980);
        if (flag == 0) {
            printf("data-05 correct \r\n");
        } else {
                printf("data-05  not correct flag == %d \r\n", flag);
        }
        printf("reboot hash\r\n");
        print_hash128();
        print_mem_map();
    }
    return 0;
}

