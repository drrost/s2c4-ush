//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#include <private/mx_cd_private.h>
#include <ush.h>

int mx_cd(const char *line) {
    char flag = 0;
    char *dir = 0;

    mx_cd_parse_arguments(line, &flag, &dir);
    mx_cd_validate_input(flag, dir);

    mx_cd_do(flag, dir);

    mx_strdel(&dir);
    return 0;
}