//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

static int mx_count_el(char **arr) {
    int i = 0;

    if (arr != NULL) {
        while (arr[i])
            i++;
        return i;
    }
    return 0;
}

int mx_unset(char *arguments) {
    if (mx_strlen(arguments)) {
        char **arr = mx_strsplit(arguments, ' ');
        for (int i = 0; i < mx_count_el(arr); i++) {
            if (mx_isalpha(arr[i][0]) || arr[i][0] == '_')
                unsetenv(arr[i]);
            else if (mx_strcmp(arr[i], "-") == 0) {
                mx_printerr("unset: not enough arguments\n");
                return 1;
            }
            else {
                mx_printerr("unset: bad option: -");
                write(2, &arr[i][1], 1);
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
