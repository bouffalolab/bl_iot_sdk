#include "mbedtls_port_key_file.h"

#include "mbedtls/platform_util.h"
#include "mbedtls/platform.h"

#include <stdio.h>
#include <vfs.h>

#define PK_VALIDATE_RET( cond )    \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_PK_BAD_INPUT_DATA )
#define PK_VALIDATE( cond )        \
    MBEDTLS_INTERNAL_VALIDATE( cond )

int mbedtls_x509_crt_parse_file( mbedtls_x509_crt *chain, const char *path )
{
    int ret;
    size_t n;
    unsigned char *buf;

    if( ( ret = mbedtls_pk_load_file( path, &buf, &n ) ) != 0 )
        return( ret );

    ret = mbedtls_x509_crt_parse( chain, buf, n );

    mbedtls_platform_zeroize( buf, n );
    mbedtls_free( buf );

    return( ret );
}

int mbedtls_pk_load_file( const char *path, unsigned char **buf, size_t *n )
{
    off_t size;
    int fd;

    PK_VALIDATE_RET( path != NULL );
    PK_VALIDATE_RET( buf != NULL );
    PK_VALIDATE_RET( n != NULL );

    if ( ( fd = aos_open( path, 0 ) ) < 0 )
        return( MBEDTLS_ERR_PK_FILE_IO_ERROR );

    if( ( size = aos_lseek( fd, 0, SEEK_END ) ) < 0 )
    {
        aos_close( fd );
        return( MBEDTLS_ERR_PK_FILE_IO_ERROR );
    }
    aos_lseek( fd, 0, SEEK_SET );

    *n = (size_t)size;

    if( *n + 1 == 0 ||
        ( *buf = mbedtls_calloc( 1, *n + 1 ) ) == NULL )
    {
        aos_close( fd );
        return( MBEDTLS_ERR_PK_ALLOC_FAILED );
    }

    if( aos_read( fd, *buf, *n ) != *n )
    {
        aos_close( fd );

        mbedtls_platform_zeroize( *buf, *n );
        mbedtls_free( *buf );

        return( MBEDTLS_ERR_PK_FILE_IO_ERROR );
    }

    aos_close( fd );

    (*buf)[*n] = '\0';


    if( strstr( (const char *) *buf, "-----BEGIN " ) != NULL )
        ++*n;

    return( 0 );
}

int mbedtls_pk_parse_keyfile( mbedtls_pk_context *ctx,
                      const char *path, const char *pwd )
{
    int ret;
    size_t n;
    unsigned char *buf;

    PK_VALIDATE_RET( ctx != NULL );
    PK_VALIDATE_RET( path != NULL );

    if( ( ret = mbedtls_pk_load_file( path, &buf, &n ) ) != 0 )
        return( ret );

    if( pwd == NULL )
        ret = mbedtls_pk_parse_key( ctx, buf, n, NULL, 0 );
    else
        ret = mbedtls_pk_parse_key( ctx, buf, n,
                (const unsigned char *) pwd, strlen( pwd ) );

    mbedtls_platform_zeroize( buf, n );
    mbedtls_free( buf );

    return( ret );
}
