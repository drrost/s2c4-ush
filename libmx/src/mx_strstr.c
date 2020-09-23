#include "libmx.h"

static int my_strncmp(const char *s1, const char *s2, int n);

char *mx_strstr(const char *s1, const char *s2) 
{
    char *s = (char *) s1;
    int l = mx_strlen(s2);
    while (*s) {
        if (my_strncmp(s, s2, l) == 0) {
            return s;
        }
        s++;
    }
    return NULL;
}

static int my_strncmp(const char *s1, const char *s2, int n) 
{
    int i = 0;
    while ((s1[i] == s2[i]) && s1[i] && s2[i] && i < n) {
        i++;
    }
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}
