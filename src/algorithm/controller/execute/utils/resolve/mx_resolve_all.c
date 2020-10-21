//
// Created by Rostyslav Druzhchenko on 21.10.2020.
//

#include <ush.h>

static void substitute_escapes_forward(char **line) {
    mx_str_replace_p(line, "\\ ", MX_SPACE_SUBSTITUTION);
    mx_str_replace_p(line, "\\'", MX_APPOS_SUBSTITUTION);
    mx_str_replace_p(line, "\\\\", MX_SLASH_SUBSTITUTION);
}

static void substitute_escapes_back(char **line) {
    mx_str_replace_p(line, MX_SPACE_SUBSTITUTION, "\\ ");
    mx_str_replace_p(line, MX_APPOS_SUBSTITUTION, "\\'");
    mx_str_replace_p(line, MX_SLASH_SUBSTITUTION, "\\\\");
}

static void resolve_tilde(char **s) {
//    errno = 1;
//    mx_setenv("ERR_TEXT", "u$h: no such user or named directory: presentatio");
    wordexp_t p;
    char **w;
    substitute_escapes_forward(s);
    int exit_code = wordexp(*s, &p, 0);
    w = p.we_wordv;
    if (exit_code == 0 && p.we_wordc > 0) {
        char *old = *s;
        *s = mx_strdup(w[0]);
        mx_strdel(&old);
        wordfree(&p);
    }
    substitute_escapes_back(s);
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
    }
}

static char **split_arguments(char *line) {
    char *escaped = mx_str_replace(line, "\\ ", MX_SPACE_SUBSTITUTION);
    char **result = mx_strsplit(escaped, ' ');
    mx_strdel(&escaped);
    int size = mx_arr_size(result);

    for (int i = 0; i < size; i++) {
        mx_str_replace_p(&(result[i]), MX_SPACE_SUBSTITUTION, "\\ ");
    }

    return result;
}

void mx_resolve_all(t_command *command) {
    char **arr = split_arguments(command->arguments);

    resolve_do(arr);

    mx_strdel(&(command->arguments));
    command->arguments = mx_str_joined_by(arr, " ");

    mx_del_strarr(&arr);
}
