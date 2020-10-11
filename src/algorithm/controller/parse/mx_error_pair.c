#include "../inc/ush.h"

static int fiend_count(char *str, char c) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            result++;
    }
    return result;
}

void mx_error_pair(char *str) {
    if ((fiend_count(str, '"') % 2) != 0) {
        mx_printerr(MX_DELIM_NO_PAIR);
        mx_printerr("\n");
        exit(-1);
    } else if ((fiend_count(str, '`') % 2) != 0) {
        mx_printerr(MX_DELIM_NO_PAIR2);
        mx_printerr("\n");
        exit(-1);
    }
    if (fiend_count(str, '(') != fiend_count(str, ')')) {
        if (fiend_count(str, '(') < fiend_count(str, ')')) {
            mx_printerr(MX_DELIM_NO_PAIR3);
            mx_printerr("\n");
            exit(-1);
        } else if (fiend_count(str, ')') < fiend_count(str, '(')) {
            mx_printerr(MX_DELIM_NO_PAIR4);
            mx_printerr("\n");
            exit(-1);
        }
    }
}
