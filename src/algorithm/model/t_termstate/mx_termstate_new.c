//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <algorithm.h>

t_termstate *mx_termstate_new() {
    t_termstate *instance = (t_termstate *)malloc(sizeof(t_termstate));
    mx_memset(instance, 0, sizeof(t_termstate));
    instance->line = mx_strnew(1024);
    return instance;
}
