#include "libmx.h"

static bool my_isspace(char c) 
{
    return c == '\t'
        || c == '\n'
        || c == '\v'
        || c == '\f'
        || c == '\r'
        || c == ' ';
}

static void add_char_in_string(char *s, char c, int *j) 
{
    s[*j] = c;
    (*j)++;
}

char *mx_del_extra_spaces(const char *str) 
{
    if (str == NULL) return NULL;
    char *s = mx_strtrim(str);
    char *new_str = mx_strnew(mx_strlen(s));
    bool flag = false;
    int j = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (my_isspace(s[i])) {
            if (flag) {
                add_char_in_string(new_str, ' ', &j);
            }
            flag = false;
        }
        else {
            add_char_in_string(new_str, s[i], &j);
            flag = true;
        }
        
    }
    char *ss = mx_strndup(new_str, mx_strlen(new_str));
    free(new_str);
    free(s);
    return ss;
}
