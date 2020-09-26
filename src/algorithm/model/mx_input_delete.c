//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

void mx_input_delete(t_input **instance) {
    mx_strdel((*instance)->command);
    free(*instance);
    *instance = 0;
}