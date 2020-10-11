//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

void print_env(void) {

    t_map *env = mx_env_get();
    t_list *list = env->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_printstr(pair->key);
        mx_printstr("=");
        mx_printstr(pair->value);
        mx_printstr("\n");
        list = list->next;
    }
}

static int env_flags(char **args) {
    int i = 0;

    for (; args[i]; i++)
        for (int j = 0; args[i][j]; j++)
            if (args[i][0] == '-') {
                if (!args[i][1] && args[i + 1])
                    return env_not_found(args[i + 1]);
                if (args[i][1] == 'P')
                    if (!args[i + 1] && !args[i][2])
                        return env_option_required(args[i][1]);
                if (args[i][1] == 'i') {
                    return env_i(args, i);
                }
                if (args[i][1] == 'u') {
                    if (!args[i + 1] && !args[i][2])
                        return env_option_required(args[i][1]);
                    else
                        return env_u(args, i);
                }
                else {
                    mx_printerr("env: illegal option -- ");
                    write(2, &args[i][1], 1);
                    mx_printerr("\n");
                    return 0;
                }
            }
            else
                return env_not_found(args[i]);

    return 0;
} 

int mx_env(const char *args) {
    int status = 0;
    if (mx_strlen(args) == 0) {
        print_env();
        return 0;
    }
    else {
        char **arr = mx_strsplit(args, ' ');
        status = env_flags(arr);
        mx_del_strarr(&arr);
    }
    return status;
}
