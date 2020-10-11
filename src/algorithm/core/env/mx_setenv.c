//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>

void mx_setenv(const char *key, const char *value) {
    t_map *env = mx_env_get();
    env->set(env, (char *)key, (char *)value);
}
