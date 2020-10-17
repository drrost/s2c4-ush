//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

static void save_key_value(char *arr, int key_length, char *key, char *value) {
    for (int i = 0; arr[i] != '='; i++)
        key[i] = arr[i];
    for (int i = 0; arr[key_length + i + 1] != '\0'; i++)
        value[i] = arr[key_length + i + 1];
}

static void mx_print_export(void) {
    t_map *env = mx_env_get();
    t_list *list = env->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        printf("%s=%s\n", pair->key, pair->value);
        list = list->next;
    }
    mx_map_delete(&env);
}

static void mx_export_error(const char *s) {
    mx_printerr("export: not an identifier: ");
    mx_printerr(s);
    mx_printerr("\n");
}

static void mx_export_del(char *key, char *value) {
    mx_strdel(&key);
    mx_strdel(&value);
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
                if (mx_isdigit(key[0])) {
                    mx_export_error(key);
                    mx_export_del(key, value);
                    mx_del_strarr(&arr);
                    return 1;
                }
                mx_setenv(key, value);
                mx_export_del(key, value);
            }
            mx_setenv(arr[i], "''");
        }
        mx_del_strarr(&arr);
    }
    else
        mx_print_export();
    return 0;
}
