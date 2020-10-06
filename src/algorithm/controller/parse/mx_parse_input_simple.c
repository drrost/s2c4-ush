//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <ush.h>

t_input *mx_parse_input_simple(const char *str) {
    t_input *input = mx_input_new();

    t_command *command = mx_command_new();
    command->name = mx_strdup(str);
    mx_push_back(&(input->commands), command);

    return input;
}
