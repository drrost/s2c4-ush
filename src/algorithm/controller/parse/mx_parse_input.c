#include "../inc/ush.h"
#include <stdlib.h>

t_input *mx_parse_input(const char *str) {
    int i = 0;
    int start = 0;

    char **strnew = mx_strsplit(str, ';');
    t_input *inp = (t_input *)malloc(sizeof(t_input) * mx_count_words(str, ';') + 1);
    inp->commands = NULL;
    for (; strnew[i] != NULL; i++) {
        char *strend = strnew[i];
        while (1) {
            int end = mx_get_logic_operator_index(strend, '&');
            char *sub = mx_substr(strend, start, end == -1 ? mx_strlen(strend) + 1 : end);
            char *strpipe = sub;

            while (1) {
                int pipend = mx_get_logic_operator_index(strpipe, '|');
                char *subpipe = mx_substr(strpipe, start, pipend == -1 ? mx_strlen(strpipe) + 1 : pipend);

                if (pipend > 0)
                    strpipe += pipend + 2;

                t_command *command = mx_command_new();
                char *trim = mx_strtrim(subpipe);
                command->name = mx_get_command(trim);
                command->arguments = mx_get_args(trim);
                command->get_input_from_prev = get_subst(command->arguments);
                command->stop_on_fail = pipend == -1 ? true : false;
                mx_push_back(&inp->commands, command);
                free(trim);
                free(subpipe);
                if (pipend == -1)
                    break;
            }
            strend += end + 2;
            if (end == -1)
                break;
        }
    }
    return inp;
}
