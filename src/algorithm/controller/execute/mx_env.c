//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

void mx_print_env(void) {
    t_map *env = mx_env_get();
    t_list *list = env->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_printstr(pair->key);
        mx_printstr("=");
        mx_printstr(pair->value);
        mx_printstr("\n");
        list = list->next;
    }
    mx_map_delete(&env);
}

// void env_print_err(char a, int flag) {
//     if (flag == 1) {
//         mx_printerr("env: illegal option -- ");
//         mx_printerr_char(a);
//         mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\n");
//         mx_printerr("           [name=value ...] [utility [argument ...]]\n");
//         exit(EXIT_FAILURE);
//     }
//     if (flag == 2) {
//         mx_printerr("env: option requires an argument -- P");
//         mx_printerr("\nusage: env [-i] [-P utilpath] [-u name]\n");
//         mx_printerr("           [name=value ...] [utility [argument ...]]\n");
//         exit(EXIT_FAILURE);
//     }
// }

// static void get_command(char **com, char *args) {
//     char *bin[] = {"env", "export", "unset", "pwd", "exit", "cd",
//                    "which", "echo", "true", "false", "arch", NULL};
//     int (*bin_f[])() = {&mx_env, &mx_export, &mx_unset, &mx_pwd, &mx_exit,
//                         &mx_cd, &mx_which, &mx_echo, &mx_true, &mx_false,
//                         &mx_arch};

//     for (int i = 0; bin[i]; i++) {
//         if (!mx_strcmp(com[0], bin[i])) {
//             char *sub = mx_strstr(args, com[0]);
//             int comlen = mx_strlen(com[0]);
//             while (comlen > 0) {
//                 sub++;
//                 comlen--;
//             }
//             if (sub == NULL) {
//                 (*bin_f[i])("");
//             }
//             else
//                 (*bin_f[i])(sub);
//             return;
//         }
//     }
//     mx_run_exec(com[0], args);
// }

// void env_mode(char *args, int *pos) {
//     char **arr = mx_strsplit(args, ' ');
//     int com_count = 0;
//     char **com_new = NULL;

//     if (!arr[(*pos)]) {
//         mx_print_env();
//         return;
//     }

//     for (;arr[(*pos)]; (*pos)++, com_count++);
//     (*pos) -= com_count;
//     com_new = malloc(sizeof(char *) * com_count);
//     for (int i = 0; i < com_count; i++, (*pos)++)
//         com_new[i] = mx_strdup(arr[(*pos)]);
//     com_new[com_count] = NULL;
//     get_command(com_new, args);
//     mx_del_strarr(&com_new);
//     mx_del_strarr(&arr);
// }

// void env_flags_equal(char *args, int *pos) {
//     char **arr = mx_strsplit(args, ' ');

//     for (int i = 0; arr[i] && i <= (*pos); i++) {
//         if (mx_get_char_index(arr[i], '=') > 0) {
//             (*pos) = i + 1;
//             mx_setenv(mx_strndup(arr[i], mx_get_char_index(arr[i], '=')),
//                    arr[i] + mx_get_char_index(arr[i], '=') + 1);
//         }
//     }
//     mx_del_strarr(&arr);
// }

// void env_p(char *args, int *pos) {
//     char **arr = mx_strsplit(args, ' ');

//     for (int i = 0; arr[i]; i++) {
//         if (mx_strcmp(arr[i], "-P") == 0) {
//             if (!arr[i + 1])
//                 env_print_err('a', 2);
//             mx_setenv("PATH", arr[i + 1]);
//             if ((*pos) < i + 1)
//                 (*pos) = i + 2;
//         }
//     }
//     mx_del_strarr(&arr);
// }

// void env_u(char *args, int *pos) {
//     char **arr = mx_strsplit(args, ' ');
    
//     for  (int i = 0; arr[i]; i++) {
//         if (mx_strcmp(arr[i], "-u") == 0) {
//             if ((*pos) <= i)
//                 (*pos) = i + 1;
//             for (int j = i + 1; arr[j]; j++) {
//                 if (!mx_getenv(arr[j]))
//                     break;
//                 (*pos) = j + 1;

