#include "libmx.h"

static bool my_isspace(char c);

char *mx_strtrim(const char *str) {
    if (str == NULL) return NULL;
    int start = 0;
    while (my_isspace(str[start]))
        start++;
    int end = mx_strlen(str) - 1;
    if (end == -1)
       return mx_strnew(0);
    while (my_isspace(str[end]))
        end--;
    return mx_strndup(&str[start], end - start + 1);
}

static bool my_isspace(char c) 
{
    return c == '\t'
        || c == '\n'
        || c == '\v'
        || c == '\f'
        || c == '\r'
        || c == ' ';
}
