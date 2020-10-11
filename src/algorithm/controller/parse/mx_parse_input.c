#include "../inc/ush.h"
#include <stdlib.h>

t_input *mx_parse_input(const char *str) {
    int i = 0;
    int start = 0;

    char **strnew = mx_strsplit(str, ';');
    t_input *inp = (t_input *) malloc(sizeof(t_input) * mx_count_words(str, ';') + 1);
    inp->commands = NULL;
    for (; strnew[i] != NULL; i++) {
        char *strend = strnew[i];
        while (1) {
            int end = mx_get_logic_operator_index(strend, '&');
            create_comm_and_arg(inp, end, strend, start);
            strend += end + 2;
            if (end == -1)
                break;
        }
    }
    return inp;
}
