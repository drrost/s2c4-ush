//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>
#include <private/mx_cd_private.h>

int mx_cd_validate_input(char flag, const char *dir) {

    t_path *path = mx_path_new(dir);
    char *full_path = mx_cd_resolve_path(dir);
    mx_strdel(&(path->p));
    path->p = full_path;

    const char *flags = "sP-";
    if (!(flag == 0 || mx_get_char_index(flags, flag) >= 0)) {
        mx_printerr("cd: string not in pwd: -");
        mx_printerr_char(flag);
        mx_printerr("\n");
    }

    // cd Makefile cd: not a directory: Makefile
    // cd ddd - > cd: no such file or directory: ddd
    // cd /.fseventsd -> cd: permission denied: /.fseventsd

    // cd . . -> cd: string not in pwd:

    int exit_code = 0;

    if (path->exists(path) == false) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(dir);
        mx_printerr("\n");
        exit_code = 1;
    }

    mx_path_del(&path);
    return exit_code;
}
