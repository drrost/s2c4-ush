//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <ush.h>

t_map *mx_env_get() {
    static t_map *env = 0;
    if (env == 0)
        env = mx_map_build();
    return env;
}
