//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>
#include <ush.h>

static void init_env() {
    extern char **environ;
    char *s = *environ;
    int i = 1;

    for (; s; i++) {
        char **split_arr = mx_strsplit(s, '=');
        mx_setenv(split_arr[0], split_arr[1]);
        mx_del_strarr(&split_arr);
        s = *(environ + i);
    }
}

char *mx_history_file() {
    return 0;
}

static void init_history() {
    static char *history_file_name = ".ush_history";
    char *home_dir = mx_getenv("HOME");
    t_path *path = mx_path_new(home_dir);
    path->append(path, history_file_name);
    int fd = open(path->p, O_RDONLY);
    mx_path_del(&path);

    char *line = 0;
    while (mx_read_line(&line, 1000, '\n', fd) > 0) {
        mx_history_add(line);
    }
}

void mx_core_init() {
    init_env();
    init_history();
}
