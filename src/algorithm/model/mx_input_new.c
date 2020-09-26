//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

t_input *mx_input_new() {
    t_input *instance = (t_input *)malloc(sizeof(t_input));
    mx_memset(instance, 0, sizeof(t_input));
    return instance;
}
