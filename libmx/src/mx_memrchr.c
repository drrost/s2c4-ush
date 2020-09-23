#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) 
{
    byte *src = (byte *)s;
    byte chr = (byte)c;
    for (int i = n - 1; i >= 0; i--) {
        if(src[i] == chr)
            return src + i;
    }
    return NULL;
}
