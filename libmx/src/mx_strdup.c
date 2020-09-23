#include "libmx.h"

char *mx_strdup(const char *src) 
{
    return mx_strcpy(mx_strnew(mx_strlen(src)), src);
}
