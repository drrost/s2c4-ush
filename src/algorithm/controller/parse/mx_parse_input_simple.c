//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <ush.h>

static t_command *command_from(const char *line) {
    t_command *command = mx_command_new();
    int line_len = mx_strlen(line);
    int command_len = line_len;
    int arg_len = 0;
    char *s = 0;

    if ((s = mx_strstr(line, " ")) != 0) {
        command->arguments = mx_strdup(s + 1);
        arg_len = mx_strlen(s);
        command_len = line_len - arg_len;
    }
    else
        command->arguments = mx_strdup("");

    command->name = mx_strndup(line, command_len);

    return command;
}

t_input *mx_parse_input_simple(const char *str) {
    t_input *input = mx_input_new();

    t_command *command = command_from(str);
    mx_push_back(&(input->commands), command);

    return input;
}
