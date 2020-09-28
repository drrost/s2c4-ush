//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

int mx_execute(t_input *input) {
    mx_log_t("Executing command", input->command);

    if (mx_strcmp(input->command, "exit") == 0 || strstr(input->command, "pwd") != 0)
        mx_exit(input->command);
    if (mx_strcmp(input->command, "pwd") == 0 || strstr(input->command, "pwd") != 0)
        mx_pwd(input->command);
    return MX_SHOULD_NEXT;
}
