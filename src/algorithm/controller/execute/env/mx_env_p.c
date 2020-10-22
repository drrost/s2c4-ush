//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

static void env_printer_wrapper(char **arr) {
    mx_print_env();
    
    int i = 2;
    while(arr[i]) {
        printf("%s\n", arr[i]);
        i++;
    }
}

void mx_specified_vars_unsetter(char **arr, int start) {
    char *var_name;
    int i = start;
    /*
     * While condition checks:
     *   '=' in arr[i] 
     *   && arr[last_elem]  != '=' 
     *   && arr[first_elem] != '='
     *   if condition == True
     *       Unset var user specified in arr[i] ("VAR=VALUE") expression
     */
    while (arr[i]
         && mx_is_in_arr(arr[i], '=') 
         && arr[i][mx_strlen(arr[i]) - 1] != '=' 
         && arr[i][0] != '=') {
        var_name = mx_substr_retriever(arr[i], 0, 
                                       mx_get_char_index(arr[i], '=') - 1);
        unsetenv(var_name);
        free(var_name);
        i++;
    }
}

int mx_env_flag_p(char **arr) {
    int binary_index;
    int exit_code = 0;

    if (mx_arr_size(arr) == 1) {
        mx_option_requires_an_argument("P");
        return 1;
    }
    if (mx_arr_size(arr) == 2) {
        mx_print_env();
        return 0;
    }
    binary_index = mx_binary_index_finder(arr, 2);
    if (arr[binary_index]) {
        mx_specified_vars_setter(arr, 2);
        exit_code = mx_env_exe(arr, binary_index, arr[1]);
        mx_specified_vars_unsetter(arr, 2);
    }
    else
        env_printer_wrapper(arr);
    return exit_code;
}
