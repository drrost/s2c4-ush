//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>
#include <stdlib.h>
#include <unistd.h>

static void pwd_default(void) {
    char *pwd = mx_strdup(getenv("PWD"));

    printf("%s\n", pwd);
    mx_strdel(&pwd);
}

bool contains(char *line, char symbol) {
    if ((mx_get_char_index(line, symbol)) != -1)
        return true;
    return false;
}

static void pwd_p(void) {
    char *pwd = mx_strdup(getenv("PWD"));
    char line[4096];
    struct stat buf;

    if ((lstat(pwd, &buf)) == 0) {
        if (MX_ISLNK(buf.st_mode)) {
            char *res = realpath(pwd, line);
            if (res)
                printf("%s\n", line);
        }
        else {
            printf("%s\n", pwd);
        }
        mx_strdel(&pwd);
    }
}

static char check_pwd(char *line, bool *error) {
    char flag = 'L';
    bool start = false;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '-') {
            start = true;
            continue;
        }
        if (line[i] == 10)
            continue;
        if (line[i] != 'P' && line[i] != 'L' && start) {
            mx_printerr("ush: ");
            if (!isatty(0))
                mx_printerr("line 1: ");
            mx_printerr("pwd: -");
            write(2, &line[i], 1);
            mx_printerr(": invalid option\npwd: usage: pwd [-LP]\n");
//            mx_env_replace(&environment, "?=1");
            *error = true;
        }
        if (line[i + 1] == '\0' && !start)
            flag = 'L';
        else 
            flag = line[i];
    }
    return flag;
}

int mx_pwd(char *line) {
    char flag = 'L'; //default

    if ((line && contains(line, '-')) || (strcmp(line, "pwd") == 0)) { //TO DO: add check on "--"
        bool error = false;
        flag = check_pwd(line, &error);
        if (error)
            return 1;
    }
    else {
        mx_printerr("pwd: too many arguments\n");
        return 1;
    }
    if (flag == 'L')
        pwd_default();
    if (flag == 'P')
        pwd_p();
//    mx_env_replace(&environment, "?=0");
    return 0;
}
