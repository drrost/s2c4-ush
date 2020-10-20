//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>

static void pwd_default(void) {
    char *pwd = mx_strdup(mx_getenv("PWD"));

    mx_printline(pwd);
    mx_strdel(&pwd);
}

bool contains(char *line, char symbol) {
    if ((mx_get_char_index(line, symbol)) != -1)
        return true;
    return false;
}

static void pwd_p(void) {
    char *pwd = mx_strdup(mx_getenv("PWD"));
    char *cur = getcwd(NULL, 256);
    char *read_link = realpath(pwd, NULL);

    if (read_link && mx_strcmp(cur, read_link) == 0){
        mx_printline(pwd);
    }
    else {
        mx_printline(cur);
    }
    mx_strdel(&pwd);
}

static char check_pwd(char *line, bool *error) {
    char flag = 'L';

    for (int i = 0; line[i]; i++) {
        if (line[i] == '-') {
            continue;
        }
        if (line[i] != 'P' && line[i] != 'L') {
            mx_printerr("ush: ");
            if (!isatty(0))
                mx_printerr("line 1: ");
            mx_printerr("pwd: -");
            mx_printerr_char(line[i]);
            mx_printerr(": invalid option\npwd: usage: pwd [-LP]\n");
            *error = true;
            break;
        }
        if (line[i] == 'P')
            flag = 'P';
        else
            flag = line[i];
    }
    return flag;
}

int mx_pwd(char *line) {
    char flag = 'L';
    if (mx_strlen(line) > 0) {
        char **arr = mx_strsplit(line, ' ');

        if ((arr[0] && !arr[1] &&
             contains(arr[0], '-'))) { //TO DO: add check on "--"
            bool error = false;
            flag = check_pwd(line, &error);
            if (error) {
                mx_del_strarr(&arr);
                return 1;
            }
        }
        else {
            mx_printerr("ush: pwd: too many arguments\n");
            mx_del_strarr(&arr);
            return 1;
        }
        if (flag == 'L')
            pwd_default();
        if (flag == 'P')
            pwd_p();
        mx_del_strarr(&arr);
        return 0;
    }
    else {
        pwd_default();
        return 0;
    }
}
