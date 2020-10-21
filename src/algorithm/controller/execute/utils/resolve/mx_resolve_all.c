//
// Created by Rostyslav Druzhchenko on 21.10.2020.
//

#include <ush.h>

static void resolve_tilde(char **s) {
//    errno = 1;
//    mx_setenv("ERR_TEXT", "u$h: no such user or named directory: presentatio");
    wordexp_t p;
    char **w;
    int exit_code = wordexp(*s, &p, 0);
    w = p.we_wordv;
    if (exit_code == 0 && p.we_wordc > 0) {
        char *old = *s;
        *s = mx_strdup(w[0]);
        mx_strdel(&old);
        wordfree(&p);
    }
}

static void private_envvar(char **s) {
    char *old = *s;
    *s = mx_resolve_envvars(*s);
    mx_strdel(&old);
}

static void resolve_do(char **arr) {
    int size = mx_arr_size(arr);

    for (int i = 0; i < size; i++) {
        // resolve ~
        // resolve relatives
        resolve_tilde(&(arr[i]));
        if (errno)
            break;

        // resolve ${}
        private_envvar(&(arr[i]));

        // resolve excapes
        char *s = arr[i];
        arr[i] = mx_path_resolve_all_escapes(s);
        mx_strdel(&s);
    }
}

void mx_resolve_all(t_command *command) {
    char **arr = mx_split_array_of_a_command(command->arguments);

    resolve_do(arr);

    mx_strdel(&(command->arguments));
    command->arguments = mx_str_joined_by(arr, " ");

    mx_del_strarr(&arr);
}
