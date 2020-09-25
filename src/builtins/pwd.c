//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void pwd_default(void) {
    char *pwd = mx_strdup(getenv("PWD"));

    mx_printstr(pwd);
    mx_printstr("\n");
    mx_strdel(&pwd);
}

bool contains(char *line, char symbol) {
	if ((mx_get_char_index(line, symbol)) != -1)
		return true;
	return false;
}

static void pwd_p(void) {
    char *pwd = mx_strdup(getenv("PWD"));
    char line[1024];
    struct stat buf;

    if (!lstat(line, &buf)) {
        if (MX_ISLNK(buf.st_mode)) {
            char *res = realpath(pwd, line);
            if (res) {
                mx_printstr(line);
                mx_printstr("\n");
            }
        }
        else {
            mx_printstr(pwd);
            mx_printstr("\n");
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
        if (line[i] != 'P' && line[i] != 'L' && start) {
            mx_printerr("ush: ");
            if (!isatty(0))
                mx_printerr("line 1: ");
            mx_printerr("pwd: -");
            write(2, &line[i], 1);
            mx_printerr(": invalid option\npwd: usage: pwd [-LP]\n");
            *error = true;
        }
        flag = line[i];
    }
    return flag;
}

void mx_pwd(char *line) {
    char flag = 'L'; //default
    
    if (line && contains(line, '-')) { //TO DO: add check on "--"
        bool error = false;
        flag = check_pwd(line, &error);
        if (error)
            return;
    }
    if (flag == 'L')
        pwd_default();
    if (flag == 'P')
        pwd_p();
    return;
}
