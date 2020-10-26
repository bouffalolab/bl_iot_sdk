#include <string.h>
#include <mbedtls/mycalloc.h>
void *mycalloc(size_t numitems, size_t size)
{
  size_t sizel = numitems * size;
  void *ptr = pvPortMalloc(sizel);
  memset(ptr, 0, sizel);
  return ptr;
}
