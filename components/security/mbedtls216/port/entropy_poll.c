/*
 *  Platform-specific and custom entropy polling functions
 *
 *  Copyright (C) 2006-2016, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_ENTROPY_C)

#include "mbedtls/entropy.h"
#include "mbedtls/entropy_poll.h"

#if defined(MBEDTLS_TIMING_C)
#include <string.h>
#include "mbedtls/timing.h"
#endif
#if defined(MBEDTLS_HAVEGE_C)
#include "mbedtls/havege.h"
#endif
#if defined(MBEDTLS_ENTROPY_NV_SEED)
#include "mbedtls/platform.h"
#endif

extern int bl_rand();
int mbedtls_platform_entropy_poll( void *data,
                           unsigned char *output, size_t len, size_t *olen )
{
    // FILE *file;
    // size_t read_len;
    ((void) data);
    size_t i;
    *olen = 0;
    unsigned int rand_buf = 0;
#if defined(HAVE_GETRANDOM)
    if( has_getrandom == -1 )
        has_getrandom = ( check_version_3_17_plus() == 0 );

    if( has_getrandom )
    {
        int ret;

        if( ( ret = getrandom_wrapper( output, len, 0 ) ) < 0 )
            return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );

        *olen = ret;
        return( 0 );
    }
#endif /* HAVE_GETRANDOM */

    // file = fopen( "/dev/urandom", "rb" );
    // if( file == NULL )
    //      return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );

    // read_len = fread( output, 1, len, file );
    // if( read_len != len )
    // {
    //     fclose( file );
    //     return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );
    // }

    // fclose( file );
    for(i = 0;i < len;i++) {
        if(0 == (i % 4)) {
            rand_buf = bl_rand();
        }
        output[i] = rand_buf & 0xff;
        rand_buf = rand_buf >> 8;
    }
    *olen = len;

    return( 0 );
}

#endif /* MBEDTLS_ENTROPY_C */
