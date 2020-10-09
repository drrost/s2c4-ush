//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

extern char **environ;

static void save_key_value(char *arr, int key_length, char *key, char *value) {
    for (int i = 0; arr[i] != '='; i++)
        key[i] = arr[i];
    for (int i = 0; arr[key_length + i + 1] != '\0'; i++)
        value[i] = arr[key_length + i + 1];
}

int mx_export(char *arguments) {
    if (mx_strlen(arguments)) {
        char *key = 0;
        char *value = 0;
        int key_length = 0;
        int value_length = 0;
        char **arr = mx_strsplit(arguments, ' ');
        for (int i = 0; i < mx_arr_size(arr); i++) {

            key_length = mx_get_char_index(arr[i], '=');
            if (key_length != -1) {
                value_length = mx_strlen(arr[i]) - key_length - 1;
                key = mx_strnew(key_length);
                value = mx_strnew(value_length);
                save_key_value(arr[i], key_length, key, value);
                mx_setenv(key, value);
                mx_strdel(&key);
                mx_strdel(&value);
            }
        }
        mx_del_strarr(&arr);
    }
    else {
        for (char **env = environ; *env; ++env)
        mx_printline(*env);
    }
    return 0;
}
