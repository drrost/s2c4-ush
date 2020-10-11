//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>

char *mx_getenv(const char *s) {
    t_map *env = mx_env_get();
    return env->get(env, (char *)s);
}
