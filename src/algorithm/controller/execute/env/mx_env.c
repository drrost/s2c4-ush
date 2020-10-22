//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>
extern char **environ;

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
    // else if (mx_strcmp("-P", arr[0]) == 0) {
    //     mx_env_flag_p(arr);
    //     return;
    // }
    else
         mx_env_exe(arr, 1, getenv("PATH"));
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
