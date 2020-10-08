//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>


int echo_flag(char *str, int *n) {
    int flag = 1;

    for (int i = 1; i < mx_strlen(str); i++) {
        if (str[i] == 'e' && flag != 2)
            flag = 1;
        else if (str[i] == 'E' || str[i] == 'e')
            flag = 2;
        else if (str[i] == 'n')
            *n = 1;
        else {
            flag = -1;
            break;
        }
    }
    return flag;
}

char *clear_str_of_symbols(const char *line) {
    char *str = mx_strdup(line);

    for ( int i = 0, j; str[i]; ++i) {
        while (!(mx_isalpha(str[i])) && !(str[i] == '\0')) {
            for (j = i; str[j]; ++j)
                str[j] = str[j + 1];
            str[j] = '\0';
        }
    }
    return str;
}
