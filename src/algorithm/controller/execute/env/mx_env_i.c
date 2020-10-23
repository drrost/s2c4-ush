//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>
extern char **environ;

int mx_is_in_arr(char *s, char c) {
    for (int i = 0; i < mx_strlen(s); ++i) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}

static void env_ignore() {
    int eq_index;
    char *var_name;

    int i = 0;
    while(environ[i]) {
        eq_index = mx_get_char_index(environ[i], '=');
        var_name = mx_substr_retriever(environ[i], 0, eq_index - 1);
        if (mx_strcmp("PATH", var_name) != 0 && mx_strcmp("LOGNAME", var_name) != 0 && mx_strcmp("SHLVL", var_name) != 0 
            && mx_strcmp("PWD", var_name) != 0 && mx_strcmp("OLDPWD", var_name) != 0 && mx_strcmp("PATH", var_name) != 0
            && mx_strcmp("_", var_name) != 0 && mx_strcmp("LESS", var_name) != 0 && mx_strcmp("ZSH", var_name) != 0
            && mx_strcmp("PAGER", var_name) != 0) {
            unsetenv(var_name);
        }
        free(var_name);
        i++;
    }
    unsetenv("TERM");
    unsetenv("XPC_FLAGS");
    unsetenv("TERM_PROGRAM");
    unsetenv("TERM_SESSION_ID");
    unsetenv("TERM_PROGRAM_VERSION");

}

int mx_binary_index_finder(char **arr, int start) {
    int i = start;

     while (arr[i]
         && mx_is_in_arr(arr[i], '=') 
         && arr[i][mx_strlen(arr[i]) - 1] != '=' 
         && arr[i][0] != '=') {
        i++;
    }
    return i;
}

void mx_specified_vars_setter(char **arr, int start) {
    int i = start;

    while (arr[i]
         && mx_is_in_arr(arr[i], '=') 
         && arr[i][mx_strlen(arr[i]) - 1] != '=' 
         && arr[i][0] != '=') {
        putenv(arr[i]);
        i++;
    }
}

void mx_specified_vars_unset(char **arr, int start) {
    char **name_value;
    int i = start;

    while (arr[i]
        && mx_is_in_arr(arr[i], '=') 
        && arr[i][mx_strlen(arr[i]) - 1] != '=' 
        && arr[i][0] != '=') {
        name_value = mx_strsplit(arr[i], '=');
        unsetenv(name_value[0]);
        mx_del_strarr(&name_value);
        i++;
    }
}

static void print_specified_vars(char **arr) {
    int i = 1;

    while(arr[i]) {
        mx_printline(arr[i]);
        i++;
    }
}

static void env_restore(char **copy_env) {
    int i = 0;

    while(copy_env[i]) {
        if (mx_strcmp("PATH", copy_env[i]) != 0 && mx_strcmp("LOGNAME", copy_env[i]) != 0 && mx_strcmp("SHLVL", copy_env[i]) != 0 
            && mx_strcmp("PWD", copy_env[i]) != 0 && mx_strcmp("OLDPWD", copy_env[i]) != 0 && mx_strcmp("PATH", copy_env[i]) != 0
            && mx_strcmp("_", copy_env[i]) != 0 && mx_strcmp("LESS", copy_env[i]) != 0 && mx_strcmp("ZSH", copy_env[i]) != 0
            && mx_strcmp("PAGER", copy_env[i]) != 0)
            putenv(copy_env[i]);
        i++;
    }
}

int mx_env_flag_i(char **arr) {
    int binary_index;
    int exit_code = 0;
    char **copy_env = mx_arr_copy(environ);

    if (mx_arr_size(arr) == 1) {
        mx_del_strarr(&copy_env);
        return 0;
    }
    env_ignore(); //TO DO: find out why this function has to be called a couple of times to show no envvars
    binary_index = mx_binary_index_finder(arr, 1);
    if (arr[binary_index]) {
        mx_specified_vars_setter(arr, 2);
        exit_code = mx_env_exe(arr, binary_index, getenv("PATH"));
        mx_specified_vars_unset(arr, 2);
    }
    else
        print_specified_vars(arr);
    env_restore(copy_env);
    mx_del_strarr(&copy_env);
    return exit_code;
}
