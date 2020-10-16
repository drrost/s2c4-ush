#include <ush.h>

t_input *mx_parse_input(const char *str) {
    int i = 0;
    int start = 0;

    char **strnew = mx_strsplit(str, ';');
    t_input *input = mx_input_new();
    for (; strnew[i] != NULL; i++) {
        char *strend = strnew[i];
        while (1) {
            int end = mx_get_logic_operator_index(strend, '&');
            create_comm_and_arg(input, end, strend, start);
            strend += end + 2;
            if (end == -1)
                break;
        }
    }
    mx_del_strarr(&strnew);

    return input;
}
