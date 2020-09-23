#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) 
{
    if (s1 == NULL && s2 == NULL)
        return NULL;
    if (s1 == NULL || s2 == NULL) {
        if (s1 == NULL)
            return mx_strdup(s2);
        else
            return mx_strdup(s1);
    }
    char *p = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    if (p == NULL)
        return NULL;
    mx_strcpy(p, s1);
    mx_strcat(p, s2);
    return p;
}
