//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

static void log_command_execution(t_command *command) {
    char *s = 0;

    mx_str_append(&s, "name: \"");
    mx_str_append(&s, command->name);
    mx_str_append(&s, "\"");
    if (mx_strlen(command->arguments)) {
        mx_str_append(&s, ", arguments: \"");
        mx_str_append(&s, command->arguments);
        mx_str_append(&s, "\"");
    }

    mx_log_d("Executing command", s);
    mx_strdel(&s);
}

int mx_execute(t_input *input) {
    if (!input->commands)
        return 0;

    t_command *command = (t_command *)input->commands->data;
    log_command_execution(command);

    if (mx_strcmp(command->name, "exit") == 0 ||
        strstr(command->name, "exit") != 0)
        return mx_exit(command->name);

    if (mx_strcmp(command->name, "pwd") == 0 ||
        strstr(command->name, "pwd") != 0)
        command->exit_code = mx_pwd(command->name);

    if (mx_streq(command->name, "env"))
        mx_env("");

    return MX_SHOULD_NEXT;
}
