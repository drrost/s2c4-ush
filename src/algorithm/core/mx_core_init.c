//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>
#include <ush.h>

static void update_shlvl() {
    char *shlvl_s = mx_getenv("SHLVL");
    int shlvl_i = atoi(shlvl_s);

    shlvl_i++;
    shlvl_s = mx_itoa(shlvl_i);
    mx_setenv("SHLVL", shlvl_s);

    mx_strdel(&shlvl_s);
}

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

    update_shlvl();
}

static void init_history() {
    char *file_name = mx_history_file();
    int fd = open(file_name, O_RDONLY);
    mx_strdel(&file_name);

    char *line = 0;
    while (mx_read_line(&line, 1000, '\n', fd) > 0) {
        mx_history_add_to_list(line);
        line = 0;
    }

    mx_strdel(&line);
    close(fd);
}

void mx_core_init() {
    init_env();
    init_history();
}
