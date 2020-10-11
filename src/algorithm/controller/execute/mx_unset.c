//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

int mx_unset(char *arguments) {
    if (mx_strlen(arguments)) {
        char **arr = mx_strsplit(arguments, ' ');
        for (int i = 0; i < mx_arr_size(arr); i++) {
            if (mx_isalpha(arr[i][0]) || arr[i][0] == '_')
                mx_unsetenv(arr[i]);
            else if (mx_strcmp(arr[i], "-") == 0) {
                mx_printerr("unset: not enough arguments\n");
                return 1;
            }
            else {
                mx_printerr("unset: bad option: -");
                mx_printerr_char(arr[i][1]);
                mx_printerr("\n");
                return 1;
            }
        }
        mx_del_strarr(&arr);
    }
    else {
        mx_printerr("unset: not enough arguments\n");
        return 1;
    }
    return 0;
}
