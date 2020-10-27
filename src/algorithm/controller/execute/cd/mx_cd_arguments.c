//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>
#include <private/mx_cd_private.h>
#include <mx_log.h>

void mx_cd_parse_arguments(const char *line, char *flag, char **dir) {
    char **arr = mx_split_array_of_a_command((char *)line);
    int size = mx_arr_size(arr);
    const char *home_dir = mx_get_home_dir();

    if (size > 0 && arr[0][0] == '-')
        *flag = mx_strlen(arr[0]) == 1 ? '-' : arr[0][1];

    if (size == 0)
        *dir = mx_strdup(home_dir);
    else if (size == 1)
        *dir = arr[0][0] == '-' ? mx_strdup(home_dir) : mx_strdup(arr[0]);
    else // size == 2
        *dir = mx_strdup(arr[1]);

    mx_del_strarr(&arr);
}
