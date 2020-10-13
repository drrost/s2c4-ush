//
// Created by Karina Barinova on 12.10.2020.
//

#include <ush.h>

char *mx_checkflags_echo(char **arr, int *counter) {
    char *flags = mx_strnew(2);

    flags[0] = '0';
    flags[1] = 'e';
    for (int i = 0; arr[i]; i++) {
        if (arr[i][0] != '-')
            return flags;
        for (int j = 1; arr[i][j] != '\0'; j++)
            if (arr[i][j] != 'n' && arr[i][j] != 'e' && arr[i][j] != 'E')
                return flags;
            *counter = i;
            for (int j = 1; arr[i][j]; j++) {
                if (arr[i][j] == 'n')
                    flags[0] = 'n';
                else
                    flags[1] = arr[i][j] == 'e' ? 'e' : 'E';
            }
    }
    return flags;
}

int mx_print_echo_d(char *str, int *i) {
    if (str[0] == '\\' && str[1] == 'a' && ++(*i) > 0)
        return '\a';
    else if (str[0] == '\\' && str[1] == 'b' && ++(*i) > 0)
        return '\b';
    else if (str[0] == '\\' && str[1] == 't' && ++(*i) > 0)
        return '\t';
    else if (str[0] == '\\' && str[1] == 'n' && ++(*i) > 0)
        return '\n';
    else if (str[0] == '\\' && str[1] == 'v' && ++(*i) > 0)
        return '\v';
    else if (str[0] == '\\' && str[1] == 'f' && ++(*i) > 0)
        return '\f';
    else if (str[0] == '\\' && str[1] == 'r' && ++(*i) > 0)
        return '\r';
    else if (str[0] == '\\' && str[1] == 'e' && ++(*i) > 0)
        return '\033';
    return -1;
}



