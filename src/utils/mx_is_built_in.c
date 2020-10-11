//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>

bool mx_is_built_in(char *str) {
    if (!mx_strcmp(str, "pwd"))
        return 1;
    else if (!mx_strcmp(str, "unset"))
        return 1;
    else if (!mx_strcmp(str, "exit"))
        return 1;
    else if (!mx_strcmp(str, "env"))
        return 1;
    else if (!mx_strcmp(str, "false"))
        return 1;
    else if (!mx_strcmp(str, "true"))
        return 1;
    else if (!mx_strcmp(str, "which"))
        return 1;
    else if (!mx_strcmp(str, "echo"))
        return 1;
    else
        return 0;
}
