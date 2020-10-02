//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <algorithm.h>

void mx_termstate_del(t_termstate **state) {
    t_termstate *instance = *state;
    mx_strdel(&(instance->line));
    free(instance);
    *state = 0;
}
