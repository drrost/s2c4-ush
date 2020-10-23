//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>
#include <private/mx_cd_private.h>

static bool is_path_has_symlinks(char *dir) {
    t_path *path = mx_path_new(dir);
    bool result = false;

    while (mx_strlen(path->p) > 0) {
        struct stat buf;
        lstat(path->p, &buf);
        if (MX_ISLNK(buf.st_mode)) {
            result = true;
            break;
        }
        path->last_del(path);
    }

    mx_path_del(&path);
    return result;
}

static char *resolve_all_links_in(char *dir) {
    char *s = realpath(dir, 0);
    return mx_strdup(s);
}

void mx_cd_do(char flag, const char *dir) {
    if (flag == '-')
        dir = mx_getenv("OLDPWD");
    else if (mx_strlen(dir) == 0)
        dir = "~";

    char *resolved_dir = mx_cd_resolve_path(dir);

    if (flag == 's') {
        if (is_path_has_symlinks(resolved_dir)) {
            mx_printerr("cd: not a directory: ");
            mx_printerr(dir);
            mx_printerr("\n");
            return;
        }
    }

    if (flag == 'P') {
        char *old_value = resolved_dir;
        resolved_dir = resolve_all_links_in(old_value);
        mx_strdel(&old_value);
    }

    chdir(resolved_dir);

    char *current_pwd = mx_getenv("PWD");
    mx_setenv("OLDPWD", current_pwd);

    mx_setenv("PWD", resolved_dir);
    mx_strdel(&resolved_dir);
}
