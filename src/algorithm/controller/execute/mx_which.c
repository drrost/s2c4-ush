//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>
#include <mx_core.h>

static void mx_not_found(char *str) {
    mx_printerr(str);
    mx_printerr(" not found\n");
}

static int check_flag(char *str, int *flag) {
    for (int y = 1; y < mx_strlen(str); y++) {
        if (str[y] == 's' && *flag != 2)
            *flag = 1;
        else if (str[y] == 'a')
            *flag = 2;
        else {
            mx_printerr("which: bad option: -");
            mx_printerr_char(str[y]);
            mx_printerr("\n");
            return -1;
        }
    }
    return 0;
}

int mx_which(char *arguments) {
    if (mx_strlen(arguments) > 0) {
        char **arr = mx_strsplit(arguments, ' ');
        int flag = 0;
        int exit_code = 0;

        for (int i = 0; i < mx_arr_size(arr); i++) {
            if (mx_strcmp(arr[i], "--") == 0)
                flag = 3;
            else if (arr[i][0] == '-' && flag < 3) {
                if ((exit_code = check_flag(arr[i], &flag)) == -1) {
                    mx_del_strarr(&arr);
                    return 1;
                }
                else if ((exit_code = check_flag(arr[i], &flag)) == 0)
                     continue;
            }
            mx_check_command(arr[i], &exit_code, flag);
            if (exit_code == 1)
                mx_not_found(arr[i]);
        }
        mx_del_strarr(&arr);
        return exit_code;
    }
    return 1;
}
