//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>
#include <ush.h>

static void update_shlvl() {
    char *shlvl_s = mx_getenv("SHLVL");
    if (shlvl_s == 0)
        shlvl_s = "0";
    int shlvl_i = atoi(shlvl_s);

    shlvl_i++;
    shlvl_s = mx_itoa(shlvl_i);
    mx_setenv("SHLVL", shlvl_s);

    mx_strdel(&shlvl_s);
}

static void force_pwd() {
    char *pwd = getcwd(NULL, MX_MAX_PATH);
    if (pwd)
        mx_setenv("PWD", pwd);
}

static void force_logname() {
    char *logname = mx_getenv("LOGNAME");
    if (logname == 0) {
        logname = getlogin();
        if (logname != 0)
            mx_setenv("LOGNAME", logname);
    }
}

static void init_env() {
    update_shlvl();
    force_pwd();
    force_logname();
}

static void init_history() {
    char *file_name = mx_history_file();
    int fd = open(file_name, O_RDONLY);
    mx_strdel(&file_name);

    if (fd != -1) {
        char *line = 0;
        while (mx_read_line(&line, 1000, '\n', fd) > 0) {
            mx_history_add_to_list(line);
            mx_strdel(&line);
            line = 0;
        }
        mx_strdel(&line);
    }

    close(fd);
}

void mx_core_init() {
    init_env();
    init_history();
}
