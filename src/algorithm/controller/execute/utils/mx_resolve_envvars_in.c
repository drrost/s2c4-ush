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

static char *resolve_envars(char *s) {
    char *envvar = 0;
    s = mx_strdup(s);

    while (1) {
        envvar = next_envvar(s);

        if (envvar == 0)
            break;

        char *value = mx_getenv(envvar);
        char *buff = mx_strnew(mx_strlen(envvar) + 3);
        sprintf(buff, "${%s}", envvar);
        char *old_s = s;
        s = mx_str_replace(s, buff, value);
        mx_strdel(&old_s);
        mx_strdel(&buff);
        mx_strdel(&envvar);
    }

    return s;
}

void mx_resolve_envvars_in(t_command *command) {
    // Resolve envvars in name
    char *new_name = resolve_envars(command->name);
    mx_strdel(&(command->name));
    command->name = new_name;

    // Resolve envvars in arguments
    char *new_arguments = resolve_envars(command->arguments);
    mx_strdel(&(command->arguments));
    command->arguments = new_arguments;
}
