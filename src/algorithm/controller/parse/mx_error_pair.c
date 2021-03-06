#include <ush.h>

static int fiend_count(const char *str, char c) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            result++;
    }
    return result;
}

char *mx_error_pair(const char *str) {
    char *err = 0;
    if ((fiend_count(str, '"') % 2) != 0)
        err = mx_strdup(MX_DELIM_NO_PAIR);
    else if ((fiend_count(str, '`') % 2) != 0)
        err = mx_strdup(MX_DELIM_NO_PAIR2);

    else if (fiend_count(str, '(') != fiend_count(str, ')')) {
        if (fiend_count(str, '(') < fiend_count(str, ')'))
            err = mx_strdup(MX_DELIM_NO_PAIR3);
        else if (fiend_count(str, ')') < fiend_count(str, '('))
            err = mx_strdup(MX_DELIM_NO_PAIR4);
    }
    else if (fiend_count(str, '{') != fiend_count(str, '}'))
        err = mx_strdup(MX_DELIM_NO_PAIR5);

    else {

        for (int i = 0; str[i] != '\0'; i++){
            if (str[i] == '{' && str[i + 1] == '`') {
                err = mx_strdup(MX_BAD_SUBSTITUTION);
            }
        }
    }
    return err;
}


char *mx_error_pair_for_command(const char *str) {
    char *err = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '`' && str[i + 1] == '{') {
            err = mx_strdup(MX_NO_SUCH_FILE);
        }
    }
    return err;
}
