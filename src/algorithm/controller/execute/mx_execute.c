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

    if (command->name[0] == '/') {
        char *s = mx_strjoin(" ", command->arguments);
        char *s2 = mx_strjoin(command->name, s);
        system(s2);
        mx_strdel(&s);
        mx_strdel(&s2);
    }

    else if (mx_streq(command->name, "color"))
        command->exit_code = mx_change_color(command->arguments);

    else if (mx_streq(command->name, "exit"))
        return mx_exit(command->name);

    else if (mx_streq(command->name, "pwd"))
        command->exit_code = mx_pwd(command->arguments);

    else if (mx_streq(command->name, "which"))
        command->exit_code = mx_which(command->arguments);

    else if (mx_streq(command->name, "echo"))
        command->exit_code = mx_echo(command->arguments, command->exit_code);

    else if (mx_streq(command->name, "true")) {
        command->exit_code = mx_true();
    }

    else if (mx_streq(command->name, "false"))
        command->exit_code = mx_false();

    else if (mx_streq(command->name, "clear"))
        system("clear");

    else if (mx_streq(command->name, "env"))
        mx_env("");
    else
        command->exit_code = command_not_found(command->name);

    return MX_SHOULD_NEXT;
}
