#ifndef MBEDTLS_PORT_KEY_FILE_H_BVYIJLEF
#define MBEDTLS_PORT_KEY_FILE_H_BVYIJLEF

#include <mbedtls/x509_crt.h>

int mbedtls_x509_crt_parse_file( mbedtls_x509_crt *chain, const char *path );
int mbedtls_pk_load_file( const char *path, unsigned char **buf, size_t *n );
int mbedtls_pk_parse_keyfile( mbedtls_pk_context *ctx,
                      const char *path, const char *pwd );

#endif /* end of include guard: MBEDTLS_PORT_KEY_FILE_H_BVYIJLEF */
