//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#include <private/mx_cd_private.h>
#include <ush.h>

int mx_cd(const char *line) {
    char flag = 0;
    char *dir = 0;
    int exit_code = 0;

    mx_cd_parse_arguments(line, &flag, &dir);
    exit_code = mx_cd_validate_input(flag, dir);

    if (exit_code != 0) {
    	mx_strdel(&dir);
	    return exit_code;
    }

    exit_code = mx_cd_do(flag, dir);

    mx_strdel(&dir);
    return exit_code;
}
