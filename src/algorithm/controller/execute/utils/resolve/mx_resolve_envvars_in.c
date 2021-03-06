//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#include <ush.h>

static char *next_envvar(char *s) {
    const char *prefix = "${";
    int prefix_len = mx_strlen(prefix);
    char *begin = mx_strstr(s, prefix);

    if (begin == 0)
        return 0;

    char *end = mx_strstr(s, "}");
    if (end == 0)
        return 0;

    int result_len = end - begin - prefix_len;
    return mx_strndup(begin + prefix_len, result_len);
}

char *mx_resolve_envvars(char *s) {
    char *envvar = 0;
    s = mx_strdup(s);
    char *value = 0;

    while (1) {
        envvar = next_envvar(s);

        if (envvar == 0)
            break;

        value = mx_getenv(envvar);
        if (value != NULL)
            value = mx_strdup(value);
        else
            value = mx_strdup("");
        char *buff = mx_strnew(mx_strlen(envvar) + 3);
        sprintf(buff, "${%s}", envvar);
        char *old_s = s;
        s = mx_str_replace(s, buff, value);
        mx_strdel(&old_s);
        mx_strdel(&buff);
        mx_strdel(&envvar);
        mx_strdel(&value);
    }

    return s;
}
