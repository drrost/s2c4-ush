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

int env_not_found(const char *s) {
    mx_printerr("env: ");
    mx_printerr(s);
    mx_printerr(": No such file or directory\n");
    return 127;
}

static int find_equal_sign(char **arr, int i) {
    for (int j = i + 1; arr[j]; j++) {
        if (mx_get_char_index(arr[j], '=') == -1)
            return j;
    }
    return 0;
}

int env_i(char **arr, int i) {
    int status = 0;
    int index = 0;
    for (int j = i + 1; arr[j]; j++) {
        if ((index = find_equal_sign(arr, i)) == 0)
            mx_printline(arr[j]);
        else {
            status = env_not_found(arr[index]);
            break;
        }
    }
    return status;
}

int env_u(char **arr, int i) {
    int status = 0;
    if (!arr[i + 2]) {
        mx_unsetenv(arr[i + 1]);
        print_env();
    }
    else
        status = env_not_found(arr[i + 2]);
    return status;
}

int env_option_required(char c) {
    mx_printerr("env: option requires an argument -- ");
    write(2, &c, 1);
    mx_printerr("\n");
    return 1;
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
