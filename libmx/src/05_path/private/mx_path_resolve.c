//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <libmx.h>

static char *hadle_relatives(char *s) {
    char *result;
    char *dir = s;
    if (mx_str_begins_with(dir, "..") ||
        (dir[0] != '.' && dir[0] != '/' && dir[0] != '$' && dir[0] != '~')) {
        char *pwd = mx_getenv("PWD");
        result = mx_strdup(pwd);
        mx_str_append(&result, "/");
        mx_str_append(&result, dir);
    }
    else
        result = mx_strdup(dir);
    return result;
}

static char *resolve_relatives(char *s) {
    wordexp_t p;
    char **w;
    int exit_code = wordexp(s, &p, 0);
    w = p.we_wordv;
    char *result;
    if (exit_code == 0 && p.we_wordc > 0) {
        result = mx_strdup(w[0]);
        wordfree(&p);
    }
    else
        result = mx_strdup(s);

    return result;
}

char *mx_path_resolve(t_path *this) {
    char *temp = mx_path_resolve_all_escapes(this->p);
    char *old = temp;
    temp = hadle_relatives(temp);
    mx_strdel(&old);

    char *result = resolve_relatives(temp);

    mx_strdel(&temp);

    char *resolved = realpath(result, 0);
    mx_strdel(&result);
    result = mx_strdup(resolved);

    return result;
}
