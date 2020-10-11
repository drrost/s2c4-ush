//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <private/mx_cd_private.h>
#include <ush.h>

char *mx_cd_resolve_path(const char *dir) {
    t_path *path = mx_path_new(dir);
    const char *home_dir = mx_get_home_dir();
    const char *pwd_dir = mx_get_pwd_dir();

    char *result = path->reslolve(path, home_dir, pwd_dir);

    mx_path_del(&path);
    return result;
}
