//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

int mx_execute(t_input *input, t_env *environment) {
    mx_log_t("Executing command", input->command);

    if (mx_strcmp(input->command, "exit") == 0 ||
        strstr(input->command, "exit") != 0)
        return mx_exit(input->command, environment);
    if (mx_strcmp(input->command, "pwd") == 0 ||
        strstr(input->command, "pwd") != 0)
        mx_pwd(input->command, environment);

    return MX_SHOULD_NEXT;
}
