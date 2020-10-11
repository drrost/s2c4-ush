//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

static void print_env(void) {

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

void env_i(char **arr, int i) {
    for (int j = i + 1; arr[j]; j++) {
        mx_printline(arr[j]);
    }
}

void env_u(char **arr, int i) {
    if (!arr[i + 2]) {
        mx_unsetenv(arr[i + 1]);
        print_env();
    }
    else {
        mx_printerr("env: ");
        mx_printerr(arr[i + 2]);
        mx_printerr(": No such file or directory\n");
    }
}

static int env_flags(char **args) {
    int i = 0;

    for (; args[i]; i++)
        for (int j = 0; args[i][j]; j++)
            if (args[i][0] == '-') {
                if (args[i][1] == 'P') {
                    if (!args[i + 1] && !args[i][2]) {
                        mx_printerr("env: option requires an argument -- P\n");
                        return 0;
                    }
                }
                if (args[i][1] == 'i') {
                    env_i(args, i);
                    return 0;
                }
                if (args[i][1] == 'u') {
                    if (!args[i + 1] && !args[i][2]) {
                        mx_printerr("env: option requires an argument -- u\n");
                        return 0;
                    }
                    else {
                        env_u(args, i);
                        return 0;
                    }
                }
                else {
                    mx_printerr("env: illegal option -- ");
                    write(2, &args[i][1], 1);
                    mx_printerr("\n");
                    return 0;
                }
            }

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