//             }
//         } 
//     }
//     mx_del_strarr(&arr);
// }

// void env_i(char *args, int *pos) { //not finished flag
//     char **arr = mx_strsplit(args, ' ');

//     for (int i = 0; arr[i]; i++) {
//         if (mx_strcmp(arr[i], "-i") == 0) {
//             t_map *env = mx_env_get();
//             t_list *list = env->content;
//             while (list) {
//                 t_pair *pair = (t_pair *)list->data;
//                 mx_unsetenv(pair->key);
//                 list = list->next;
//              }
//              (*pos) = i + 1;
//             mx_map_delete(&env);
//         }
//     }
//     mx_del_strarr(&arr);
// }

// void env_handle_error(char *args) {
//     char **arr = mx_strsplit(args, ' ');
//     for (int i = 0; arr[i] && mx_strcmp(arr[i], "--") != 0; i++)
//         if (arr[i][0] == '-' && !mx_is_built_in(arr[i + 1]))
//             for (int j = 1; arr[i][j]; j++)
//                 if (arr[i][j] != 'i' && arr[i][j] != 'u' && arr[i][j] != 'P') {
//                     env_print_err(arr[i][j], 1);
//                 }
//     mx_del_strarr(&arr);
// }

static void error_msg(char *option) {
    char *msg  = "env: illegal option "; 
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    write(2, msg,    mx_strlen(msg));
    write(2, option, mx_strlen(option));
    write(2, "\n", 1);
    write(2, msg1,   mx_strlen(msg1));
    write(2, msg2,   mx_strlen(msg2));
}

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

void mx_option_requires_an_argument(char *option) {
    char *msg  = "env: option requires an argument -- ";
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    write(2, msg, mx_strlen(msg));
    write(2, option, mx_strlen(option));
    write(2, "\n", 1);
    write(2, msg1, mx_strlen(msg1));
    write(2, msg2, mx_strlen(msg2));
}

static int print_env_without_var(char *var_name) {
    if (mx_get_char_index(var_name, '=') != -1) {
        mx_printerr("env: unsetenv ");
        mx_printerr(var_name);
        mx_printerr(": Invalid argument\n");
        return 1;
    }
    unsetenv(var_name);
    mx_print_env();
    return 0;
}

char *mx_three_join(char *str1, char *str2, char *str3) {
    char *str1_str2 = mx_strjoin(str1, str2);
    char *result = mx_strjoin(str1_str2, str3);

    free(str1_str2);
    return result;  
}


char **mx_new_strarr(int number_of_str) {
    char **arr = (char **)malloc((number_of_str + 1) * sizeof(char *));

    arr[number_of_str] = NULL;
    return arr;
}

char *mx_string_copy(char *str) {
    char *new_str = mx_strnew(mx_strlen(str));
    char *pointer = new_str;
    int i = 0;

    while(str[i]) {
        *pointer = str[i];
        pointer++;
        i++;
    }
    pointer = NULL;
    return new_str;
}

static char **correct_command_retriever(char **old_arr, int bin_index) {
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

    char *str = mx_str_joined_by(new_arr, " ");

    mx_run_exec(new_arr[0], str);
    mx_del_strarr(&new_arr);
    mx_strdel(&str);
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

static int flags_resolver(char **arr) {
    if (mx_strcmp("-u", arr[0]) == 0) {
        return mx_env_flag_u(arr);
    }
    // else if (mx_strcmp("-i", arr[0]) == 0 || mx_strcmp("-", arr[0]) == 0) {
    //     mx_env_flag_i(arr);
    //     return;
    // }
    // else if (mx_strcmp("-P", arr[0]) == 0) {
    //     mx_env_flag_p(arr);
    //     return;
    // }
    // else
    //     mx_env_exe(arr, 1, getenv("PATH"));
    return 0;
}

int mx_env(char *args) {
    if (mx_strlen(args) == 0) {
        mx_print_env();
        return 0;
    }
    else {
        int exit_code = 0;
        char **arr = mx_strsplit(args, ' ');
        
        if (mx_invalid_option_checker(arr))
            return 1;
        exit_code = flags_resolver(arr);
        mx_del_strarr(&arr);
    }
    return 0;
}
