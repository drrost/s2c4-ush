//
// Created by Karina Barinova on 11.10.2020.
//

#include <ush.h>

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
