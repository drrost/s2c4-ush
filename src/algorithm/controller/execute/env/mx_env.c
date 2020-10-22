//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

int mx_invalid_option_checker(char **arr) {
    if (arr[0][0] == '-') {
        if (mx_strcmp("-u", arr[0]) == 0)
            return 0;
        else if (mx_strcmp("-P", arr[0]) == 0)
            return 0;
        else if (mx_strcmp("-i", arr[0]) == 0)
            return 0;
        else if (mx_strcmp("-", arr[0]) == 0)
            return 0;
        else {
            error_msg(arr[0]);
            return 1;
        }
    }
    return 0;
}

static int flags_resolver(char **arr) {
    if (mx_strcmp("-u", arr[0]) == 0) {
        return mx_env_flag_u(arr);
    }
    else if (mx_strcmp("-i", arr[0]) == 0 || mx_strcmp("-", arr[0]) == 0) {
        return mx_env_flag_i(arr);
    }
    else if (mx_strcmp("-P", arr[0]) == 0) {
        return mx_env_flag_p(arr);
    }
    else
         mx_env_exe(arr, 1, getenv("PATH"));
    return 0;
}

int mx_env(char *args) {
    int exit_code = 0;
    if (mx_strlen(args) == 0) {
        mx_print_env();
        return exit_code;
    }
    else {
        char **arr = mx_strsplit(args, ' ');

        if (mx_invalid_option_checker(arr))
            return 1;
        exit_code = flags_resolver(arr);
        mx_del_strarr(&arr);
    }
    return exit_code;
}
