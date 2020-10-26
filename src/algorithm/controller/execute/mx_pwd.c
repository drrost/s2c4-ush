//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>

static void pwd_default(void) {
    char *env_pwd = mx_getenv("PWD");
    char *pwd = mx_strdup(env_pwd);

    mx_printline(pwd);
    mx_strdel(&pwd);
}

bool contains(char *line, char symbol) {
    if ((mx_get_char_index(line, symbol)) != -1)
        return true;
    return false;
}

static void pwd_p(void) {
    char *cur = getcwd(NULL, 1024);
    char *read_link = realpath(cur, NULL);
    mx_printline(read_link);
}

static char check_pwd(char *line, bool *error) {
    char flag = 'L';

    for (int i = 0; line[i]; i++) {
        if (line[i] == '-') {
            continue;
        }
        if (line[i] != 'P' && line[i] != 'L') {
            if (!isatty(0))
                mx_printerr("line 1: ");
            mx_printerr("pwd: bad option: -");
            mx_printerr_char(line[i]);
            mx_printerr("\n");
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

        if ((arr[0] && contains(arr[0], '-'))) { //TO DO: add check on "--"
            bool error = false;
            flag = check_pwd(line, &error);
            if (error) {
                mx_del_strarr(&arr);
                return 1;
            }
        }
        else {
            mx_printerr("pwd: too many arguments\n");
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
