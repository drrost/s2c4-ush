//
// Created by Rostyslav Druzhchenko on 01.10.2020.
//

#include <algorithm.h>

void mx_command_delete(t_command **command) {
    t_command *instance = *command;
    mx_strdel(&(instance->name));
    mx_strdel(&(instance->arguments));
    mx_strdel(&(instance->output));
    mx_strdel(&(instance->error_text));
    free(*command);
    *command = 0;
}
