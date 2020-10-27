//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <ush.h>

static void force_init_home() {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL)
        return;

    mx_setenv("HOME", pw->pw_dir);
}

char *mx_history_file() {
    static char *history_file_name = ".ush_history";
    char *home_dir = mx_getenv("HOME");

    if (home_dir == 0) {
        force_init_home();
        home_dir = mx_getenv("HOME");
    }

    t_path *path = mx_path_new(home_dir);
    path->append(path, history_file_name);

    char *result = mx_strdup(path->p);
    mx_path_del(&path);
    return result;
}
