#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) 
{
    void *temp = malloc(len);
    if (temp == NULL) return NULL;
    mx_memcpy(temp, src, len);
    mx_memcpy(dst, temp, len);
    free(temp);
    return dst;
}
