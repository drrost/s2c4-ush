//
// Created by Rostyslav Druzhchenko on 01.10.2020.
//

#include <algorithm.h>

t_command *mx_command_new() {
    t_command *command = (t_command *)malloc(sizeof(t_command));
    mx_memset(command, 0, sizeof(t_command));
    return command;
}
