//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

char **correct_command_retriever(char **old_arr, int bin_index) {
    int len        = mx_arr_size(old_arr) - bin_index;
    char **new_arr = mx_new_strarr(len);
    int index = 0;

    while(old_arr[bin_index]) {
        new_arr[index] = mx_string_copy(old_arr[bin_index]);
        index++;
        bin_index++;
    }
    return new_arr;
}

void mx_env_exe(char **arr, int binary_index, char *path) {
    char **new_arr = correct_command_retriever(arr, binary_index);
    path++;
    int exit_code = 0;

    char *str = mx_str_joined_by(new_arr, " ");

    if (mx_is_built_in(new_arr[0])) {
        exit_code = mx_run_built_in(new_arr[0], "");
    }
    else
        exit_code = mx_run_exec(new_arr[0], str);

    mx_del_strarr(&new_arr);
    mx_strdel(&str);
}

char *mx_three_join(char *str1, char *str2, char *str3) {
    char *str1_str2 = mx_strjoin(str1, str2);
    char *result = mx_strjoin(str1_str2, str3);

    free(str1_str2);
    return result;  
}

int mx_env_flag_u(char **arr) {
    int exit_code = 0;
    char *unset_var = 0;
    char *unset_var_value = 0;

    if (mx_arr_size(arr) == 1) {
        mx_option_requires_an_argument("u");
        return 1;
    }
    else if (mx_arr_size(arr) == 2) {
        exit_code = print_env_without_var(arr[1]);
        if (exit_code != 0)
            return exit_code;
    }
    else if (mx_arr_size(arr) > 2) {
        unset_var = getenv(arr[1]);
        if (unset_var == NULL) {
            mx_env_exe(arr, 2, getenv("PATH"));
        }
        else  {
            unset_var_value = mx_three_join(arr[1], "=", unset_var);
            unsetenv(arr[1]);
            mx_env_exe(arr, 2, getenv("PATH"));
            putenv(unset_var_value);
            free(unset_var_value);
        }
    }
    return 0;
}
