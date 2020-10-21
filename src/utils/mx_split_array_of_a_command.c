//
// Created by Rostyslav Druzhchenko on 20.10.2020.
//

#include <ush.h>
#include <private/mx_run_exec_private.h>

// TODO: Delete
//
char **mx_split_array_of_a_command(char *line) {
    char *s = mx_replace_spaces_to_magic(line);

    char **arr = mx_strsplit(s, ' ');
    mx_strdel(&s);

    mx_handle_spaces(arr);

    return arr;
}
