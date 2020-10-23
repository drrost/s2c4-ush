//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>
#include <private/mx_cd_private.h>

static bool has_permission_to_execute(t_path *path) {
    DIR *dir = opendir(path->p);
    if (dir == 0)
        return false;
    closedir(dir);
    return true;
}

static void cd_print_error(const char *title, const char *details) {
    mx_printerr("cd: ");
    mx_printerr(title);
    mx_printerr(": ");
    mx_printerr(details);
    mx_printerr("\n");
}

int mx_cd_validate_input(char flag, const char *dir) {

    t_path *path = mx_path_new(dir);
    char *full_path = mx_cd_resolve_path(dir);
    mx_strdel(&(path->p));
    path->p = full_path;
    int exit_code = 0;

    const char *flags = "sP-";
    if (!(flag == 0 || mx_get_char_index(flags, flag) >= 0)) {
        mx_printerr("cd: string not in pwd: -");
        mx_printerr_char(flag);
        mx_printerr("\n");
        exit_code = 1;
    }

    // cd . . -> cd: string not in pwd:

    if (path->exists(path) == false) {
        cd_print_error("no such file or directory", dir);
        exit_code = 1;
    }
    else if (path->is_dir(path) == false) {
        cd_print_error("not a directory", dir);
        exit_code = 1;
    }
    else if (has_permission_to_execute(path) == false) {
        cd_print_error("permission denied", dir);
        exit_code = 1;
    }

    mx_path_del(&path);
    return exit_code;
}
