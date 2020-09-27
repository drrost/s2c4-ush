//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

t_input *mx_parse_input(const char *input) {
    mx_log_d("Parsing input", input);

    t_input *instance = mx_input_new();
    instance->command = mx_strdup(input);
    return instance;
}
