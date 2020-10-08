//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>
#include <libmx.h>

void mx_core_init() {
    extern char **environ;
    char *s = *environ;
    int i = 1;

    for (; s; i++) {
        char **split_arr = mx_strsplit(s, '=');
        mx_setenv(split_arr[0], split_arr[1]);
        mx_del_strarr(&split_arr);
        s = *(environ + i);
    }
}
