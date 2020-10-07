//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

int mx_execute(t_input *input) {
    if (!input->commands)
        return 0;

    t_command *command = (t_command *)input->commands->data;
    mx_log_t("Executing command", command->name);

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
