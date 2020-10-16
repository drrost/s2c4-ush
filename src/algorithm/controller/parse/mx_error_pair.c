#include <ush.h>

static int fiend_count(char *str, char c) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            result++;
    }
    return result;
}

char *mx_error_pair(char *str) {
    //t_input *err = mx_input_new();
    char *err = 0;

    if ((fiend_count(str, '"') % 2) != 0) {
        err = mx_strdup(MX_DELIM_NO_PAIR);

    }
    else if ((fiend_count(str, '`') % 2) != 0) {
        err = mx_strdup(MX_DELIM_NO_PAIR2);

    }
    if (fiend_count(str, '(') != fiend_count(str, ')')) {
        if (fiend_count(str, '(') < fiend_count(str, ')')) {
            err = mx_strdup(MX_DELIM_NO_PAIR3);
        }
        else if (fiend_count(str, ')') < fiend_count(str, '(')) {
            err = mx_strdup(MX_DELIM_NO_PAIR4);
        }
    }
    if (fiend_count(str, '{') != fiend_count(str, '}')) {
        err = mx_strdup(MX_DELIM_NO_PAIR5);
    }

    return err;
}
