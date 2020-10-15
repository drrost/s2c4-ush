#include "../inc/ush.h"

// static char *remove_sym_from_arg(const char *str) {
//     char *arg = mx_strdup(str);

//     for (int i = 0, j; arg[i] != '\0'; i++) {
//         while (arg[i] == '22') {
//             for (j = i; arg[j]; ++j)
//                 arg[j] = arg[j + 1];
//             arg[j] = '\0';
//         }
//     }
//     return arg;
// }

static t_command *get_command_node(char *trim, int pipend) {
    t_command *command = mx_command_new();
    int trim_len = mx_strlen(trim);
    int command_len = trim_len;
    int arg_len = 0;
    char *s = 0;
    // command->name = mx_get_command(trim);
    // command->name = mx_strdup(mx_strtrim(command->name));
    //char *arg = mx_get_args(trim);

        if ((s = mx_strstr(trim, " ")) != 0) {
            command->arguments = mx_strdup(s + 1);
            arg_len = mx_strlen(s);
            command_len = trim_len - arg_len;
        }
        else
            command->arguments = mx_strdup("");

        command->name = mx_strndup(trim, command_len);
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
        inp->error_text = mx_error_pair(trim);
        mx_push_back(&inp->commands, get_command_node(trim, pipend));
        mx_strdel(&trim);
        mx_strdel(&subpipe);
        if (pipend == -1)
            break;
    }
}
