#include "../inc/ush.h"
#include <stdlib.h>

static t_command *get_command_node(char *trim, int pipend) {
    t_command *command = mx_command_new();
    //system ("leaks -q ush"); TODO 6 liks
    command->name = mx_get_command(trim);
    command->arguments = mx_get_args(trim);
    command->get_input_from_prev = get_subst(command->arguments);
    if (pipend == -1) {
        command->stop_on_fail = true;
    } else {
        command->stop_on_fail = false;
    }
    return command;
}

void create_comm_and_arg(t_input *inp, int end, char *strend, int start) {
    char *sub;

    if (end == -1) {
        sub = mx_substr(strend, start, mx_strlen(strend) + 1);
    } else {
        sub = mx_substr(strend, start, end);
    }
    char *strpipe = sub;

    while (1) {
        int pipend = mx_get_logic_operator_index(strpipe, '|');
        if (pipend > 0)
            strpipe += pipend + 2;
        char *subpipe;
        if (pipend == -1) {
            subpipe = mx_substr(strpipe, start, mx_strlen(strpipe) + 1);
        } else {
            subpipe = mx_substr(strpipe, start, pipend);
        }

        char *trim = mx_strtrim(subpipe);

        mx_push_back(&inp->commands, get_command_node(trim, pipend));
        free(trim);
        free(subpipe);
        if (pipend == -1)
            break;
    }
}
