#ifndef __UTILS_STRING_H__
#define __UTILS_STRING_H__
void get_bytearray_from_string(char** params, uint8_t *result,int array_size);
void get_uint8_from_string(char** params, uint8_t *result);
void get_uint16_from_string(char** params, uint16_t *result);
void get_uint32_from_string(char** params, uint32_t *result);
void utils_parse_number(const char *str, char sep, uint8_t *buf, int buflen, int base);
void utils_parse_number_adv(const char *str, char sep, uint8_t *buf, int buflen, int base, int *count);
unsigned long long convert_arrayToU64(uint8_t* inputArray);
void convert_u64ToArray(unsigned long long inputU64, uint8_t result[8]);
void utils_memcpy8(void *dst, void *src, size_t len);
void utils_memcpy16(void *dst, void *src, size_t len);
void utils_memcpy32(void *dst, void *src, size_t len);
void utils_memcpy64(void *dst, void *src, size_t len);
void utils_memset8(void *src, uint8_t n, size_t len);
void utils_memset16(void *src, uint16_t n, size_t len);
void utils_memset32(void *src, uint32_t n, size_t len);
void utils_memset64(void *src, uint64_t n, size_t len);
void utils_memset8_with_seq(void *src, uint8_t seq, size_t len);
void utils_memset16_with_seq(void *src, uint16_t seq, size_t len);
void utils_memset32_with_seq(void *src, uint32_t seq, size_t len);
void utils_memset64_with_seq(void *src, uint64_t seq, size_t len);
void utils_memdrain8(void *src, size_t len);
void utils_memdrain16(void *src, size_t len);
void utils_memdrain32(void *src, size_t len);
void utils_memdrain64(void *src, size_t len);
void * utils_memdrain8_with_check(void *src, size_t len, uint8_t seq);
void * utils_memdrain16_with_check(void *src, size_t len, uint16_t seq);
void * utils_memdrain32_with_check(void *src, size_t len, uint32_t seq);
void * utils_memdrain64_with_check(void *src, size_t len, uint64_t seq);
#endif
