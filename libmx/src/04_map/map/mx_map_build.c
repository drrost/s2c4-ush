//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_map.h>

t_map *mx_map_build() {
    t_map *instance = mx_map_new();

    instance->get = mx_map_get;
    instance->set = mx_map_set;
    instance->remove = mx_map_remove;

    return instance;
}
