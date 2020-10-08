//
// Created by Rostyslav Druzhchenko on 08.10.2020.
//

#include <libmx.h>

void mx_pant_del(t_path **path) {
    mx_strdel(&((*path)->p));
    free(*path);
    *path = 0;
}
