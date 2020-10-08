//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>

void mx_env_delete() {
    t_map *env = mx_env_get();
    mx_map_delete(&env);
}
