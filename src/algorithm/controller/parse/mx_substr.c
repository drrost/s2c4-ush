#include <ush.h>

char *mx_substr(const char *src, int start, int end) {
    char *result = (char *)malloc(end - start + 1);
    int iter = 0;

    for (int i = start; i < end && src[i] != '\0'; i++) {
        result[iter++] = src[i];
    }
    result[iter] = '\0';
    return result;
}
