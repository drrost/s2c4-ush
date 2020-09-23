#include "libmx.h"

static bool replace_first(char **new_str, char *old_str, char *sub, char *replace);

char *mx_replace_substr(const char *str, const char *sub, const char *replace) 
{
    if (str == NULL || sub == NULL || replace == NULL) return NULL;
    if (mx_strlen(str) == 0 || mx_strlen(sub) == 0 || mx_strlen(replace) == 0)
        return (char *)str;

    char *old_str = (char *) str;
    char *new_str = NULL;
    replace_first(&new_str, old_str, (char *)sub, (char *)replace);
    old_str = new_str;
    while (replace_first(&new_str, old_str, (char *)sub, (char *)replace)) {
        free(old_str);
        old_str = new_str;
    }
    free(old_str);
    return new_str;
}

static bool replace_first(char **new_str, char *old_str, char *sub, char *replace) 
{
    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int old_str_len = mx_strlen(old_str);
    int index = mx_get_substr_index(old_str, sub);
    
    if (index != -1) {
        *new_str = mx_strnew(old_str_len - sub_len + replace_len);
        mx_strncpy(*new_str, old_str, index);
        mx_strcat(*new_str, replace);
        mx_strcat(*new_str, &old_str[index + sub_len]);
        return true;
    }
    *new_str = mx_strdup(old_str);
    return false;
}
