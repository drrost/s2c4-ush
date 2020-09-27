//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

int mx_execute(t_input *input) {
    if (mx_strcmp(input->command, "exit"))
        return MX_SHOULD_EXIT;
    if (mx_strcmp(input->command, "pwd"))
        mx_pwd("");
    return MX_SHOULD_NEXT;
}
