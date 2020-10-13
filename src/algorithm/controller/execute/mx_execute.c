//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>
#include <mx_log.h>

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

int mx_run_built_in(char *command, char *arguments) {
    int exit_code = 0;

    if (mx_streq(command, "color"))
        exit_code = mx_change_color(arguments);
    else if (mx_streq(command, "export"))
        exit_code = mx_export(arguments);
    else if (mx_streq(command, "unset"))
        exit_code = mx_unset(arguments);
    else if (mx_streq(command, "exit"))
        return mx_exit(command);
    else if (mx_streq(command, "bye"))
        return mx_bye(command);
    else if (mx_streq(command, "cd"))
        exit_code = mx_cd(arguments);
    else if (mx_streq(command, "pwd"))
        exit_code = mx_pwd(arguments);
    else if (mx_streq(command, "whoami"))
        exit_code = mx_whoami(arguments);
    else if (mx_streq(command, "which"))
        exit_code = mx_which(arguments);
    else if (mx_streq(command, "echo"))
        exit_code = mx_echo(arguments, exit_code);
    else if (mx_streq(command, "true"))
        exit_code = mx_true();
    else if (mx_streq(command, "false"))
        exit_code = mx_false();
    else if (mx_streq(command, "env"))
        exit_code = mx_env(arguments);

    return MX_SHOULD_NEXT;
}

int mx_execute(t_input *input) {
    if (!input->commands)
        return 0;

    t_command *command = (t_command *)input->commands->data;
    log_command_execution(command);

    if (mx_is_built_in(command->name))
        return mx_run_built_in(command->name, command->arguments);
    else if (!mx_strlen(command->name))
        return 0;
    else
        mx_run_exec(command->name, command->arguments);

    return MX_SHOULD_NEXT;
}
