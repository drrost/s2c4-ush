//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>

char *mx_cd_resolve_path(const char *dir) {
    t_path *path = mx_path_new(dir);
    char *result = path->reslolve(path);
    mx_path_del(&path);
    return result;
}
