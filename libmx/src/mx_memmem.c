#include "libmx.h"

void *mx_memmem(const void *haystack, size_t hs_len, const void *needle, size_t ne_len) {
    byte *hs = (byte *) haystack;
    const unsigned char *ne = (const unsigned char *) needle;

    if (ne_len == 0)
        return (void *) hs;
    if (ne_len == 1)
        return (void *) mx_memchr(hs, ne[0], hs_len);

    if (hs_len < ne_len || haystack == NULL || needle == NULL) // added NULL cases
        return NULL;
    
    const unsigned char *end = hs + hs_len - ne_len;
    while (hs <= end) {
        if (mx_memcmp(hs, ne, ne_len) == 0)
            return hs;
        hs++;
    }
    return NULL;
}
