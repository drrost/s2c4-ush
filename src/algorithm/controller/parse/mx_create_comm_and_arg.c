#include <ush.h>
#include <private/mx_parse_private.h>

t_list *get_commands_chain(char *trim, bool has_or, bool has_and) {
    t_list *result = 0;
    mx_get_command_node(&result, trim, has_or, has_and);
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
