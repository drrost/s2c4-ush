//
// Created by Rostyslav Druzhchenko on 23.10.2020.
//

#include <ush.h>

char *mx_trim_quotes(char *line) {
    int len = mx_strlen(line);
    int start = 0;
    int end = len - 1;

    if (line[start] == '\"' && line[end] == '\"')
        return mx_strndup(line + 1, len - 2);
    return mx_strdup(line);
}
