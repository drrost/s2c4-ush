//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#include <ush.h>

static int handle_input(const char *line) {
    // cd Makefile cd: not a directory: Makefile
    // cd ddd - > cd: no such file or directory: ddd
    // cd . . -> cd: string not in pwd: .
    // cd /.fseventsd -> cd: permission denied: /.fseventsd

    int exit_code = 0;
    t_path *path = mx_path_new(line);

    if (path->exists(path) == false) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path->p);
        mx_printerr("\n");
        exit_code = 1;
    }

    mx_path_del(&path);
    return exit_code;
}

int mx_cd(const char *line) {
    handle_input(line);

    return 0;
}
