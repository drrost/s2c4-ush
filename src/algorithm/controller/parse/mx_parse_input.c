#include <ush.h>

t_input *mx_parse_input(const char *str) {
    t_input *input = mx_input_new();
    int i = 0;
    int start = 0;
    bool has_and;
    char *err = mx_error_pair(str);
    if(err)
        input->error_text = err;

    char **strnew = mx_strsplit(str, ';');

    for (; strnew[i] != NULL; i++) {
        char *strend = strnew[i];
        while (1) {
            int end = mx_get_logic_operator_index(strend, '&');
            has_and = end != -1;
            create_comm_and_arg(input, end, strend, start, has_and);
            strend += end + 2;
            if (end == -1)
                break;
        }
    }
    mx_del_strarr(&strnew);

    return input;
}
