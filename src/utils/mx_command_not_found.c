//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

void command_not_found(const char *s) {
    mx_printerr("ush: command not found: ");
    mx_printerr(s);
    mx_printerr("\n");
}
