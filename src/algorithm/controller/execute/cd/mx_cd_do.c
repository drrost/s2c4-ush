//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>
#include <private/mx_cd_private.h>


void mx_cd_do(char flag, const char *dir) {
    flag++; // TODO: Add path handling.

    char *pwd = mx_cd_resolve_path(dir);
    mx_setenv("PWD", pwd);
    mx_strdel(&pwd);
}
