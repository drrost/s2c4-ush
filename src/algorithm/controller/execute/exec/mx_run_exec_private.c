//
// Created by Rostyslav Druzhchenko on 19.10.2020.
//

#include <ush.h>

char *mx_replace_spaces_to_magic(char *line) {
    return mx_str_replace(line, "\\ ", MX_SPACE_SUBSTITUTION);
}

static char *replace_magic_to_spaces(char *line) {
    return mx_str_replace(line, MX_SPACE_SUBSTITUTION, " ");
}

void mx_handle_spaces(char **arr) {
    int i = 0;

    while (arr[i]) {
        char *old = arr[i];
        arr[i] = replace_magic_to_spaces(arr[i]);
        mx_strdel(&old);
        i++;
    }
}
