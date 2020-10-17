//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <libmx.h>
#include <mx_core.h>

char *mx_path_resolve(t_path *this) {
    char *temp;
    char *dir = this->p;
    if (dir[0] != '.' && dir[0] != '/' && dir[0] != '$' && dir[0] != '~') {
        char *pwd = mx_getenv("PWD");
        temp = mx_strdup(pwd);
        mx_str_append(&temp, "/");
        mx_str_append(&temp, dir);
    }
    else
        temp = mx_strdup(dir);

    wordexp_t p;
    char **w;
    wordexp(temp, &p, 0);
    w = p.we_wordv;
    char *result;
    if (p.we_wordc > 0)
        result = mx_strdup(w[0]);
    else
        result = mx_strdup(temp);
    wordfree(&p);
    mx_strdel(&temp);

    return result;
}
