//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

t_input *mx_parse_input(const char *input) {
    t_input *instance = mx_input_new();
    mx_strcpy(instance->command, input);
    return instance;
}
