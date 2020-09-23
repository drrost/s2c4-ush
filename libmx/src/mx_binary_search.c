#include "libmx.h"

static int compare(char *s1, char *s2);

int mx_binary_search(char **arr, int size, const char *s, int *count) 
{
    if (!count) return -1;

    *count = 0; // dont forget
    
    if (size <= 0) return -1;

    if (!s || !arr || !(*arr)) return -1;

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        (*count)++; // dont forget
        int mid = left + (right - left) / 2;
        if (compare((char *)s, arr[mid]) < 0)
            right = mid - 1;
        else if (compare((char *)s, arr[mid]) > 0)
            left = mid + 1;
        else
            return mid;
    }
    *count = 0;
    return -1;
}

static int compare(char *s1, char *s2) {
    return mx_strcmp(s1, s2);
}
