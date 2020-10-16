//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#include <ush.h>

static char *next_envvar(char *s) {

    // TODO: implement a REAL search of env variables.
    //       It's most likely we should use regexs here.
    //

    s++;
    static int count = 0;
    count++;
    if (count == 2)
        return mx_strdup("PWD");
    return 0;
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
