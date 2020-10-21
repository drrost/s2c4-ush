#include <ush.h>

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

static t_command *get_command_node(char *trim, bool has_or, bool has_and) {
    t_command *command = mx_command_new();
    int trim_len = mx_strlen(trim);
    int command_len = trim_len;
    int arg_len = 0;
    char *s = 0;


    if ((s = mx_strstr(trim, " ")) != 0) {
        command->arguments = mx_strdup(s + 1);
        arg_len = mx_strlen(s);
        command_len = trim_len - arg_len;
    }
    else
        command->arguments = mx_strdup("");

    command->name = mx_strndup(trim, command_len);
    command->get_input_from_prev = get_subst(command->arguments);
    if (has_or) {
        command->has_or = has_or;
        command->has_and = false;
    } else {
        command->has_and = has_and;
        command->has_or = false;
    }
    if (!has_and && !has_or) {
        command->is_last_in_sequesce = true;
    } else {
        command->is_last_in_sequesce = false;
    }
    return command;
}

void create_comm_and_arg(t_input *input, int end, char *strend, int start, bool has_and) {
    char *sub;
    bool has_or;

    if (end == -1)
        sub = mx_substr(strend, start, mx_strlen(strend) + 1);
    else
        sub = mx_substr(strend, start, end);

    char *strpipe = sub;

    while (1) {
        int pipend = mx_get_logic_operator_index(strpipe, '|');
        if (pipend > 0)
            strpipe += pipend + 2;
        char *subpipe;
        if (pipend == -1) {
            has_or = false;
            subpipe = mx_substr(strpipe, start, mx_strlen(strpipe) + 1);
        } else {
            has_or = true;
            subpipe = mx_substr(strpipe, start, pipend);
        }
        char *trim = mx_strtrim(subpipe);
        mx_strdel(&(input->error_text));
        input->error_text = mx_error_pair(trim);
        mx_push_back(&input->commands,
                     get_command_node(trim, has_or, has_and));
        mx_strdel(&trim);
        mx_strdel(&subpipe);
        if (pipend == -1)
            break;
    }
    mx_strdel(&sub);
}
