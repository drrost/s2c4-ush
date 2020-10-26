#include <ush.h>

static void get_command_node(t_list **chain, char *trim,
                             bool has_or, bool has_and) {
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
    }
    else {
        command->has_and = has_and;
        command->has_or = false;
    }
    if (!has_and && !has_or)
        command->is_last_in_sequesce = true;
    else
        command->is_last_in_sequesce = false;

    mx_push_front(chain, command);

    if (mx_str_has_prefix(command->arguments, "$(")) {
        int idx = mx_get_char_index(command->arguments, ')');
        if (idx != -1) {
            char *new_line = mx_strndup(command->arguments + 2, idx - 2);
            get_command_node(chain, new_line, false, false);
            t_command *prev_command = (t_command *)((*chain)->data);
            prev_command->pass_out_to_next = true;
            mx_strdel(&new_line);

            mx_strdel(&(command->arguments));
            command->arguments = mx_strdup("");
        }
    }
}

t_list *get_commands_chain(char *trim, bool has_or, bool has_and) {
    t_list *result = 0;
    get_command_node(&result, trim, has_or, has_and);
    return result;
}

void create_comm_and_arg(t_input *input, int end, char *strend, int start,
                         bool has_and) {
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
        }
        else {
            has_or = true;
            subpipe = mx_substr(strpipe, start, pipend);
        }
        char *trim = mx_strtrim(subpipe);
        mx_strdel(&(input->error_text));
        input->error_text = mx_error_pair(trim);
        t_list *commands_chain = get_commands_chain(trim, has_or, has_and);

        mx_list_attach_back(&(input->commands), commands_chain);
        mx_strdel(&trim);
        mx_strdel(&subpipe);
        if (pipend == -1)
            break;
    }
    mx_strdel(&sub);
}
